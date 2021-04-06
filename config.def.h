/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const int gappx              = 15;        /* gaps between windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "JoyPixels:size=12:antialias=true:autohint=true", "Symbols Nerd Font:size=15:style=bold:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";
static const char normbgcolor[]     = "#222222"; /* main bar color */
static const char normbordercolor[] = "#444444"; /* border color unfocused windows */
static const char normfgcolor[]     = "#bbbbbb"; /* tag unselected and main foreground */
static const char titlefg[]         = "#458588"; /* title foreground color */
static const char selfgcolor[]      = "#1d2021"; /* tag selected and title foreground */
static const char selbordercolor[]  = "#770000"; /* border color focused windows and tags */
static char selbgcolor[]            = "#d79921"; /* tag selected and title background */
static const char *colors[][3]      = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
  [SchemeTitle] = { titlefg, selfgcolor,  selfgcolor  },
};

/* tagging */
/*static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
/*static const char *tags[] = { "1:home", "2:web", "3:chat", "4:games", "5:dev" }; */
static const char *tags[] = { "1:", "2:", "3:", "4:", "5:" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class            instance    title                      tags mask     iscentered   isfloating   monitor */
  { "Gimp",           NULL,       NULL,                      1 << 4,       0,           0,           -1 },
  { "firefox",        NULL,       NULL,                      1 << 1,       0,           0,           -1 },
  { "qutebrowser",    NULL,       NULL,                      1 << 1,       0,           0,           -1 },
  { "Gcr-prompter",   NULL,       NULL,                      0,            1,           1,           -1 },
  { "mpv",            NULL,       NULL,                      0,            1,           1,           -1 },
  { "Signal",         NULL,       NULL,                      1 << 2,       0,           0,           -1 },
  { "discord",        NULL,       "Discord",                 1 << 4,       1,           1,           -1 },
  { "Steam",          NULL,       "Steam",                   1 << 4,       1,           1,           -1 },
  { "dota2",          NULL,       NULL,                      1 << 3,       0,           0,           -1 },
  { "RimWorldLinux",  NULL,       NULL,                      1 << 3,       0,           0,           -1 },
  { "Zenity",         NULL,       NULL,                      1 << 4,       1,           1,           -1 },
  { "steam_proton",   NULL,       NULL,                      1 << 4,       1,           1,           -1 },
  { NULL,             NULL,       "Friends List",            1 << 4,       1,           1,           -1 },
  { NULL,             NULL,       "Wine System Tray",        1 << 4,       0,           1,           -1 },
  { NULL,             NULL,       "Rockstar Games Launcher", 1 << 4,       1,           1,           -1 },
  { NULL,             NULL,       "Grand Theft Auto V",      1 << 3,       0,           0,           -1 },
  { NULL,             NULL,       "tremc",                   1 << 4,       0,           0,           -1 },
  { NULL,             NULL,       "pulsemixer",              0,            1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },                    /* 00 first entry is default */

  { "[@]",      spiral },                  /* 01 ru_gaps compatible fibonacci spiral */
  { "[\\]",     dwindle },                 /* 02 ru_gaps compatible decreasing in size right and leftward */

  { "|M|",      centeredmaster },          /* 03 ru_gaps compatible centeredmaster */
  { ">M>",      centeredfloatingmaster },  /* 04 ru_gaps compatible */

  { "><>",      NULL },                    /* 05 no layout function means floating behavior */
  { "[M]",      monocle },                 /* 06 all windows on top of eachother */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/*static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { ALTKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { ALTKEY,                       XK_comma,  incnmaster,     {.i = +1 } },
  { ALTKEY,                       XK_period, incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_j,      zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
  { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} }, /* fibonacci spiral */
  { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[2]} }, /* fibonacci dwindle */
  { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} }, /* centered master */
  { MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[4]} }, /* centered floating master */
  { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[5]} }, /* floating */
  { MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[6]} }, /* monocle */
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,             XK_t,      togglefloating, {0} },
  { MODKEY,                       XK_f,      togglefullscr,  {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
/*{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
  { ALTKEY,                       XK_Tab,    focusmon,       {.i = +1 } },
  { ALTKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
  { ALTKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
  { ALTKEY,                       XK_minus,  setgaps,        {.i = -5 } },
  { ALTKEY,                       XK_equal,  setgaps,        {.i = +5 } },
  { ALTKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
/*TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  TAGKEYS(                        XK_9,                      8) */
  { MODKEY|ShiftMask,             XK_r,      quit,           {0} },
  { MODKEY,                       XK_x,      spawn,          SHCMD("prompt \"Shutdown?\" \"systemctl poweroff\"") },
  { MODKEY,                       XK_r,      spawn,          SHCMD("prompt \"Reboot?\" \"systemctl reboot\"") },
  { MODKEY,                       XK_Escape, spawn,          SHCMD("prompt \"Kill Xorg?\" \"killall Xorg\"") },
  { MODKEY,                       XK_Delete, spawn,          SHCMD("varecord kill") },
  { ALTKEY,                       XK_Delete, spawn,          SHCMD("camtog kill") },
  { MODKEY,                       XK_F5,     spawn,          SHCMD("varecord") },
  { MODKEY,                       XK_F6,     spawn,          SHCMD("camtog") },
  { MODKEY,                       XK_F7,     spawn,          SHCMD("cluttertog") },
  { MODKEY,                       XK_F8,     spawn,          SHCMD("st -e pulsemixer)") },
  { MODKEY,                       XK_F9,     spawn,          SHCMD("mnt") },
  { MODKEY,                       XK_F10,    spawn,          SHCMD("umnt") },
  { MODKEY,                       XK_F11,    spawn,          SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
  { MODKEY,                       XK_F12,    spawn,          SHCMD("st -e tremc") },
  { MODKEY,                       XK_Insert, spawn,          SHCMD("showclip") },
  { MODKEY,                       XK_grave,  spawn,          SHCMD("emojis") },
  { MODKEY,                       XK_b,      spawn,          SHCMD("$BROWSER") },
  { MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("signal-desktop") },
  { MODKEY,                       XK_g,      spawn,          SHCMD("st -e htop") },
  { MODKEY,                       XK_e,      spawn,          SHCMD("st -e nnnrun") },
  { MODKEY,                       XK_n,      spawn,          SHCMD("st -e newsboat") },
  { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("st -e bc -ql") },
  { MODKEY,                       XK_p,      spawn,          SHCMD("mpc toggle") },
  { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("mpc pause ; pauseallmpv") },
  { MODKEY,                       XK_m,      spawn,          SHCMD("st -e ncmpcpp") },
  { MODKEY,                       XK_equal,  spawn,          SHCMD("pamixer --allow-boost -i 5; pulsevol") },
  { MODKEY,                       XK_minus,  spawn,          SHCMD("pamixer --allow-boost -d 5; pulsevol") },
  { MODKEY,                       XK_comma,  spawn,          SHCMD("mpc prev") },
  { MODKEY,                       XK_period, spawn,          SHCMD("mpc next") },
  { MODKEY|ShiftMask,             XK_comma,  spawn,          SHCMD("mpc seek -10") },
  { MODKEY|ShiftMask,             XK_period, spawn,          SHCMD("mpc seek +10") },
  { MODKEY,                       XK_Print,  spawn,          SHCMD("screenshot") },
  { MODKEY|ShiftMask,             XK_Print,  spawn,          SHCMD("keyshot") },
  { MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("manterm") },
  { MODKEY,                       XK_z,      spawn,          SHCMD("manzathura") },
  { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("notes") },
  { MODKEY|ShiftMask,             XK_slash,  spawn,          SHCMD("cheatx") },
  { MODKEY,                       XK_s,      spawn,          SHCMD("searchplaylist") },
  { MODKEY,                       XK_w,      spawn,          SHCMD("searchweb") },

  { 0,                            XK_Print,  spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
  { 0,   XF86XK_AudioRaiseVolume,            spawn,          SHCMD("pamixer --allow-boost -i 5; pulsevol") },
  { 0,   XF86XK_AudioLowerVolume,            spawn,          SHCMD("pamixer --allow-boost -d 5; pulsevol") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


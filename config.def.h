/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */

/* Gapit oli 10 */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 14;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 18;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 18;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=15" };
static const char dmenufont[]       = "Iosevka Term Extended:size=16";
/*static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#06b0ac";
static const char col_urgborder[]   = "#ff0000";
static const char *colors[][3]      = {*/
	/*               fg         bg         border   */
/*	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
};*/

#include "/home/jere/.cache/wal/colors-wal-dwm.h"

/* tagging */
/*static const char *tags[] = { "", "", "", "", "", }; */
static const char *tags[] = { "www", "cli", "moc", "dc", "vidya", "p2p", };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Ranger",  NULL,     NULL,           0,	  0,          0,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ "Steam",   NULL,     NULL,           0,         1,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/*Pywal color jutut*/
static const char *dmenucmd[] = { "rofi", "-font", "hack 13", "-show", "drun", };

/* terminal */
static const char *termcmd[] = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* cmd stuff */
	{ MODKEY,            		XK_Return, spawn,          {.v = termcmd } },		
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },

	/* Software launching etc */
	{ MODKEY,			XK_Home,   spawn,          SHCMD("qbittorrent") },
	{ MODKEY,			XK_f,      spawn,          SHCMD("firefox") }, 
	{ MODKEY,			XK_s,	   spawn,	   SHCMD("alacritty -e mocp") },
	{ MODKEY,			XK_n,	   spawn,	   SHCMD("alacritty -e newsboat") },
	{ MODKEY,			XK_m,	   spawn,	   SHCMD("alacritty -e pulsemixer") },
        { 0,                            XK_Print,  spawn,          SHCMD("screenshot.sh") },
	{ MODKEY,			XK_Insert, spawn,	   SHCMD("pkill slstatus && slstatus &") },
	{ MODKEY,			XK_d,	   spawn,	   SHCMD("Discord") },

	/* Scripts */
	{ MODKEY,			XK_Pause,  spawn,	   SHCMD("/home/jere/.local/bin/dmenu/dmenuvpn") },
	{ MODKEY,			XK_Delete, spawn,	   SHCMD("/home/jere/.local/bin/dmenu/dmenupower") },
	{ MODKEY,			XK_End,    spawn,          SHCMD("/home/jere/.local/bin/dmenu/dmenubm") },
	
	/* Media keys */
	{ 0, XF86XK_AudioMute,		spawn, SHCMD("amixer sset Master toggle") },
	{ 0, XF86XK_AudioLowerVolume,	spawn, SHCMD("amixer sset Master 5%-")},
	{ 0, XF86XK_AudioRaiseVolume,	spawn, SHCMD("amixer sset Master 5%+") },
	{ 0, XF86XK_AudioPlay,		spawn, SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioPrev,		spawn, SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext, 		spawn, SHCMD("playerctl next") },

	/* Media control MPD */
	{ 0, XF86XK_AudioPlay,		spawn, SHCMD("mpc toggle") },
	{ 0, XF86XK_AudioPrev,		spawn, SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,		spawn, SHCMD("mpc next") },

	/* Laptop brightness */
	{ 0, XF86XK_MonBrightnessDown,  spawn, SHCMD("xbacklight -dec 20") },
	{ 0, XF86XK_MonBrightnessUp,	spawn, SHCMD("xbacklight -inc 20") },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } }, 
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	// Gaps
	{ MODKEY,                       XK_x,      incrgaps,       {.i = +5 } },
	{ MODKEY,                       XK_z,      incrgaps,       {.i = -5 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_c,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
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


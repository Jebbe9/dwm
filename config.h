/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 30;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 30;       /* vert inner gap between windows */
static const unsigned int gappoh    = 30;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 30;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 30;        /* 0 means no bar */
static const int topbar             = 30;        /* 0 means bottom bar */
static const char *fonts[]          = { "iosevka:size=14" };
static const char dmenufont[]       = "iosevka:size=14";

static const char col_grayD1[]       = "#222222";
static const char col_grayD2[]       = "#444444";
static const char col_grayB1[]       = "#bbbbbb";
static const char col_grayB2[]       = "#eeeeee";


static const char col_yellow[]	    = "#eddc23";
static const char col_redD1[]	    = "#c1132d";
static const char col_redD2[]	    = "#af5273";
static const char col_purple[]	    = "#493d82";
static const char col_blueD[]	    = "#0c399b";
static const char col_blueB[]	    = "#2eaadb";
static const char col_greenB1[]	    = "#23d317";
static const char col_greenB2[]      = "#54d8b7";
static const char col_orange[]      = "#F47D03";
static const char col_black[]       = "#000000";
static const char col_white[]	    = "#fcfcfc";
static const char col_pinkD[]	    = "#c68baa";


// Pinkki & valkoinen
//static const char *colors[][3]      = {
	///*              fg (text)  bg (behind text)  border   */
	//[SchemeNorm] = { col_grayD2, col_white, col_black }, // Not selected
	//[SchemeSel]  = { col_black, col_pinkD,  col_pinkD  }, // Selected
//}; 

// Purppura & musta
static const char *colors[][3]      = {
	/*              fg (text)  bg (behind text)  border   */
	[SchemeNorm] = { col_grayB1, col_grayD1, col_black }, // Not selected
	[SchemeSel]  = { col_grayB2, col_purple,  col_purple  }, // Selected
};


/* tagging */
//static const char *tags[] = { "", "", "", "", "" }; 
static const char *tags[] = { "I", "II", "III", "IV", "V" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title      tags mask      isfloating      isterminal      noswallow   monitor */
	{ "Gimp",     NULL,         NULL,       0,            1,              0,              0,                -1 },
	{ "Firefox",  NULL,         NULL,       1 << 8,       0,              0,              0,                -1 },
	{ "pavucontrol", NULL,      NULL,       0,            1,              0,              0,                -1 },
	{ "nvidia-settings", NULL,  NULL,       0,            1,              0,              0,                -1 },
	{ "Steam", NULL, NULL,		        0,            1,              0,              0,                -1 },
	{ "battle.net.exe", NULL, NULL,		0,	      1,              0,              0,                -1 },
	{ "St", NULL, NULL,			0,	      0,              1,              0,                -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

#include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_grayD1, "-nf", col_grayB1, "-sb", col_purple, "-sf", col_grayB2, NULL };

/* terminal */
static const char *termcmd[]  = { "st", NULL };

/* other apps*/
static const char *firefoxcmd[] = { "firefox", NULL };
static const char *discordcmd[] = { "discord", NULL };
static const char *spotifycmd[] = { "spotify", NULL };
static const char *screenshotcmd[] = { "scrot", "gui", NULL };

/* media */
static const char *mutecmd[]  = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[]  = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[]  = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *playerctltoggle[] = { "playerctl", "play-pause", NULL };
static const char *playerctlnextcmd[] = { "playerctl", "next", NULL };
static const char *playerctlprevcmd[] = { "playerctl", "previous", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_d,      spawn,          {.v = discordcmd } },
	{ MODKEY|ShiftMask,		XK_s,      spawn,          {.v = spotifycmd } },
	{ MODKEY|ShiftMask,		XK_f,      spawn,          {.v = firefoxcmd } }, 
        { 0,                            XK_Print,  spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
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
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	
	/* Media keys */
	{ 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0, XF86XK_AudioPlay, spawn, {.v = playerctltoggle } },
	{ 0, XF86XK_AudioPrev, spawn, {.v = playerctlprevcmd } },
	{ 0, XF86XK_AudioNext, spawn, {.v = playerctlnextcmd } },
	
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
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


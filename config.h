/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 6;        /* horizontal padding for statusbar */
static const int vertpadbar         = 7;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=9:weight=bold:antialias=true:hinting=true",
										"emoji:size=10:antialias=true:autohint=true" };
static const char col_bg[]          = "#282828";
static const char col_fg3[]         = "#bdae93";
static const char col_bg2[]         = "#504945";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg3,   col_bg,    col_bg    },
	[SchemeSel]  = { col_fg3,   col_bg2,   col_bg2   },
};

// #define SHCMD(cmd) "/bin/sh", "-c", cmd, NULL
static const char *const autostart[] = {
    "sh", ".autostart.sh", NULL,
    NULL
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "discord",  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char j4dmenucmd[]       = "j4-dmenu-desktop";
static const char dmenucmd[]         = "dmenu_run";
static const char termcmd[]          = "alacritty";

static const char lockcmd[]          = "betterlockscreen --lock blur";
static const char screenshotcmd[]    = "flameshot gui";

// static const char raisevolcmd[]      = "";
// static const char lowervolcmd[]      = "";
// static const char muteaudiocmd[]     = "";
static const char toggleplayercmd[]  = "empress play-pause";

#include <X11/XF86keysym.h>
#include "shift-tools.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key               function          argument */
	{ 0,                            XF86XK_AudioPlay, spawn,            SHCMD(toggleplayercmd) },
	{ ControlMask,                  XK_Insert,        spawn,            SHCMD(screenshotcmd) },
	{ MODKEY,                       XK_Escape,        spawn,            SHCMD(lockcmd) },
	{ MODKEY,                       XK_Return,        spawn,            SHCMD(termcmd) },
	{ MODKEY|AltMask|ShiftMask,     XK_Return,        spawn,            SHCMD(dmenucmd) },
	{ MODKEY|ShiftMask,             XK_Return,        spawn,            SHCMD(j4dmenucmd) },
	{ MODKEY,                       XK_b,             togglebar,        { 0 } },
	{ MODKEY,                       XK_h,             shiftview,        { .i  = -1 } },
	{ MODKEY,                       XK_l,             shiftview,        { .i  = +1 } },
	{ MODKEY|ShiftMask,             XK_j,             rotatestack,      { .i  = -1 } },
	{ MODKEY|ShiftMask,             XK_k,             rotatestack,      { .i  = +1 } },
	{ MODKEY,                       XK_j,             focusstack,       { .i  = +1 } },
	{ MODKEY,                       XK_k,             focusstack,       { .i  = -1 } },
	{ MODKEY,                       XK_u,             incnmaster,       { .i  = +1 } },
	{ MODKEY,                       XK_p,             incnmaster,       { .i  = -1 } },
	{ MODKEY,                       XK_i,             setmfact,         { .f  = -0.05 } },
	{ MODKEY,                       XK_o,             setmfact,         { .f  = +0.05 } },
	{ MODKEY|ShiftMask,             XK_h,             shiftboth,        { .i  = -1 } },
	{ MODKEY|ShiftMask,             XK_l,             shiftboth,        { .i  = +1 } },
	{ MODKEY|ControlMask,           XK_h,             shiftswaptags,    { .i  = -1 } },
	{ MODKEY|ControlMask,           XK_l,             shiftswaptags,    { .i  = +1 } },
	{ MODKEY|AltMask|ShiftMask,     XK_j,             movestack,        { .i  = +1 } },
	{ MODKEY|AltMask|ShiftMask,     XK_k,             movestack,        { .i  = -1 } },
	{ MODKEY,                       XK_slash,         zoom,             { 0 } },
	{ MODKEY,                       XK_Tab,           view,             { 0 } },
	{ MODKEY|ShiftMask,             XK_c,             killclient,       { 0 } },
	{ MODKEY,                       XK_t,             setlayout,        { .v  = &layouts[0] } },
	{ MODKEY,                       XK_f,             setlayout,        { .v  = &layouts[1] } },
	{ MODKEY,                       XK_m,             setlayout,        { .v  = &layouts[2] } },
	{ MODKEY,                       XK_space,         setlayout,        { 0 } },
	{ MODKEY|ShiftMask,             XK_space,         togglefloating,   { 0 } },
	{ MODKEY,                       XK_0,             view,             { .ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,             tag,              { .ui = ~0 } },
	{ MODKEY,                       XK_comma,         focusmon,         { .i  = -1 } },
	{ MODKEY,                       XK_period,        focusmon,         { .i  = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,         tagmon,           { .i  = -1 } },
	{ MODKEY|ShiftMask,             XK_period,        tagmon,           { .i  = +1 } },
	TAGKEYS(                        XK_1,                                 0 )
	TAGKEYS(                        XK_2,                                 1 )
	TAGKEYS(                        XK_3,                                 2 )
	TAGKEYS(                        XK_4,                                 3 )
	TAGKEYS(                        XK_5,                                 4 )
	TAGKEYS(                        XK_6,                                 5 )
	TAGKEYS(                        XK_7,                                 6 )
	TAGKEYS(                        XK_8,                                 7 )
	TAGKEYS(                        XK_9,                                 8 )
	{ MODKEY|ShiftMask,             XK_q,             quit,             { 0 } },
	{ MODKEY|ShiftMask,             XK_r,             quit,             { 1 } }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      { 0 } },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      { .v = &layouts[2] } },
	{ ClkWinTitle,          0,              Button2,        zoom,           { 0 } },
	{ ClkStatusText,        0,              Button2,        spawn,          { .v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      { 0 } },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, { 0 } },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    { 0 } },
	{ ClkTagBar,            0,              Button1,        view,           { 0 } },
	{ ClkTagBar,            0,              Button3,        toggleview,     { 0 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            { 0 } },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      { 0 } },
};


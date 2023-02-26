/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
//static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char font[]            = "-*-fixed-medium-r-semicondensed-*-13-*-*-*-*-*-iso10646-*";
static const char normbordercolor[] = "#333333";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#aaaaaa";
static const char selbordercolor[]  = "#aaaaaa";
static const char selbgcolor[]      = "#333333";
static const char selfgcolor[]      = "#999999";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */

#define NUMCOLORS         5
static const char colors[NUMCOLORS][ColLast][8] = {
  // border   foreground background
  { "#333333", "#aaaaaa", "#000000" },  // normal
  { "#000088", "#00ff00", "#000000" },  // good
  { "#ff0000", "#ffff00", "#000000" },  // warning
  { "#ff0000", "#ff0000", "#000000" },  // error
  { "#333333", "#aaaaaa", "#000000" },  // back to normal (for endpoints that are regular)
  // add more here
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MODMETAKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[] = { "lock", NULL };
static const char *dclip_copy_cmd[] = { "dclip", "copy" };
static const char *dclip_paste_cmd[] = { "dclip", "paste", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor , "-sf", selfgcolor, NULL };
static const char *upvol[] = { "amixer", "-D", "pulse", "set", "Master", "5%+", NULL};
static const char *downvol[] = { "amixer", "-D", "pulse", "set", "Master", "5%-", NULL};
static const char *mute_toggle_vol[] = { "amixer", "-D", "pulse", "set", "Master", "toggle", NULL};
static const char *mute_mic_toggle_vol[] = { "amixer", "-D", "pulse", "set", "Capture", "toggle", NULL};
static const char *upbrightness[] = { "xbacklight", "-inc", "10", NULL};
static const char *downbrightness[] = { "xbacklight", "-dec", "10", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODMETAKEY,                   XK_l,      spawn,          {.v = lockcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODMETAKEY,                   XK_1,      focusvisible,   {.i = 0 } },
    { MODMETAKEY,                   XK_2,      focusvisible,   {.i = 1 } },
    { MODMETAKEY,                   XK_3,      focusvisible,   {.i = 2 } },
    { MODMETAKEY,                   XK_4,      focusvisible,   {.i = 3 } },
    { MODMETAKEY,                   XK_5,      focusvisible,   {.i = 4 } },
    { MODMETAKEY,                   XK_6,      focusvisible,   {.i = 5 } },
    { MODMETAKEY,                   XK_7,      focusvisible,   {.i = 6 } },
    { MODMETAKEY,                   XK_8,      focusvisible,   {.i = 7 } },
    { MODMETAKEY,                   XK_9,      focusvisible,   {.i = 8 } },
    { MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
    { MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_c,      spawn,          {.v = dclip_copy_cmd } },
    { MODKEY,                       XK_v,      spawn,          {.v = dclip_paste_cmd } },
    { MODKEY,                       XK_F5,     spawn,          SHCMD("video-swap") },
    { 0,                            XF86XK_AudioLowerVolume,   spawn,  {.v = downvol } },
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,  {.v = upvol } },
    { 0,                            XF86XK_AudioMute,          spawn,  {.v = mute_toggle_vol } },
    { 0,                            XF86XK_AudioMicMute,       spawn,  {.v = mute_mic_toggle_vol } },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,  {.v = downbrightness } },
    { 0,                            XF86XK_MonBrightnessUp,    spawn,  {.v = upbrightness } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODMETAKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODMETAKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODMETAKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODMETAKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODMETAKEY,         Button3,        toggletag,      {0} },
};


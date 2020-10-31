/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "FontAwesome:pixelsize=18:antialias=true:autohint=true",
                                        "Source Code Pro Regular:pixelsize=20:antialias=true:autohint=true" };
static const char dmenufont[]       = "Source Code Pro:pixelsize=20:antialias=true:autohint=true";
static const char col_font[]        = "#e6e6e6";
static const char col_dark[]        = "#141414";
static const char col_light[]       = "#3b3b3b";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_font, col_dark, col_dark },
	[SchemeSel]  = { col_font, col_light,  col_light },
};

static const char *const autostart[] = {
	"sh", "-c", "dwmblocks;", NULL,
	"sh", "-c", "xfce4-clipman;", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered    isfloating   monitor */
	{ "Skype",        NULL,   NULL,       0,            1,            1,           -1 },
	{ "feh",          NULL,   NULL,       0,            1,            1,           -1 },
	{ "Viewnior",     NULL,   NULL,       0,            1,            1,           -1 },
	{ "Thunar",       NULL,   NULL,       0,            1,            1,           -1 },
	{ "Mousepad",     NULL,   NULL,       0,            1,            1,           -1 },
	{ "Signal",       NULL,   NULL,       0,            1,            1,           -1 },
	{ "Pavucontrol",  NULL,   NULL,       0,            1,            1,           -1 },
	{ "Firefox",      NULL,   NULL,       1 << 8,       0,            0,           -1 },
	{ "kitty",        NULL,   NULL,       0,            1,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark, "-nf", col_font, "-sb", col_light, "-sf", col_font, NULL };
static const char *termcmd[]  = { "xfce4-terminal", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,         spawn,          {.v = dmenucmd } },
	{ MODKEY,             		    XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY,             		    XK_m,         spawn,          SHCMD("thunderbird") },
	{ MODKEY|ShiftMask,    		    XK_p,         spawn,          SHCMD("zathura") },
	{ MODKEY,             		    XK_w, 	      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_Right,     spawn,          SHCMD("pactl set-sink-volume 0 +10%; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_Left,      spawn,          SHCMD("pactl set-sink-volume 0 -10%; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_m,         spawn,          SHCMD("pactl set-sink-mute 0 toggle; pkill -RTMIN+11 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_Up,        spawn,          SHCMD("xbacklight -inc 4.99; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_Down,      spawn,          SHCMD("xbacklight -dec 4.99; pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,		        XK_k,         spawn,          SHCMD("/home/diego/.scripts/kb_change; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY,		                XK_t,         spawn,          SHCMD("/home/diego/.scripts/TASKS/loader.sh") },
	{ MODKEY,       		        XK_a,         spawn,          SHCMD("kitty -e /home/diego/.scripts/TASKS/add_task.sh") },
	{ MODKEY,             		    XK_r,         spawn,          SHCMD("kitty -e /home/diego/.scripts/TASKS/rm_task.sh") },
	{ MODKEY|ShiftMask,        		XK_BackSpace, spawn,          SHCMD("shutdown now") },
	{ MODKEY|ShiftMask,     		XK_s,	      spawn,          SHCMD("systemctl suspend") },
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,         incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,    zoom,           {0} },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,         killclient,     {0} },
	//{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,     setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,     togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
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


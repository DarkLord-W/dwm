/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows *//* 窗口边框大小 */
static const unsigned int snap      = 32;       /* snap pixel *//* 边缘依附宽度 */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */ /* 托盘跟随的显示器 0代表不指定显示器 */ /* 托盘跟随的显示器 0代表不指定显示器 */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing *//* 托盘间距 */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systrayspadding = 5;        /* 托盘和状态栏的间隙 */
static int gappi                         = 14;        /* 窗口与窗口 缝隙大小 */
static int gappo                         = 14;        /* 窗口与边缘 缝隙大小 */
static const int vertpad                 = 5;         /* vertical padding of bar */
static const int sidepad                 = 5;         /* horizontal padding of bar */
static const int overviewgappi           = 24;        /* overview时 窗口与边缘 缝隙大小 */
static const int overviewgappo           = 60;        /* overview时 窗口与窗口 缝隙大小 */
static const int showsystray        = 1;        /* 0 means no systray *//* 是否显示托盘栏 */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font Mono:size=15" };
static const char dmenufont[]       = "SauceCodePro Nerd Font Mono:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#dddddd";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xc0; /* 状态栏透明度 */
static const unsigned int borderalpha = 0xdd; /* 边框透明度 */
static const char *colors[][3]      = { /* 颜色设置 */
	/*               fg         bg         border   */
//	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
//	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
    [SchemeNorm] = { "#bbbbbb", "#333333", "#444444" },
    [SchemeSel] = { "#ffffff", "#37474F", "#42A5F5" },
    [SchemeSelGlobal] = { "#ffffff", "#37474F", "#42A5F5" },
    [SchemeHid] = { "#dddddd", NULL, NULL },
    [SchemeSystray] = { NULL, "#7799AA", NULL },
    [SchemeUnderline] = { "#7799AA", NULL, NULL }, 
    [SchemeNormTag] = { "#bbbbbb", "#333333", NULL },
    [SchemeSelTag] = { "#eeeeee", "#333333", NULL },
    [SchemeBarEmpty] = { NULL, "#111111", NULL },
};
static const unsigned int alphas[][3]      = { /* 透明度设置*/ 
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
    [SchemeSelGlobal] = { OPAQUE, baralpha, borderalpha },
    [SchemeNormTag] = { OPAQUE, baralpha, borderalpha }, 
    [SchemeSelTag] = { OPAQUE, baralpha, borderalpha },
    [SchemeBarEmpty] = { NULL, 0x11, NULL },
    [SchemeStatusText] = { OPAQUE, 0x88, NULL },

};


/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
/* 自定义tag名称 */
static const char *tags[] = {"" , "", "", "", "", "", "", "", "" };

/*定义autostart脚本位置*/
static const char *autostartscript = "/home/darklord/.dwm/scripts/autostart.sh";

/* 自定义窗口显示规则 */
/* class instance title 主要用于定位窗口适合哪个规则 */
/* tags mask 定义符合该规则的窗口的tag 0 表示当前tag */
/* isfloating 定义符合该规则的窗口是否浮动 */
/* monitor 定义符合该规则的窗口显示在哪个显示器上 -1 为当前屏幕 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const char *overviewtag = "OVERVIEW";
static const Layout overviewlayout = { "﬿",  overview };

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﬿",  tile },        /* first entry is default */ /* 主次栈 */
    { "﩯",  magicgrid },    /* 网格 */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },

};

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
static const char *termcmd[]  = { "terminator", NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show","drun","-theme","darklord",NULL };
static const char *xkill[]  = { "xkill", NULL };
static const char *blurlock[]  = { "blurlock", NULL };
static const char *flameshot[]  = { "flameshot","gui", NULL };
static const char *ranger[]    = { "terminator", "-e", "ranger", NULL };
static const char *vim[]      = { "terminator", "-e", "vim", NULL };
static const char *upvol[]   = { "/home/darklord/.dwm/scripts/vol-up.sh",  NULL };
static const char *downvol[] = { "/home/darklord/.dwm/scripts/vol-down.sh",  NULL };
static const char *mutevol[] = { "/home/darklord/.dwm/scripts/vol-toggle.sh",  NULL };
static const char *uplight[]   = { "/home/darklord/.dwm/scripts/xlight-up.sh",  NULL };
static const char *downlight[] = { "/home/darklord/.dwm/scripts/xlight-down.sh",  NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_s,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = blurlock } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = flameshot } },
	{ MODKEY,						XK_r,	   spawn,          {.v = ranger } },
	{ MODKEY,						XK_v,	   spawn,          {.v = vim } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = downvol } },
	{ MODKEY,                       XK_F1,   spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F6,   spawn,          {.v = uplight } },
	{ MODKEY,                       XK_F5,     spawn,          {.v = downlight   } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },   /* super b  |  开启/关闭 状态栏 */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, /*本tag内切换聚焦窗口 */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, /*本tag内切换聚焦窗口 */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, /*窗口模式变为左右垂直*/
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, /*窗口模式变为上下水平*/
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, /*缩小主工作区 */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, /*放大主工作区 */
	{ MODKEY,                       XK_Return, zoom,           {0} }, /*将当前聚焦窗口置为主窗口*/
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      quit,     {0} },  /*退出dwm*/
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, /*开启/关闭 聚焦目标的float模式 */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /*光标移动到另一个显示器*/
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /*光标移动到另一个显示器*/
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /*将聚焦窗口移动到另一个显示器*/
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, /*将聚焦窗口移动到另一个显示器*/
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_k,      killclient,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = xkill } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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


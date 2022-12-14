; 结构变量声明区域
;消息结构数组
MSGStruct STRUCT
	msgWnd				DWORD ?
	msgMessage			DWORD ?
	msgWparam			DWORD ?
	msgLparam			DWORD ?
	msgTime				DWORD ?
	msgPt				POINT <>
MSGStruct ENDS

;子弹数组定义
BULLET STRUCT
	xCoor				SWORD ? ;单位：像素
	yCoor				SWORD ? ;单位：像素
	color				WORD  ? ;1代表黑方射出的子弹（黑色），2代表白方，0代表不合法子弹
	heading				WORD  ? ;子弹的朝向，1代表上，2代表下，3代表左，4代表右
BULLET ENDS

; 特有变量声明区域
; 窗口长宽
WINDOW_WIDTH			EQU		640
WINDOW_HEIGHT			EQU		480

; 消息固定参数
WM_PAINT				EQU		00000000fh
WM_KEYDOWN				EQU		000000100h
WM_KEYUP				EQU		000000101h


; 函数声明区域
; 消息部分
; 消息转换用于后面翻译键盘输入为字符码
TranslateMessage		PROTO STDCALL :DWORD

; 定时器部分
; 定时器设置
SetTimer				PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
; 定时器删除
KillTimer				PROTO STDCALL :DWORD,:DWORD

; 绘图部分
; 获取程序显示DC句柄
GetDC					PROTO STDCALL :DWORD
; 释放DC窗口句柄
ReleaseDC				PROTO STDCALL :DWORD,:DWORD
; 图片加载函数 
LoadImageA				PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
; 开始绘画函数
BeginPaint				PROTO STDCALL :DWORD,:DWORD
; 结束绘画函数
EndPaint				PROTO STDCALL :DWORD,:DWORD
; 创造与指定DC兼容的存储DC
CreateCompatibleDC		PROTO STDCALL: DWORD
; 创造与指定DC兼容的位图句柄
CreateCompatibleBitmap	PROTO STDCALL :DWORD,:DWORD,:DWORD
; 用选定的DC填充目标DC
SelectObject			PROTO STDCALL :DWORD,:DWORD
; 将指定的DC链接到目标DC的某一个区域上，是一个显示图片的函数
BitBlt					PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
; 设置背景颜色
SetBkColor				PROTO STDCALL :DWORD,:DWORD
; 将字符串链接到目标DC的某一个区域上，是一个显示数字的函数
TextOutA				PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
; 创建指定的字体
CreateFontA				PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
; 播放音频文件函数
PlaySound				PROTO STDCALL :DWORD,:DWORD,:DWORD


; 自定义函数声明区域
PaintProc				PROTO STDCALL :DWORD,:DWORD,:DWORD,:DWORD
emitBullet				PROTO STDCALL :WORD,:WORD,:WORD,:WORD
;==================== DATA =======================
.data

; 字符串定义区域
WindowName				BYTE	"INVERSUS ASM",0		; 窗口名
className				BYTE	"ASMWin",0				; 窗口类名

ErrorTitle				BYTE	"Error",0				; 错误警告弹窗标题

P1WinMsg				BYTE	"P1 Win",0				; P1胜利提示   
P2WinMsg				BYTE	"P2 Win",0				; P2胜利提示   
endbacktip				BYTE	"press r to comeback",0	; 结束页面提示语言

gamename               byte   "INVERSUS",0 ;8
gamebanben             byte    "ASM",0    ;3

startText				BYTE	"start",0				; 开始游戏标签     
helpText				BYTE	"help",0				; 控制帮助文档标签
customText				BYTE	"custom",0				; 个性化定义颜色标签
exitText				BYTE	"exit",0				; 退出游戏标签
tipsText                byte     "--tips: you can use up-down or w-s to select the menu.--"
tipsText2                byte     "--tips: you can use left-right or a-d to select the map.--"
modeselectText            byte   "Game Mode Selection",0  ; 模式选择界面
PVPText					BYTE	"P V P",0				; 双人小游戏模式标签
PVEText					BYTE	"P V E",0				; 单机模式标签     unused
BackText				BYTE	"<-back",0				; 返回上一级目录标签
mapselectText			byte    "Map Selection",0       ; 选地图
arrowText1				BYTE	"|",0					; 指示地图选择标签
arrowText2				byte    "V",0                   ; 指示地图选择标签
pauseText				BYTE	"       Pausing, press C to continue, press Q to quit.       ",0   ; 暂停标签
bgChooseText			BYTE	"background",0			; 背景选择标签
p1ChooseText			BYTE	"    p1    ",0			; p1选择标签
p2ChooseText			BYTE	"    p2    ",0			; p2选择标签

; 以下部分为帮助文档的内容，采用文字显示和笔刷绘画，能够提供较大的自定义属性
helptext_title1			byte	"GAME RULE SHOW",0  ; 14

helptext_hang1			byte	"INVERSUS is a shooting game. In this game, you need to",0  ; 54
helptext_hang2			byte	"manipulate one of two color blocks to move and shoot.",0  ;53
helptext_hang3			byte	"The goal to win is to HIT THE OPPONENT.",0   ;39
helptext_hang4			byte	"Please note that the map is also divided into two colors.",0     ;57
helptext_hang5			byte	"You can only move in areas that are the OPPOSITE of your",0    ;56
helptext_hang6			byte	"color.You can change the color of any area, but void area,",0  ;58
helptext_hang7			byte	"by shooting. The color of the shot path will be changed",0  ;55
helptext_hang8			byte	"to your opposite color.",0       ;23

helptext_title2			byte	"GAME CONTROL SHOW",0  ;17
helptext_hang9_1		byte	"Player 1: Move by",0  ;17
helptext_hang9_2		byte	"W",0 ;1
helptext_hang9_3		byte	"S",0 ;1
helptext_hang9_4		byte	"A",0  ;1
helptext_hang9_5		byte	"D",0  ;1
helptext_hang9_6		byte	".Shoot by",0  ; 9
helptext_hang9_7		byte	"SPACE",0  ;5
helptext_hang10_1		byte	"Player 2: Move by",0  ;17
helptext_hang10_2		byte	"UP",0    ; 2
helptext_hang10_3		byte	"DOWN",0  ; 4
helptext_hang10_4		byte	"<-",0   ;  2
helptext_hang10_5		byte	"->",0   ; 2
helptext_hang10_6		byte	".Shoot by",0  ; 9
helptext_hang10_7		byte	"ENTER",0  ;5
helptext_hang11			byte	"You can customize your color and background color in",0  ;52
helptext_hang12_1       byte	"custom menu. Select background color by",0 ;39
helptext_hang12_2		byte	"I",0    ; 1
helptext_hang12_3		byte	"J",0  ; 1
helptext_hang12_4		byte	"K",0   ;  1
helptext_hang12_5		byte	"L",0   ; 1
helptext_hang12_6       byte    "Select p1",0 ;9
helptext_hang13			byte	",p2 color by your movekey.Press ENTER or SPACE to confirm.",0  ; 58

helptext_hang14			BYTE	"-----------------PRESS DOWN OR S TO GO ON-----------------",0 ;58

helptext2_title1		BYTE	"SHOOT MECHANISM",0  ;15
helptext2_hang1			BYTE	"Your bullets will NOT defeat the opponent directly.",0 ;51
helptext2_hang2			BYTE	"Instead, they only change the color of the area they pass",0 ;57
helptext2_hang3			BYTE	"through. Once part of the opponent's color block is in the",0 ;58
helptext2_hang4			BYTE	"area where changed color, which means an illegal position,",0 ;58
helptext2_hang5			BYTE	"it is defeated.",0 ;15

helptext2_title2		BYTE	"PAUSE AND QUIT",0 ;14
helptext2_hang6_1		BYTE	"During gaming, you can pause the game by pressing",0 ;49
helptext2_hang6_2		BYTE	"ESC",0 ;3
helptext2_hang7_1		BYTE	"If you want to continue the game, press",0 ;39
helptext2_hang7_2		BYTE	"C",0 ;1
helptext2_hang7_3		BYTE	"after pausing.",0 ;6
helptext2_hang8_1		BYTE	"If you want to quit the game, press",0 ;35
helptext2_hang8_2		BYTE	"Q",0 ;1
helptext2_hang8_3		BYTE	"after pausing.",0 ;14

helptext2_title3		BYTE	"CONTACT US",0 ;10
helptext2_hang9			BYTE	"Lin Xintao: linxt20@mails.tsinghua.edu.cn",0 ;41
helptext2_hang10		BYTE	"Du Jiakun: djk20@mails.tsinghua.edu.cn",0 ;38
helptext2_hang11		BYTE	"Zhu Simo: zhusm18@mails.tsinghua.edu.cn",0 ;39

helptext2_hang12		BYTE	"-----------------PRESS UP OR W TO GO BACK-----------------",0 ;58
helptext2_hang13		BYTE	"---------------PRESS ENTER OR SPACE TO QUIT---------------",0 ;58

; 结构变量定义区域
; Define the Application's Window class structure.
MainWin					WNDCLASS	<NULL,WinProc,NULL,NULL,NULL,NULL,NULL, COLOR_WINDOW,NULL,className>
; 消息结构变量定义
msg						MSGStruct	<>
; 画笔结构变量定义
ps						PAINTSTRUCT	<>

; 普通变量定义区域
; 句柄变量
hMainWnd				DWORD ? ; 总窗口句柄
hInstance				DWORD ? ; 用于创建调用进程的文件的句柄
hdc						DWORD ? ; 程序窗口的句柄
hdcMempage				DWORD ? ; 布局页面显示句柄
hdcMemp2				DWORD ? ; 白色块显示句柄
hdcMemp1				DWORD ? ; 黑色块显示句柄
hdcMembg				DWORD ? ; 背景块显示句柄
hdcMemhelp				DWORD ? ; 帮助图显示句柄
hdcMemhelp2				DWORD ? ; 帮助图显示句柄2
hdcMemMap1				DWORD ? ; 地图1图片显示句柄
hdcMemMap2				DWORD ? ; 地图2图片显示句柄
hdcMemMap3				DWORD ? ; 地图3图片显示句柄
hdcMemColors			DWORD 20 DUP(?) ; 20种颜色显示句柄

; 菜单选项变量
WhichMenu				DWORD 0  ; 哪个界面，0表示开始，1表示选择游戏模式，2表示正在游戏，3表示游戏结束，4代表帮助界面，5代表选关界面，6代表自定义主题色界面
SelectMenu				SDWORD 0 ; 正在选择的菜单项 0表示第一项; 或者用于自定义主题颜色界面给p1提供光标移动选择
SelectMenu2				SDWORD 0 ; 用来在自定义主题颜色界面给p2提供光标移动选择
SelectMenu3				SDWORD 0 ; 用来在自定义主题颜色界面对背景进行选择
helpPage				DWORD 1  ; 用来指示当前处于帮助界面的哪一面

; 方块状态变量  前两位是位置，第三位是大小，第四位是朝向(heading)，指示子弹发射的方向，第五位为剩余子弹数（每人上限为4）
;第六位是冷却（子弹恢复）计数器，当达到100时（也即，子弹恢复时间为3秒）清零，并增加一发子弹
p1block				WORD 164,164,23,1,4,0
p2block				WORD 452,292,23,1,4,0

; 每一轮黑白块的初始位置 第一个数是横向的刻度，第二个数是纵向的刻度
p1_initpos			WORD 164,164
p2_initpos			WORD 452,292

; 颜色变量，用于自定义主题页面
Colors					DWORD 00000000h,00FFFFFFh,00CCA700h,00FF0000h,0000FF00h
						DWORD 00FF00FFh,0000FFFFh,00FFFF00h,000000FFh,009900FFh
						DWORD 00674EA7h,00777777h,00777700h,008E7CC3h,00D1EEEEh
						DWORD 008E388Eh,00D9D9D9h,007F6000h,00274E13h,00EAD1DCh

titlecolor                DWORD 00696946h ; 标题的颜色
judgeup                 DWORD 1 ;

; 字体变量
font_100                 DWORD ?  ; 高度为100像素的字体
font_80                 DWORD ?  ; 高度为80像素的字体
font_50					DWORD ?  ; 高度为50像素的字体
font_40					DWORD ?  ; 高度为40像素的字体
font_20					DWORD ?  ; 高度为20像素的字体

; 每一轮地图数组，20*15，0代表该格为空，1代表黑格，2代表白格
roundone_map			WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
						WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,0
						WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
						WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

roundtwo_map			WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,2,2,0,0,2,2,2,2,2,1,1,1,1,1,0,0,1,1,0
						WORD 0,2,2,0,0,2,2,2,2,2,1,1,1,1,1,0,0,1,1,0
						WORD 0,2,2,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0
						WORD 0,2,2,0,0,2,2,2,2,2,1,1,1,1,1,0,0,1,1,0
						WORD 0,2,2,0,0,2,2,2,2,2,1,1,1,1,1,0,0,1,1,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

roundthree_map			WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,1,0
						WORD 0,2,0,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,1,0
						WORD 0,2,0,2,0,2,0,0,0,0,0,0,0,0,1,0,1,0,1,0
						WORD 0,2,0,2,0,2,2,2,2,2,1,1,1,1,1,0,1,0,1,0
						WORD 0,2,0,2,0,2,0,0,0,2,1,0,0,0,1,0,1,0,1,0
						WORD 0,2,2,2,0,2,2,2,2,2,1,1,1,1,1,0,1,1,1,0
						WORD 0,2,0,2,0,2,0,0,0,2,1,0,0,0,1,0,1,0,1,0
						WORD 0,2,0,2,0,2,2,2,2,2,1,1,1,1,1,0,1,0,1,0
						WORD 0,2,0,2,0,2,0,0,0,0,0,0,0,0,1,0,1,0,1,0
						WORD 0,2,0,2,2,2,2,2,2,2,1,1,1,1,1,1,1,0,1,0
						WORD 0,2,0,0,0,0,0,0,0,2,1,0,0,0,0,0,0,0,1,0
						WORD 0,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,0
						WORD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

; 游戏中使用的临时地图数组，主要拷贝地图数组的内容，使地图数组能够反复利用
map						WORD 300 DUP(?)

;子弹数组，储存地图中的每颗子弹，在计时器中令所有子弹向指定方向移动一段距离
bullets					BULLET 10 DUP(< -1,-1,0,0 >)  ; 这一部分参考其结构，前两个位为位置，第三个位是颜色，第四个位是方向
;假定地图中同时最多有10颗子弹，采取队列的思想，每次从currentBullet插入，并令currentBullets加一（并模10）
currentBullet			WORD 0

; 状态变量
statusFlag				WORD 0 ;状态flag，0代表未胜利，游戏正常进行，1代表黑方胜利，2代表白方胜利，3代表暂停
attack_p1            DWORD 1 ;space正在按下则设置为0，与space的状态位相乘，使其保持为0，这样就能实现按一次只发射一次子弹
attack_p2            DWORD 1 ;同上理

; 按键是否按下的指示变量
UpKeyHold				DWORD 0 
DownKeyHold				DWORD 0
LeftKeyHold				DWORD 0
RightKeyHold			DWORD 0
WKeyHold				DWORD 0
SKeyHold				DWORD 0
AKeyHold				DWORD 0
DKeyHold				DWORD 0
SpaceKeyHold			DWORD 0
EnterKeyHold			DWORD 0
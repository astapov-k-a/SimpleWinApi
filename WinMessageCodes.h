#ifndef   WIN_MESSAGE_CODES_H_PROTECT_SIGNATURE_DSAMMNW43532DFDFF
#define   WIN_MESSAGE_CODES_H_PROTECT_SIGNATURE_DSAMMNW43532DFDFF

struct WinMessage {
  enum Code : unsigned {
    	Create	 = 	  WM_CREATE	,
    	Destroy	 = 	  WM_DESTROY	,
    	Move	 = 	  WM_MOVE	,
    	Size	 = 	  WM_SIZE	,
    	Activate	 = 	  WM_ACTIVATE	,
    	SetFocus	 = 	  WM_SETFOCUS	,
    	KillFocus	 = 	  WM_KILLFOCUS	,
    	Enable	 = 	  WM_ENABLE	,
    	SetRedraw	 = 	  WM_SETREDRAW	,
    	SetText	 = 	  WM_SETTEXT	,
    	GetText	 = 	  WM_GETTEXT	,
    	TetTextLength	 = 	  WM_GETTEXTLENGTH	,
    	Paint	 = 	  WM_PAINT	,
    	Close	 = 	  WM_CLOSE	,
    	QueryEndSession	 = 	  WM_QUERYENDSESSION	,
    	Quit	 = 	  WM_QUIT	,
    	QueryOpen	 = 	  WM_QUERYOPEN	,
    	EraseBkgnd	 = 	  WM_ERASEBKGND	,
    	SysColorChange	 = 	  WM_SYSCOLORCHANGE	,
    	EndSession	 = 	  WM_ENDSESSION	,
    	ShowWindow	 = 	  WM_SHOWWINDOW	,
    	WinIniChange	 = 	  WM_WININICHANGE	,
    	DevModeChange	 = 	  WM_DEVMODECHANGE	,
    	ActivateApp	 = 	  WM_ACTIVATEAPP	,
    	FontChange	 = 	  WM_FONTCHANGE	,
    	TimeChange	 = 	  WM_TIMECHANGE	,
    	CancelMode	 = 	  WM_CANCELMODE	,
    	SetCursor	 = 	  WM_SETCURSOR	,
    	MouseActivate	 = 	  WM_MOUSEACTIVATE	,
    	ChilActivate	 = 	  WM_CHILDACTIVATE	,
    	QueueSync	 = 	  WM_QUEUESYNC	,
    	GetMinMaxInfo	 = 	  WM_GETMINMAXINFO	,
    	PaintIcon	 = 	  WM_PAINTICON	,
    	IconEraseBkgnd	 = 	  WM_ICONERASEBKGND	,
    	NextDlgCtl	 = 	  WM_NEXTDLGCTL	,
    	SpoolerStatus	 = 	  WM_SPOOLERSTATUS	,
    	DrawItem	 = 	  WM_DRAWITEM	,
    	MeasureItem	 = 	  WM_MEASUREITEM	,
    	DeleteItem	 = 	  WM_DELETEITEM	,
    	VKeyToItem	 = 	  WM_VKEYTOITEM	,
    	CharToItem	 = 	  WM_CHARTOITEM	,
    	SetFont	 = 	  WM_SETFONT	,
    	GetFont	 = 	  WM_GETFONT	,
    	SetHotKey	 = 	  WM_SETHOTKEY	,
    	GetHotKey	 = 	  WM_GETHOTKEY	,
    	QueryDragIcon	 = 	  WM_QUERYDRAGICON	,
    	CompareItem	 = 	  WM_COMPAREITEM	,
    	Compacting	 = 	  WM_COMPACTING	,
    	CommonNotify	 = 	  WM_COMMNOTIFY	,
    	WindowPosChanging	 = 	  WM_WINDOWPOSCHANGING	,
    	WindowPosChanged	 = 	  WM_WINDOWPOSCHANGED	,
    	Power	 = 	  WM_POWER	,
    	Notify	 = 	  WM_NOTIFY	,
    	InputLangChangeRequest	 = 	  WM_INPUTLANGCHANGEREQUEST	,
    	InputLangChange	 = 	  WM_INPUTLANGCHANGE	,
    	TCard	 = 	  WM_TCARD	,
    	Help	 = 	  WM_HELP	,
    	UserChanged	 = 	  WM_USERCHANGED	,
    	NotifyFormat	 = 	  WM_NOTIFYFORMAT	,
    	ContextMenu	 = 	  WM_CONTEXTMENU	,
    	StyleChanging	 = 	  WM_STYLECHANGING	,
    	StyleChanged	 = 	  WM_STYLECHANGED	,
    	DisplayChange	 = 	  WM_DISPLAYCHANGE	,
    	GetIcon	 = 	  WM_GETICON	,
    	SetIcon	 = 	  WM_SETICON	,
    	NCCreate	 = 	  WM_NCCREATE	,
    	NCDestroy	 = 	  WM_NCDESTROY	,
    	NCCalcSize	 = 	  WM_NCCALCSIZE	,
    	NCHitTest	 = 	  WM_NCHITTEST	,
    	NCPaint	 = 	  WM_NCPAINT	,
    	NCActivate	 = 	  WM_NCACTIVATE	,
    	GetDlgCode	 = 	  WM_GETDLGCODE	,
    	SyncPaint	 = 	  WM_SYNCPAINT	,
    	NCMouseMove	 = 	  WM_NCMOUSEMOVE	,
    	NCLButtonDown	 = 	  WM_NCLBUTTONDOWN	,
    	NCLButtonUp	 = 	  WM_NCLBUTTONUP	,
    	NCLButtonDblClk	 = 	  WM_NCLBUTTONDBLCLK	,
    	NCRButtonDown	 = 	  WM_NCRBUTTONDOWN	,
    	NCRButtonUp	 = 	  WM_NCRBUTTONUP	,
    	NCRButtonDblClk	 = 	  WM_NCRBUTTONDBLCLK	,
    	NCMButtonDown	 = 	  WM_NCMBUTTONDOWN	,
    	NCMButtonUp	 = 	  WM_NCMBUTTONUP	,
    	NCMButtonDblClk	 = 	  WM_NCMBUTTONDBLCLK	,
    	NCXButtonDown	 = 	  WM_NCXBUTTONDOWN	,
    	NCXButtonUp	 = 	  WM_NCXBUTTONUP	,
    	NCXButtonDblClk	 = 	  WM_NCXBUTTONDBLCLK	,
    	KeyDown	 = 	  WM_KEYDOWN	,
    	KeyUp	 = 	  WM_KEYUP	,
    	Char	 = 	  WM_CHAR	,
    	DeadChar	 = 	  WM_DEADCHAR	,
    	SysKeyDown	 = 	  WM_SYSKEYDOWN	,
    	SysKeyUp	 = 	  WM_SYSKEYUP	,
    	SysChar	 = 	  WM_SYSCHAR	,
    	SysDeadChar	 = 	  WM_SYSDEADCHAR	,
    	UniChar	 = 	  WM_UNICHAR	,
    	IME_StartComposition	 = 	  WM_IME_STARTCOMPOSITION	,
    	IME_EndComposition	 = 	  WM_IME_ENDCOMPOSITION	,
    	IME_Composition	 = 	  WM_IME_COMPOSITION	,
    	InitDialog	 = 	  WM_INITDIALOG	,
    	Command	 = 	  WM_COMMAND	,
    	SysCommand	 = 	  WM_SYSCOMMAND	,
    	Timer	 = 	  WM_TIMER	,
    	Hscroll	 = 	  WM_HSCROLL	,
    	Vscroll	 = 	  WM_VSCROLL	,
    	InitMenu	 = 	  WM_INITMENU	,
    	InitMenuPopup	 = 	  WM_INITMENUPOPUP	,
    	Gesture	 = 	  WM_GESTURE	,
    	GestureNotify	 = 	  WM_GESTURENOTIFY	,
    	MenuSelect	 = 	  WM_MENUSELECT	,
    	MenuChar	 = 	  WM_MENUCHAR	,
    	EnterIDLE	 = 	  WM_ENTERIDLE	,
    	MenuRButtonUp	 = 	  WM_MENURBUTTONUP	,
    	MenuDrag	 = 	  WM_MENUDRAG	,
    	MenuGetObject	 = 	  WM_MENUGETOBJECT	,
    	UninitMenuPopup	 = 	  WM_UNINITMENUPOPUP	,
    	MenuCommand	 = 	  WM_MENUCOMMAND	,
    	ChangeUIState	 = 	  WM_CHANGEUISTATE	,
    	UpdateUIState	 = 	  WM_UPDATEUISTATE	,
    	QueryUIState	 = 	  WM_QUERYUISTATE	,
  };
};
typedef WinMessage::Code WinMessageCode;

  /*
  WM_NULL
  WM_CREATE
  WM_DESTROY
  WM_MOVE
  WM_SIZE
  WM_ACTIVATE
  WM_SETFOCUS
  WM_SETFOCUS
  WM_KILLFOCUS
  WM_ENABLE
  WM_SETREDRAW
  WM_SETTEXT
  WM_GETTEXT
  WM_GETTEXTLENGTH
  WM_PAINT
  WM_CLOSE
  WM_QUERYENDSESSION
  WM_QUIT
  WM_QUERYOPEN
  WM_ERASEBKGND
  WM_SYSCOLORCHANGE
  WM_ENDSESSION
  WM_SHOWWINDOW
  WM_WININICHANGE
  WM_DEVMODECHANGE
  WM_ACTIVATEAPP
  WM_FONTCHANGE
  WM_TIMECHANGE
  WM_CANCELMODE
  WM_SETCURSOR
  WM_MOUSEACTIVATE
  WM_CHILDACTIVATE
  WM_QUEUESYNC
  WM_GETMINMAXINFO
  WM_PAINTICON
  WM_ICONERASEBKGND
  WM_NEXTDLGCTL
  WM_SPOOLERSTATUS
  WM_DRAWITEM
  WM_MEASUREITEM
  WM_DELETEITEM
  WM_VKEYTOITEM
  WM_CHARTOITEM
  WM_SETFONT
  WM_GETFONT
  WM_SETHOTKEY
  WM_GETHOTKEY
  WM_QUERYDRAGICON
  WM_COMPAREITEM
  WM_COMPACTING
  WM_COMMNOTIFY
  WM_WINDOWPOSCHANGING
  WM_WINDOWPOSCHANGED
  WM_POWER
  WM_NOTIFY
  WM_INPUTLANGCHANGEREQUEST
  WM_INPUTLANGCHANGE
  WM_TCARD
  WM_HELP
  WM_USERCHANGED
  WM_NOTIFYFORMAT
  WM_CONTEXTMENU
  WM_STYLECHANGING
  WM_STYLECHANGED
  WM_DISPLAYCHANGE
  WM_GETICON
  WM_SETICON
  WM_NCCREATE
  WM_NCDESTROY
  WM_NCCALCSIZE
  WM_NCHITTEST
  WM_NCPAINT
  WM_NCACTIVATE
  WM_GETDLGCODE
  WM_SYNCPAINT
  WM_NCMOUSEMOVE
  WM_NCLBUTTONDOWN
  WM_NCLBUTTONUP
  WM_NCLBUTTONDBLCLK
  WM_NCRBUTTONDOWN
  WM_NCRBUTTONUP
  WM_NCRBUTTONDBLCLK
  WM_NCMBUTTONDOWN
  WM_NCMBUTTONUP
  WM_NCMBUTTONDBLCLK
  WM_NCXBUTTONDOWN
  WM_NCXBUTTONUP
  WM_NCXBUTTONDBLCLK
  WM_KEYDOWN
  WM_KEYUP
  WM_CHAR
  WM_DEADCHAR
  WM_SYSKEYDOWN
  WM_SYSKEYUP
  WM_SYSCHAR
  WM_SYSDEADCHAR
  WM_UNICHAR
  WM_IME_STARTCOMPOSITION
  WM_IME_ENDCOMPOSITION
  WM_IME_COMPOSITION
  WM_INITDIALOG
  WM_COMMAND
  WM_SYSCOMMAND
  WM_TIMER
  WM_HSCROLL
  WM_VSCROLL
  WM_INITMENU
  WM_INITMENUPOPUP
  WM_GESTURE
  WM_GESTURENOTIFY
  WM_MENUSELECT
  WM_MENUCHAR
  WM_ENTERIDLE
  WM_MENURBUTTONUP
  WM_MENUDRAG
  WM_MENUGETOBJECT
  WM_UNINITMENUPOPUP
  WM_MENUCOMMAND
  WM_CHANGEUISTATE
  WM_UPDATEUISTATE
  WM_QUERYUISTATE
  WM_CTLCOLORMSGBOX
  WM_CTLCOLOREDIT
  WM_CTLCOLORLISTBOX
  WM_CTLCOLORBTN
  WM_CTLCOLORDLG
  WM_CTLCOLORSCROLLBAR
  WM_CTLCOLORSTATIC
  MN_GETHMENU
  WM_MOUSEMOVE
  WM_LBUTTONDOWN
  WM_LBUTTONUP
  WM_LBUTTONDBLCLK
  WM_RBUTTONDOWN
  WM_RBUTTONUP
  WM_RBUTTONDBLCLK
  WM_MBUTTONDOWN
  WM_MBUTTONUP
  WM_MBUTTONDBLCLK
  WM_MOUSEWHEEL
  WM_XBUTTONDOWN
  WM_XBUTTONUP
  WM_XBUTTONDBLCLK
  WM_MOUSEHWHEEL
  WM_PARENTNOTIFY
  WM_ENTERMENULOOP
  WM_EXITMENULOOP
  WM_NEXTMENU
  WM_SIZING
  WM_CAPTURECHANGED
  WM_MOVING
  WM_POWERBROADCAST
  WM_DEVICECHANGE
  WM_MDICREATE
  WM_MDIDESTROY
  WM_MDIACTIVATE
  WM_MDIRESTORE
  WM_MDINEXT
  WM_MDIMAXIMIZE
  WM_MDITILE
  WM_MDICASCADE
  WM_MDIICONARRANGE
  WM_MDIGETACTIVE
  WM_MDISETMENU
  WM_ENTERSIZEMOVE
  WM_EXITSIZEMOVE
  WM_DROPFILES
  WM_MDIREFRESHMENU
  WM_TOUCH
  WM_IME_SETCONTEXT
  WM_IME_NOTIFY
  WM_IME_CONTROL
  WM_IME_COMPOSITIONFULL
  WM_IME_SELECT
  WM_IME_CHAR
  WM_IME_REQUEST
  WM_IME_KEYDOWN
  WM_IME_KEYUP
  WM_MOUSEHOVER
  WM_MOUSELEAVE
  WM_NCMOUSEHOVER
  WM_NCMOUSELEAVE
  WM_WTSSESSION_CHANGE
  WM_TABLET_FIRST
  WM_TABLET_LAST
  WM_CUT
  WM_COPY
  WM_PASTE
  WM_CLEAR
  WM_UNDO
  WM_RENDERFORMAT
  WM_RENDERALLFORMATS
  WM_DESTROYCLIPBOARD
  WM_DRAWCLIPBOARD
  WM_PAINTCLIPBOARD
  WM_VSCROLLCLIPBOARD
  WM_SIZECLIPBOARD
  WM_ASKCBFORMATNAME
  WM_CHANGECBCHAIN
  WM_HSCROLLCLIPBOARD
  WM_QUERYNEWPALETTE
  WM_PALETTEISCHANGING
  WM_PALETTECHANGED
  WM_HOTKEY
  WM_PRINT
  WM_PRINTCLIENT
  WM_APPCOMMAND
  WM_THEMECHANGED
  WM_CLIPBOARDUPDATE
  WM_DWMCOMPOSITIONCHANGED
  WM_DWMNCRENDERINGCHANGED
  WM_DWMCOLORIZATIONCOLORCHANGED
  WM_DWMWINDOWMAXIMIZEDCHANGE
  WM_DWMSENDICONICTHUMBNAIL
  WM_DWMSENDICONICLIVEPREVIEWBITMAP
  WM_GETTITLEBARINFOEX
  WM_HANDHELDFIRST
  WM_HANDHELDLAST
  WM_AFXFIRST
  WM_AFXLAST
  WM_PENWINFIRST
  WM_PENWINLAST
  */

#endif // WIN_MESSAGE_CODES_H_PROTECT_SIGNATURE_DSAMMNW43532DFDFF
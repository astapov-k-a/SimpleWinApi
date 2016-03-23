/// @file WinApi.cpp
/// @brief тЮИК, ЯНДЕПФЮЫХИ ПЕЮКХГЮЖХХ АХАКХНРЕЙХ ДКЪ ПЮАНРШ Я winapi - БШБНДЮ НЙНМ, ЙНМРПНКНБ, НАПЮАНРЙХ ЯНАШРХИ Х ОПНВЕЦН
/// @details яРХКЭ ЙНДЮ - ОНВРХ Google Code Style
/// @author юЯРЮОНБ йНМЯРЮМРХМ (Astapov K.A.)
/// @copyright Astapov K.A. Call (+7-931)-29-17-0-16 or mail to konstantinlancer@gmail.com if you want commercial use of this code
/// @date 10.03.2016

#include "stdafx.h"
#include "WinApi.h"
#include <iostream>
#include <Shlobj.h>


namespace winapi {

Size  WndClassEx::counter_ = 0;

WndClassEx::WndClassEx() {
  cbSize = sizeof (WNDCLASSEX) ;
  style = CS_HREDRAW | CS_VREDRAW;
  lpfnWndProc = 0;
  cbClsExtra = 0;
  cbWndExtra = 0;
  hInstance = 0;
  hIcon = NULL;
  hCursor = NULL;
  hbrBackground = NULL;
  lpszMenuName = NULL;
  lpszClassName = NULL;
  hIconSm = NULL;
}

bool WndClassEx::Register(
    MessageCycleCallback callback,
    HINSTANCE instance_arg,
    Size sizeof_inherited ) {
  //cbWndExtra     = (sizeof_inherited > sizeof (WndClassEx) ) ?
  //                 (sizeof_inherited - sizeof (WndClassEx)) : 0;
  cbWndExtra = sizeof(This *);
  lpfnWndProc = callback;
  instance(instance_arg);
  String name;
  name = L"winapi::WindowClass_xkjs_";
  name .append( std::to_wstring(counter()) );
  SetWindowClassName( name );
  
  SetLastError(0);
  atom(  RegisterClassEx( static_cast<WndClassEx*>(this) )  );
  PrintWinError(); //@debug
  ATOM debug = atom();
  return atom()!=0;
}

void WndClassEx::SetWindowClassName(const String & value) {
  get_window_class_name_storage() = value;
  window_class_name_ptr( get_window_class_name_storage().c_str() );
}

void WndClassEx::Unregister() {
  UnregisterClass( window_class_name_ptr(), instance() );
}

CreateStruct::CreateStruct () {
  lpCreateParams=0;
  hInstance = 0;
  hMenu = 0;
  hwndParent = 0;
  cy = 0;
  cx = 0;
  y = 0;
  x = 0;
  style = 0;
  lpszName = 0;
  lpszClass = 0;
  dwExStyle = 0;
}
CreateStruct::CreateStruct(void * create_params) {
  lpCreateParams=reinterpret_cast<LPVOID>(create_params);
  hInstance = 0;
  hMenu = 0;
  hwndParent = 0;
  cy = 0;
  cx = 0;
  y = 0;
  x = 0;
  style = 0;
  lpszName = 0;
  lpszClass = 0;
  dwExStyle = 0;
}


static int WINAPI BrowseCallbackProc(HWND window, UINT message_code, LPARAM, LPARAM data)
{
    if (message_code == BFFM_INITIALIZED)
      Message((WinMessageCode)BFFM_SETSELECTION, (int)TRUE, data).Send(window);
    return 0;
}

bool GetFolder(const String & title,const String & start_directory,HWND owner, String & out_selected_path)
{
  Char * path = new (std::nothrow) Char[MAX_PATH];
  if (!path) return 0;
  std::unique_ptr<Char, std::default_delete<Char[]> > path_ptr(path);
  //memcpy( path, start_directory.c_str(), (start_directory.size() + 1) * sizeof(Char) );
    bool result = false;
    LPMALLOC pMalloc;

    if (SHGetMalloc(&pMalloc) == NOERROR) {
        BROWSEINFO bi;
        ZeroMemory(&bi,sizeof (bi) );
        bi.ulFlags   = BIF_RETURNONLYFSDIRS;

        bi.hwndOwner = owner;
        bi.lpszTitle = title.c_str();
        bi.lpfn      = NULL;
        bi.ulFlags  |= BIF_STATUSTEXT;
        bi.lParam    = LPARAM(path);
        if ( start_directory != String() )
        {
            bi.lpfn     = BrowseCallbackProc;
            bi.lParam   = (LPARAM)start_directory.c_str();
        }
        LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);

        if (pidl != NULL) 
        {
            if (SHGetPathFromIDList(pidl,path))
                result = true;
            pMalloc->Free(pidl);
        }
        if (bi.pidlRoot != NULL)
            pMalloc->Free(&bi);
        pMalloc->Release();
    }
    if (result) {
      out_selected_path.assign(path);
    }
    return result;
}
 

bool ListView::Add(const String & item) {
  int index = 0;
  LVITEM lvi;
  lvi.mask = LVIF_TEXT;
  lvi.cchTextMax = item.size() + 1;
  lvi.iItem = index;
  lvi.pszText = (LPWSTR)item.c_str();
  lvi.iSubItem = 0; 
  Char * value = (Char *) item.c_str();
  Char * * stor = &value;
  if (ListView_InsertItem(GetHandle(), &lvi) == -1) {
    return 0;
  }    
  ListView_SetItemText( GetHandle(), 1, 1, (LPWSTR)stor ); 
  return 1;
}

void ListView::Clear() {
  Size count = GetNumberItems();
  for ( ; count; --count) {
    Delete(0);
  }
}

int ListView::SetColumns(int colNum, const String * header)
{
    RECT rcl;
    GetClientRect( GetHandle(), &rcl );
 
    int index = -1;
 
    LVCOLUMN lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.cx = (rcl.right - rcl.left) / colNum;
    lvc.cchTextMax = 65536;
 
    for (int i = 0; i < colNum; i++)
    {
        lvc.pszText = (LPWSTR) header[i].c_str();
        index = ListView_InsertColumn( GetHandle(), i, &lvc);
        if (index == -1) break;
    }
 
    return index;
}
 
void InitialiseCommonControls(DWORD ICC) {
  static DWORD mask = 0;
  if ( (mask | ICC) != mask ) { //ïðîâåðÿåì, áûëà ëè èíèöèàëèçàöèÿ äëÿ ýòèõ ôëàãîâ
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC;
    InitCommonControlsEx(&icex);  
    mask = mask | ICC; //óñòàíàâëèâàåì ïðîèíèöèàëèçèðîâàííûå ôëàãè
  }
}

bool ControlBody::Construct(HWND parent_handle_arg, Parent * parent_object_arg, Size id_arg,  Position position, Params param) {  
  RECT rcl;
  InitialiseCommonControls(param.icc);
  parent_handle(parent_handle_arg);
  parent(parent_object_arg);
  GetClientRect( parent_handle(), &rcl );
  int width = position.width;
  int height = position.height;
  if ( height < 0 ) {
    height = max (0, rcl.bottom - rcl.top + height);
  }
  if (width < 0) {
    width = max (0, rcl.right - rcl.left + width);
  }

  HWND hwnd = CreateWindow(param.class_name, L"",
      WS_CHILD | param.control_flags,
      //0, 0, rcl.right - rcl.left - width_decrease, rcl.bottom - rcl.top - height_decrease,
      position.x, position.y, width, height,
      parent_handle(), (HMENU)id_arg, GetModuleHandle(NULL), NULL);
  handle (hwnd);
  if ( !handle() ) return 0;
 
  // ×òîáû îïðåäåëÿëèñü ñòðîêà (item) è ñòîëáåö (subitem) îáÿçàòåëüíî óñòàíàâëèâàåì
  // ðàñøèðåííûé ñòèëü LVS_EX_FULLROWSELECT.
  //ListView_SetExtendedListViewStyleEx(hWndLV, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
 //(DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, dwMask, dw)
  param.final_message.Send( handle() );
  //ShowWindow( handle(), SW_SHOWDEFAULT);
  return 1;
}

void ControlBody::Deconstruct() {
  DestroyWindow( handle() );
  handle(0);
}

bool ControlBody::Create(
    HWND parent_handle_arg,
    Parent * parent_object_arg,
    Size id,
    Position position,
    const Params& param,
    ControlBody::ThisPtr & out_created_object) {
  This * allocated  = new (std::nothrow) ControlBody;
  if (!allocated) return 0;
  bool re = allocated->Construct(
    parent_handle_arg,
    parent_object_arg,
    id,
    position,
    param);
  if (re) {
    out_created_object = allocated;
  } else {
    delete allocated;
  }
  return re;
}

Size Control::id_counter_ = 0;

bool Control::Initialize(HWND parent_handle_arg, Parent * parent_object_arg,  Position position) {
  Body::ThisPtr pointer;
  GenerateId();
  bool re = Body::Create(parent_handle_arg, parent_object_arg, id(), position, GetParam(), pointer);
  if (re) {
    IcreaseIdCounter();
    bodyptr(pointer);
  }
  return re;
}
const ListView::ParamsStruct ListView::params_ = {
  LVS_REPORT | WS_VISIBLE, //control_flags
  ICC_LISTVIEW_CLASSES, //icc
  { (WinMessageCode)LVM_SETEXTENDEDLISTVIEWSTYLE , 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES}, //final_message
  WC_LISTVIEW 
};

const ListView::Params & ListView::GetParam() const {
  return static_cast<const Params &>(params_);
}

const Button::ParamsStruct Button::params_ = {
  WS_VISIBLE | BS_PUSHBUTTON, //control_flags
  ICC_STANDARD_CLASSES, //icc
  { (WinMessageCode)0 , 0, 0}, //final_message (no final message)
  WC_BUTTON 
};

const Button::Params & Button::GetParam() const {
  return static_cast<const Params &>(params_);
}

const StaticText::ParamsStruct StaticText::params_ = {
  WS_VISIBLE, //control_flags
  ICC_STANDARD_CLASSES, //icc
  { (WinMessageCode)0 , 0, 0}, //final_message (no final message)
  WC_STATIC 
};

const StaticText::Params & StaticText::GetParam() const {
  return static_cast<const Params &>(params_);
}

void DebugTemplate() {
  WindowClassDebug a;
  //a.Register(0);
}


String GetWinErrorEng(DWORD errcode) {
   LPVOID buffer;
   //LPVOID display;
  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      errcode,
      MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
      (LPTSTR) &buffer,
      0, NULL );
  return String((wchar_t *)buffer);
}

String GetWinErrorRu(DWORD errcode) {
   LPVOID buffer;
   //LPVOID display;
  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      errcode,
      MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT),
      (LPTSTR) &buffer,
      0, NULL );
  return String((wchar_t *)buffer);
}
void PrintWinError() {
  DWORD errcode = GetLastError();
  String errtext = GetWinErrorEng(errcode);
  String errtextru = GetWinErrorRu(errcode);
  wprintf(L"Error: %d %s", (int)errcode, errtext );
  std::wcout<<errtext << std::flush;
}

} // namespace winapi

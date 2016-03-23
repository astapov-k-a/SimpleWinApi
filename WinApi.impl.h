#ifndef WINAPI_H_IMPLEMENTATION_PERMIT_INCLUDE_ON
#   error Do not include this file - use "include WinApi.h"
#endif


#define WINDOW_CLASS_METHOD(ResultType, MethodName) template<typename DataTn> ResultType WindowClass<DataTn>::MethodName

#define WINDOW_CLASS_MEMBER(Typename, DataName) template<typename DataTn> Typename WindowClass<DataTn>::DataName

WINDOW_CLASS_MEMBER(struct, Params) {
  Params(
      DWORD style_arg = WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      DWORD style_extend_arg = 0,
      HWND parent_arg = 0,
      HMENU menu_arg = 0,
      const EventTable * events_arg = 0)
      : style_extend(style_extend_arg),
        style(style_arg),
        parent(parent_arg),
        menu(menu_arg),
        events(events_arg) {
  }
  explicit Params(const EventTable * events_arg)  {
    new (this) Params();
    events = events_arg;
  }
  DWORD style_extend;
  DWORD style;
  HWND parent;
  HMENU menu;
  const EventTable * events;
};

WINDOW_CLASS_METHOD(bool, Register) (
    UserMessageCallback user_callback_arg,
    HINSTANCE instance_arg) {
  user_callback(user_callback_arg);
  return WndClassEx::Register( &Callback, instance_arg, sizeof(This) );
}

//WINDOW_CLASS_METHOD(void, Unregister) () {
//  UnregisterClassEx(this);
//}

WINDOW_CLASS_METHOD(void, Destroy) () {
  DestroyWindow( handle() ); /// unregister производитс€ в деструкторе материнского класса
  handle( 0 );
}

WINDOW_CLASS_METHOD(WindowClass<DataTn> *, Create) () {
}

WINDOW_CLASS_METHOD(bool, Initialize) (
    const String & window_name,
    Position position,
    const Params & param_arg,
    HINSTANCE instance_arg,
    UserMessageCallback user_callback_arg) {
  if ( !Register(user_callback_arg, instance_arg) ) return 0;
  params(param_arg);
  if (param_arg.events != 0) {
    RegisterEvents(*param_arg.events);
  }
  HWND re = CreateWindowEx(
      param_arg.style_extend, //dwStyleEx
      window_class_name_ptr(),
      window_name.c_str(),
      param_arg.style,
      position.x,
      position.y,
      position.width,
      position.height,
      param_arg.parent,
      param_arg.menu,
      instance_arg,
      this );
  if (re == NULL) {
    Unregister();
  } else {
    handle(re);
  }  
  return re != NULL;
}

WINDOW_CLASS_METHOD(LRESULT CALLBACK, Callback) (HWND window, UINT message_arg,  WPARAM w_param, LPARAM l_param) {  
  This * sender = reinterpret_cast<This * >( GetWindowLongPtr(window, GWL_USERDATA) ); // до WM_NCCREATE не установлено
 if (message_arg == WM_NCCREATE) {
    SetLastError(0); //об€зательное условие дл€ обнаружени€ ошибки в SetWindowLongPtr
    LPCREATESTRUCT create_structure = (LPCREATESTRUCT)l_param;
    //sender = reinterpret_cast<This*>(l_param);
    This * object;    
    //object=reinterpret_cast<This*>(l_param);
    object=reinterpret_cast<This*>(create_structure->lpCreateParams);
    This * previous_data=reinterpret_cast<This*>(SetWindowLongPtr(window,GWL_USERDATA,(LONG_PTR)object)); // ≈сли успех - возвращает предыдущее значение. ¬озвращает ноль как если ошибка, так и если предыдущее значение равно нулю
    PrintWinError();
    UASSERT(previous_data!=0 || GetLastError()==0 , "CreateWindow error - zero data pointer", Error);
    sender = object;
    //return DefWindowProc(window, message_arg, w_param, l_param);
 }
 if ( sender ) {
  LRESULT re = sender->MessageCycleProcessor(window, static_cast<MessageCode>(message_arg), w_param, l_param);
  if (message_arg == WM_DESTROY) {
    PostQuitMessage(0);
  }
  return re;
 } else {
   return DefWindowProc(window, message_arg, w_param, l_param);
 }
}

WINDOW_CLASS_METHOD(LRESULT CALLBACK, MessageCycleProcessor) (HWND window, MessageCode message_code,  WPARAM w_param, LPARAM l_param) {
  LRESULT re = 0;
  //MessageCode message_code = static_cast<MessageCode> (message_arg);
  //std::wcout << std::to_wstring(message_code) <<std::endl; //@debug
  bool need_continue = 1;
  if (message_code == MessageCode::Command) { /// @debug
    volatile int x = 0;
    ++x;
  }
  if (events().count( message_code ) ) {
    EventCallback event = get_events()[message_code];
    event(*this, data(), w_param, l_param, need_continue);
  }
  if (need_continue) {
    auto user_fun = user_callback();
    if (user_fun) {
      re = user_fun(window, static_cast<UINT>(message_code), w_param, l_param, need_continue);
    }
    if (need_continue) {
      return DefWindowProc(window, static_cast<UINT>(message_code), w_param, l_param);
    } else {
      return re;
    }
  }
  return re;
}

WINDOW_CLASS_METHOD(void, RegisterEvent) (MessageCode message_code, EventCallback function) {
  get_events()[message_code] = function;
}
  
WINDOW_CLASS_METHOD(void, UnregisterEvent) (MessageCode message_code) {
  get_events().remove(message_code);
}


WINDOW_CLASS_METHOD(void, RegisterEvents) (const EventTable & from) {
#if _MSC_VER >=1800
  for ( const auto & it : from) {
    RegisterEvent(it.code, it.callback);
  }
#else
  const EventEntry * current = (from);
  enum {kMaxEventsEntry = 500};
  for (Size count = kMaxEventsEntry; current->callback && count; ++current, --count) {
    RegisterEvent(current->code, current->callback);
  }
#endif
}

typedef WindowClass<int> WindowClassDebug;
#undef WINDOW_CLASS_METHOD
#undef WINDOW_CLASS_MEMBER

#undef  WINAPI_H_IMPLEMENTATION_PERMIT_INCLUDE_ON
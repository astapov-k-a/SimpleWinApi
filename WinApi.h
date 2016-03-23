#ifndef   WIN_API_H_PROTECT_SIGNATURE_FDSALLKJNHGGA
#define   WIN_API_H_PROTECT_SIGNATURE_FDSALLKJNHGGA

#include <windows.h>
#include <windowsx.h>
#include <WinUser.h>

#include <string>
#include <memory>
#include <new>
#include <map>
#include <vector>

#include <commctrl.h>
#include "resource.h"
 
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(lib, "Shell32.lib")


#define UERROR(error_message, object_to_throw) printf("\n\n\nERROR!!! %s, at file = %s line = %s", error_message, __FILE__, __LINE__);
#define UASSERT(condition, error_message, object_to_throw) {if (!(condition)) UERROR(error_message, object_to_throw);}

namespace winapi {

#include "WinMessageCodes.h"

typedef wchar_t Char;
typedef std::wstring String;
typedef unsigned long Size;
typedef  LRESULT (CALLBACK  * MessageCycleCallback)(HWND window, UINT message_arg,  WPARAM w_param, LPARAM l_param);
typedef  LRESULT (CALLBACK  * UserMessageCallback)(HWND window, UINT message_arg,  WPARAM w_param, LPARAM l_param, bool & continue_process_message);
typedef void (* KeyboardMouseCallbackType)(HWND , UINT , WPARAM , LPARAM ,void * );
enum {
  IDC_USER_START = 1111,
  IDC_LISTVIEW = IDC_USER_START + 0,
};

bool GetFolder(const String & title,const String & start_directory, HWND owner, String & out_selected_path);

String GetWinErrorEng(DWORD errcode);
String GetWinErrorRu(DWORD errcode);
void PrintWinError();

/// @details Отрицательные значения ширины значает, что правая кромка объекта будет подгонятся под правый край минус
///          указанная ширина. Аналогично с высотой
struct Position {
  Position(int x_arg, int y_arg, unsigned width_arg, unsigned height_arg)
      : x(x_arg),
        y(y_arg),
        width(width_arg),
        height(height_arg) {
  }
  int x;
  int y;
  int width;
  int height;
};
  
#pragma pack (push, 1)
class CreateStruct : public CREATESTRUCT {
 public:
  CreateStruct ();
  CreateStruct(void * create_params);
};
#pragma pack ( pop)

#pragma pack (push, 1)
class WndClassEx : protected WNDCLASSEX {
 public:
  typedef WndClassEx This;
  WndClassEx();
  ~WndClassEx() {Unregister();}

  bool Register(
      MessageCycleCallback callback = 0,
      HINSTANCE instance_arg = GetModuleHandle(NULL),
      Size sizeof_inherited = sizeof (This) );
  void Unregister();
  HWND GetHandle() const {return handle();}

 protected:
  ATOM atom() const {return atom_;}
  void atom(ATOM val) {atom_ = val;}
  bool IsInited() const  {return atom() != 0;}
  HWND handle() const {return handle_;}
  void handle(HWND value) {handle_ = value;}
  const Char * window_class_name_ptr() const {return lpszClassName;}
  void window_class_name_ptr(const Char * value) {lpszClassName = value;}
  String const &     window_class_name_storage() const {return window_class_name_;}
  String       & get_window_class_name_storage()       {return window_class_name_;}
  void SetWindowClassName(const String & value);
  HINSTANCE instance() const {return hInstance;}
  void instance(HINSTANCE value) {hInstance = value;}
  Size counter() const {return counter_;}
  void IncreaseCounter() {++counter_;}

 private:
  ATOM atom_;
  HWND handle_;
  String window_class_name_;
  static Size counter_;
};
#pragma pack ( pop)

struct EmptyStruct {};
/// @class WindowClass
/// @brief Шаблонный класс окна, построенный по паттерну "модель-представление"
/// @details Сам класс - представление, его шаблонный параметр - модель
/// @tparam DataTn - структура, которая содержит данные для бизнес-логики. Модель по паттерну "модель-представление"
/// @remarks Идея изначально была такова, что бизнес-логике не место в классе, который отвечает
///          за отображение данных. Поэтому бизнес-логика вынесена в шаблонный параметр.
///          Это максимально обобщённый с помощью статического полиморфизма паттерн MVC - "модель-представления"
///          Для тестирования аудита изменений директории FSFileWatcher это несколько избыточно,
///          но переделывать для отдельного случая уж точно смысла нет никакого
/// @author Астапов К.А.
template <typename DataTn = EmptyStruct>
class WindowClass : public WndClassEx {
 public:
  typedef DataTn Data;
  typedef WindowClass<Data> This;
  typedef std::unique_ptr<Data> DataPtr;
  typedef void * (*EventCallback) (This & caller, Data * user_data, WPARAM wParam, LPARAM lParam, bool & continue_process_message);
  typedef WinMessageCode MessageCode;
  typedef std::map<MessageCode, EventCallback> Events;
  struct EventEntry { MessageCode code; EventCallback callback; };
  struct Params;
  /// @typedef EventTable
  /// @brief   Используется для инициализации обработчиков событий.
  /// @details @ref RegisterEvents связывает каждый код оконного сообщения с обработчиком события,
  ///           и вызывает его, если в данное сообщение приходит в цикл обработки сообщений
#if _MSC_VER >=1800  // к сожалению, vs2012 не поддерживает списки инициализации для векторов - а без них EventTable теряет смысл. Приходится делать сишный массив, а в качестве указателя конца использовать поле с нулевым кэллбэком
  typedef std::vector<EventEntry> EventTable;
#else
  typedef EventEntry EventTable[];
#endif

  WindowClass() : data_(new (std::nothrow) Data) {}
  ~WindowClass() {Destroy();}

  This * Create();
  void RegisterEvents(const EventTable & from);
  void RegisterEvent(MessageCode, EventCallback);
  void UnregisterEvent(MessageCode);
  bool Initialize(
    const String & window_name,
    Position position,
    const Params & param_arg,
    HINSTANCE instance_arg = GetModuleHandle(NULL),
    UserMessageCallback user_callback_arg = nullptr );

  
 protected:
  friend typename Data;
  bool Register(
      UserMessageCallback user_callback_arg = 0,
      HINSTANCE instance_arg = GetModuleHandle(NULL) );
  //void Unregister();
  WndClassEx * parent() {return (WndClassEx*)this;}
  void Destroy();  

  Data* data() const {return data_.get();}
  void  data(Data * val) {data_.reset(val);} //data_ = val;}
  Events const &     events() const {return events_;}
  Events       & get_events()       {return events_;}
  Params const &     params() const {return params_;}
  Params       & get_params()       {return params_;}
  void params(const Params & value) {params_ = value;}
  UserMessageCallback user_callback() const {return user_callback_;}
  void user_callback(UserMessageCallback value) {user_callback_ = value;}

 private:
  static LRESULT CALLBACK Callback(HWND window, UINT message_arg,  WPARAM w_param, LPARAM l_param);
  /// @brief   Основной метод обработки сообщений Windows - запускает пользовательские события и пользовательский кэллбек
  /// @details Если есть пользовательское событие, связанное с сообщением - запускает его.
  ///          Если события нет или оно возвращает статус "продолжать обработку сообщений", то
  ///          запускает пользовательский кэллбек (если есть)
  ///          Если пользовательского кэллбека нет, или он возвращает статус "продолжать обработку сообщений", то
  ///          передаёт обработку сообщения Windows
  /// @remark Пользовательский кэллбек - это хак на крайний случай. Используйте его только тогда,
  ///         когда нельзя обойтись пользовательскими событиями.
  LRESULT CALLBACK MessageCycleProcessor(HWND hWnd, MessageCode message,  WPARAM wParam, LPARAM lParam);

  DataPtr data_;
  Events events_;
  Params params_;
  UserMessageCallback user_callback_;
};

struct MessageStruct {
  typedef WinMessageCode MessageCode;
  void Send(HWND receiver) {
    if (message != MessageCode::Null) SendMessage(receiver, message, w_param, l_param);
  }

  MessageCode message;
  WPARAM w_param;
  LPARAM l_param;
};

/// @remarks изначально была одна структура - Message, но в виду устаревшего VS 2012, не желавшего статически инициализировать их
///          через фигурные скобки списков инициализации, пришлось поделить их на class Message и структуру struct MessageStruct
class Message : public MessageStruct {
 public:
  typedef WinMessageCode MessageCode;
  Message() {
    message = MessageCode::Null;
    w_param = 0;
    l_param = 0;
  }
  Message(MessageCode message_code, WPARAM w_param_arg, LPARAM l_param_arg) {
    message = message_code;
    w_param = w_param_arg;
    l_param = l_param_arg;
  }
};

class Control;

class ControlBody {
public:
  typedef WndClassEx Parent;
  typedef ControlBody This;
  //typedef std::shared_ptr<This> ThisPtr;
  typedef This * ThisPtr;
  typedef WinMessageCode MessageCode;
  class Params;
  struct ParamsStruct;
  class Params;
  enum {
    height_decrease = 50,
    width_decrease =  0
  };
  ControlBody()
      : handle_(0),
        parent_handle_(0),
        parent_(0) {
  }
  bool Construct(HWND parent_handle_arg, Parent * parent_object_arg, Size id_arg,  Position position, Params param);
  void Deconstruct();

 protected:
  static bool Create(HWND parent_handle_arg, Parent * parent_object_arg, Size id, Position position, const Params& param,
                     ControlBody::ThisPtr & out_created_object);
  HWND handle() const {return handle_;}
  void handle(HWND value) {handle_ = value;}
  HWND parent_handle() const {return parent_handle_;}
  void parent_handle(HWND value) {parent_handle_ = value;}
  Parent * parent() const {return parent_;}
  void parent(Parent * value) {parent_ = value;}

 private:
  friend class Control;

  HWND handle_;
  HWND parent_handle_;
  Parent * parent_;
};


/// @remarks изначально была одна структура - @ref ControlBody::Params, но в виду устаревшего VS 2012, не желавшего статически
///          инициализировать их через фигурные скобки списков инициализации, пришлось поделить их на
///          @ref Message "class Message" и структуру @ref MessageStruct "struct MessageStruct"
struct ControlBody::ParamsStruct {
  DWORD control_flags;
  DWORD icc;
  MessageStruct final_message;
  Char * class_name;
};
class ControlBody::Params : public ControlBody::ParamsStruct {
 public:
  Params(DWORD control_flags_arg, DWORD icc_arg) {
    control_flags = control_flags_arg;
    icc = icc_arg;
    new (&final_message) Message();
  }
  Params(DWORD control_flags_arg, DWORD icc_arg, const Message & message_arg ) {
    control_flags = control_flags_arg;
    icc = icc_arg;
    new (&final_message) Message(message_arg);
  }
};

class Control {
 public:
  typedef ControlBody Body;
  typedef Body::Parent Parent;
  typedef Body::Parent MessageCode;
  typedef Body::Params Params;
  typedef Body::ParamsStruct ParamsStruct;
  typedef std::unique_ptr<Body> BodyPtr;
  typedef Control This;

  Control() : body_(nullptr) {}
  virtual ~Control() {}
  virtual const Params & GetParam() const = 0;
  bool Initialize(HWND parent_handle_arg, Parent * parent_object_arg,  Position position);
  HWND GetHandle() const {return body().handle();}
  Size id() const {return id_;}

 protected:
  Body const &     body() const {return *body_;}
  Body       & get_body()       {return *body_;}
  Body  * bodyptr() const {return body_.get();}
  void bodyptr(Body * val) {body_.reset(val);}
  void IcreaseIdCounter() {++id_counter_;}
  Size id_counter() const {return id_counter_;}
  void GenerateId() {id_ = id_counter_;}

 private:
   BodyPtr body_;
   static Size id_counter_;
   Size id_;
};

class ListView : public Control {
 public:
  typedef Control Superclass;
  virtual const Params & GetParam() const;
  void Clear();
  bool Add(const String & item);
  void Delete(int index) {ListView_DeleteItem( GetHandle(), index );}
  int SetColumns(int colNum, const String * header);
  Size GetNumberItems() const {return ListView_GetItemCount( GetHandle() );}

 protected:
   //using Superclass::Initialize;

 private:
   static const ParamsStruct params_;
};

class Button : public Control {
 public:
  typedef Control Superclass;
  virtual const Params & GetParam() const;
  void SetText(const String & text) {SetWindowText( GetHandle(), text.c_str() );}

 protected:
   //using Superclass::Initialize;

 private:
   static const ParamsStruct params_;
};

class StaticText : public Control {
 public:
  typedef Control Superclass;
  virtual const Params & GetParam() const;
  void SetText(const String & text) {SetWindowText( GetHandle(), text.c_str() );}

 protected:
   //using Superclass::Initialize;

 private:
   static const ParamsStruct params_;
};

#define WINAPI_H_IMPLEMENTATION_PERMIT_INCLUDE_ON
#include "WinApi.impl.h"

} // namespace winapi

#endif // WIN_API_H_PROTECT_SIGNATURE_FDSALLKJNHGGA

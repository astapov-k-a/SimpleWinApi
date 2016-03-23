#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <new>
#include <mutex>

class DbgFlush {};
class DbgNl {};

class StdFile {
 public:
  typedef StdFile This;
  typedef std::wstring FString;
  typedef std::wfilebuf FileBuffer;
  typedef std::wostream Stream;
  typedef std::unique_ptr<Stream> StreamPtr;
  ~StdFile() {Close();}

  void Open(const FString & name , std::ios_base::openmode mode = std::ios_base::app );
  void Close();
  void Flush() {*get_stream() << std::flush;}

  template <typename ToPrintType> This & operator<<( const ToPrintType & to_print);

 protected:
  FileBuffer const &     buffer() const {return buffer_;}
  FileBuffer       & get_buffer()       {return buffer_;}
  StreamPtr const &     stream() const {return stream_;}
  StreamPtr       & get_stream()       {return stream_;}

 private:
  FileBuffer buffer_;
  StreamPtr stream_;
};

template <typename ToPrintType> StdFile & StdFile::operator<<( const ToPrintType & to_print) {
  *get_stream() << to_print;
  return *this;
}

class DebugLog
{
 public:
  typedef DebugLog This;
  typedef std::wstring FString;
  typedef wchar_t Char;
  typedef std::mutex Locker;
  enum NeedPrint {kNoPrint = 0, kPrint = 1};
  
  DebugLog(void);
  DebugLog(const Char * name);
  ~DebugLog(void);

  void Initialize(const Char * name);
  void Initialize(const Char * name, NeedPrint value);
  template <typename ToPrintType> This & operator<<( const ToPrintType & to_out);  
  template <typename ToPrintType> This & out( const ToPrintType & to_print, NeedPrint need_print = kPrint );
  void Flush();
  void PrintOn()  {last_need_print = kPrint;}
  void PrintOff() {last_need_print = kNoPrint;}
  void SetPrintStatus(NeedPrint value) {last_need_print = value;}
  void Lock() {locker.lock();}
  void Unlock() {locker.unlock();}

 protected:
  void backup(const Char * name,int count = 0, int max = 15);
  StdFile file;
  int last_need_print;
  bool logoff;
  Locker locker;
};

template <typename ToPrintType> DebugLog & DebugLog::operator<<( const ToPrintType & to_print) {
  out(to_print, static_cast<NeedPrint>(last_need_print) );
  return *this;
}

template <typename ToPrintType> DebugLog & DebugLog::out( const ToPrintType & to_print, NeedPrint need_print) {
  last_need_print = need_print;
  if (need_print == kPrint) {
    std::wcout<< to_print;
  }
  file << to_print;
  return *this;
}

template <> DebugLog & DebugLog::out(const DbgFlush& , NeedPrint need_print);
template <> DebugLog & DebugLog::operator<<( const DbgFlush & to_print);
template <> DebugLog & DebugLog::out(const DbgNl& , NeedPrint need_print);
template <> DebugLog & DebugLog::operator<<( const DbgNl & to_print);


extern std::wstring to_wstring(const std::string & str);
extern std::wstring to_wstring(const char * str);

extern DebugLog g_DebugLog;
extern const DbgFlush dbgflush;
extern const DbgNl dbgnl;


class FalseDebugLog
{
 public:
  typedef FalseDebugLog This;
  typedef std::wstring FString;
  typedef wchar_t Char;
  enum NeedPrint {kNoPrint = 0, kPrint = 1};
  
  FalseDebugLog(void){}
  FalseDebugLog(const Char *){}
  ~FalseDebugLog(void){}

  void Initialize(const Char * ){}
  void Initialize(const Char * , NeedPrint ) {}
  template <typename ToPrintType> This & operator<<( const ToPrintType & ) {return *this;}
  template <typename ToPrintType> This & out( const ToPrintType & , NeedPrint ) {return *this;}
  void Flush(){}
  void PrintOn()  {}
  void PrintOff() {}
  void SetPrintStatus(NeedPrint ) {}

 protected:
  void backup(const Char, int, int);
};

class ThreadSafeLogger {
 public:
  typedef ThreadSafeLogger This;
  typedef DebugLog Log;
  typedef Log::NeedPrint NeedPrint;
  ThreadSafeLogger(Log & log_arg) : log(&log_arg) {log_arg.Lock();}
  ~ThreadSafeLogger() {log->Unlock();}
  template <typename ToPrintType> This & operator<<( const ToPrintType & to_out) {log->operator<<(to_out); return *this;}
  template <typename ToPrintType> This & out( const ToPrintType & to_print, NeedPrint need_print = kPrint ) {log->out(to_print, need_print); ; return *this;}
 private:
  Log * log;
};

#ifdef DEBUG_LOGGING_
#   define DEBUGLOG() (ThreadSafeLogger(g_DebugLog) << L"\nat " << to_wstring(__FILE__) << L" in " << to_wstring(__FUNCTION__ ) << L", ln." << __LINE__ <<L" ")
#   define DEBUGMARK {ThreadSafeLogger(g_DebugLog) << L"\nat " << to_wstring(__FILE__) << L" in " << to_wstring(__FUNCTION__ ) << L", ln." << __LINE__ <<L" MARK "<<dbgflush;}
#else
#   define DEBUGLOG() (FalseDebugLog())
#   define DEBUGMARK
#endif
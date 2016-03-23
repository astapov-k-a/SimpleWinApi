#include "stdafx.h"
#include "DebugLog.h"
#include <assert.h>
#include <iostream>

std::wstring GetExeName() {
 WCHAR path[MAX_PATH];
 int len = GetModuleFileNameW(NULL, path, MAX_PATH );
 std::wstring re;
 re.assign(path, len);
 return re;
}


int LastDot(const DebugLog::FString & string) {
  DebugLog::Char const * base = string.c_str();
  -- base;
  for (unsigned count = string.size(); count; --count) {
    if (base[count] == L'.') {
      return count - 1;
    }
  }
  return 0;
}

DebugLog::FString RemoveExt(const DebugLog::FString & name) {
  int dot = LastDot(name);
  if (dot) {
    return name.substr(0, dot);
  } else {
    return name;
  }
}

bool FileExists(LPCTSTR fname)
{
  return ::GetFileAttributes(fname) != DWORD(-1);
}


void StdFile::Open(const FString & name , std::ios_base::openmode mode) {
  bool re = get_buffer().open(name, mode);
  if (!re) std::wcout<< L"\n\nStdFile::Open failed\n\n";
  assert(re);
  get_stream().reset(  new (std::nothrow) Stream( &get_buffer() )  );
}

void StdFile::Close() {
  if ( buffer().is_open() ) {
    get_buffer().close();
  }
}

DebugLog::DebugLog(const Char * name) : last_need_print(kPrint) , logoff(0) {
  Initialize(name);
}

DebugLog::DebugLog(void) : last_need_print(kPrint) , logoff(0) {
  Initialize( RemoveExt(GetExeName()).append(L".dlog").c_str() );
}


DebugLog::~DebugLog(void)
{
}
void DebugLog::Initialize(const Char * name, NeedPrint value) {
  last_need_print = value;
  Initialize(name);
}

void DebugLog::Initialize(const Char * name) {
  backup(name);
  file.Open(name);
}


void DebugLog::backup(const Char * name,int count,int max)
{
FString bckname=name;
if ( (count!=0) && (count<max) ) {
   FString nm = name;
   nm = RemoveExt(name);
   FString add = L".old_";
   add.append(std::to_wstring(count));
   bckname=nm+add;
   }
if (FileExists(name)) {
   if (count!=max) backup(bckname.c_str(),count+1,max);
   CopyFile(name,bckname.c_str(),0);
   DeleteFile(name);
   }
};

int StringToWString(std::wstring &ws, const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());

    ws = wsTmp;

    return 0;
}

void DebugLog::Flush() {
  if (last_need_print == kPrint) {
    std::wcout << std::flush;
  }
  file.Flush();
}

std::wstring to_wstring(const std::string & str) {
  std::wstring re(str.begin(), str.end());
  return re;
}
std::wstring to_wstring(const char * str) {
  return to_wstring( std::string(str) );
}

template <> DebugLog & DebugLog::out(const DbgFlush& , NeedPrint need_print) {
  if (need_print == kPrint) {
    std::wcout<< std::flush;
  }
  file.Flush();
  return *this;
}

template <> DebugLog & DebugLog::operator<<( const DbgFlush & ) {
  Flush();
  return *this;
}


template <> DebugLog & DebugLog::out(const DbgNl& , NeedPrint need_print) {
  out(L"\n", need_print);
  return *this;
}

template <> DebugLog & DebugLog::operator<<( const DbgNl & ) {
  operator<<(L"\n");
  return *this;
}

DebugLog g_DebugLog;//(L"e:\\W\\WinFsWatcher\\debuglog.log");
const DbgFlush dbgflush;
const DbgNl dbgnl;
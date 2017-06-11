#include "crk/util.h"

#include <codecvt>
#include <locale>

using namespace std;

namespace crk {

std::string wc2s(const wchar_t& wc) {
  std::wstring ws(1, wc);
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.to_bytes(ws);

}

std::wstring s2ws(const std::string& str)
{

  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  wstring ret;
  try {
    ret = converterX.from_bytes(str);
  } catch (...) {
    return wstring();
  }
  return ret;
}

std::string ws2s(const std::wstring& wstr)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  string ret;
  try {
    ret = converterX.to_bytes(wstr);
  } catch (...) {
    return string();
  }
  return ret;
}


} // namespace crk


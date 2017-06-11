#ifndef _CRK_UTIL_H_
#define _CRK_UTIL_H_

#include <string>

namespace crk {

// handle chinese character
std::string wc2s(const wchar_t& wc);

std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& wstr);


} // namespace crk

#endif // _CRK_UTIL_H_

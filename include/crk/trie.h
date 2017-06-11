#ifndef _CRK_TRIE_H_
#define _CRK_TRIE_H_

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

namespace crk {
class Node {
public:
  Node(wchar_t str) : str_(str) {}
  wchar_t str_;
  // {region_code, string of name}
  std::vector<std::pair<std::string, std::string>> region_codes_;
  std::unordered_map<wchar_t, Node*> next_;
};

class Trie {
public:
  Trie(std::vector<std::pair<std::string, std::wstring>>& locations);
  std::vector<std::pair<std::string, std::string>>& Find(
              const std::wstring& wstr);
  bool IsLevel(const wchar_t& wc);
  void debug();
private:
  Node* root_;
};

} // namespace crk

#endif // _ANALYZE_TRIE_H_

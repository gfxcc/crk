#include "crk/trie.h"

#include "crk/util.h"

namespace crk {
Trie::Trie(std::vector<std::pair<std::string, std::wstring>>& regions) {
  root_ = new Node(L' ');
  for (auto& p : regions) {
    Node* cur = root_;
    int len = p.second.size();
    for (int i = 0; i < len; i++) {
      auto& c = p.second[i];
      if (cur->next_.find(c) == cur->next_.end()) {
        cur->next_[c] = new Node(c);
      }
      cur = cur->next_[c];
      // pattern without last character(shi/xian/qu) should be count, like bei/jin should be treat as bei/jin/shi
      // TODO handle exceptions like zi/zhi/qu/ qun/dao
      if (i == len - 2 && i >= 1  && IsLevel(p.second[len - 1]))
        cur->region_codes_.emplace_back(p.first, ws2s(p.second));
    }
    // move to the end of the pattern
    cur->region_codes_.emplace_back(p.first, ws2s(p.second));
  }
}

std::vector<std::pair<std::string, std::string>>& Trie::Find(const std::wstring& wstr) {
  Node* cur = root_;
  for (auto& c : wstr) {
    if (cur->next_.find(c) == cur->next_.end()) {
      break;
    }
    cur = cur->next_[c];
  }
  return cur->region_codes_;
}


bool Trie::IsLevel(const wchar_t& wc) {
  std::vector<wchar_t> levels = {L'省', L'市', L'区', L'州', L'盟', L'县', L'旗'};
  for (auto& c : levels)
    if (c == wc)
      return true;
  return false;
}


void Trie::debug() {
  std::cout << "size of first level:" << root_->next_.size() << std::endl;
  for (auto& p : root_->next_) {
    std::cout << wc2s(p.first) << std::endl;
  }
}

} // namespace crk

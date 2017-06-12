//
// created by Yong Cao at Jun/10/2017
//

#ifndef _CRK_CRK_H_
#define _CRK_CRK_H_

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace crk {

struct Options {
  std::string model_segmentor;          // path to segmentor model file
  std::string model_postagger;          // path to postagger model file
  std::string region_data;              // path to region data directory
};

struct Status {
  int ret;
  std::string msg;

  bool ok() { return ret == 0; }
};

class Trie;

class Engine {
public:
  static Status CreateEngine(const Options& options, Engine** engine_ptr);

  Engine() { }
  virtual ~Engine();

  // regions return matched region code pair <region_name, region_code>
  // multiple region might be matched, so the regions was organizaed
  // by two dimensional vector
  int MatchRegion(const std::string& input,
      std::vector<std::vector<std::pair<std::string, std::string>>>& regions);

private:
  // recursively load region data from directory
  int LoadRegionDataFromDir(const std::string& path);
  int LoadRegionDataFromFile(const std::string& path);


  std::vector<std::pair<std::string, std::wstring>> regions_;
  // trie
  Trie* trie_;
  // ltp engines
  void* segmentor_engine_;
  void* postagger_engine_;
};

} // namespace crk


#endif // _ANALYZE_CRK_H_

//
// created by Yong Cao at Jun/10/2017
//
//

#include "crk/crk.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <json.hpp>
#include <ctype.h>

#include "crk/util.h"
#include "crk/trie.h"
#include "ltp/segment_dll.h"
#include "ltp/postag_dll.h"

using namespace std;
using nlohmann::json;

namespace crk {

Status Engine::CreateEngine(const Options& options, Engine** engine_ptr) {
  Status s;

  Engine* engine = new Engine();
  engine->segmentor_engine_ = segmentor_create_segmentor(options.model_segmentor.c_str());
  if (!engine->segmentor_engine_) {
    s.msg = "Error: faild to load segmentor model";
    s.ret = -1;
    return s;
  }
  engine->postagger_engine_ = postagger_create_postagger(options.model_postagger.c_str());
  if (!engine->postagger_engine_) {
    s.msg = "Error: faild to load postagger model";
    s.ret = -2;
    return s;
  }

  if (engine->LoadRegionDataFromDir(options.region_data) != 0) {
    s.msg = "Error: faild to load region data";
    s.ret = -3;
    return s;
  }

  engine->trie_ = new Trie(engine->regions_);

  *engine_ptr = engine;
  s.ret = 0;
  return s;
}

Engine::~Engine() {
  segmentor_release_segmentor(segmentor_engine_);
  postagger_release_postagger(postagger_engine_);
}


int Engine::MatchRegion(const std::string& input,
    std::vector<std::vector<std::pair<std::string, std::string>>>& regions) {

  vector<string> words;
  int len = segmentor_segment(segmentor_engine_, input, words);

  unordered_map<string, string> regions_map;
  for (int i = 0; i < len; i++) {
    auto& word = words[i];
    auto& ret = trie_->Find(s2ws(word));
    for (auto& ele : ret) {
      auto iter = regions_map.find(ele.first);
      if (iter == regions_map.end()) {
        regions_map.insert(iter,
                           unordered_map<string, string>::value_type(
                             ele.first, ele.second
                             )
                          );
      }
    }
  }

  vector<pair<string, string>> vec;
  for (auto& region : regions_map) {
    vec.push_back(region);
  }
  regions.push_back(move(vec));
  return 0;
}

int Engine::LoadRegionDataFromDir(const std::string& path) {
  int ret = 0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(path.c_str())) == NULL) {
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    string filename(dirp->d_name);
    switch (dirp->d_type) {
      case DT_REG:
        // load file
        ret = LoadRegionDataFromFile(path + "/" + filename);
        if (ret != 0) {
          return ret;
        }
        break;
      case DT_DIR:
        if (filename != "." && filename != "..") {
          // recursivly load folder
          ret = LoadRegionDataFromDir(path + "/" + filename);
          if (ret != 0) {
            return ret;
          }
        }
        break;
      default:
        break;
    }
  }
  closedir(dp);
  return 0;

}

int Engine::LoadRegionDataFromFile(const std::string& path) {

  ifstream input(path);
  if (input.is_open() == false) {
    return -1;
  }
  json j;
  input >> j;

  for (auto it = j.begin(); it != j.end(); it++) {
    if (it.value().get<string>() == "城区")
      continue;
    regions_.emplace_back(it.key(), s2ws(it.value().get<string>()));
  }
  return 0;

}


} // namespace crk

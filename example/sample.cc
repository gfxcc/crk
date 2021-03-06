#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "crk/crk.h"

using namespace std;
using namespace crk;

int main() {

  Engine* engine;
  Options options;
  options.model_segmentor = "/home/yong/Program/project/crk/thirdparty/ltp/models/cws.model";
  options.model_postagger = "/home/yong/Program/project/crk/thirdparty/ltp/models/pos.model";
  options.region_data = "/home/yong/Program/project/crk/region_data/";
  Status s = Engine::CreateEngine(options, &engine);

  if (s.ok() == false) {
    cout << "Error: failed to create crk engine" << endl;
    return 0;
  }
  //
  ifstream input("/home/yong/Program/project/crk/example/input.txt");
  string line;
  while (getline(input, line)) {

    vector<vector<pair<string, string>>> regions;
    engine->MatchRegion(line, regions);

    for (auto& vec : regions) {
      for (auto& region : vec) {
        cout << region.first << ":" << region.second << endl;
      }
      cout << endl;
    }
  }

  delete engine;
  return 0;
}

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
  options.model_segmentor = "../thirdparty/ltp/models/cws.model";
  options.model_postagger = "../thirdparty/ltp/models/pos.model";
  options.region_data = "../region_data/";
  Status s = Engine::CreateEngine(options, &engine);

  //
  ifstream input("./input.txt");
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

# CRK - Chinese Region Kit

**crk** is an open source library which used to extract region tags
from chinese nature language

# Motivation
To create a library generate region tags from chinese nature language
[arbitrary chinese words] -> [ processed by CRK] -> [organized region tags]
"魅族集团位于广东省珠海市，我们的员工有来自河北，上海，四川成都的。"

              |
	     [CRK]
	      |
{
1."xxxxxx":"广东省", "xxxxxx":"珠海市"
2."xxxxxx":"四川省", "xxxxxx":"成都市"
3."xxxxxx":"上海市"
4."xxxxxx":"河北省"
}

**crk** relies on [LTP](https://github.com/HIT-SCIR/ltp) and [中国行政区划信息](https://github.com/gfxcc/data_location)

# Build

**crk** relies [cmake](https://cmake.org)

```
git clone https://github.com/gfxcc/crk
cd crk
cmake .
make
```

# Models
To use [LTP](https://github.com/HIT-SCIR/ltp), we need models.  
>1. [baidu](https://pan.baidu.com/share/link?shareid=1988562907&uk=2738088569)
>2. [...](...)


# Usage
* Add this into your code

```cpp
#include "crk.h"
using namespace crk;

```
* download model files and fill options with **absolutely path**
* add library **lcrk** into your makefile or cmakelists.txt


```
target_link_libraries(sample  
	crk
	)
```


# Code Example
```cpp
...
Engine* engine;
Options options;
options.model_segmentor = "/home/.../thirdparty/ltp/models/cws.model";
options.model_postagger = "/home/.../thirdparty/ltp/models/pos.model";
options.region_data = "../region_data/";

Status s = Engine::CreateEngine(options, &engine);

vector<vector<pair<string, string>>> regions;
engine->MatchRegion(line, regions);
...
```
Please check details in `example/sample.cc`

# API Reference
```cpp
  // regions return matched region code pair <region_code, region_name>
  // multiple region might be matched, so the regions was organizaed
  // by two dimensional vector
  int MatchRegion(const std::string& input,
      std::vector<std::vector<std::pair<std::string, std::string>>>& regions);
```


# Tests


```
"善领汽电集团旗下专门负责4S店集团及特殊渠道运营的销售服务公司，代理众易畅、任我通、艾酷等多个知名品牌，经营项目：DVD导航、大屏机、原车屏升级、360全景、智能云镜、记录仪、脚踏板、行李架、前后大包围、电动踏板、电动尾门；美容镀晶等",
"440300": "深圳市"

"新疆特产：葡萄干、若羌大枣、和田大枣、巴旦木、纸皮核桃、无花果、精河枸杞、木垒鹰嘴豆、昆仑山胎菊、大漠肉苁蓉、伊犁薰衣草。绿色、天然、健康。"
"652722": "精河县",
"652824": "若羌县",
"653201": "和田市",
"653221": "和田县"


"学校发布信息，教育咨询交流 无锡市长安中心小学"
"130102": "长安区",
"320200": "无锡市",
"610116": "长安区"

```

# Projects built on CRK

* [wechat_location_analyze_tool](https://github.com/gfxcc/wechat_location_analyze_tool)

# TODO
Analyzing multiple regions code and generating organized tags

```
魅族集团位于广东省珠海市，我们的员工有来自河北，上海，四川成都的。
{
1."xxxxxx":"广东省", "xxxxxx":"珠海市"
2."xxxxxx":"四川省", "xxxxxx":"成都市"
3."xxxxxx":"上海市"
4."xxxxxx":"河北省"
}
```

# License
limited by license from [LTP](https://github.com/HIT-SCIR/ltp)






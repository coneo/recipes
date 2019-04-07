这里a.cpp b.cpp都包含了common.h，在common.h中用宏定义了RT的值，这里a.cpp自己又重新定义了RT的变量。

```
#include "a.cpp" // 重新定义了RT=22
#include "b.cpp"
#include "main.cpp"
```
这种方式，b.cpp的RT值也会受a.cpp重新定义的影响，但b.cpp设计初衷是希望引用common.h中的RT

```
#include "b.cpp"
#include "a.cpp" // 重新定义了RT=22,但是b.cpp不会受影响
#include "main.cpp"
```
换了下包含cpp的顺序，结果就不一样了，b.cpp还是用的common.h中的RT。

这就很坑了！

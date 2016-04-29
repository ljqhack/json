##JSON简介
###1.数据类型
* JSON包含4种基础类型（字符串，数字，布尔和null）和两种结构类型（对象和数组）; 
* 字符串是一个由零或者多个Unicode字符组成的序列; 
* 对象是一个由零或者多个名/值对组成的无序集合，其中名/值对中名是字符串类型，值则可以是字符串，数字，布尔，null，对象或数组类型;
* 数组是一个由零或者多个值组成的有序序列。

###2.语法

一个JSON文本是一个标记（token）序列，标记包含6种结构字符，字符串，数字和3个字面量。一个JSON文本是一个对象或者数组的序列化结果。
```
JSON - text = object / array
```
下面是6种结构字符：
```
begin - array      = ws % x5B ws    [ 左中括号
begin - object     = ws % x7B ws    { 左大括号
end - array        = ws % x5D ws    ] 右中括号
end - object       = ws % x7D ws    } 右大扩号
name - separator   = ws % x3A ws    : 冒号
value - separator  = ws % x2C ws    , 逗号
```
6种结构字符前后都可以添加无意义的空白字符。
```
ws = * (
   % x20 / ; 空格
   % x09 / ; \ t 水平制表符
   % x0A / ; \ n 换行符
   % x0D   ; \ r 回车符
)
```
###3.值
JSON值是一个对象，数组，数字，字符串或下列三个字面量之一：
```
false null true
```
字面量必须是小写的，其他任何字面量都是不允许的。
```
value   = false / null / true / object / array / number / string
false   = % 0x66.61.6c.73.65  ； false
null    = % 0x6e.75.6c.6c     ； null
true    = % 0x74.72.75.65     ； true
```
###4.对象
对象结构表示为一对大括号包裹着0到多个名/值对（或者叫成员）。名/值对中名称是一个字符串，后面是一个冒号，用来分隔名称和值。值后面是一个逗号用来分隔值和下一个名/值对的名称。一个对象内的名称SHOULD是唯一的。
```
object = begin - object [ member * ( value - separator member ) ] end - object
member = string name - separator value
```
###5.数组
数组结构表示为一对中括号包裹着0到多个值（或者叫元素）,值之间用逗号分隔。
```
array = begin - array [ value * ( value - separator value ) ] end - array
```

###6.数字
数字的表示和其他大部分语言相似。
* 数字包含一个以可选的减号为前缀的整数部分，其后面可以跟有小数部分和/或指数部分;
* 八进制或者十六进制的形式是不允许的。以0开头也是不允许的;
* 小数部分是一个小数点后跟随一位或多位数字;
* 指数部分以不限大小写的字母E开头，之后可跟一个加号或减号;
* E和可选的符号后可 跟一位或多位数字;
* 不能被表示为数字的序列（例如，无穷大和NaN）的数字值是不允许的。
```
number          = [ minus ] int [ frac ] [ exp ]
decimal - point = % x2E                                 ; .
digit1 - 9      = % x31 - 39                            ; 1 - 9
e               = % x65 / % x45                         ; e E
exp             = e [ minus / plus ] 1 * DIGIT
frac            = decimal - point 1 * DIGIT
int             = zero / ( digit1 - 9 * DIGIT )
minus           = % x2D                                 ; -
plus            = % x2B                                 ; +
zero            = % x30                                 ; 0
```

###7.字符串
字符串的表示和C语言家族的处理方式相似。字符串用引号作为开头和结尾。除了以下一些必须被转义的字符以外所有的Unicode字符都可以直接被放在字符串中：引号（”或’），反斜杠(\)和控制字符（U+0000 到 U+001F）。
任何字符都可以被转义。如果是在基本多语言平面（Basic Multilingual Plane(U+0000到U+FFFF)）内，则应该表示为6字符序列：反斜杠后面跟一个小写字母u，再跟4位表示字符所在位置的16进制数字。16进制数字中的字母A-F可以是大写的，也可以是小写的。例如：一个只有一个反斜杠组成的字符串可以表示为”\u005C”。
另外，有一些流行的字符可以用两字符序列来转义，例如：一个只有一个反斜杠组成的字符串可以表示为”\\”。
要转义不在基本多语言平面（Basic Multilingual Plane）内的字符，则使用表示为UTF-16编码代理对（encoding the UTF-16 surrogate pair）的12字符序列。例如：一个只包含G谱字符（U+1D11E）的字符串可以被表示为”\uD834\uDD1E”
```
string          = quotation - mark * char quotation - mark
char            = unescaped / escape （
    0x22 /                                             ; " 引号 U+0022
    0x5C /                                             ; \ 反斜杠 U+005c
    0x2F /                                             ; / 斜杠 U+002F
    0x62 /                                             ; b 退格符 U+0062
    0x66 /                                             ; f 分页符 U+0066
    0x6E /                                             ; n 换行符 U+006E
    0x72 /                                             ; r 回车符 U+0072
    0x74 /                                             ; t 水平制表符 U+0074
    0x75 4HEXDIG                                       ; uXXXX U+XXXX
)
escape         = %x5C                                  ; \
quotation-mark = %x22                                  ; "
unescaped        = % x20 - 21 / % x23 - 5B / % x5D - 10FFFF
```
###8.编码
JSON文本SHALL使用unicode编码。默认的编码方式为UTF-8。
由于JSON文本的头两个字符一定是ASCII字符[RFC0020]，因此可以通过观察第一组4个8位字节来判断字节流是UTF-8,UTF-16（BE或LE）还是UTF-32（BE或LE）编码的。
```
00 00 00 xx UTF - 32BE
00 xx 00 xx UTF - 16BE
xx 00 00 00 UTF - 32LE
xx 00 xx 00 UTF - 16BE
xx xx xx xx UTF - 8
```

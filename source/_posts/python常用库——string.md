---
title: Python常用库——string
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
categories: 技术
date: 2021-9-26 15:15:36
comments: true
tags:
  - Python
  - Python stl
keywords: Python
description: Python常用库学习
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/89193760_p0.jpg
---

string 库是一个 Python 标准库, 主要包
含[字符常量](#字符常量)和[Formatter](#formatter), 这里我们主要了解 Formatter.

## 字符常量

不过多解释啦, 都是某一类字符组成的字符串.

```py
# 小写字母组成的字符串
print(f"All lowercase letters characters: {list(string.ascii_lowercase)}")

# 大写字母组成的字符串
print(f"All uppercase letters characters: {list(string.ascii_uppercase)}")

# 英文字母组成的字符串 ascii_letters = ascii_lowercase + ascii_uppercase
print(f"All letters characters: {list(string.ascii_letters)}")

# 十进制数字
print(f"All digits number characters: {list(string.digits)}")

# 十六进制数字
print(f"All hexdigits number characters: {list(string.hexdigits)}")

# 八进制数字
print(f"All octdigits number characters: {list(string.octdigits)}")

# 标点符号
print(f"All punctuation characters: {list(string.punctuation)}")

# 空白符号
print(f"All whitespace characters: {list(string.whitespace)}")

# 所有可打印的字符 printable = digits + ascii_letters + punctuation + whitespace
print(list(string.printable))

# All lowercase letters characters: abcdefghijklmnopqrstuvwxyz
# All uppercase letters characters: ABCDEFGHIJKLMNOPQRSTUVWXYZ
# All letters characters: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
# All digits number characters: 0123456789
# All hexdigits number characters: 0123456789abcdefABCDEF
# All octdigits number characters: 01234567
# All punctuation characters: !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
# All whitespace characters: [' ', '\t', '\n', '\r', '\x0b', '\x0c']
# ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', ' ', '\t', '\n', '\r', '\x0b', '\x0c']
```

[ 因为空白字符的打印在命令行不便查看, 使用列表将其变为字符形式 ]

## Formatter

### 基础使用

Formatter 是 string.py 包中定义的一个类, 其中定义了一个用于格式化字符串的方法:
format(这是我们主要使用的 API), 这是一个简单的例子:

```py
f = string.Formatter()
morning = "Good morning"

print(f.format("{greet}, {name}", name="Ranshi", greet=morning))

# output:
# Good morning, Ranshi
```

根据输出结果可以看出, 两个字符串被拼接起来了. 但是这种形式看起来并不是非常优雅,
因为我们还需要定义一个 string.Formatter 的对象, 然后才调用 format 方法. 其实,
Python 针对 str 对象就实现了 format 方法, 我们可以直接调用一个 str 对象的 format
方法.

```py
morning = "Good morning"

print("{greet}, {name}".format(name="Ranshi", greet=morning))

# output:
# Good morning, Ranshi
```

而在 python3.6 之后, 引入了 f-string 写法, 进一步地简化了格式化字符串的使用.

```py
morning = "Good morning"

print(f"{morning}, {'Ranshi'}")

# output:
# Good morning, Ranshi
```

相比起来是不是非常简单, 下文中我们就都用这种形式来书写格式化字符串.

在`{}`中可以使用"格式规格", 用于定义单个值如果格式到字符串中. 如果未指定则默认调
用`str()`函数.

一般形式如下:

`[[fill]align][sign][#][0][width][grouping_option][.precision][type]`

### 定位

格式化字符串有两种定位方式.

一种是将 format 函数接收的参数当作一个列表, 然后依次显示在每个`{}`中, 而`{}`中也
可以携带数字, 表示替换的是列表中的第几个元素.

```py
print("{0}, {1}, {2}".format("a", "b", "c"))

print("{}, {}, {}".format("a", "b", "c"))

print("{0}, {0}, {1}".format("a", "b"))

print("{1}, {0}, {2}".format("a", "b", "c"))

# output:
# a, b, c
# a, b, c
# a, a, b
# b, a, c
```

第二种是将 format 函数接收的字典参数, 然后对应在相应健的位置.

```py
print("{greet}, {name}".format(greet="goodbye", name="Ranshi"))

# output:
# goodbye, Ranshi
```

由于传入的参数是一个解包的列表或字典, 因此也可以将列表或字典解包后作为 format 函
数的参数.

```py
lst = ["a", "b", "c"]
print("{1}, {0}, {2}".format(*lst))

d = {"greet": "goodbye", "name": "Ranshi"}
print("{greet}, {name}".format(**d))

# output:
# b, a, c
# goodbye, Ranshi
```

### 格式化参数

#### 转换符

在`{}`中, 可以设置转换符, 设置后表达式结果会先转换, 再格式化. 转换符一共有
`s | r | a` 三种, 分别表示调用`str()`, `repr()`, `ascii()`. 在转换符前使用 `!`表
示需要转换.

```py
greet = "你好,\tRanshi"

print(f"{greet}")
print(f"{greet!s}")
print(f"{greet!r}")
print(f"{greet!a}")

# output:
# 你好,   Ranshi
# 你好,   Ranshi
# '你好,\tRanshi'
# '\u4f60\u597d,\tRanshi'
```

由此可见, 默认是调用`str()`方法.

#### `=` 格式化

在 Python 3.8 版本中, 可以使用 `=` 来进行格式化. 可以将变量格式化成 `s=str(s)`
的字符串. 并且可以在其中任意位置加入字符串.

```py
result = 15 * 32

print(f"{result=}!")
print(f"{  result=}!")
print(f"{result  =}!")

# output:
# result=480!
#   result=480!
# result  =480!
```

#### 对齐

[官方文档写的比我详细多了.](https://docs.python.org/zh-cn/3/library/string.html#format-specification-mini-language)

例子:

```py
x = 158

print(f"#{x:~<10}#")
print(f"#{x:~<+10}#")
print(f"#{x:~< 10}#")
print(f"#{-x:~<+10}#")
print(f"#{x:~^10}#")
print(f"#{x:~>10}#")

# output:
# #158~~~~~~~#
# #+158~~~~~~#
# # 158~~~~~~#
# #-158~~~~~~#
# #~~~158~~~~#
# #~~~~~~~158#
```

#### 进制转换

可以使用字符表示数字的进制.

- b => 二进制
- c => 字符, 将帧数转换为 unicode 字符
- d => 十进制
- o => 八进制
- x => 十六进制
- n => 数字, 与 'd' 相似, 当会使用当前区域来插入适当的数字分隔符.

```py
num = 105
print(f"{num:b}")
print(f"{num:c}")
print(f"{num:d}")
print(f"{num:o}")
print(f"{num:x}")
print(f"{num:n}")

# output:
# 1101001
# i
# 105
# 151
# 69
# 105
```

#### 特殊表示

千位分隔符:

```py
num = 1316513216513216513
print(f"{num:,}")

# output:
# 1,316,513,216,513,216,513
```

时间格式化:

```py
d = datetime.datetime.now()
print(f"{d:%Y-%m-%d %H:%M:%S}")

# output:
# 2021-09-26 13:51:05
```

百分比转换

```py
per = 0.35
print(f"{per:%}")

# output:
# 35.000000%
```

---
title: Markdown教程
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 正是你花费在玫瑰上的时间才使得你的玫瑰花珍贵无比
categories: 技术
date: 2020-11-08 15:37:36
comments: true
tags:
  - markdown说明
  - 博客编写指导
keywords: markdown
description: markdown常用说明
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/6.jpg
---

markdown 是一种学习成本很低的标记语言，也就是传说中的，易上手且易精通的语言。最近刚刚搭建好网站，也是第一次尝试写博客，打算趁此机会写一篇博客，并边写边学习 markdown 语言。

---

## Markdown 说明

Markdown 是一种轻量级标记语言，它允许人们使用易读易写的纯文本格式编写文档。 Markdown 语言在 2004 由约翰·格鲁伯（英语：John Gruber）创建。 Markdown 编写的文档可以导出 HTML 、Word、图像、PDF、Epub 等多种格式的文档。 Markdown 编写的文档后缀为 .md, 或.markdown。

---

## markdown 标题

markdown 标题有两种格式：一种是标题底下加分割线：

```
一级标题
===========

二级标题
------------
```

或者是# + 空格：

```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```

---

## markdown 段落格式

### markdown 字体

markdown 可以使用以下几种字体：

```
*斜体文本*
_斜体文本_
**粗体文本**
__粗体文本__
___粗斜体文本___
```

显示效果分别为：斜体： _斜体文本_ _斜体文本_ 粗体： **粗体文本** **粗体文本** 粗斜体： **_粗斜体文
本_**

### markdown 分割线

```
***
* * *
*****
- - -
----------
```

---

---

---

---

### markdown 特殊字体

~~删除线文本~~ `~~删除线文本~~`

<u>下划线文本</u> `<u>下划线文本</u>`

注脚[^脚注]

```
创建脚注格式类似这样 [^脚注]。
[^RUNOOB]: 菜鸟教程 -- 学的不仅是技术，更是梦想！！！
```

[^脚注]: 这是一个脚注

---

## markdown 列表

### markdown 无序列表

无序列表使用星号(\*)、加号(+)或是减号(-)作为列表标记，这些标记后面要添加一个空格，然后再填写内容：

```
* 第一项
    - 第一点

+ 第一项
    * 第一点

- 第一项
    + 第二点
```

- 第一项

  - 第一点

- 第一项

  - 第一点

- 第一项
  - 第一点

### markdown 有序列表

有序列表使用数字并加上 . 号来表示，如：

```
1. 第一项
2. 第二项
```

1. 第一项
2. 第二项

### markdown 列表嵌套

```
1. 第一项：
    - 第一项的第一个元素
    - 第一项的第二个元素
2. 第二项：
```

1. 第一项：
   - 第一项的第一个元素
   - 第一项的第二个元素
2. 第二项：

---

## markdown 分块

```
> 最外层
> > 第一层嵌套
> > > 第二层嵌套
```

> 最外层
>
> > 第一层嵌套
> >
> > > 第二层嵌套

### 与列表一起使用

```
* 第一项
>成为更好的自己
>才能守护最好的你
```

- 第一项

> 成为更好的自己才能守护最好的你

---

## markdown 代码

分为代码块和代码片：代码片是用反引号括起来的文字：

```
`这是一段代码片`
```

`这是一段代码片`

---

## markdown 链接

```
这是一个连接[ranshi](https://github.com/Zranshi)
```

这是一个连接[ranshi](https://github.com/Zranshi)

### 高级链接

我们可以通过变量来设置一个链接，变量赋值在文档末尾进行：

```
这个链接用 r 作为网址变量 [github][r]
这个链接用 s 作为网址变量 [ranshi][s]
然后在文档的结尾为变量赋值（网址）

  [r]: https://github.com/
  [s]: https://github.com/Zranshi
```

这个链接用 r 作为网址变量 [github][r] 这个链接用 s 作为网址变量 [ranshi][s] 然后在文档的结尾为变量赋
值（网址）

[r]: https://github.com/
[s]: https://github.com/Zranshi

---

## markdown 图片

Markdown 图片语法格式如下：

```
![alt 属性文本](图片地址)

![alt 属性文本](图片地址 "可选标题")
```

![ranshi头像](https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg)

---

## markdown 高级

### table

```
| Item     |    Value |  Qty  |
| :------- | -------: | :---: |
| Computer | 1600 USD |   5   |
| Phone    |   12 USD |  12   |
| Pipe     |    1 USD |  234  |
```

| Item     |    Value | Qty |
| :------- | -------: | :-: |
| Computer | 1600 USD |  5  |
| Phone    |   12 USD | 12  |
| Pipe     |    1 USD | 234 |

### Checkbox

You can use `- [ ]` and `- [x]` to create checkboxes, for example:

```
- [x] Item1
- [ ] Item2
- [ ] Item3
```

- [x] Item1

* [ ] Item2
* [ ] Item3

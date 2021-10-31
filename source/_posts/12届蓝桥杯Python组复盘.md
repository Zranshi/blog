---
title: 第12届蓝桥杯Python组复盘
date: 2021-4-19 21:51:15
author: Ranshi
avatar: https://i.loli.net/2021/10/27/quMyIgbaD6tURx5.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc: 成为更好的自己，才能守护最好的你
categories: 技术
comments: true
tags:
  - 蓝桥杯
  - Python
keywords: 比赛
description: 复盘12届蓝桥杯Python组,看看自己能否做得更好.
photos: https://i.loli.net/2021/04/19/S2hXdi7eWnzu5Fo.png
---

## 前言

以前都是报名第 C++ B 组的, 因为自己本身对 Python 更感兴趣, 所以这次选择报名 Python 试试, 反正钱是由
学院出的, 我就当是尝试一下呗.

结果这次就翻车了, 好多题没做出来. 可能是因为 Python 没有分组的原因吧, 或者我被分到了 A 组, 看了一下
C++ A 组的题目, 感觉果然是上当了, 和 A 组的题目基本是一样的, 唉, 只能祈求能拿个奖水一下了.

第一次参加蓝桥杯 Python 组, 不知道怎么书写, 就按照自己舒服的格式来了.

## 解题

---

### A 卡片

![A](https://i.loli.net/2021/04/19/mjzXKpk3B2Ql6YV.png) 第一时间就想到了用 python 的 collections 库
的 Counter 计数, 如果我是参加的 C++ 可能会专门列一个数组用来计数吧.

```python
def A():
    from collections import Counter
    cardNum = 2021
    cards = [cardNum] * 10

    def check(num: int) -> bool:
        c = Counter(str(num))
        for i in c:
            cards[int(i)] -= c[i]
            if cards[int(i)] < 0:
                return False
        return True

    index = 1
    while True:
        if not check(index):
            print(index - 1)
            return
        index += 1
```

---

### B 直线

![B](https://i.loli.net/2021/04/19/AtnIyZ6Pl5QKpUj.png)

当时看着就烦, 最讨厌写这种题目了, 于是就放着没写了.

#### 赛后解答

没想到意外的还挺简单的, 怎么办, 5 分没有了

我是将所有的直线都化作 y = ax + b 的形式, 这样 a,b 就不会有重复, 别人说的精度问题, 我没有遇到, 可能
python 不存在精度问题吧.

```python
def B():
    xList = [i for i in range(20)]
    yList = [i for i in range(21)]
    points = [(x, y) for x in xList for y in yList]
    s = set()
    res = 20 + 21

    def getLine(p, q):
        a = (q[1] - p[1]) / (q[0] - p[0])
        b = (p[0] * (p[1] - q[1]) + p[1] * (q[0] - p[0])) / (q[0] - p[0])
        return a, b

    for p in points:
        for q in points:
            if p != q and p[0] != q[0] and p[1] != q[1]:
                s.add(getLine(p, q))
    print(len(s) + res)
```

---

### C 货物摆放

![C](https://i.loli.net/2021/04/19/dylpUcwgihZAJW3.png)

我注意到 i，j，k 都是 Num 到因数，而且两两相乘也是 Num 的因数

我的做法就是用一个集合存储 2021041820210418 的所有因子，然后用三重循环暴力

需要注意的是一定不能强行遍历到 Num，肯定跑不出来的，在每次存因子时保存对应的因子就好了。

因为顺序不同算不同方案，所以直接暴力 😂

```python
def C():
    Num = 2021041820210418
    factors = set()

    for i in range(1, Num):
        if i in factors:
            break
        if Num % i == 0:
            factors.add(i)
            factors.add(Num // i)

    res = 0

    for i in factors:
        for j in factors:
            for k in factors:
                if i * j * k == Num:
                    res += 1
    print(res)
```

---

### D 路径

![D](https://i.loli.net/2021/04/19/m7Hfk2qsThwo9OY.png)

DP 题, 在 leetcode 上练习了一个多月 DP 的我只想说, 下一个!

```python
def D():
    import math

    def lcm(x, y: int) -> int:
        return x * y // math.gcd(x, y)

    dp = [float('inf')] * 2022
    dp[2021] = 0
    for i in range(2021, 0, -1):
        for j in range(i - 1, i - 22, -1):
            if j <= 0:
                break
            dp[j] = min(dp[j], dp[i] + lcm(i, j))
    print(dp[1])
```

---

### E 回路计算

![E](https://i.loli.net/2021/04/19/xU3FDj5QlnaCoBv.png)

这道题想了一个多小时, 写出来一个肯定暴时间的, Python 跑了 20 分钟, 硬是没跑出来

---

### F 时间

![F](https://i.loli.net/2021/04/19/UGXP5b1HZKWeas9.png)

没啥好说的，1 秒=1000 毫秒 考场的时候用样例推一下就好了

```python
def F():
    millisecond = int(input())
    second = millisecond % (1000 * 60 * 60 * 24) // 1000
    hour = second // (60 * 60)
    minute = second // 60 % 60
    second = second % 60

    def out(x: int) -> str:
        s = ""
        if x < 10:
            s += "0"
        s += str(x)
        return s

    s = out(hour) + ':' + out(minute) + ':' + out(second)
    print(s)
```

---

### G 杨辉三角

![G](https://i.loli.net/2021/04/19/RhZBaInNu6FSjK2.png)

我没搞懂为啥都说暴内存了，我是直接在原地处理每一层的

```python
def G():
    num = int(input())
    if num == 1:
        return 1
    pascal = [1, 1]
    index = 3
    while True:
        print(pascal)
        l = pascal[:]
        for i in range(1, len(l)):
            pascal[i] = l[i] + l[i - 1]
        pascal.append(1)
        if num in pascal:
            index += pascal.index(num) + 1
            print(index)
            return
        else:
            index += len(pascal)
```

---

### H 左孩子右兄弟

![H1](https://i.loli.net/2021/04/19/OsraP8SChLINdcp.png)

![H2](https://i.loli.net/2021/04/19/PfG3XFRhzkqHBNw.png)

同样是想了半天, 没想清楚就开始写了, 最后发现算法是错的, 崩溃了呜呜呜

赛后解答

比赛时直接使用的数组存储的, 结果发现要搜索子节点和父节点非常麻烦. 而且当时只考虑了根节点的情况, 然后
判断哪个分支最高(捂脸, 我好蠢, 明明是相似的结构). 写到半路发现不对劲, 原本树的高度和变成二叉树后的高
度没太大关系, 发现要递归. 最崩溃的是发现存储结构也要改一下, 最后没时间了, 就没写了.

在赛后, 我把我当时的想法分析了一下, 自己设计了一个数据结构. 我用一个 孩子列表 存储每个子节点在数组中
的下标, 然后用数组的下标表示节点的编号, 然后在结构体中使用 targetNode 表示父节点的编号. 这样在递归中
就可以很好地遍历整个树了.

然后我使用了贪心算法, 我认为要想获得最高的高度, 只需要在原树每一层中选取转化为二叉树后高度最高的分支
, 让其作为当前层的最下的一个节点, 这样就能获取最大的高度. ( 不过我没有证明)

```python
def H():
    class node():
        def __init__(self, targetNode):
            self.targetNode = targetNode
            self.childList = []

    n = int(input())
    tree = [None, node(targetNode=0)]
    for i in range(2, n + 1):
        target = int(input())
        tree.append(node(targetNode=target))
        tree[target].childList.append(i)

    def getMaxLength(n: node) -> int:
        if len(n.childList) != 0:
            return len(n.childList) + max(getMaxLength(tree[_next]) for _next in n.childList)
        return 1

    print(getMaxLength(tree[1]) - 1)
```

---

### I 异或数列

![I1](https://i.loli.net/2021/04/19/ZoIR76YM5HVpOPg.png)

![I2](https://i.loli.net/2021/04/19/nwmqvfbRyTaH2oA.png)

没时间了, 没看题

---

### J 括号序列

![J](https://i.loli.net/2021/04/19/5N1bXVneazlcjUx.png)

没时间了, 没看题

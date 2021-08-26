---
title: LeetCode——76. 最小覆盖子串
date: 2021-2-5 16:22:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - LeetCode
  - Python
  - 滑动窗口
keywords: LeetCode
description: 滑动窗口滑动窗口滑动窗口!
photos: https://i.loli.net/2021/02/05/dRWjIPvaNnAQF1K.jpg
---

今天在清理以前没做完的 LeetCode 题目时, 发现了这么一道困难题... 于是开始写题时间.

## 题目描述

给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

## 样例

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"

## 写题

最开始我想先用暴力解决, 然后慢慢优化.(万一暴力过了呢?😂)
以下是毫无参考意义的暴力解法:

```py
# 暴力写法，果然超时了
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        sc = Counter(s)
        tc = Counter(t)
        length, res = len(s), s

        def isHas(x: Counter, y: Counter) -> bool:
            for item in y:
                if y[item] > x[item]:
                    return False
            return True

        if isHas(sc, tc):
            for i in range(length):
                for j in range(i, length + 1):
                    print('s[i:j]: ', s[i:j], end=" ")
                    if res in s[i:j]:
                        print('continue')
                        continue
                    idx = Counter(s[i:j])
                    if isHas(idx, tc):
                        if len(res) > len(s[i:j]):
                            res = s[i:j]
                            print('success')
                            continue
                        print('has but not less')
                    print('not has')
        else:
            return ''
        return res
```

思路很暴力, 就是遍历所有子串. 去其中符合条件的最小的, 如果以前的答案包含在子串中, 则这个子串不考虑.

然后想到了滑动窗口来优化, 于是走上了漫漫改 bug 之路.

发现自己写的滑动窗口还是超时了... 好丢人

```py
# 没想到自己写的滑动窗口还是超时了...心累
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        length, res, left, right = len(s), s, 0, 0

        def isHas(x: str, y: str) -> bool:
            x, y = Counter(x), Counter(y)
            for item in y:
                if y[item] > x[item]:
                    return False
            return True

        if not isHas(s, t):
            return ''
        else:
            while right <= length:
                si = s[left:right]
                print('si: ', si)
                if isHas(si, t):
                    while isHas(si, t):
                        left += 1
                        si = s[left:right]
                        print('     left loop: ', si)
                    res = res if len(res) < len(s[left - 1:right]) else s[left - 1:right]
                    print("         res: ", res)
                right += 1
        return res
```

自己最终改良的滑动窗口, 提交后终于是过了, 但是时间不是很理想, 只有 20%

```py
# 自己改良的滑动窗口，每次更新不重新生成Counter对象了，改为修改Counter对象的值... 这么想我刚才好蠢，
# 但总算是能过了... 不容易呀
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        length, res, left, right = len(s), s, 0, 1
        sc, tc = Counter(s), Counter(t)

        def isHas(x: Counter, y: Counter) -> bool:
            for item in y:
                if y[item] > x[item]:
                    return False
            return True

        if not isHas(sc, tc):
            return ''
        else:
            sc = Counter()
            while right <= length:
                sc[s[right - 1]] += 1
                print('si: ', s[left:right])
                if isHas(sc, tc):
                    while isHas(sc, tc):
                        sc[s[left]] -= 1
                        left += 1
                        print('     left loop: ', s[left:right])
                    res = res if len(res) < len(s[left - 1:right]) else s[left - 1:right]
                    print("         res: ", res)
                right += 1
        return res
```

最后学习题解大佬的解法.

```py
# 大佬的滑动窗口和我的滑动窗口为啥差别这么大呢。
# 瞬间 99.84% tql
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = defaultdict(int)
        for c in t:
            need[c] += 1
        needCnt = len(t)
        i = 0
        res = (0, float('inf'))
        for j, c in enumerate(s):
            if need[c] > 0:
                needCnt -= 1
            need[c] -= 1
            if needCnt == 0:  # 步骤一：滑动窗口包含了所有T元素
                while True:  # 步骤二：增加i，排除多余元素
                    c = s[i]
                    if need[c] == 0:
                        break
                    need[c] += 1
                    i += 1
                if j - i < res[1] - res[0]:  # 记录结果
                    res = (i, j)
                need[s[i]] += 1  # 步骤三：i增加一个位置，寻找新的满足条件滑动窗口
                needCnt += 1
                i += 1
        return '' if res[1] > len(s) else s[res[0]:res[1] + 1]  # 如果res始终没被更新过，代表无满足条件的结果

```

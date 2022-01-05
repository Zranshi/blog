---
title: leetcode打卡
date: 2020-11-18 22:37:36
author: ranshi
avatar: https://i.loli.net/2021/10/27/quMyIgbaD6tURx5.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - leetcode
  - 算法
keywords: leetcode
description: leetcode
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/17.jpg
---

## 2020.11.18 T134

### 题目

在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i + 1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 - 1。

### 代码

```python
class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        a = []
        for i in range(len(gas)):
            a.append(gas[i] - cost[i])
        if sum(a) < 0:
            return -1
        start, money = 0, 0
        for i in range(len(a)):
            money += a[i]
            if money < 0:
                start = i + 1
                money = 0
        return start
```

### 分析

- 有一个环形路上有 n 个站点； 每个站点都有一个好人或一个坏人； 好人会给你钱，坏人会收你一定的过路费，如果你带的钱不够付过路费，坏人会跳起来把你砍死； 问：从哪个站点出发，能绕一圈活着回到出发点?
- 首先考虑一种情况：如果全部好人给你 的钱加起来 小于 坏人收的过路费之和，那么总有一次你的钱不够付过路费，你的结局注定会被砍死。
- 假如你随机选一点 start 出发，那么你肯定会选一个有好人的站点开始，因为开始的时候你没有钱，遇到坏人只能被砍死；
- 现在你在 start 出发，走到了某个站点 end，被 end 站点的坏人砍死了，说明你在 [start, end) 存的钱不够付 end 点坏人的过路费，因为 start 站点是个好人，所以在 (start, end) 里任何一点出发，你存的钱会比现在还少，还是会被 end 站点的坏人砍死；
- 于是你重新读档，聪明的选择从 end + 1 点出发，继续你悲壮的征程； 终于有一天，你发现自己走到了尽头(下标是 n - 1)的站点而没有被砍死； 此时你犹豫了一下，那我继续往前走，身上的钱够不够你继续走到出发点 Start?
- 当然可以，因为开始已经判断过，好人给你的钱数是大于等于坏人要的过路费的，你现在攒的钱完全可以应付[0, start) 这一段坏人向你收的过路费。 这时候你的嘴角微微上扬，眼眶微微湿润，因为你已经知道这个世界的终极奥秘：Start 就是这个问题的答案。

## 2020.11.23 T72

### 题目

给你两个单词  word1 和  word2，请你计算出将  word1  转换成  word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：

- 插入一个字符
- 删除一个字符
- 替换一个字符

### 代码

```python
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        len1, len2 = len(word1), len(word2)
        if len1 * len2 == 0:
            return len1 + len2
        dp = [[0] * (len2 + 1) for _ in range(len1 + 1)]
        for i in range(len1 + 1):
            dp[i][0] = i
        for i in range(len2 + 1):
            dp[0][i] = i
        for i in range(1, len1 + 1):
            for j in range(1, len2 + 1):
                left = dp[i - 1][j] + 1
                down = dp[i][j - 1] + 1
                left_down = dp[i - 1][j - 1]
                if word1[i - 1] != word2[j - 1]:
                    left_down += 1
                dp[i][j] = min(left, down, left_down)
        for i in range(0, len1):
            for j in range(0, len2):
                print(dp[i][j], end=" ")
            print()
        return dp[len1][len2]
```

### 分析

- 问题 1：如果 word1[0..i - 1] 到 word2[0..j - 1] 的变换需要消耗 k 步，那 word1[0..i] 到 word2[0..j]的变换需要几步呢？
- 答：先使用 k 步，把 word1[0..i - 1] 变换到 word2[0..j - 1]，消耗 k 步。再把 word1[i] 改成 word2[j]，就行了。如果 word1[i] == word2[j]，什么也不用做，一共消耗 k 步，否则需要修改，一共消耗 k + 1 步。

- 问题 2：如果 word1[0..i - 1] 到 word2[0..j] 的变换需要消耗 k 步，那 word1[0..i] 到 word2[0..j] 的变换需要消耗几步呢？
- 答：先经过 k 步，把 word1[0..i - 1] 变换到 word2[0..j]，消耗掉 k 步，再把 word1[i] 删除，这样，word1[0..i] 就完全变成了 word2[0..j] 了。一共 k + 1 步。

- 问题 3：如果 word1[0..i] 到 word2[0..j - 1] 的变换需要消耗 k 步，那 word1[0..i] 到 word2[0..j] 的变换需要消耗几步呢？
- 答：先经过 k 步，把 word1[0..i] 变换成 word2[0..j - 1]，消耗掉 k 步，接下来，再插入一个字符 word2[j], word1[0..i] 就完全变成了 word2[0..j] 了。

从上面三个问题来看，word1[0..i] 变换成 word2[0..j] 主要有三种手段，用哪个消耗少，就用哪个。

## 2020.11.24 T587

### 题目

在一个二维的花园中，有一些用(x, y) 坐标表示的树。由于安装费用十分昂贵，你的任务是先用最短的绳子围起所有的树。只有当所有的树都被绳子包围时，花园才能围好栅栏。你需要找到正好位于栅栏边界上的树的坐标。

### 代码

```python
class Solution:
    def outerTrees(self, points: List[List[int]]) -> List[List[int]]:
        n = len(points)
        if n < 3:
            return points
        points.sort(key=lambda x: (x[0], x[1]))

        def cross(a, b, c): return (b[0] - a[0]) * \
            (c[1] - b[1]) - (b[1] - a[1]) * (c[0] - b[0])

        low = []
        for p in points:
            while len(low) > 1 and cross(low[-2], low[-1], p) < 0:
                low.pop()
            low.append((p[0], p[1]))
        up = []
        for p in reversed(points):
            while len(up) > 1 and cross(up[-2], up[-1], p) < 0:
                up.pop()
            up.append((p[0], p[1]))
        return list(set(low[:-1] + up[:-1]))


```

### 分析

- 节选自 CSDN 用户[九茶](https://blog.csdn.net/Bone_ACE)
- 分析链接
  ：[https://blog.csdn.net/Bone_ACE/article/details/46239187](https://blog.csdn.net/Bone_ACE/article/details/46239187)

## 2020.11.29 T15

### 题目

给你一个包含 n 个整数的数组  nums，判断  nums  中是否存在三个元素 a，b，c ，使得  a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

### 代码

```python
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        l = len(nums)
        nums.sort()
        result = set()
        for x in range(l-2):
            if nums[x] > 0:
                break
            if x >= 1 and nums[x] == nums[x-1]:
                continue
            a, b = x+1, l-1
            while a < b:
                if nums[a]+nums[b] < -nums[x]:
                    a += 1
                elif nums[a]+nums[b] > -nums[x]:
                    b -= 1
                else:
                    result.add((nums[x], nums[a], nums[b]))
                    a += 1
                    b -= 1
        result = list(result)
        for i in range(len(result)):
            result[i] = list(result[i])
        return result
```

### 分析

- 对于这道题，如果采用暴力三重循环的解法，肯定是会超时的，所以需要另辟蹊径。
- 我们观察可知，这道题如果只用一重循环，是可以转化为 leetcode 第一题[两数相加](https://leetcode-cn.com/problems/two-sum/)，因此我们只用遍历数组一次，然后采用双指针首尾遍历一次就可以找到结果了。
- 但是需要注意的是，这道题要返回的是所有满足条件的不重复三元组，所以先用 set 保存，可以自动去重，最后再将 set 变为 list 返回。(需要注意的是，set 中不能存 list，所以用 tuple 保存)

## 2020.12.3 T236

### 题目

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

### 代码

```python
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if root in (None, p, q):
            return root
        L = self.lowestCommonAncestor(root.left, p, q)
        R = self.lowestCommonAncestor(root.right, p, q)
        return R if None == L else L if None == R else root
```

### 分析

左子树或自己含 p 就返回 p，右子树或自己含 q 就返回 q，左右子树返回一 p 一 q 则返回自己，如果某子树返回了答案（另一子树必然返回 None），则返回答案，剩下就是两个子树都返回空，则返回空。 经过逻辑化简：

1. 先分析自己，自己是 p,q,None 中的一者，自然返回自己
2. 然后分析左右子树的返回值，如果其中一个是 None，则返回另一个，作为传递，无论是传递最终的答案，还是传递 p 和 q
3. 如果左右子树返回 p 和 q，当然返回 root

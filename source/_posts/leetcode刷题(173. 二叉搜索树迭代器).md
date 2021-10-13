---
title: LeetCode——173. 二叉搜索树迭代器
date: 2021-3-28 16:52:57
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
  - golang
keywords: LeetCode
description: 大佬的代码tql!!!
photos: https://i.loli.net/2021/03/28/qpfvKYSrgzHm2Bn.jpg
---

# leetcode 刷题(173. 二叉搜索树迭代器)

## 题目

实现一个二叉搜索树迭代器类 BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭
代器： BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点
root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数
字小于 BST 中的任何元素。 boolean hasNext() 如果向指针右侧遍历存在数字，则返回
true ；否则返回 false 。 int next()将指针向右移动，然后返回指针处的数字。注意，
指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最
小元素。

你可以假设  next()  调用总是有效的，也就是说，当调用 next()  时，BST 的中序遍历
中至少存在一个下一个数字。

## 实例

输入 ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next",
"hasNext", "next", "hasNext"] [[[7, 3, 15, null, null, 9, 20]], [], [], [], [],
[], [], [], [], []] 输出 [null, 3, 7, true, 9, true, 15, true, 20, false]

解释 BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next(); // 返回 3 bSTIterator.next(); // 返回 7
bSTIterator.hasNext(); // 返回 True bSTIterator.next(); // 返回 9
bSTIterator.hasNext(); // 返回 True bSTIterator.next(); // 返回 15
bSTIterator.hasNext(); // 返回 True bSTIterator.next(); // 返回 20
bSTIterator.hasNext(); // 返回 False

## 解题

### 我的解法

关于这道题, 我首先想到的是在数据传入时, 使用中序遍历保存整个顺序, 然后只用记录目
前是遍历到哪一个结点即可.

以下是 Python3 和 Golang 的代码:

```python
class BSTIterator:

    def __init__(self, root: TreeNode):
        self.queue = []
        self.idx = 0
        self.inOrder(root)

    def next(self) -> int:
        self.idx += 1
        return self.queue[self.idx - 1]

    def hasNext(self) -> bool:
        if self.idx < len(self.queue):
            return True
        return False

    def inOrder(self, root: TreeNode):
        if root.left:
            self.inOrder(root.left)
        self.queue.append(root.val)
        if root.right:
            self.inOrder(root.right)
```

```Golang
type BSTIterator struct {
 queue []int
 idx   int
}

func Constructor(root *TreeNode) BSTIterator {
 b := BSTIterator{}
 b.inOrder(root)
 return b
}

func (b *BSTIterator) Next() int {
 b.idx += 1
 return b.queue[b.idx-1]
}

func (b *BSTIterator) HasNext() bool {
 if b.idx < len(b.queue) {
  return true
 }
 return false
}

func (b *BSTIterator) inOrder(root *TreeNode) {
 if root.Left != nil {
  b.inOrder(root.Left)
 }
 b.queue = append(b.queue, root.Val)
 if root.Right != nil {
  b.inOrder(root.Right)
 }
}
```

### 大佬的解法

#### leetcode 大佬的解法(Python3)

在迭代时计算 next 节点的值:

在设计迭代器时, 尽量避免提前把所有的值都取出来, 最好能设计成遍历过程中求 next 节
点. 因此使用迭代来实现:

- 把**递归**转成**迭代**, 使用栈实现
- 迭代总体思路就是: 栈中只保留**左节点**

代码实现为:

```python
class BSTIterator(object):

    def __init__(self, root):
        self.stack = []
        while root:
            self.stack.append(root)
            root = root.left

    def next(self):
        cur = self.stack.pop()
        node = cur.right
        while node:
            self.stack.append(node)
            node = node.left
        return cur.val

    def hasNext(self):
        return len(self.stack) > 0
```

#### 官方解答(Golang)

思想基本相同, 都是通过栈实现每次调用 next 只用常熟时间.

```Golang
type BSTIterator struct {
    stack []*TreeNode
    cur   *TreeNode
}

func Constructor(root *TreeNode) BSTIterator {
    return BSTIterator{cur: root}
}

func (it *BSTIterator) Next() int {
    for node := it.cur; node != nil; node = node.Left {
        it.stack = append(it.stack, node)
    }
    it.cur, it.stack = it.stack[len(it.stack)-1], it.stack[:len(it.stack)-1]
    val := it.cur.Val
    it.cur = it.cur.Right
    return val
}

func (it *BSTIterator) HasNext() bool {
    return it.cur != nil || len(it.stack) > 0
}
```

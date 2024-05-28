---
title: 写一篇文章来吐槽Go语言的机制
date: 2021-7-7 22:09:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 正是你花费在玫瑰上的时间才使得你的玫瑰花珍贵无比
authorDesc:
categories: 技术
comments: true
tags:
  - golang
  - leetcode
keywords: Go
description: Go的slice、map真的把我搞疯！
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/57648299_p0.png
---

# 吐槽 Go 语言的机制

## 起因

今天突发奇想想用 Go 来写一写 LeetCode 困难题。因为平时感觉 Go 还是挺靠谱的（而且速度比 Python 快多了），比起 Python 的方便快捷，Go 更给我一种我能完全掌握我在干嘛的感觉（现在看来这就是幻觉）。

所以打开了今天的[拦路虎](https://leetcode-cn.com/problems/bst-sequences-lcci/)

## 题目介绍

首先看到这个题，我发现结点的顺序有如下限制：

1. 父结点总是在子结点之前
2. 没了

是的，没错，只有一个限制。那么问题就很简单了，就是从头结点开始遍历，每次将当前结点的子结点放入 map 中，从 map 中找到下一个结点，继续这个过程就可以找到所有的路径了。

因此我发现可以使用回溯法，因此我使用递归实现。

在编写中有几点需要注意的：

1. 子结点加入后，在函数完成时需要将其剔除，不然会影响到之后的递归。
2. 遍历到当前结点时，需要剔除该结点，在处理完后需要将其加入

## 题目解答

想到这里，我随手写了一个低效率版本，并且十分合理地以低效率的时间和空间通过了该题。

```go
// 执行用时：28 ms, 在所有 Go 提交中击败了6.98%的用户
// 内存消耗：14.1 MB, 在所有 Go 提交中击败了6.98%的用户

func BSTSequences(root *TreeNode) [][]int {
	if root == nil {
		return append([][]int{}, []int{})
	}
	var (
		res       [][]int
		path      []int
		dfs       func(idx *TreeNode, que map[*TreeNode]bool, path []int)
		sliceCope func([]int) []int
		mapCope   func(map[*TreeNode]bool) map[*TreeNode]bool
	)
	sliceCope = func(i []int) (res []int) {
		for _, x := range i {
			res = append(res, x)
		}
		return
	}
	mapCope = func(m map[*TreeNode]bool) map[*TreeNode]bool {
		res := map[*TreeNode]bool{}
		for k, v := range m {
			res[k] = v
		}
		return res
	}

	que := map[*TreeNode]bool{root: true}
	dfs = func(idx *TreeNode, que map[*TreeNode]bool, path []int) {
		delete(que, idx)
		path = append(path, idx.Val)
		if idx.Left != nil {
			que[idx.Left] = true
		}
		if idx.Right != nil {
			que[idx.Right] = true
		}
		if len(que) == 0 {
			res = append(res, path)
		} else {
			for key := range que {
				newQue := mapCope(que)
				newPath := sliceCope(path)
				dfs(key, newQue, newPath)
			}
		}
		return
	}
	dfs(root, que, path)
	return res
}
```

这我肯定不能满意，我发现了我在复制 map 和 slice 上花费了很多不应该的时间。因此我下定决心研究代码，结果问题就来了。

1. Go 语言在遍历 map 的时候不是将其 keys 保存成一个数组，从而遍历它的。而是每次从 map 中去除一个 key。这就导致了如果在遍历过程中修改了 map，则会发生很多难以预料的事情。因此需要使用一个 slice 保存其 key 值，再遍历数组就可以保证能够顺利遍历了。
2. 然后在复制 Slice 的时候，已经习惯 Python 的原本想使用 slice[:]从而获得一个副本。结果突然想起来 Go 的切片不同于 Python，Python 是生成一个新的列表，而 Go 这则是修改该 slice 的指针。在高效的同时也导致其...根本没有发生改变。
3. 最后使用 copy 也有一些坑点，在复制 slice 的时候，如果被覆盖的那个 slice 空间不够大，则无法成功复制，也就是说得先分配一定的大小的空间，才能使用 copy 函数。

以下是修改后的代码（但是不得不说，Go 是真的香），

```go
// 执行用时：12 ms, 在所有 Go 提交中击败了90.70%的用户
// 内存消耗：6.9 MB, 在所有 Go 提交中击败了95.35%的用户
func BSTSequences(root *TreeNode) [][]int {
	if root == nil {
		return append([][]int{}, []int{})
	}
	var (
		res  [][]int
		path []int
		dfs  func(idx *TreeNode)
	)
	que := map[*TreeNode]bool{root: true}
	dfs = func(idx *TreeNode) {
		delete(que, idx)
		path = append(path, idx.Val)
		if idx.Left != nil {
			que[idx.Left] = true
			defer delete(que, idx.Left)
		}
		if idx.Right != nil {
			que[idx.Right] = true
			defer delete(que, idx.Right)
		}
		if len(que) == 0 {
			newSlice := make([]int, len(path))
			copy(newSlice, path)
			res = append(res, newSlice)
		} else {
			st := make([]*TreeNode, 0, len(que))
			for key := range que {
				st = append(st, key)
			}
			for i := range st {
				dfs(st[i])
			}
		}
		que[idx] = true
		path = path[:len(path)-1]
		return
	}
	dfs(root)
	return res
}
```

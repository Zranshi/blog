---
title: LeetCode——208. 实现 Trie (前缀树)
date: 2021-4-14 8:47:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc: 
categories: 技术
comments: true
tags: 
 - LeetCode
 - 前缀树\字典树
 - golang
keywords: LeetCode
description: 学习前缀树
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.43/2020.12.16/52.jpg
---

![Trie](https://pic2.zhimg.com/80/v2-9d07fbd164fc0d737aabe428b4484bd1_720w.png)

## 介绍(以下摘抄自维基百科)

在计算机科学中，trie，又称前缀树或字典树，是一种有序树，用于保存关联数组，其中的键通常是字符串。与二叉查找树不同，键不是直接保存在节点中，而是由节点在树中的位置决定。一个节点的所有子孙都有相同的前缀，也就是这个节点对应的字符串，而根节点对应空字符串。一般情况下，不是所有的节点都有对应的值，只有叶子节点和部分内部节点所对应的键才有相关的值。

Trie这个术语来自于retrieval。根据词源学，trie的发明者Edward Fredkin把它读作/ˈtriː/ "tree"。[1][2]但是，其他作者把它读作/ˈtraɪ/ "try"。

在图示中，键标注在节点中，值标注在节点之下。每一个完整的英文单词对应一个特定的整数。Trie可以看作是一个确定有限状态自动机，尽管边上的符号一般是隐含在分支的顺序中的。

键不需要被显式地保存在节点中。图示中标注出完整的单词，只是为了演示trie的原理。

trie中的键通常是字符串，但也可以是其它的结构。trie的算法可以很容易地修改为处理其它结构的有序序列，比如一串数字或者形状的排列。比如，bitwise trie中的键是一串比特，可以用于表示整数或者内存地址。

## [leetcode题目](https://leetcode-cn.com/problems/implement-trie-prefix-tree/submissions/)

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。

- void insert(String word) 向前缀树中插入字符串 word 。
- boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
- boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

## 实现

使用数组存储

```Golang
package myCode

// Trie 字典树结构
type Trie struct {
 size   int
 isWord bool
 next   [26]*Trie
}

// Constructor 构造函数
func Constructor() Trie {
 return Trie{}
}

// Insert 插入一个新的字符串
func (t *Trie) Insert(word string) {
 if len(word) == 0 {
  return
 }
 cur := t
 for i := range word {
  if cur.next[word[i]-'a'] == nil {
   cur.next[word[i]-'a'] = new(Trie)
  }
  cur = cur.next[word[i]-'a']
 }
 if !cur.isWord {
  cur.isWord = true
  t.size++
 }
}

// Search 搜索是否存在当前字符串
func (t *Trie) Search(word string) bool {
 length := len(word)
 if length == 0 {
  return false
 }
 cur := t
 for i := 0; i < length; i++ {
  if cur = cur.next[word[i]-'a']; cur == nil {
   return false
  }
 }
 return cur.isWord
}

// StartsWith 搜索是否存在以当前字符串开头的字符串
func (t *Trie) StartsWith(prefix string) bool {
 length := len(prefix)
 if length == 0 {
  return true
 }
 cur := t
 for i := 0; i < length; i++ {
  if cur = cur.next[prefix[i]-'a']; cur == nil {
   return false
  }
 }
 return true
}

```

-----

使用map存储

```Golang
type Trie struct {
 isWord bool
 next   map[rune]*Trie
}

func Constructor() Trie {
 return Trie{
  false,
  make(map[rune]*Trie),
 }
}

func (t *Trie) Insert(word string) {
 if len(word) == 0 {
  return
 }
 cur := t
 for _, v := range word {
  _, ok := cur.next[v]
  if !ok {
   cur.next[v] = &Trie{false, make(map[rune]*Trie)}
  }
  cur = cur.next[v]
 }
 if !cur.isWord {
  cur.isWord = true
 }
}

func (t *Trie) Search(word string) bool {
 if len(word) == 0 {
  return false
 }
 cur := t
 for _, v := range word {
  t1, ok := cur.next[v]
  if !ok {
   return false
  }
  cur = t1
 }
 return cur.isWord
}

func (t *Trie) StartsWith(word string) bool {
 if len(word) == 0 {
  return true
 }
 cur := t
 for _, v := range word {
  t1, ok := cur.next[v]
  if !ok {
   return false
  }
  cur = t1
 }
 return true
}

```

## 分析

总体上来说使用数组存储时间更快, 但是使用map存储空间更小. 具体使用哪种方法根据需求改变.

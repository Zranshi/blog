---
title: 自己用Go实现一个进度条库
date: 2022-1-17 11:02:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - Go
  - progress
keywords: Go
description: 准备将rs-get替换为用go语言实现，那么先从进度条开始吧！
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/88996856_p0.png
---

## 进度条的显示结构

对于一个进度条来说，最重要的应该是显示进度。对于进度的显示，可以有多种形式：

1. 用一个长条来表示，随着任务的逐渐完成，长条逐渐被填满。因为人类对于形象的信息接受地更快，所以形象的长条状能够很好地让使用者认识到当前进度以及还差多少。
2. 使用百分比来显示。直观展现还剩多少，已经完成了多少。
3. 已完成的任务数/总共的任务数。当数据量较大的时候，单个任务的完成可能导致前两种形式无法展示。而该种形式能够让使用者明白任务正在进行。

大致计划成品如下：

![](https://s2.loli.net/2022/01/17/TYifLy51Z9KnqaX.png)

## 定义数据结构

根据进度条的显示结构，我们可以知道一个进度条类型的结构如下：

```go
type Progress struct {
	percent   int64
	current   int64
	total     int64
	startTime time.Time
	rate      float64
	line      string
	graph     string
	lock      *sync.Mutex
}
```

同时可以写出其的初始化函数：

```go
func InitProgress(total int64) *Progress {
	return &Progress{
		current:   0,
		total:     total,
		line:      "",
		graph:     "#",
		percent:   0.0,
		startTime: time.Now(),
		rate:      0.0,
		lock:      &sync.Mutex{},
	}
}
```

## 实现功能

初步构想的是和 Python 的 alive_progress 库一样，先用一个函数定义了一个对象，然后在完成一个任务之后调用该对象的方法，即可刷新进度条。

那么用以下形式实现。

```go
func (p *Progress) Complete() {
	p.lock.Lock()

	p.current += 1
	currentPercent := p.GetPercent()
	if currentPercent != p.percent && currentPercent%2 == 0 {
		p.line += string(p.graph)
	}
	p.line = strings.Repeat(string(p.graph), int(p.percent/2))
	fmt.Printf("\r[%-50s] %3d%% %6d/%d(tasks)", p.line, p.percent, p.current, p.total)
	if p.current == p.total {
		duration := time.Since(p.startTime).Seconds()
		fmt.Printf("\nAll tasks have been completed, taking a total of %.2f seconds.\n", duration)
	}

	p.lock.Unlock()
}
```

并且为了保证并行安全，为该对象加了锁，保证每次只有一个协程/线程正在给进度条+1。

## 代码

```go
package progress

import (
	"fmt"
	"strings"
	"sync"
	"time"
)

// @Time     : 2022/01/17 14:11
// @Author   : Ranshi
// @File     : main.go
// @Doc      : 自己编写的cli进度条库

type Progress struct {
	percent   int64
	current   int64
	total     int64
	startTime time.Time
	rate      float64
	line      string
	graph     string
	lock      *sync.Mutex
}

func InitProgress(total int64) *Progress {
	return &Progress{
		current:   0,
		total:     total,
		line:      "",
		graph:     "#",
		percent:   0.0,
		startTime: time.Now(),
		rate:      0.0,
		lock:      &sync.Mutex{},
	}
}

func (p *Progress) SetGraph(ch byte) {
	p.graph = string(ch)
}

func (p *Progress) GetPercent() int64 {
	return (p.current * 100) / p.total
}

func (p *Progress) Complete() {
	p.lock.Lock()

	p.current += 1
	currentPercent := p.GetPercent()
	if currentPercent != p.percent && currentPercent%2 == 0 {
		p.line += string(p.graph)
	}
	p.line = strings.Repeat(string(p.graph), int(p.percent/2))
	fmt.Printf("\r[%-50s] %3d%% %6d/%d(tasks)", p.line, p.percent, p.current, p.total)
	if p.current == p.total {
		duration := time.Since(p.startTime).Seconds()
		fmt.Printf("\nAll tasks have been completed, taking a total of %.2f seconds.\n", duration)
	}

	p.lock.Unlock()
}
```

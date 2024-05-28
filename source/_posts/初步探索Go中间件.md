---
title: 初步探索Go中间件
date: 2022-1-15 16:18:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 正是你花费在玫瑰上的时间才使得你的玫瑰花珍贵无比
authorDesc:
categories: 技术
comments: true
tags:
  - Go
  - Middleware
keywords: Go
description: 学习一下中间件吧！
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/88996856_p0.png
---

## 什么是中间件？

中间件通常是一小部分代码，能够在后端处理请求之前或者之后，对请求和响应作出处理。这就要求了中间件的体量不能过大，并且职责要求尽量单一，便于接藕。

一个很简单的例子，如果我们打算记录每个请求被响应的总时间，那么我们可以在最外层套一层中间件。这样就可以得知从收到请求到返回响应的总时间了。

![](https://s2.loli.net/2022/01/15/o2rmMxvYsc73pX5.png)

根据上图中，外层的处理代码就是中间件，内层的代码就是应用的核心功能。

## 怎么编写中间件？

在 Go 语言中，我们可以将函数嵌套起来，构成一个中间件。

比如一下代码，就是一个用来验证请求 Method 是否合法的中间件。

```go
// http.HandlerFunc 是将一类具有相同的函数签名的函数定义为这个类型。
// 也就是说，这种类型的实例是一个函数，该函数的的参数是http.ResponseWriter, 和http.Request的指针。
// 而Middleware类型是将一类函数定义为Middleware，这类函数接收一个http.HandlerFunc类型，
// 并返回一个http.HandlerFunc类型
type Middleware func(http.HandlerFunc) http.HandlerFunc

// 该中间件是用于检测请求是否为合法的 HTTP Method，不是则返回 400 Bad Request
func CheckMethod(m string) Middleware {
	// 返回一个Middleware类型，
	return func(hf http.HandlerFunc) http.HandlerFunc {
		// 返回一个http.HandlerFunc类型，
		return func(rw http.ResponseWriter, r *http.Request) {
			if r.Method != m {
				http.Error(rw, http.StatusText(http.StatusBadRequest), http.StatusBadRequest)
				return
			}

			// 调用下一个中间件或者最终处理的handler程序
			hf(rw, r)
		}
	}
}
```

其中 CheckMethod 是用于返回一个 Middleware 类型的函数。为啥不直接定义一个 Middleware 类型的函数呢，而要定义一个返回 Middleware 类型的函数呢？其实上面这个函数就是一个很好的例子。因为 Middleware 类型有固定的函数签名，因此无法给中间件添加参数，比如该函数中的参数 m，就是指的是应该的 Method 类型。如果单独定一个 Middleware 类型的函数，则无法实现。

其中`return func(hf http.HandlerFunc) http.HandlerFunc`是返回 http.HandlerFunc 类型的函数，http.HandlerFunc 类型其实就是指的有着`func(ResponseWriter, *Request)`签名的函数类型。而接收一个该类型的函数，又返回一个该类型的函数，也就可以根据链式调用将核心功能一层一层的包裹在中间件之中。

其中`return func(rw http.ResponseWriter, r *http.Request)`则是编写中间件核心处理功能的函数。需要在该函数中实现中间件的功能，并调用下一层的中间件或核心功能的函数。

## 调用中间件

根据上图中我们可以看出来，想要添加新的中间件，只需要在外层多加几层就能达到目的了。那么可以写一个链式调用的函数，将核心功能一层一层套起来。

```go
func Chain(f http.HandlerFunc, middlewares ...Middleware) http.HandlerFunc {
	for _, middleware := range middlewares {
		f = middleware(f)
	}
	return f
}
```

## 例子

```go
package main

import (
	"fmt"
	"log"
	"net/http"
	"time"
)

// http.HandlerFunc 是将一类具有相同的函数签名的函数定义为这个类型。
// 也就是说，这种类型的实例是一个函数，该函数的的参数是http.ResponseWriter, 和http.Request的指针。
// 而Middleware类型是将一类函数定义为Middleware，这类函数接收一个http.HandlerFunc类型，
// 并返回一个http.HandlerFunc类型
type Middleware func(http.HandlerFunc) http.HandlerFunc

// 该中间件是用来记录URL请求的执行时长的
func Logging() Middleware {
	// 返回一个Middleware类型，
	return func(hf http.HandlerFunc) http.HandlerFunc {
		// 返回一个http.HandlerFunc类型，
		return func(rw http.ResponseWriter, r *http.Request) {
			start := time.Now()
			defer func() {
				log.Println(r.URL.Path, time.Since(start))
			}()

			// 调用下一个中间件或者最终处理的handler程序
			hf(rw, r)
		}
	}
}

// 该中间件是用于检测请求是否为合法的 HTTP Method，不是则返回 400 Bad Request
func CheckMethod(m string) Middleware {
	// 返回一个Middleware类型，
	return func(hf http.HandlerFunc) http.HandlerFunc {
		// 返回一个http.HandlerFunc类型，
		return func(rw http.ResponseWriter, r *http.Request) {
			if r.Method != m {
				http.Error(rw, http.StatusText(http.StatusBadRequest), http.StatusBadRequest)
				return
			}

			// 调用下一个中间件或者最终处理的handler程序
			hf(rw, r)
		}
	}
}

func Chain(f http.HandlerFunc, middlewares ...Middleware) http.HandlerFunc {
	for _, middleware := range middlewares {
		f = middleware(f)
	}
	return f
}

func Hello(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintln(w, "hello world")
}

func main() {
	http.HandleFunc("/", Chain(Hello, CheckMethod("GET"), Logging()))

	http.ListenAndServe("localhost:8000", nil)
}

```

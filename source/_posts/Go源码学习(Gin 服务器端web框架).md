---
title: Go源码学习(Gin 服务器端web框架)
date: 2021-1-28 17:07:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - golang
  - Gin
keywords: Go源码阅读
description: Ranshi努力中...学习Go源码, 为了找到一个好工作!
photos: https://i.loli.net/2021/01/29/glJyPCvVH3dj4WK.jpg
---

# Go 源码学习 --Gin 框架

学习 Go 真是一个不可思议的事情, 不得不说果然配置环境是后端最难的事情. 我曾经为了
Java 环境困扰了一个星期, 如今也为 Go 的 module 模式配置了半天. 但是不得不说 Go
也是一个很魔幻的语言, 我第一次知道可以这么简单地创建一个后端服务器, 基本上学习
Gin 框架只用了 2 个小时... 差不多后端基础功能就知道是个怎么回事了.

但是学得这么快, 总感觉心里不踏实. 其实在学习的过程中, 基本都是使用大佬编写的轮子
. 然后感觉自己也没学什么东西, 于是打算开始学习源码, 来攀登巨人的高峰!

## 一个简单的 Demo

```go
func main() {
	r := gin.Default()
	r.Run()
}
```

![代码](https://i.loli.net/2021/01/29/tW4qXoFBja68xsR.png) 由此我们可以看到, Gin
的基础功能可以分为两个阶段: Default()函数用来创建实例; Run()函数用来运行服务器.

Gin 框架非常简洁, 仅仅使用了两个函数就能实现一个简单的服务器功能. 对比其他语言的
后端框架可以称得上是精简了. 正是因为 Gin 已经帮我们把功能封装完毕了, 我们才需要
去深入了解其原理.

## gin.Default()

`gin.Default()`创建了一个**Engine**实例, 然后使用了**Logger**和**Recovery**中间
件. `gin.Default()`和`gin.New()` 功能类似. 实际上, `gin.Default()`函数只是在调用
了`gin.New()`基础上使用了`engine.Use(Logger(),Recovery())`, 接下来查看
gin.Defualt 源码.

```go
// 默认返回一个引擎实例, 并且已经连接了Logger和Recovery中间件.
func Default() *Engine {
	debugPrintWARNINGDefault()
	engine := New()
	engine.Use(Logger(), Recovery())
	return engine
}
```

这里我们可以看到`Default()`函数实际上就是调用了`New()`函数, 所以我们不妨来看
看`New()`函数.

```go
// New返回了一个新的空白Engine实例, 不附加任何中间件.
func New() *Engine {
	debugPrintWARNINGNew()
	engine := &Engine{
		RouterGroup: RouterGroup{
			Handlers: nil,
			basePath: "/",
			root:     true,
		},
		FuncMap:                template.FuncMap{},
		RedirectTrailingSlash:  true,
		RedirectFixedPath:      false,
		HandleMethodNotAllowed: false,
		ForwardedByClientIP:    true,
		AppEngine:              defaultAppEngine,
		UseRawPath:             false,
		RemoveExtraSlash:       false,
		UnescapePathValues:     true,
		MaxMultipartMemory:     defaultMultipartMemory,
		trees:                  make(methodTrees, 0, 9),
		delims:                 render.Delims{Left: "{{", Right: "}}"},
		secureJsonPrefix:       "while(1);",
	}
	engine.RouterGroup.engine = engine
	engine.pool.New = func() interface{} {
		return engine.allocateContext()
	}
	return engine
}
```

可以看到实际上是初始化并返回了一个 Engine 对象.

再来看看`Use()`函数.

```go
// Use将全局中间件附加到路由器。 即通过Use()连接中间件.
// 将每个请求都包含在处理程序链中, 甚至404、405，静态文件...
// 例如, 这对于日志或者错误管理中间件是一个正确的位置.
func (engine *Engine) Use(middleware ...HandlerFunc) IRoutes {
	engine.RouterGroup.Use(middleware...)
	engine.rebuild404Handlers()
	engine.rebuild405Handlers()
	return engine
}
```

可以看到, 实际上也是调用了`engine.RouterGroup.Use()`函数来存放中间件. 我们不妨看
看这个函数:

```go
// 将中间件存放在Group中, 并返回这个Group
func (group *RouterGroup) Use(middleware ...HandlerFunc) IRoutes {
	group.Handlers = append(group.Handlers, middleware...)
	return group.returnObj()
}
```

## Run()

```go
// Run()函数将路由器附加到 http.Server上, 并开始侦听和处理请求.
// 这是http.ListenAndServe(addr, router)的快捷使用方法
// 注意: 该方法将无限期阻止调用goroutine, 除非发生错误
func (engine *Engine) Run(addr ...string) (err error) {
	defer func() { debugPrintError(err) }()

	address := resolveAddress(addr)
	debugPrint("Listening and serving HTTP on %s\n", address)
	err = http.ListenAndServe(address, engine)
	return
}
```

在 Go 中只要实现 ServeHTTP 就可以, 所以我们看一看:

```go
// ServeHTTP符合http.Handler接口
func (engine *Engine) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	c := engine.pool.Get().(*Context)
	c.writermem.reset(w)
	c.Request = req
	c.reset()

	engine.handleHTTPRequest(c)

	engine.pool.Put(c)
}
```

这个函数描述了处理的流程: 请求来了, 从`engine.pool`中获取一个空的`context`, 丢
入`engine.handelHTTPRequest()`中处理, 然后回收. 我们查看一下这个函数.

```go
func (engine *Engine) handleHTTPRequest(c *Context) {
	httpMethod := c.Request.Method
	rPath := c.Request.URL.Path
	unescape := false
	if engine.UseRawPath && len(c.Request.URL.RawPath) > 0 {
		rPath = c.Request.URL.RawPath
		unescape = engine.UnescapePathValues
	}

	if engine.RemoveExtraSlash {
		rPath = cleanPath(rPath)
	}
	// 查找给定HTTP方法的树的根
	t := engine.trees
	for i, tl := 0, len(t); i < tl; i++ {
		if t[i].method != httpMethod {
			continue
		}
		root := t[i].root
		// 在树中查找路由
		value := root.getValue(rPath, c.Params, unescape)
		if value.handlers != nil {
			c.handlers = value.handlers
			c.Params = value.params
			c.fullPath = value.fullPath
			c.Next()
			c.writermem.WriteHeaderNow()
			return
		}
		if httpMethod != "CONNECT" && rPath != "/" {
			if value.tsr && engine.RedirectTrailingSlash {
				redirectTrailingSlash(c)
				return
			}
			if engine.RedirectFixedPath && redirectFixedPath(c, root, engine.RedirectFixedPath) {
				return
			}
		}
		break
	}

	if engine.HandleMethodNotAllowed {
		for _, tree := range engine.trees {
			if tree.method == httpMethod {
				continue
			}
			if value := tree.root.getValue(rPath, nil, unescape); value.handlers != nil {
				c.handlers = engine.allNoMethod
				serveError(c, http.StatusMethodNotAllowed, default405Body)
				return
			}
		}
	}
	c.handlers = engine.allNoRoute
	serveError(c, http.StatusNotFound, default404Body)
}
```

大致的流程就是从路由里找出 handler, 然后进行处理. 其中路由使用 httprouter 实现，
使用的数据结构是基数树(radix tree).

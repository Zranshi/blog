---
title: Rust中的所有权系统
date: 2023-2-7 17:55:06
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 正是你花费在玫瑰上的时间才使得你的玫瑰花珍贵无比
authorDesc:
categories: 技术
comments: true
tags:
  - rust
  - 所有权类型
keywords: rust
description: 浅析Rust中的所有权系统
photos: https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2023.02.07-15:34:16-86764353_p0.jpg
---

对于所有的编程语言, 都必须要考虑的一件事就是**管理内存**. 对于这件事, 各种语言是八仙过海, 各显神通.

C/C++ 将内存的管理交给程序员, 这样就的好处就是能够细致化地优化程序, 但弊端则是十分难以维护. 往往会出现野指针、指针悬挂等问题, 导致程序出现 bug 或者内存没有得到释放.

而高级语言(Java, Python, Go)则使用 GC(Garbage collection)机制. 这个机制会收集分配的内存, 并统一释放. 因此其能大大降低程序出现 Bug 的概率, 并提高程序员的工作效率. 但其也存在一定的弊端, 就是在释放内存时会出现 STW(Stop The World)时间, 在这段时间中程序中的所有线程都会被挂起, 并专心进行垃圾收集操作, 这对于非常追求效率的程序来说是无法容忍的.

而 Rust 选择了另外一种方式来管理内存. Rust 程序是没有 GC 的, 但是其也不需要程序员专门去释放内存, 而是通过一种特殊的系统————所有权系统来保证内存不会泄漏. 这种系统不会影响到编译后的二进制程序, 是因为其通过优秀的编译器, 在程序编译阶段就将大部分的会造成内存泄漏的问题都考虑到了. 这就相当于一个能够完美考虑 C/C++代码中的 Bug 的大神在给你的程序做 Debug. 这种方法即能降低程序员的压力也能兼顾到程序的运行效率.

## 所有权简述

### 所有权移动

```rust
fn main() {
    let a = 20;
    let mut b = a;
    b = b - 7;
    println!("a={}", a);
    println!("b={}", b);
}

// a=20
// b=13
```

```rust
fn main() {
    let a = "Hello".to_string();
    let mut b = a;
    b.push('!');
    println!("a={}", a);
    println!("b={}", b);
}

|
2 |     let a = "Hello".to_string();
|         - move occurs because `a` has type `String`, which does not implement the `Copy` trait
3 |     let mut b = a;
|                 - value moved here
4 |     b.push('!');
5 |     println!("a={}", a);
|                      ^ value borrowed here after move

```

这两个程序一个正常运行, 一个报错. 这是因为在第一个程序中的 a 和 b 都是一个 i32 类型的变量, 其大小是固定的, 因此其是存放在栈内存中的.

而第二个程序中的字符串是可变长度的, 因此无法保证其在栈中能够合理地存放(如果需要扩容则需要全部重新在栈上分配内存), 因此其是存放在堆内存中的.

因此这两个程序的内存分布如下图所示:

![](https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2023.02.07-16:51:08-memory1.dio.png)

![](https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2023.02.07-16:48:58-memory1.dio.png)

变量在堆内存和在栈内存上有什么区别呢? 除了访问速度以外, 最主要的区别是栈内存是能够通过变量的生命周期自动释放的, 而堆内存则需要通过程序员手动释放或者由 GC 释放.

另外, 可以明显从内存分布中看到, 在第一个程序中的 a 和 b 没有共享任何内存, 因此它们是不会进行相互影响的. 而在第二个程序中, a 和 b 共享了字符串在堆中的内存, 因此其必须考虑到各种情况下的内存安全. 在 C/C++代码中, 如果堆内存被两个指针使用, 则可能出现二次释放的错误.

因此在这个 rust 程序中, a 已经失去了堆内存的所有权, 而 b 获得了堆内存的所有权. 这种情况就称为**所有权转移(move)**, 因无法再通过 a 访问到堆内存中的字符串了. 因此得这样写:

```rust
fn main() {
    let a = "Hello".to_string();
    let mut b = a;
    b.push('!');
    println!("b={}", b);
}

// b=Hello!
```

### Copy 与 Clone

但是如想要创建一个全新的变量 b, 其拥有一个全新的堆内存该怎么办呢? Rust 针对不同的类型设计了不同的拷贝方式. 对于 Rust 中分配在栈内存中的大小可知的变量, 其实现了 copy 函数, 其能够在拷贝时自动将栈内存复制给新变量. 而对于分配在堆内存中的变量, Rust 实现了 clone 函数, 其将重新在堆上分配内存给新的变量.

```rust
fn main() {
    let a = "Hello".to_string();
    let mut b = a.clone();
    b.push('!');
    println!("b={}", b);
    println!("a={}", a);
}

// b=Hello!
// a=Hello
```

可以看到这样就不会出现之前的问题. 则是因为 b 所指向的字符串是在堆上重新分配的, 因此 a 的并没有失去原先内存的所有权. 其内存分布如图:

![](https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2023.02.07-17:19:38-memory1.dio.png)

需要注意的是, 由于 b 增加了一个字符, 导致容量不够容纳这么多字符, 因此容量会进行翻倍. 多分配了 4 个容量给 b 变量. 这样有利于减少内存分配的次数.

## 所有权借用

#### 读取

但存在这么一种情况, 需要将变量 a 传入到一个函数中, 在函数返回时有需要对 a 进行访问. 由于函数传参的机制, 如果使用所有权移动, 则会导致在函数结束后无法访问.

```rust
fn print_str(b: String) {
    println!("str={}", b);
}

fn main() {
    let a = "Hello".to_string();
    print_str(a);
    println!("a={}", a);
}

  |
6 |     let a = "Hello".to_string();
  |         - move occurs because `a` has type `String`, which does not implement the `Copy` trait
7 |     print_str(a);
  |               - value moved here
8 |     println!("a={}", a);
  |                      ^ value borrowed here after move

```

这时, 就需要使用**所有权借用**.

所有权借用就是将所有权暂时借用给另一个变量, 并且改变量会在未来的某一时刻将其交还给其原来的主人. 具体来说, 使用以下格式进行所有权借用.

```rust
fn print_str(b: &String) {
    println!("str={}", b);
}

fn main() {
    let a = "Hello".to_string();
    print_str(&a);
    println!("a={}", a);
}

// str=Hello
// a=Hello
```

所有权借用的内存分布如图:

![](https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2023.02.07-17:50:27-memory1.dio.png)

其实, 由于借用只是为了读取原变量的值, 因此可以将其所有权借用给多个变量.

```rust
fn print_str(b: &String) {
    println!("str={}", b);
}

fn main() {
    let a = "Hello".to_string();
    let c = &a;
    print_str(&a);
    println!("c={}", c);
    println!("a={}", a);
}

// str=Hello
// c=Hello
// a=Hello
```

#### 修改

在特殊情况下, 需要在函数中对传入的存储在堆内存的变量进行修改, 还能使用原先的做法吗?

```rust
fn print_str(b: &mut String) {
    b.push('!');
    println!("str={}", b);
}

fn main() {
    let mut a = "Hello".to_string();
    let c = &a;
    print_str(&mut a);
    println!("c={}", c);
    println!("a={}", a);
}

   |
8  |     let c = &a;
   |             -- immutable borrow occurs here
9  |     print_str(&mut a);
   |               ^^^^^^ mutable borrow occurs here
10 |     println!("c={}", c);
   |                      - immutable borrow later used here
```

会发现, 这也遇到了问题. 根据提示, 这种情况出现的问题是在使用可变借用时还有不可变借用存在, 即在对变量进行修改操作时, 还在对其进行读取操作. 这在 rust 中是不被允许的.

但这意味着必须删除 c 变量吗? 其实不是的, 可以看到最后一个提示, "immutable borrow later used here" 这是不是意味着只要在不可变借用的生命周期中不存在可变借用, 就能够避免错误呢?

```rust
fn print_str(b: &mut String) {
    b.push('!');
    println!("str={}", b);
}

fn main() {
    let mut a = "Hello".to_string();
    let c = &a;
    println!("c={}", c);
    print_str(&mut a);
    println!("a={}", a);
}

// c=Hello
// str=Hello!
// a=Hello!
```

确实是这样的, 这表示. 在同一时间, 只能存在多个不可变借用(只读)或者一个可变借用(可读可写). 而如果一个借用在之后没有使用, 其生命周期在其最后一次使用时就结束了, 也就不对其他借用造成影响了.

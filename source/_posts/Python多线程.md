---
title: PySimpleGUI演示多线程
date: 2020-12-10 19:40:06
author: ranshi
avatar: https://i.loli.net/2021/10/27/quMyIgbaD6tURx5.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - Python
  - 线程
  - PySimpleGUI
keywords: Python
description: 通过PySimpleGUI演示多线程操作
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/163.jpg
---

## 一. 实验目标设计

1. 通过 Python 完成线程的创建。创建两个线程，一个线程每 0.1 秒对一个变量加 1，一
   个线程每 0.1 秒对一个变量减 1。实时在界面中显示出来，可以通过“结束进程”按钮停
   止线程运行。

2. 通过 Python 完成互斥线程的演示。创建两个线程，共同操作同一个变量，一个每 0.1
   秒加 1，另一个每 0.1 秒减 1；一个线程每次循环对共享变量 x 做 100 次加 1 操作
   ，另一个线程不断循环，每次循环对共享变量 x 做 100 次减 1 操作。实时在界面中显
   示出来，可以通过“结束进程”按钮停止线程运行。

3. 通过 Python 完成非互斥线程的演示。创建两个线程，共同操作同一个变量。一个每
   0.1 秒加 1，另一个每 0.15 秒减 1（为了能将加减体现在界面上）；实时在界面中显
   示出来，可以通过“结束进程”按钮停止线程运行。

## 二. 实验详细设计

### 1. 界面设计

界面采用 Python 的 PySimpleGUI 库，PySimpleGUI 库是一个简单的界面库，能够简单地
在 layout 中设计图形界面。主要 Python 代码：

```python
layout = [
    [sg.Text('线程自加文本框:   '), sg.InputText(default_text='0', key='data1')],
    [sg.Text('线程自减文本框:   '), sg.InputText(default_text='0', key='data2')],
    [sg.Text('线程互斥文本框:   '), sg.InputText(default_text='0', key='data3')],
    [sg.Text('线程非互斥文本框:'), sg.InputText(default_text='0', key='data4')],
    [sg.Button("创建线程", k='创建')],
    [sg.Button("演示线程互斥", k='线程互斥')],
    [sg.Button('演示非线程互斥', k='非线程互斥')],
    [sg.Button('结束线程', k='结束线程')],
    [sg.Quit()],
]
window = sg.Window('线程实验演示', layout=layout, finalize=True)
```

### 2. 界面事件与多线程交互

界面事件通过点击按钮实现，在主循环中，PySimpleGUI 有 window.read()函数来获取界面
事件和输入值。之后通过判断事件(event) 来判断执行哪个事件。线程创建通过指定函数的
形式，使用 threading 模块的 Thread 类创建线程，并通过 start 函数运行主要 Python
代码：

```python
while True:
    event, value = window.read()
    if event == 'Quit' or event == sg.WIN_CLOSED:
        break
    elif event == '创建':
        x, y = threading.Thread(target=run1), threading.Thread(target=run2)
        flag = True
        x.start()
        y.start()
    elif event == '线程互斥':
        x, y = threading.Thread(target=run3), threading.Thread(target=run4)
        flag = True
        x.start()
        y.start()
    elif event == '非线程互斥':
        x, y = threading.Thread(target=run5), threading.Thread(target=run6)
        flag = True
        x.start()
        time.sleep(0.5)
        y.start()
    elif event == '结束线程':
        flag = False
```

### 3. 创建线程设计

当 event 等于“创建线程”时，flag 会被置为 True，并创建两个线程，操作两个数据框的
值，每 0.1 秒更新值。当 event 等于“结束进程”时，会见 flag 置为 Flase，线程也随之
停止。主要 Python 代码：

```python
def run1():
    '''
    创建线程1
    并通过flag控制是否运行
    每次处理数据完成后，都将更新界面显示
    0.1秒循环一次
    '''
    while flag:
        nums[0] += 1
        window['data1'].update(nums[0])
        time.sleep(0.1)

def run2():
    '''创建线程2
    并通过flag控制是否运行
    每次处理数据完成后，都将更新界面显示
    0.1秒循环一次
    '''
    while flag:
        nums[1] -= 1
        window['data2'].update(nums[1])
        time.sleep(0.1)
```

### 4. 互斥线程演示设计

当 event 等于“创建线程”时，flag 会被置为 True，并创建两个线程，操作同一个数据框
的值。并引入全局信号量 lock，如果 lock 等于 True，线程 1 运行，如果 lock 等于
False，线程 2 运行。设置 0 和 100 为分界点。主要 Python 代码：

```python
def run3():
    '''互斥线程1
    0-100时，启动线程，自加，并更新内容
    100-0时，空循环
    '''
    global lock
    while flag:
        if lock:
            nums[2] += 1
            window['data3'].update(nums[2])
            time.sleep(0.01)
            if nums[2] == 100:
                lock = False

def run4():
    '''互斥线程2
    100-0时，启动线程，自加，并更新内容
    0-100时，空循环
    '''
    global lock
    while flag:
        if not lock:
            nums[2] -= 1
            window['data3'].update(nums[2])
            time.sleep(0.01)
            if nums[2] == 0:
                lock = True
```

### 5. 非互斥线程演示设计

当 event 等于“创建线程”时，flag 会被置为 True，并创建两个线程，操作同一个数据框
的值。为了能方便地观察是否成功，每次改变值都会在控制台打印当前值，并且自加为 0.1
秒一循环，自减为 0.15 秒一循环。主要 Python 代码：

```python
def run5():
    '''非互斥线程1
    自加，0.1秒一个循环
    '''
    while flag:
        nums[3] += 1
        print(nums[3] , end=" ")
        window['data4'].update(nums[3])
        time.sleep(0.1)

def run6():
    '''非互斥线程2
    自减，0.15秒一个循环
    '''
    while flag:
        nums[3] -= 1
        print(nums[3] , end=" ")
        window['data4'].update(nums[3])
        time.sleep(0.15)
```

## 总结

通过这次实验，我学会了很多知识。包括但不限于，使用 Python 创建线程对象，控制线程
互斥和非互斥关系，使我受益匪浅。在这次实验中，我遇到过非常多的困难：

1. PySimpleGUI 是一个在 Github 上全新的开源项目，反馈社区并不完善，遇到许多困难
   ，只能查找开发文档。
2. 由于基于 Tkinter 开发，导致多线程开发时偶尔会出现"RuntimeError: main thread
   is not in main loop"的错误，后来查找文档发现是 Tkinter 的主线程无法等待子线程
   过长的时间。后来设置为子线程和主线程同时运行，解决了问题。
3. 非互斥线程运行结果显示不明显。于是调整自加和自减的运行时间，并在控制台打印出
   每次改变的结果。

总而言之，通过这次实验，我学会了许多技术，但最重要的是学会了解决问题的方法。期待
自己未来更大的进步。

## 全部源码

```python
import time
import threading
import PySimpleGUI as sg
from mttkinter import mtTkinter as tk


def run1():
    '''创建线程1
    并通过flag控制是否运行
    每次处理数据完成后，都将更新界面显示
    0.1秒循环一次
    '''
    while flag:
        nums[0] += 1
        window['data1'].update(nums[0])
        time.sleep(0.1)


def run2():
    '''创建线程2
    并通过flag控制是否运行
    每次处理数据完成后，都将更新界面显示
    0.1秒循环一次
    '''
    while flag:
        nums[1] -= 1
        window['data2'].update(nums[1])
        time.sleep(0.1)


def run3():
    '''互斥线程1
    0-100时，启动线程，自加，并更新内容
    100-0时，空循环
    '''
    global lock
    while flag:
        if lock:
            nums[2] += 1
            window['data3'].update(nums[2])
            time.sleep(0.01)
            if nums[2] == 100:
                lock = False


def run4():
    '''互斥线程2
    100-0时，启动线程，自加，并更新内容
    0-100时，空循环
    '''
    global lock
    while flag:
        if not lock:
            nums[2] -= 1
            window['data3'].update(nums[2])
            time.sleep(0.01)
            if nums[2] == 0:
                lock = True


def run5():
    '''非互斥线程1
    自加，0.1秒一个循环
    '''
    while flag:
        nums[3] += 1
        print(nums[3], end=" ")
        window['data4'].update(nums[3])
        time.sleep(0.1)


def run6():
    '''非互斥线程2
    自减，0.15秒一个循环
    '''
    while flag:
        nums[3] -= 1
        print(nums[3], end=" ")
        window['data4'].update(nums[3])
        time.sleep(0.15)


if __name__ == '__main__':
    nums = [0]*4
    layout = [
        [sg.Text('线程自加文本框:   '), sg.InputText(default_text='0', key='data1')],
        [sg.Text('线程自减文本框:   '), sg.InputText(default_text='0', key='data2')],
        [sg.Text('线程互斥文本框:   '), sg.InputText(default_text='0', key='data3')],
        [sg.Text('线程非互斥文本框:'), sg.InputText(default_text='0', key='data4')],
        [sg.Button("创建线程", k='创建')],
        [sg.Button("演示线程互斥", k='线程互斥')],
        [sg.Button('演示非线程互斥', k='非线程互斥')],
        [sg.Button('结束线程', k='结束线程')],
        [sg.Quit()],
    ]
    window = sg.Window('线程实验演示', layout=layout, finalize=True)
    x, y = None, None
    flag = False
    lock = True
    while True:
        event, value = window.read()
        if event == 'Quit' or event == sg.WIN_CLOSED:
            break
        elif event == '创建':
            x, y = threading.Thread(target=run1), threading.Thread(target=run2)
            flag = True
            x.start()
            y.start()
        elif event == '线程互斥':
            x, y = threading.Thread(target=run3), threading.Thread(target=run4)
            flag = True
            x.start()
            y.start()
        elif event == '非线程互斥':
            x, y = threading.Thread(target=run5), threading.Thread(target=run6)
            flag = True
            x.start()
            time.sleep(0.5)
            y.start()
        elif event == '结束线程':
            flag = False


```

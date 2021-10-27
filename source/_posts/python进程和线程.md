---
title: PySimpleGUI演示多进程
date: 2020-11-26 20:29:06
author: ranshi
avatar: https://i.loli.net/2021/10/27/quMyIgbaD6tURx5.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc:
categories: 技术
comments: true
tags:
  - Python
  - 进程
  - PySimpleGUI
keywords: Python
description: 通过PySimpleGUI演示进程的通信
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/56.jpg
---

## 界面设计

界面设计使用了[PySimpleGUI 库](https://github.com/PySimpleGUI/PySimpleGUI),详情
使用方式请查
阅[https://pysimplegui.readthedocs.io/en/latest/](https://pysimplegui.readthedocs.io/en/latest/)

### 主进程

```py
layout = [
        [sg.Multiline(key='date', size=(50, 10))],
        [sg.Button("发送消息", k='发送')],
        [sg.Button("将数据写入内存", k='写入内存')],
        [sg.Button("写数据到管道文件", k='写入文件')],
        [sg.Quit()],
    ]
window = sg.Window('主进程', layout, finalize=True)
```

### 子进程

```python
layout = [
        [sg.Multiline(key='date', size=(50, 10))],
        [sg.Button("接收消息", k='接收')],
        [sg.Button("从内存读取数据", k='读取内存')],
        [sg.Button("从管道文件中读取数据", k='读取文件')],
        [sg.Quit()],
    ]
window = sg.Window('子进程', layout=layout, finalize=True)
```

## 用消息队列传递

发送：

```python
if event == '发送':
            que.put(value)
            print('成功发送')
```

接收：

```python
if event == '接收':
            string += '通过队列消息获得：'
            message = que.get()
            string += message['date']
            window['date'].update(string)
            print('成功接收')
```

## 用内存映像文件传递

发送：

```python
if event == '写入内存':
            with open('test.dat', 'wb')as f:
                message = bytes(value['date'], encoding='utf-8')
                f.write(message)
            print('写入成功')
```

接收：

```python
if event == '读取内存':
            string += '通过共享内存获得：'
            with open('test.dat', 'r+b') as f:
                mm = mmap.mmap(f.fileno(), 0)
                message = mm.read()
                message = str(message, encoding='utf-8')
                string += message
                window['date'].update(string)
            print('读取成功')
```

## 用管道文件传递

发送：

```python
if event == '写入文件':
            conn.send(value)
            print('写入成功')
```

接收：

```python
if event == '读取文件':
            string += '通过读取管道文件获得：'
            message = conn.recv()
            string += message['date']
            window['date'].update(string)
            print('读取成功')
```

## 全部源码

```python
import PySimpleGUI as sg
from multiprocessing import Pipe, Process, Queue
import mmap


def run_process2(que, conn):
    layout = [
        [sg.Multiline(key='date', size=(50, 10))],
        [sg.Button("接收消息", k='接收')],
        [sg.Button("从内存读取数据", k='读取内存')],
        [sg.Button("从管道文件中读取数据", k='读取文件')],
        [sg.Quit()],
    ]
    window = sg.Window('子进程', layout=layout, finalize=True)
    window.make_modal()
    string = ''
    while True:
        event, value = window.read()
        if event == sg.WIN_CLOSED or event == 'Quit':
            break
        print('子进程: ', event)
        if event == '接收':
            string += '通过队列消息获得：'
            message = que.get()
            string += message['date']
            window['date'].update(string)
            print('成功接收')
        if event == '读取内存':
            string += '通过共享内存获得：'
            with open('test.dat', 'r+b') as f:
                mm = mmap.mmap(f.fileno(), 0)
                message = mm.read()
                message = str(message, encoding='utf-8')
                string += message
                window['date'].update(string)
            print('读取成功')
        if event == '读取文件':
            string += '通过读取管道文件获得：'
            message = conn.recv()
            string += message['date']
            window['date'].update(string)
            print('读取成功')
    window.close()


def run_process1(que, conn):
    layout = [
        [sg.Multiline(key='date', size=(50, 10))],
        [sg.Button("发送消息", k='发送')],
        [sg.Button("将数据写入内存", k='写入内存')],
        [sg.Button("写数据到管道文件", k='写入文件')],
        [sg.Quit()],
    ]
    window = sg.Window('主进程', layout, finalize=True)
    window.make_modal()
    while True:
        event, value = window.read()
        if event == sg.WIN_CLOSED or event == 'Quit':
            break
        print('主进程: ', event, value)
        if event == '发送':
            que.put(value)
            print('成功发送')
        if event == '写入内存':
            with open('test.dat', 'wb')as f:
                message = bytes(value['date'], encoding='utf-8')
                f.write(message)
            print('写入成功')
        if event == '写入文件':
            conn.send(value)
            print('写入成功')
    window.close()


if __name__ == "__main__":
    que = Queue(1)
    conn1, conn2 = Pipe(True)
    p1 = Process(target=run_process1, args=(que, conn1))
    p2 = Process(target=run_process2, args=(que, conn2))
    p1.start()
    p2.start()
    p1.join()
    p2.join()

```

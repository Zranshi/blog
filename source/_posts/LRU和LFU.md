---
title: LRU和LFU
date: 2024-3-20 14:27:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 正是你花费在玫瑰上的时间才使得你的玫瑰花珍贵无比
authorDesc:
categories: 技术
comments: true
tags:
  - 操作系统
  - coding
keywords: 操作系统
description: 使用哈希表和双链表实现LRU和LFU
photos: https://ranshi-cnd-1305893362.cos.ap-guangzhou.myqcloud.com/uPic/2024.05.29-00:01:57-B7789C43-E713-482B-8C6C-07615D0C1447_1_105_c.jpeg
---

## LRU

LRU(最近最少使用) 置换算法, 一般用于固定大小的缓冲区中, 选择最近使用的数据保留在缓冲区中. 这样是建立在最近使用的数据可能最近还会再次使用的假设上, 来减少耗时的读取次数.

为了尽可能快地实现 LRU, 就需要看在 LRU 算法中需要进行哪些操作:

- Get(key), 通过 Get 函数去获取缓冲区中对应的 value.
  - 在访问过后, 应该需要记录这个键是最近被访问的, 因此不能仅仅是返回 value, 还要对数据的顺序进行处理.
- Put(key, value), 通过 Put 函数去加入新的键值对.
  - 在加入后, 应该将其设置为最近被访问的 key.
  - 当达到最大容量后, 需要推出最久未使用的键值对.

因此, 我的做法是通过哈希表和双向链表来实现.

这又有这些好处:

1. 通过哈希表存储数据, 能够在 O(1)的时间复杂度下访问到数据.
2. 通过双向链表存储顺序, 能够在 O(1)的时间复杂度下删除中间的元素, 并在 O(1)的时间复杂度下将元素加入在头节点后.

Code:

```Java
import java.util.HashMap;
import java.util.Map;

class Node {
    int val;
    int key;
    Node pre;
    Node next;

    public Node() {
    }

    public Node(int key, int val, Node pre, Node next) {
        this.key = key;
        this.val = val;
        this.pre = pre;
        this.next = next;
    }
}

class DoubleLinkList {
    Node head;
    int size;

    public DoubleLinkList() {
        Node node = new Node();
        node.pre = node;
        node.next = node;
        this.head = node;
    }

    void add(Node n) {
        // 头节点插入
        n.pre = head;
        n.next = head.next;
        head.next.pre = n;
        head.next = n;
        size++;
    }

    Node remove(Node n) {
        // 删除某个节点
        n.pre.next = n.next;
        n.next.pre = n.pre;
        n.next = null;
        n.pre = null;
        size--;
        return n;
    }

    Node poll() {
        // head.pre就是最久未使用的节点, 因此直接调用remove删除.
        Node n = head.pre;
        remove(n);
        return n;
    }
}

class LRUBuffer {
    private int cap;
    private int size;
    Map<Integer, Node> nodeMap;
    DoubleLinkList list;

    public LRUBuffer(int capacity) {
        this.cap = capacity;
        this.nodeMap = new HashMap<>();
        this.list = new DoubleLinkList();
    }

    public int get(int key) {
        if (!nodeMap.containsKey(key)) {
            return -1;
        }
        Node n = nodeMap.get(key);
        list.remove(n);
        list.add(n);
        return n.val;
    }

    public void put(int key, int value) {
        if (nodeMap.containsKey(key)) {
            Node n = nodeMap.get(key);
            n.val = value;
            get(n.key);
            return;
        }
        Node node = new Node(key, value, null, null);
        list.add(node);
        nodeMap.put(key, node);
        size++;

        // 容量满了就删除最久未使用的数据
        if (size > cap) {
            Node n = list.poll();
            nodeMap.remove(n.key);
            size--;
        }
    }
}
```

## LFU

LFU(最不经常使用) 算法, 也是为了解决 LRU 相同的问题. 但是它所假设的是, 当一个数据使用次数最少, 那么就假设它之后的使用次数也最少, 因此将其从缓冲区移除能够最大地减少读取次数.因此, LFU 的核心是记录每个数据的使用次数, 并在缓冲区容量满的时候移除使用次数最少的数据. 如果有多个数据的使用次数都为最小. 那么就移除其中最久未访问的数据.

根据描述中, 我们可以知道 LFU 是建立在 LRU 之上的. 其主要的操作也和 LRU 相似, 主要区别在于淘汰数据的方式不一样.

因此, 我在 LRU 算法的基础上, 添加了一个哈希表来记录相同访问次数的数据的双向链表. 这样有这些好处:

1. 能够很好地记录相同访问次数数据的先后次序问题. 并且维持顺序的时间复杂度为 O(1)
2. 使用哈希表记录, 能够较好地节约内存, 因为次数可能会很大, 并且不连续. 如果使用数组存储的话, 会消耗内存; 如果使用链表存储的话, 需要线性时间去查找匹配的访问次数.
3. 同样使用哈希表去记录键值对, 能够在 O(1)时间复杂度下进行访问.

至于当前最小的频率是多少, 只需要维护 minFreq. 当新插入值当时候, 直接设置为 1. 当某一个频率的链表大小为 0 时, 并且该频率==minFreq 时, 代表最小频率的链表里面已经没有数据了. 也需要将 minFreq++.

Code:

```Java
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

class Node {
    int key, val, freq;
    Node pre, next;

    public Node(int key, int val, int freq, Node pre, Node next) {
        this.key = key;
        this.val = val;
        this.next = next;
        this.pre = pre;
        this.freq = freq;
    }
}

class LinkList {
    Node head;
    int size;

    public LinkList() {
        Node node = new Node(-1, -1, -1, null, null);
        node.pre = node;
        node.next = node;
        this.head = node;
    }

    void add(Node n) {
        n.pre = head;
        n.next = head.next;
        head.next.pre = n;
        head.next = n;
        size++;
    }

    Node remove(Node n) {
        n.pre.next = n.next;
        n.next.pre = n.pre;
        n.next = null;
        n.pre = null;
        size--;
        return n;
    }

    Node poll() {
        Node n = head.pre;
        remove(n);
        return n;
    }
}

class LFUBuffer {
    Map<Integer, LinkList> freqMap;
    Map<Integer, Node> nodeMap;
    int cap;
    int size;
    int minFreq;

    public LFUBuffer(int capacity) {
        freqMap = new HashMap<>();
        nodeMap = new LinkedHashMap<>();
        cap = capacity;
        size = 0;
    }

    public int get(int key) {
        if (!nodeMap.containsKey(key)) {
            return -1;
        }
        Node node = nodeMap.get(key);
        LinkList preList = freqMap.get(node.freq);
        preList.remove(node);
        if (preList.size == 0) {
            if (minFreq == node.freq) {
                minFreq++;
            }
            freqMap.remove(node.freq);
        }
        node.freq++;
        if (!freqMap.containsKey(node.freq)) {
            freqMap.put(node.freq, new LinkList());
        }
        LinkList idxList = freqMap.get(node.freq);
        idxList.add(node);
        return node.val;
    }

    public void put(int key, int value) {
        if (nodeMap.containsKey(key)) {
            Node node = nodeMap.get(key);
            node.val = value;
            this.get(key);
            return;
        } else if (size == cap) {
            Node n = freqMap.get(minFreq).poll();
            nodeMap.remove(n.key);
            size--;
        }
        Node node = new Node(key, value, 1, null, null);
        nodeMap.put(key, node);
        minFreq = 1;
        if (!freqMap.containsKey(1)) {
            freqMap.put(1, new LinkList());
        }
        LinkList list = freqMap.get(1);
        list.add(node);
        size++;
    }
}
```

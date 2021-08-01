---
title: n皇后问题
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
categories: 技术
date: 2020-11-05 16:49:45
comments: true
tags: 
 - 算法
 - 回溯法
 - 递归法
keywords: n皇后
description: n皇后问题解决
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.1/image/cha1.jpg
---


N皇后问题是一个经典的问题，在一个N*N的棋盘上放置N个皇后，每行一个并使其不能互相攻击（同一行、同一列、同一斜线上的皇后都会自动攻击）  

## 递归法

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int q[N];
int cont = 0;
void print(int n) {
    int i, j;
    cont++;
    printf("第%d个解：", cont);
    printf("\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (q[i] != j)
                printf("* ");
            else
                printf("Q ");
        }
        printf("\n");
    }
}
int find(int i, int k) {
    int j = 1;
    while (j < i) {
        if (q[j] == k || abs(j - i) == abs(q[j] - k)) return 0;
        j++;
    }
    return 1;
}
void place(int k, int n) {
    int j;
    if (k > n) {
        print(n);
    } else {
        for (j = 1; j <= n; j++) {
            if (find(k, j)) {
                q[k] = j;
                place(k + 1, n);
            }
        }
    }
}
int main(void) {
    int n;
    printf("请输入皇后的个数:");
    scanf("%d", &n);
    printf("%d皇后问题求解如下(每列的皇后所在的行数):\n", n);
    place(1, n);
    printf("\n");
    return 0;
}
```

## 回溯法

```c++
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define QUEEN 8     //皇后的数目
#define INITIAL -10000   //棋盘的初始值

int a[QUEEN];    //一维数组表示棋盘

void init(){
    int *p;
    for (p = a; p < a + QUEEN; ++p) {
        *p = INITIAL;
    }
} 
int valid(int row, int col) {
    int i;
    for (i = 0; i < QUEEN; ++i){
        if (a[i] == col || abs(i - row) == abs(a[i] - col))   //判断列冲突与斜线上的冲突
            return 0;
    }
    return 1;
} 
void print() {
    int i, j;
    for (i = 0; i < QUEEN; ++i) {
        for (j = 0; j < QUEEN; ++j) {
            if (a[i] != j)      //a[i]为初始值
                printf("%c ", '.');
            else                //a[i]表示在第i行的第a[i]列可以放置皇后
                printf("%c ", '#');
        }
        printf("\n");
    }
    for (i = 0; i < QUEEN; ++i)
        printf("%d ", a[i]);
    printf("\n");
    printf("--------------------------------\n");
}
 
void queen() {
    int n = 0;
    int i = 0, j = 0;
    while (i < QUEEN){
        while (j < QUEEN) {
            if(valid(i, j)) {
                a[i] = j;        //第i行放置皇后
                j = 0;           //第i行放置皇后以后，需要继续探测下一行的皇后位置，所以此处将j清零，从下一行的第0列开始逐列探测
                break;
            }
            else {
                ++j;             //继续探测下一列
            }
        }
        if(a[i] == INITIAL) {
            if (i == 0)             //回溯到第一行，仍然无法找到可以放置皇后的位置，则说明已经找到所有的解，程序终止
                break;
            else {
                --i;
                j = a[i] + 1;        //把上一行皇后的位置往后移一列
                a[i] = INITIAL;      //把上一行皇后的位置清除，重新探测
                continue;
            }
        }
        if (i == QUEEN - 1) {
            printf("answer %d : \n", ++n);
            print();
            //不能在此处结束程序，因为我们要找的是N皇后问题的所有解，此时应该清除该行的皇后，从当前放置皇后列数的下一列继续探测。
            //_sleep(600);
            j = a[i] + 1;             //从最后一行放置皇后列数的下一列继续探测
            a[i] = INITIAL;           //清除最后一行的皇后位置
            continue;
        }
        ++i;              //继续探测下一行的皇后位置
    }
}
 
int main(void){
    init();
    queen();
    system("pause");
    return 0;
}
```

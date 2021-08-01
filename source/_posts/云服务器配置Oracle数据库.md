---
title: 云服务器中快速配置Oracle数据库
date: 2021-5-31 18:27:15
author: Ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc: 
categories: 技术
comments: true
tags: 
 - Docker
 - Oracle
 - 云服务器
keywords: 数据库
description: 在云服务器的Linux系统中使用docker配置本地能用的oracle数据库
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.45/2021.5.20/54238455_p0.jpg
---

# 前言

这个学期学了一门叫做**高级数据库**的课程，相信学过的都知道，基本上是在说Oracle数据库。而在这门课的实验中，就需要使用到Oracle数据库来进行一些实验。但是，问题出现在学校的课程安排和电脑配置上，这次的实验课只有三次，而我正好因为一些事耽误了一节，所以现在就需要我在自己的电脑上进行实验。但是，我没想到这才是问题的开始。

在上个学期，我更换了我的电脑，我从联想拯救者迁移到了Mac mini m1，有一说一，macOS用起来太爽了，太符合我胃口了。但是它也有很多不好的地方，比如Oracle不能在MacOS上运行，这也没什么，我们不是还有万能的Docker嘛，我记得在今年年初的时候，Docker已经完成了对m1芯片的适配了，于是但我高高兴兴地打开Docker后，安装了Oracle数据库，结果在使用sqlplus登陆时一直显示`ORA-12547: TNS:lost contact`,我开始还以为是用户名或密码错了，结果上网一看，结果好像是说m1芯片现阶段不兼容...把我给整无语了。

最后想起我室友就是使用了阿里云的云服务器搭建了一个Oracle，还能在学校的电脑上使用，这不是太方便了嘛，于是我想起了我以前在vultr存的几十块钱还没用呢，这不是正好可以用来租几个云服务器嘛。于是便开始了踩坑之旅...( ；´Д｀)

在踩完坑后，发觉如果没有一些博客的指导，我肯定需要更长的时间。所以打算将这次的经历分享出来，反馈自己的经验，让更多人受益。

# 配置流程

## 配置准备

想要配置一个云服务器作为Oracle数据库，当然不是免费的，需要完成一下几项：

1. 拥有一个云服务器(不管是国外的还是国外的，能用就行)
2. 本地ssh连接工具(当然一般的云服务器在网页中也会有控制台，但是我觉得还是本地连接好用一点)
3. 数据库连接工具

## 租借云服务器

因为我使用的是vultr的服务，在此只指导如何在vultr中搭建。

![](https://i.loli.net/2021/05/31/E7GaMxpCVFB3W48.png)

点击图标中的按钮，可以查看自己的余额，要想租借一个服务器，需要余额在5美元以上。(可以使用支付宝，支付宝的英文为Alipay)

然后进入Products页面，看到自己的服务器空空如也，是不是很伤心呢？没事，只要点击右边的小加号，就可以选择自己心仪的服务器啦～(´▽｀)

首先选择服务类型，选择 Cloud Compute
![](https://i.loli.net/2021/05/31/zWClaLUQt1M72uR.png)

然后选择服务器的地区，我选择的是Atlanta，这个根据你的位置可能网速有所差别。

![](https://i.loli.net/2021/05/31/T5SokrFAbqEPJVB.png)

然后选择服务器的系统，我们选择CentOS的7x64版本，我也没用过其他版本，怕出问题，在此唠叨一句。╮(╯▽╰)╭

![](https://i.loli.net/2021/05/31/KOetNmhrdoQxXTW.png)

最后选择服务器的资源大小，一般选择5美金每月的就可以了，如果有更大的需求，可以考虑其他的。

![](https://i.loli.net/2021/05/31/mTNug4p9vSGVnjO.png)

全部选择好以后，就可以点击“Deploy Now”拥有自己的云服务器啦！

## 连接云服务器

相信有很多人和我一样，不知道如何使用云服务器。

我们可以打开“Products”，然后就可以看到自己正在运行的云服务器了，接下来只用点击状态，或者在扩展选项中查看详情，就可以进入服务器的详细页面。

![](https://i.loli.net/2021/05/31/V7NmsQA1b2hTYg3.png)

在这个页面中，最重要的几个信息就是服务器的IP地址、用户名以及密码了。请妥善保管好。

![](https://i.loli.net/2021/05/31/WPfIcyiDlp9vZhL.png)

然后就可以在自己的ssh工具中连接啦

在此放入我的示例：

```
% ssh {这里是你的云服务器的用户名哦}@{这里是你的云服务的IP地址哦}
root@155.138.207.121's password: 
Last failed login: Mon May 31 11:43:13 UTC 2021 from 91-115-102-148.adsl.highway.telekom.at on ssh:notty
There were 1206 failed login attempts since the last successful login.
Last login: Sun May 30 07:10:12 2021 from 117.152.144.111
[root@vultr ~]# 
```

如果显示 “successful login”就代表连接成功啦。
[tips：第二行的password后输入是不会显示的，但是记得要输入密码才能进入云服务器哦～]

## 安装Docker

安装命令如下：

`curl -fsSL https://get.docker.com | bash -s docker --mirror aliyun`

直接在连接后的云服务器中输入就好了

## 使用docker安装oracle

确定自己可以使用`docker --version`查看自己的docker版本，代表已经成功安装docker啦，一下我们来看看怎么使用docker安装oracle。然后使用`docker ps`查看docker是否正在运行，如果没有运行，可以使用`systemctl start docker`来启动docker

首先要知道带图形化带oracle是很大的，而我们需要安装的只不过是oracle内核，因此我们需要搜索`docker-oracle-xe-11g`是否有合适的docker版本。

因此我们可以使用docker search命令：

```
[root@vultr ~]# docker search docker-oracle-xe-11g
NAME                                 DESCRIPTION                                     STARS     OFFICIAL   AUTOMATED
deepdiver/docker-oracle-xe-11g                                                       40                   [OK]
epiclabs/docker-oracle-xe-11g        Customized Oracle XE 11g build for CI and de…   19                   [OK]
pengbai/docker-oracle-xe-11g-r2      oracle xe 11g r2 with sql initdb and web con…   10                   [OK]
arahman/docker-oracle-xe-11g         phusion/baseimage based spin off of alexei-l…   9                    [OK]
konnecteam/docker-oracle-xe-11g      Fork of https://github.com/wnameless/docker-…   3                    [OK]
rafaelri/docker-oracle-xe-11g        Fork from wnameless/docker-oracle-xe-11g        3                    [OK]
ignatov/docker-oracle-xe-11g         Dockerfile of Oracle Database Express Editio…   3                    [OK]
gswteam/docker-oracle-xe-11g         Oracle XE 11g                                   0                    [OK]
jeromefromcn/docker-oracle-xe-11g    docker-oracle-xe-11g                            0                    [OK]
nguoianphu/docker-oracle-xe-11g      Oracle Express Edition 11g Release 2 on Ubun…   0                    [OK]
lynxsolutions/docker-oracle-xe-11g   docker-oracle-xe-11g                            0                    [OK]
zzzfree/docker-oracle-xe-11g         docker-oracle-xe-11g                            0                    [OK]
deadok22/docker-oracle-xe-11g        docker-oracle-xe-11g                            0                    
rdehuyss/docker-oracle-xe-11g        Oracle Express 11g R2 on Ubuntu 14.04.2 LTS     0                    [OK]
dbanttari/docker-oracle-xe-11g       Branch of wnameless/docker-oracle-xe-11g tha…   0                    [OK]
bizybot/docker-oracle-xe-11g         wnameless/docker-oracle-xe-11g                  0                    [OK]
xtechnologies/docker-oracle-xe-11g   docker-oracle-xe-11g                            0                    [OK]
cheyu0325/docker-oracle-xe-11g       docker-oracle-xe-11g                            0                    
kikicarbonell/docker-oracle-xe-11g   Docker image of Oracle Database Express Edit…   0                    [OK]
ceagan/docker-oracle-xe-11g          Modified version of wnameless/docker-oracle-…   0                    [OK]
zigac/docker-oracle-xe-11g           Oracle xe 11g                                   0                    [OK]
demers/docker-oracle-xe-11g-spark    Oracle XE 11g with Spark                        0                    
dockerbolcom/docker-oracle-xe-11g    Fork of https://github.com/wnameless/docker-…   0                    [OK]
gmartsenkov/docker-oracle-xe-11g     oracle                                          0                    [OK]
demers/docker-oracle-xe-11g          Docker Oracle 11g XE with Java 13 and Python…   0                    

```

可以看到有这么多的oracle版本，我选择的是`epiclabs/docker-oracle-xe-11g`，选择自己喜欢的就好。

然后使用`docker pull epiclabs/docker-oracle-xe-11g`命令拉取镜像到本地就好了(不得不说国外的服务器拉取资源太TM快了，这速度，得有50MB/s吧)

然后启动镜像为一个容器就成功了，命令如下：

`docker run -h "oracle" --name "oracle" -d -p 49160:22 -p 49161:1521 -p 49162:8080 epiclabs/docker-oracle-xe-11g`

解释一个这个命令就是：

- docker run    表示运行一个镜像
- -h "oracle"   表示将这个容器的hostname指定为 “oracle”
- --name “oracle”   表示制定这个容器的名称为 “oracle”
- -d 表示后台运行容器
- -p 表示端口映射，格式为 {这个是主机端口}:{这个是容器端口}, 因为oracle默认端口为1521，因此我们配置 `49161:1521`，表示主机端口号49161就可以访问到oracle的端口了。
- 最后面是docker要运行的容器名

最后使用命令`docker ps`可以查看正在运行的容器。如果显示oracle已经启动，表示成功了。

## 连接Oracle数据库

在此只分享使用IDEA连接的截图，其他工具连接大同小异。

![](https://i.loli.net/2021/05/31/HrfxzYIk1qcNeVL.png)

其中用户名和密码，可以在网络上查找oracle数据库的默认密码

连接后就可以愉快地操作数据库啦～(´▽｀)

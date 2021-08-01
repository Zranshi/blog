---
title: 学习JavaWeb
date: 2020-11-14 16:02:47
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc: 
categories: 技术
comments: true
tags: 
 - JavaWeb
 - Tomcat
 - Servlet
keywords: javaweb学习
description: JavaWeb学习
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/19.jpg
---


# 学习Java web

## Tomcat（web服务器软件）

1. 下载：[http://tomcat.apache.org/](http://tomcat.apache.org/)
2. 安装：解压压缩包即可。
    * 注意：安装目录中不能有空格和中文
3. 卸载：删除文件夹即可
4. 启动：
    * 双击文件：startup.bat
    * 访问：浏览器输入：`http://localhost:8080 （默认，可以修改）`
    * 访问：浏览器输入：`http://别人的ip:8080 （访问别人）`
    * 可能遇到的问题：
        1. 黑屏一闪而过：
            * 原因：没有正确配置JAVA_HOME环境变量
            * 解决方法：正确配置JAVA_HOME环境变量
        2. 启动报错：
            1. 暴力：找到占用的端口号，并找到对应的进程，杀死该进程
                `netstat -ano`
            2. 温柔：修改自身的端口号
                `conf/server.xml`

                ```
                <Connector port="80" protocol="HTTP/1.1"
                connectionTimeout="20000"
                redirectPort="8443" />
                ```

                * 一般将tomcat的默认端口号改为80，80端口号是http协议的默认端口号。
                    好处：在访问时，就不用输入端口号
5. 关闭：
    1. 正常关闭：
        * bin/shutdown.bat
        * ctrl+c
    2. 强制关闭：
        * 点击启动窗口的“x”
6. 配置：
    * 部署项目的方式：
        1. 直接将项目放到webapps目录下即可。
            * /hello：项目的访问路径-->虚拟目录
            * 简化部署：将项目打成一个war包，再将war包放置到webapps目录下。
                war包会自动解压缩，并且删除war包后，项目文件夹会自动删除。
        2. 配置conf/server.xml文件
            * 在<Host>标签体中配置
                `<Context docBase="文件路径" path="虚拟目录">`
        3. 在conf/Catalina/localhost创建任意名称的xml文件。在文件里面编写
        `<Context docBase="文件路径" />`
            * 虚拟目录：xml文件的名称

***

## 学习servlet (server applet)

### Servlet基础

* 概念：运行在服务器端的小程序
  * servlet就是一个接口，定义了Java类被浏览器访问到（tomcat识别）的规则。
  * 将来我们自定义一个类，实现servlet接口，复写方法。
* 快速入门
  * 创建一个javaEE项目
  * 定义一个类，实现servlet接口。
        `public class servletDemo1 implements Servlet`
  * 实现接口中的抽象方法
  * 配置servlet

    ```
    <!--配置servlet-->
    <servlet>
        <servlet-name>demo1</servlet-name>
        <servlet-class>web.servletDemo1</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>demo1</servlet-name>
        <url-pattern>/demo1</url-pattern>
    </servlet-mapping>
    ```

* 执行原理：
  * 当服务器接收到客户端浏览器的请求后，会解析请求URL路径，获取访问的Servlet的资源路径
  * 查找web.xml文件，是否有对应的<url-pattern\>标签体内容。
  * 如果有，则在找到对应的<servlet=class\>全类名。
  * tomcat会将字节码文件加载进内存，并且创建其对象
  * 调用其方法
* Servlet中的生命周期方法：
  * init()
    * 初始化方法<br>在Servlet被创建时执行，只会执行一次。
    * 默认情况下，Servlet被访问时，Servlet被创建。
    * 可以指定Servlet的创建时期。
            1.第一次被访问时，创建
            `<load-on-stratup>`的值为负数
            2.在服务器启动时，创建
            `<load-on-stratup>`的值为正数
    * Servlet的init方法，只执行一次，说明一个Servlet在内存中只存在一个对象，Servlet时单例的。
      * 多个用户同时访问时，可能存在线程安全问题。
      * 解决方法：尽量不要在Servlet中定义成员变量。即使定义了成员变量也不要对其修改值。
  * service()
    * 提供服务的方法<br>每一次Servlet被访问时执行，执行多次。
      * 每次访问Servlet时，service方法都被调用一次
  * destroy()
    * 销毁方法<br>在服务器正在关闭时执行，执行一次。
      * Servlet被销毁时执行。服务器关闭时，Servlet被销毁。
      * 只有服务器正常关闭时，才会执行destroy方法。
      * destroy方法在Servlet销毁之前执行。
  * ServletConfig()
    * 获取ServletConfig对象<br>ServletConfig: servlet的配置对象
  * getServletInfo()
    * 获取Servlet的一些信息：版本、作者。

* Servlet3.0：
  * 好处：
    * 支持注解配置，可以不需要web.xml了。
  * 步骤：
        1.创建JavaEE项目，选择Servlet 3.0以上的版本
        2.定义一个类，实现Servlet接口
        3.复写方法
        4.在类上使用@WebServlet注解，进行配置
        `@WebServlet("资源路径")`

### IDEA与tomcat的相关配置

1. IDEA会为每一个tomcat部署的项目单独建立一份配置文件
    * 查看控制台的log：`Using CATALINA_BASE:   "C:\Users\78293\AppData\Local\JetBrains\IntelliJIdea2020.1\tomcat\Tomcat_8_5_59_ServletUp3_0"
`
2. 工作空间项目 和 tomcat部署的web项目
    * tomcat真正访问的是“tomcat部署的web项目”，“tomcat不是的web项目”对应着“工作空间项目” 的web目录下的所有资源
    * WEB-INF目录下的资源不能被浏览器直接访问
3. 断电调试：使用“小虫子”启动debug 启动

### servlet体系结构

servlet -- 接口
        |
GenericServlet -- 抽象类
        |
HttpServlet -- 抽象类

* GenericServlet : 将Servlet 接口中其它的方法做了默认空实现，只将service()方法作为抽象
  * 将来定义Servlet类时，可以继承GernericServlet,实现service()方法即可。
* HttpServlet： 对http协议的一种封装，简化操作
    1.定义类继承HttpServlet
    2.复写doGet/doPost两个方法

### Servlet相关配置

* urlpartten: Servlet访问路径
    1.一个Servlet可以定义多个访问路径： webServlet({"/d4","/dd4","/ddd4"})
    2.路径的定义规则：
    *
        1./xxx
        2./xxx/xxx 多层路径，目录结构
        3.*.do

---

## Http

* 概念：Hyper Text Transfer Protocol(超文本传输协议)
  * 传输协议：定义了，客户端于服务器端发送数据的格式
  * 特点：
        1.基于TCP/IP 的高级协议
        2.默认端口号是：80  ```http://www.itcast.cn:80```
        3.基于请求/响应模型的：一次请求对应一次响应
        4.无状态的协议：每次请求之间都相互独立，不能交互数据
  * 历史版本：
        1.0：每一次请求响应夺回建立新的连接
        1.1：复用连接
* 请求消息数据格式
    1. 请求行
        请求方式 请求url 请求协议/版本
        GET /login.html HTTP/1.1
        * 请求方式：
            HTTP协议有7种请求方式，常用的有2种
            GET:
            1.请求参数在请求行中，在url后
            2.请求的url长度有限制
            3.不太安全
            POST:
            1.请求参数在请求体中
            2.请求的url长度没有限制
            3.相对安全
    2. 请求头:客户端告诉服务器端的一些信息
        请求头名称： 请求头值：
        常见的请求头：
        1. User-Agent：浏览器告诉服务器，我访问你使用的浏览器的版本信息
            可以在服务器端获取该头文件信息，解决浏览器的兼容性问题
        2. Referer:`http://localhost/login.html`
            告诉服务器，我（当前请求）从哪里来？
            作用：
            1.防盗链
            2.统计工作

    3. 请求空行
        空行，就是用于分隔POST请求的请求头和请求体的
    4. 请求体(正文)
        封装POST请求消息的请求参数的

* 访问消息数据模式

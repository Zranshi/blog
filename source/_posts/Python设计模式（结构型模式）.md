---
title: Python实现设计模式(结构型模式)
date: 2020-12-1 17:02:19
author: ranshi
avatar: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.0/img/custom/avatar.jpg
authorLink: https://github.com/Zranshi
authorAbout: 成为更好的自己，才能守护最好的你
authorDesc: 
categories: 技术
comments: true
tags: 
 - 设计模式
 - Python
keywords: 设计模式(结构型模式)
description: 用Python实现设计模式(结构型模式)
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/33.jpg
---
## [适配器模式](https://refactoringguru.cn/design-patterns/adapter)

适配器模式是一种结构型设计模式， 它能使接口不兼容的对象能够相互合作。
对象适配器：
![对象适配器](https://refactoringguru.cn/images/patterns/diagrams/adapter/structure-object-adapter.png)
类适配器：
![类适配器](https://refactoringguru.cn/images/patterns/diagrams/adapter/structure-class-adapter.png)

### Python代码

```python
# 目标类
class Target:
    def request(self) -> str:
        return "Target: The default target's behavior."

# 待适配的类
class Adaptee:
    def specific_request(self) -> str:
        return ".eetpadA eht fo roivaheb laicepS"

# 适配器
class Adapter(Target, Adaptee):
    def request(self) -> str:
        return f"Adapter: (TRANSLATED) {self.specific_request()[::-1]}"


def client_code(target: "Target") -> None:
    print(target.request(), end="")


if __name__ == "__main__":
    print("Client: I can work just fine with the Target objects:")
    target = Target()
    client_code(target)
    print('\n')
    adaptee = Adaptee()
    print("Client: The Adaptee class has a weird interface. "
          "See, I don't understand it:")
    print(f"Adaptee: {adaptee.specific_request()}", end="\n\n")

    print("Client: But I can work with it via the Adapter:")
    adapter = Adapter()
    client_code(adapter)

# output:
# Client: I can work just fine with the Target objects:
# Target: The default target's behavior.

# Client: The Adaptee class has a weird interface. See, I don't understand it:
# Adaptee: .eetpadA eht fo roivaheb laicepS

# Client: But I can work with it via the Adapter:
# Adapter: (TRANSLATED) Special behavior of the Adaptee.
```

---

## [桥接模式](https://refactoringguru.cn/design-patterns/bridge)

桥接模式是一种结构型设计模式， 可将一个大类或一系列紧密相关的类拆分为抽象和实现两个独立的层次结构， 从而能在开发时分别使用。

![桥接模式](https://refactoringguru.cn/images/patterns/diagrams/bridge/structure-zh.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod


class Abstraction:
    def __init__(self, implementation: Implementation) -> None:
        self.implementation = implementation

    def operation(self) -> str:
        return (f"Abstraction: Base operation with:\n"
                f"{self.implementation.operation_implementation()}")


class ExtendedAbstraction(Abstraction):
    def operation(self) -> str:
        return (f"ExtendedAbstraction: Extended operation with:\n"
                f"{self.implementation.operation_implementation()}")


class Implementation(ABC):
    @abstractmethod
    def operation_implementation(self) -> str:
        pass


class ConcreteImplementationA(Implementation):
    def operation_implementation(self) -> str:
        return "ConcreteImplementationA: Here's the result on the platform A."


class ConcreteImplementationB(Implementation):
    def operation_implementation(self) -> str:
        return "ConcreteImplementationA: Here's the result on the platform B."


def client_code(abstraction: Abstraction) -> None:
    print(abstraction.operation(), end='')


if __name__ == "__main__":
    implementation = ConcreteImplementationA()
    abstraction = Abstraction(implementation)
    client_code(abstraction)
    print('\n')
    implementation = ConcreteImplementationB()
    abstraction = ExtendedAbstraction(implementation)
    client_code(abstraction)

# output:
# Abstraction: Base operation with:
# ConcreteImplementationA: Here's the result on the platform A.

# ExtendedAbstraction: Extended operation with:
# ConcreteImplementationA: Here's the result on the platform B.
```

---

## [组合模式](https://refactoringguru.cn/design-patterns/composite)

组合模式是一种结构型设计模式， 你可以使用它将对象组合成树状结构， 并且能像使用独立对象一样使用它们。  
在日常生活中类似于军队的管理模式，最高指挥官如果要下发一个通知，只需通知直接管辖的属下，然后会依次通知到每一个人。
而组合模式就是将对象构建成这样的结构的模式
![组合模式](https://refactoringguru.cn/images/patterns/diagrams/composite/structure-zh.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


class Component(ABC):
    """
    组件 （Component） 接口描述了树中简单项目和复杂项目所共有的操作。
    """
    @property
    def parent(self) -> Component:
        return self._parent

    @parent.setter
    def parent(self, parent: Component):
        self._parent = parent

    def add(self, component: Component) -> None:
        pass

    def remove(self, component: Component) -> None:
        pass

    def is_composite(self) -> bool:
        return False

    @abstractmethod
    def operation(self) -> str:
        pass


class Leaf(Component):
    """
    叶节点 （Leaf） 是树的基本结构， 它不包含子项目。
    一般情况下， 叶节点最终会完成大部分的实际工作， 因为它们无法将工作指派给其他部分。
    """
    def operation(self) -> str:
        return 'Leaf'


class Composite(Component):
    '''
    容器 （Container）——又名 “组合 （Composite）”——是包含叶节点或其他容器等子项目的单位。 
    容器不知道其子项目所属的具体类， 它只通过通用的组件接口与其子项目交互。
    容器接收到请求后会将工作分配给自己的子项目， 处理中间结果， 然后将最终结果返回给客户端。
    '''
    def __init__(self) -> None:
        self._children: List[Component] = []

    def add(self, component: Component) -> None:
        self._children.append(component)
        component.parent = self

    def remove(self, component: Component) -> None:
        self._children.remove(component)
        component.parent = None

    def is_composite(self) -> bool:
        return True

    def operation(self) -> str:
        results = []
        for child in self._children:
            results.append(child.operation())
        return f"Branch({'+'.join(results)})"


def client_code(component: Component) -> None:
    print(f"RESULT: {component.operation()}", end="")


def client_code2(component1: Component, component2: Component) -> None:
    if component1.is_composite():
        component1.add(component2)

    print(f"RESULT: {component1.operation()}", end="")


if __name__ == "__main__":
    simple = Leaf()
    print("Client: I've got a simple component:")
    client_code(simple)
    print('\n')
    tree = Composite()
    branch1 = Composite()
    branch1.add(Leaf())
    branch1.add(Leaf())
    branch2 = Composite()
    branch2.add(Leaf())

    tree.add(branch1)
    tree.add(branch2)

    print("Client: Now I've got a composite tree:")
    client_code(tree)
    print("\n")

    print("Client: I don't need to check the components classes even when managing the tree:")
    client_code2(tree, simple)

# output:
# Client: I've got a simple component:
# RESULT: Leaf

# Client: Now I've got a composite tree:
# RESULT: Branch(Branch(Leaf+Leaf)+Branch(Leaf))

# Client: I don't need to check the components classes even when managing the tree:
# RESULT: Branch(Branch(Leaf+Leaf)+Branch(Leaf)+Leaf)
```

---

## [装饰模式](https://refactoringguru.cn/design-patterns/decorator)

装饰模式是一种结构型设计模式，允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为。

![装饰模式](https://refactoringguru.cn/images/patterns/diagrams/decorator/structure.png)

### Python代码

```python
class Component():
    '''
    部件 （Component） 声明封装器和被封装对象的公用接口。
    '''
    def operation(self) -> str:
        pass


class ConcreteComponent(Component):
    '''
    具体部件 （Concrete Component） 类是被封装对象所属的类。 它定义了基础行为， 但装饰类可以改变这些行为。
    '''
    def operation(self) -> str:
        return 'ConcreteComponent'


class Decorator(Component):
    '''
    基础装饰 （Base Decorator） 类拥有一个指向被封装对象的引用成员变量。 
    该变量的类型应当被声明为通用部件接口， 这样它就可以引用具体的部件和装饰。 
    装饰基类会将所有操作委派给被封装的对象。
    '''
    _component: Component = None

    def __init__(self, component: Component) -> None:
        self._component = component

    @property
    def component(self) -> str:
        return self._component

    def operation(self) -> str:
        return self._component.operation()


class ConcreteDecoratorA(Decorator):
    '''
    具体装饰类 （Concrete Decorators） 定义了可动态添加到部件的额外行为。
    具体装饰类会重写装饰基类的方法， 并在调用父类方法之前或之后进行额外的行为。
    '''
    def operation(self) -> str:
        return f"ConcreteDecoratorA({self.component.operation()})"


class ConcreteDecoratorB(Decorator):
    def operation(self) -> str:
        return f"ConcreteDecoratorB({self.component.operation()})"


def client_code(component: Component) -> None:
    print(f"RESULT: {component.operation()}", end="")


if __name__ == "__main__":
    simple = ConcreteComponent()
    print("Client: I've got a simple component")
    client_code(simple)
    print('\n')

    decorator1 = ConcreteDecoratorA(simple)
    decorator2 = ConcreteDecoratorB(simple)
    print("Client: Now I've got a decorated component:")
    client_code(decorator2)

# output:
# Client: I've got a simple component
# RESULT: ConcreteComponent

# Client: Now I've got a decorated component:
# RESULT: ConcreteDecoratorB(ConcreteComponent)
 ```

---

## [外观模式](https://refactoringguru.cn/design-patterns/facade)

 外观模式是一种结构型设计模式， 能为程序库、 框架或其他复杂类提供一个简单的接口。
 ![外观模式](https://refactoringguru.cn/images/patterns/diagrams/facade/structure.png)

### Python代码

 ```python
from __future__ import annotations


class Facade:
    '''
    外观 （Facade） 提供了一种访问特定子系统功能的便捷方式， 
    其了解如何重定向客户端请求， 知晓如何操作一切活动部件。
    '''
    def __init__(self, subsystem1: Subsystem1, subsystem2: Subsystem2) -> None:
        self._subsystem1 = subsystem1 or Subsystem1()
        self._subsystem2 = subsystem2 or Subsystem2()

    def operation(self) -> str:
        results = []
        results.append("Facede initializes subsystems:")
        results.append(self._subsystem1.operation1())
        results.append(self._subsystem2.operation1())
        results.append("Facade orders subsystems to perform the action:")
        results.append(self._subsystem1.operation_n())
        results.append(self._subsystem2.operation_z())
        return "\n".join(results)


class Subsystem1:
    '''
    复杂子系统 （Complex Subsystem） 由数十个不同对象构成。 
    如果要用这些对象完成有意义的工作， 你必须深入了解子系统的实现细节， 
    比如按照正确顺序初始化对象和为其提供正确格式的数据。
    子系统类不会意识到外观的存在， 它们在系统内运作并且相互之间可直接进行交互。
    '''
    def operation1(self) -> str:
        return "Subsystem1: Ready!"

    def operation_n(self) -> str:
        return "Subsystem1: Go!"


class Subsystem2:
    def operation1(self) -> str:
        return "Subsystem2: Get ready!"

    def operation_z(self) -> str:
        return "Subsystem2: Fire!"


def client_code(facade: Facade) -> None:
    print(facade.operation(), end="")


if __name__ == "__main__":
    subsystem1 = Subsystem1()
    subsystem2 = Subsystem2()
    facade = Facade(subsystem1, subsystem2)
    client_code(facade)


# output:
# Facede initializes subsystems:
# Subsystem1: Ready!
# Subsystem2: Get ready!
# Facade orders subsystems to perform the action:
# Subsystem1: Go!
# Subsystem2: Fire!
 ```

 ---

## [享元模式](https://refactoringguru.cn/design-patterns/flyweight)

享元模式是一种结构型设计模式， 它摒弃了在每个对象中保存所有数据的方式， 通过共享多个对象所共有的相同状态， 让你能在有限的内存容量中载入更多对象。
![享元模式](https://refactoringguru.cn/images/patterns/diagrams/flyweight/structure.png)

### Python代码

```python
import json
from typing import Dict


class Flyweight():
    '''
    享元 （Flyweight） 类包含原始对象中部分能在多个对象中共享的状态。 
    同一享元对象可在许多不同情景中使用。 享元中存储的状态被称为 “内在状态”。 
    传递给享元方法的状态被称为 “外在状态”。
    '''
    def __init__(self, shared_state: str) -> None:
        self._shared_state = shared_state

    def operation(self, unique_state: str) -> None:
        s = json.dumps(self._shared_state)
        u = json.dumps(unique_state)
        print(
            f"Flyweight: Displaying shared ({s}) and unique ({u}) state.", end="")


class FlyweightFactory():
    '''
    享元工厂 （Flyweight Factory） 会对已有享元的缓存池进行管理。 
    有了工厂后， 客户端就无需直接创建享元， 它们只需调用工厂并向其传递目标享元的一些内在状态即可。 
    工厂会根据参数在之前已创建的享元中进行查找， 如果找到满足条件的享元就将其返回； 
    如果没有找到就根据参数新建享元。
    '''
    _flyweights: Dict[str, Flyweight] = {}

    def __init__(self, initial_flyweights: Dict) -> None:
        for state in initial_flyweights:
            self._flyweights[self.get_key(state)] = Flyweight(state)

    def get_key(self, state: Dict) -> str:
        return '_'.join(sorted(state))

    def get_flyweight(self, shared_state: Dict) -> Flyweight:
        key = self.get_key(shared_state)
        if not self._flyweights.get(key):
            print("FlyweightFactory: Can't find a flyweight, creating new one.")
            self._flyweights[key] = Flyweight(shared_state)
        else:
            print("FlyweightFactory: Reusing existing flyweight.")
        return self._flyweights[key]

    def list_flyweights(self) -> None:
        count = len(self._flyweights)
        print(f"FlyweightFactory: I have {count} flyweights:")
        print("\n".join(map(str, self._flyweights.keys())), end="")


def add_car_to_police_database(
    factory: FlyweightFactory, plates: str, owner: str,
    brand: str, model: str, color: str
) -> None:
    print("\n\nClient: Adding a car to database.")
    flyweight = factory.get_flyweight([brand, model, color])
    flyweight.operation([plates, owner])


if __name__ == "__main__":
    factory = FlyweightFactory([
        ["Chevrolet", "Camaro2018", "pink"],
        ["Mercedes Benz", "C300", "black"],
        ["Mercedes Benz", "C500", "red"],
        ["BMW", "M5", "red"],
        ["BMW", "X6", "white"],
    ])
    factory.list_flyweights()
    add_car_to_police_database(
        factory, "CL234IR", "James Doe", "BMW", "M5", "red")
    add_car_to_police_database(
        factory, "CL234IR", "James Doe", "BMW", "X1", "red")
    print("\n")
    factory.list_flyweights()

# output:
# FlyweightFactory: I have 5 flyweights:
# Camaro2018_Chevrolet_pink
# C300_Mercedes Benz_black
# C500_Mercedes Benz_red
# BMW_M5_red
# BMW_X6_white

# Client: Adding a car to database.
# FlyweightFactory: Reusing existing flyweight.
# Flyweight: Displaying shared (["BMW", "M5", "red"]) and unique (["CL234IR", "James Doe"]) state.

# Client: Adding a car to database.
# FlyweightFactory: Can't find a flyweight, creating new one.
# Flyweight: Displaying shared (["BMW", "X1", "red"]) and unique (["CL234IR", "James Doe"]) state.

# FlyweightFactory: I have 6 flyweights:
# Camaro2018_Chevrolet_pink
# C300_Mercedes Benz_black
# C500_Mercedes Benz_red
# BMW_M5_red
# BMW_X6_white
# BMW_X1_red
```

---

## [代理模式](https://refactoringguru.cn/design-patterns/proxy)

代理模式是一种结构型设计模式， 让你能够提供对象的替代品或其占位符。 代理控制着对于原对象的访问， 并允许在将请求提交给对象前后进行一些处理。
![代理模式](https://refactoringguru.cn/images/patterns/diagrams/proxy/structure.png)

### Python代码

```python
from abc import ABC, abstractmethod


class Subject(ABC):
    @abstractmethod
    def request(self) -> None:
        pass


class RealSubject(Subject):
    def request(self) -> None:
        print('RealSubject: Handling request.')


class Proxy(Subject):
    '''
    代理 （Proxy） 类包含一个指向服务对象的引用成员变量。 
    代理完成其任务 （例如延迟初始化、 记录日志、 访问控制和缓存等） 后会将请求传递给服务对象。 
    通常情况下， 代理会对其服务对象的整个生命周期进行管理。
    '''
    def __init__(self, real_subject: RealSubject) -> None:
        self.real_subject = real_subject

    def request(self) -> None:
        if self.check_access():
            self.real_subject.request()
            self.log_access()

    def check_access(self) -> bool:
        print("Proxy: Checking access prior to firing a real request.")
        return True

    def log_access(self) -> None:
        print("Proxy: Logging the time of request.", end="")


def client_code(subject: Subject) -> None:
    subject.request()


if __name__ == "__main__":
    print("Client: Executing the client code with a real subject:")
    real_subject = RealSubject()
    client_code(real_subject)
    print("")
    print("Client: Executing the same client code with a proxy:")
    proxy = Proxy(real_subject)
    client_code(proxy)


# output:
# Client: Executing the client code with a real subject:
# RealSubject: Handling request.

# Client: Executing the same client code with a proxy:
# Proxy: Checking access prior to firing a real request.
# RealSubject: Handling request.
# Proxy: Logging the time of request.
```

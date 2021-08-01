---
title: Python实现设计模式(创建型模式)
date: 2020-11-29 16:35:19
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
keywords: 设计模式(创建型模式)
description: 用Python实现设计模式(创建型模式)
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/44.jpg
---

## [工厂模式](https://refactoringguru.cn/design-patterns/factory-method)

工厂方法模式是一种创建型设计模式， 其在父类中提供一个创建对象的方法， 允许子类决定实例化对象的类型。
如果在基类及其扩展的子类中都有一个构建方法的话， 那它可能就是工厂方法。
![工厂模式](https://refactoringguru.cn/images/patterns/diagrams/factory-method/structure.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod


# 产品的基类
class Product(ABC):
    def operation(self) -> str:
        pass


# 工厂的基类
class Creator(ABC):
    @abstractmethod
    def factory_method(self):
        pass

    def some_operation(self) -> str:
        product = self.factory_method()
        result = f"Creator: The same creator's code has just worked with {product.operation()}"
        return result


# 专门用来创建具体产品1
class ConcreteCreator1(Creator):
    def factory_method(self) -> Product:
        return ConcreteProduct1()

# 专门用来创建具体产品2
class ConcreteCreator2(Creator):
    def factory_method(self) -> Product:
        return ConcreteProduct2()

# 产品1
class ConcreteProduct1(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct1}"

# 产品2
class ConcreteProduct2(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct2}"


def client_code(creator: Creator) -> None:
    print(f"Client: I'm not aware of the creator's class, but it still works.\n"
          f"{creator.some_operation()}", end="")


if __name__ == "__main__":
    print("App: Launched with the ConcreteCreator1.")
    client_code(ConcreteCreator1())
    print("\n")

    print("App: Launched with the ConcreteCreator2.")
    client_code(ConcreteCreator2())

# output:
# App: Launched with the ConcreteCreator1.
# Client: I'm not aware of the creator's class, but it still works.
# Creator: The same creator's code has just worked with {Result of the ConcreteProduct1}

# App: Launched with the ConcreteCreator2.
# Client: I'm not aware of the creator's class, but it still works.
# Creator: The same creator's code has just worked with {Result of the ConcreteProduct2}
```

---

## [抽象工厂](https://refactoringguru.cn/design-patterns/abstract-factory)

抽象工厂是一种创建型设计模式，它能创建一系列相关或相互依赖的对象，而无需指定其具体类。

什么是 “系列对象”？例如有这样一组的对象：运输工具 + 引擎 + 控制器 。它可能会有几个变体：

* 汽车+ 内燃机+ 方向盘
* 飞机+ 喷气式发动机+ 操纵杆

如果你的程序中并不涉及产品系列的话，那就不需要抽象工厂。

再次重申， 许多人分不清抽象工厂模式和声明为 abstract的简单工厂。不要犯这个错误！
![抽象工厂](https://refactoringguru.cn/images/patterns/diagrams/abstract-factory/structure.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod

# 抽象工厂
class AbstractFactory(ABC):
    @abstractmethod
    def create_product_a(self) -> AbstractProductA:
        pass

    @abstractmethod
    def create_product_b(self) -> AbstractProductB:
        pass

# 具体工厂1
class ConcreteFactory1(AbstractFactory):
    def create_product_b(self) -> AbstractProductB:
        return ConcreteProductB1()

    def create_product_a(self) -> AbstractProductA:
        return ConcreteProductA1()

# 具体工厂2
class ConcreteFactory2(AbstractFactory):
    def create_product_a(self) -> AbstractProductA:
        return ConcreteProductA2()

    def create_product_b(self) -> AbstractProductB:
        return ConcreteProductB2()

# 抽象产品A
class AbstractProductA(ABC):
    @abstractmethod
    def useful_function_a(self) -> str:
        pass

# 具体产品A1
class ConcreteProductA1(AbstractProductA):

    def useful_function_a(self) -> str:
        return "The result of the product A1."

# 具体产品A2
class ConcreteProductA2(AbstractProductA):
    def useful_function_a(self) -> str:
        return "The result of the product A2."

# 抽象产品B
class AbstractProductB(ABC):
    @abstractmethod
    def useful_function_b(self) -> None:
        pass

    @abstractmethod
    def another_useful_function_b(self, collaborator: AbstractProductA) -> None:
        pass

# 抽象产品B1
class ConcreteProductB1(AbstractProductB):
    def another_useful_function_b(self, collaborator: AbstractProductA) -> str:
        result = collaborator.useful_function_a()
        return f"The result of the B1 collaborating with the ({result})"

    def useful_function_b(self) -> str:
        return "The result of the product B1."

# 抽象产品B2
class ConcreteProductB2(AbstractProductB):
    def useful_function_b(self) -> str:
        return "The result of the product B2."

    def another_useful_function_b(self, collaborator: AbstractProductA) -> str:
        result = collaborator.useful_function_a()
        return f"The result of the B2 collaborating with the ({result})"


def client_code(factory: AbstractFactory) -> None:
    product_a = factory.create_product_a()
    product_b = factory.create_product_b()
    print(f"{product_b.useful_function_b()}")
    print(f"{product_b.another_useful_function_b(product_a)}", end="")


if __name__ == "__main__":
    print("Client: Testing client code with the first factory type:")
    client_code(ConcreteFactory1())

    print("\n")

    print("Client: Testing the same client code with the second factory type:")
    client_code(ConcreteFactory2())

# output:
# Client: Testing client code with the first factory type:
# The result of the product B1.
# The result of the B1 collaborating with the (The result of the product A1.)

# Client: Testing the same client code with the second factory type:
# The result of the product B2.
# The result of the B2 collaborating with the (The result of the product A2.)
```

---

## [生成器](https://refactoringguru.cn/design-patterns/builder)

生成器模式是一种创建型设计模式，使你能够分步骤创建复杂对象。该模式允许你使用相同的创建代码生成不同类型和形式的对象。
生成器模式建议将对象构造代码从产品类中抽取出来， 并将其放在一个名为生成器的独立对象中。
![生成器](https://refactoringguru.cn/images/patterns/diagrams/builder/structure.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod, abstractproperty
from typing import Any

# 生成器接口
class Builder(ABC):
    @abstractproperty
    def product(self) -> None:
        pass

    @abstractmethod
    def produce_part_a(self) -> None:
        pass

    @abstractmethod
    def produce_part_b(self) -> None:
        pass

    @abstractmethod
    def produce_part_c(self) -> None:
        pass

# 具体生成器1
class ConcreteBuilder1(Builder):
    def __init__(self) -> None:
        self.reset()

    def reset(self) -> None:
        self._product = Product1()

    @property
    def product(self) -> Product1:
        product = self._product
        self.reset()
        return product

    def produce_part_a(self) -> None:
        self._product.add('PartA1')

    def produce_part_b(self) -> None:
        self._product.add('PartB1')

    def produce_part_c(self) -> None:
        self._product.add("PartC1")

# 产品1
class Product1():
    def __init__(self) -> None:
        self.parts = []

    def add(self, part: Any) -> None:
        self.parts.append(part)

    def list_parts(self) -> None:
        print(f"Product parts: {', '.join(self.parts)}", end="")

# 主管
class Director:
    def __init__(self) -> None:
        self._builder = None

    @property
    def builder(self) -> Builder:
        return self._builder

    @builder.setter
    def builder(self, builder: Builder) -> None:
        self._builder = builder

    def build_minimal_viable_product(self) -> None:
        self.builder.produce_part_a()

    def build_full_featured_product(self) -> None:
        self.builder.produce_part_a()
        self.builder.produce_part_b()
        self.builder.produce_part_c()


if __name__ == '__main__':
    director = Director()
    builder = ConcreteBuilder1()
    director.builder = builder

    print("Standard basic product: ")
    director.build_minimal_viable_product()
    builder.product.list_parts()

    print("\n")

    print("Standard full featured product: ")
    director.build_full_featured_product()
    builder.product.list_parts()

    print("\n")

    print("Custom product: ")
    builder.produce_part_a()
    builder.produce_part_b()
    builder.product.list_parts()

# output:
# Standard basic product:
# Product parts: PartA1

# Standard full featured product:
# Product parts: PartA1, PartB1, PartC1

# Custom product:
# Product parts: PartA1, PartB1
```

---

## [原型模式](https://refactoringguru.cn/design-patterns/prototype)

原型模式是一种创建型设计模式， 使你能够复制已有对象， 而又无需使代码依赖它们所属的类。
基本实现：
![原型模式基本实现](https://refactoringguru.cn/images/patterns/diagrams/prototype/structure.png)
注册表实现：
![原型模式注册表实现](https://refactoringguru.cn/images/patterns/diagrams/prototype/structure-prototype-cache.png)

### Python代码

```python
import copy


class SelfReferencingEntity:
    def __init__(self):
        self.parent = None

    def set_parent(self, parent):
        self.parent = parent


class SomeComponent:

    def __init__(self, some_int, some_list_of_objects, some_circular_ref):
        self.some_int = some_int
        self.some_list_of_objects = some_list_of_objects
        self.some_circular_ref = some_circular_ref

    def __copy__(self):

        # First, let's create copies of the nested objects.
        some_list_of_objects = copy.copy(self.some_list_of_objects)
        some_circular_ref = copy.copy(self.some_circular_ref)

        # Then, let's clone the object itself, using the prepared clones of the
        # nested objects.
        new = self.__class__(
            self.some_int, some_list_of_objects, some_circular_ref
        )
        new.__dict__.update(self.__dict__)

        return new

    def __deepcopy__(self, memo={}):

        # First, let's create copies of the nested objects.
        some_list_of_objects = copy.deeply(self.some_list_of_objects, memo)
        some_circular_ref = copy.deepcopy(self.some_circular_ref, memo)

        # Then, let's clone the object itself, using the prepared clones of the
        # nested objects.
        new = self.__class__(
            self.some_int, some_list_of_objects, some_circular_ref
        )
        new.__dict__ = copy.deepcopy(self.__dict__, memo)

        return new


if __name__ == "__main__":

    list_of_objects = [1, {1, 2, 3}, [1, 2, 3]]
    circular_ref = SelfReferencingEntity()
    component = SomeComponent(23, list_of_objects, circular_ref)
    circular_ref.set_parent(component)

    shallow_copied_component = copy.copy(component)

    # Let's change the list in shallow_copied_component and see if it changes in
    # component.
    shallow_copied_component.some_list_of_objects.append("another object")
    if component.some_list_of_objects[-1] == "another object":
        print(
            "Adding elements to `shallow_copied_component`'s "
            "some_list_of_objects adds it to `component`'s "
            "some_list_of_objects."
        )
    else:
        print(
            "Adding elements to `shallow_copied_component`'s "
            "some_list_of_objects doesn't add it to `component`'s "
            "some_list_of_objects."
        )

    # Let's change the set in the list of objects.
    component.some_list_of_objects[1].add(4)
    if 4 in shallow_copied_component.some_list_of_objects[1]:
        print(
            "Changing objects in the `component`'s some_list_of_objects "
            "changes that object in `shallow_copied_component`'s "
            "some_list_of_objects."
        )
    else:
        print(
            "Changing objects in the `component`'s some_list_of_objects "
            "doesn't change that object in `shallow_copied_component`'s "
            "some_list_of_objects."
        )

    deep_copied_component = copy.deepcopy(component)

    # Let's change the list in deep_copied_component and see if it changes in
    # component.
    deep_copied_component.some_list_of_objects.append("one more object")
    if component.some_list_of_objects[-1] == "one more object":
        print(
            "Adding elements to `deep_copied_component`'s "
            "some_list_of_objects adds it to `component`'s "
            "some_list_of_objects."
        )
    else:
        print(
            "Adding elements to `deep_copied_component`'s "
            "some_list_of_objects doesn't add it to `component`'s "
            "some_list_of_objects."
        )

    # Let's change the set in the list of objects.
    component.some_list_of_objects[1].add(10)
    if 10 in deep_copied_component.some_list_of_objects[1]:
        print(
            "Changing objects in the `component`'s some_list_of_objects "
            "changes that object in `deep_copied_component`'s "
            "some_list_of_objects."
        )
    else:
        print(
            "Changing objects in the `component`'s some_list_of_objects "
            "doesn't change that object in `deep_copied_component`'s "
            "some_list_of_objects."
        )

    print(
        f"id(deep_copied_component.some_circular_ref.parent): "
        f"{id(deep_copied_component.some_circular_ref.parent)}"
    )
    print(
        f"id(deep_copied_component.some_circular_ref.parent.some_circular_ref.parent): "
        f"{id(deep_copied_component.some_circular_ref.parent.some_circular_ref.parent)}"
    )
    print(
        "^^ This shows that deepcopied objects contain same reference, they "
        "are not cloned repeatedly."
    )

# output:
# Adding elements to `shallow_copied_component`'s some_list_of_objects adds it to `component`'s some_list_of_objects.
# Changing objects in the `component`'s some_list_of_objects changes that object in `shallow_copied_component`'s some_list_of_objects.
# Adding elements to `deep_copied_component`'s some_list_of_objects doesn't add it to `component`'s some_list_of_objects.
# Changing objects in the `component`'s some_list_of_objects doesn't change that object in `deep_copied_component`'s some_list_of_objects.
# id(deep_copied_component.some_circular_ref.parent): 2933164043760
# id(deep_copied_component.some_circular_ref.parent.some_circular_ref.parent): 2933164043760
# ^^ This shows that deepcopied objects contain same reference, they are not cloned repeatedly.
```

---

## [单例模式](https://refactoringguru.cn/design-patterns/singleton)

单例模式是一种创建型设计模式， 让你能够保证一个类只有一个实例， 并提供一个访问该实例的全局节点。
![单例模式](https://refactoringguru.cn/images/patterns/diagrams/singleton/structure-zh.png)

### Python代码

```python
class SingletonMeta(type):
    _instances = {}

    def __call__(cls, *args, **kwds):
        if cls not in cls._instances:
            instance = super().__call__(*args, **kwds)
            cls._instances[cls] = instance
        return cls._instances


class Singleton(metaclass=SingletonMeta):
    def some_business_logic(self):
        pass


if __name__ == "__main__":
    s1 = Singleton()
    s2 = Singleton()
    if id(s1) == id(s2):
        print("Singleton works, both variables contain the same instance.")
    else:
        print("Singleton failed, variables contain different instances.")

# output:
# Singleton works, both variables contain the same instance.
```

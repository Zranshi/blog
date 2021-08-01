---
title: Python实现设计模式(行为模式)
date: 2020-12-2 15:56:02
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
keywords: 设计模式
description: 用Python实现设计模式(行为模式)
photos: https://cdn.jsdelivr.net/gh/Zranshi/CDN@1.3/2020.11.08/106.jpg
---

责任链模式是一种行为设计模式， 允许你将请求沿着处理者链进行发送。 收到请求后， 每个处理者均可对请求进行处理， 或将其传递给链上的下个处理者。

## [责任链模式](https://refactoringguru.cn/design-patterns/chain-of-responsibility)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any, Optional


class Handler(ABC):
    @abstractmethod
    def set_next(self, handler: Handler) -> Handler:
        pass

    @abstractmethod
    def handle(self, request) -> Optional[str]:
        pass


class AbstractHandler(Handler):
    _next_handler: Handler = None

    def set_next(self, handler: Handler) -> Handler:
        self._next_handler = handler
        # Returning a handler from here will let us link handlers in a
        # convenient way like this:
        # monkey.set_next(squirrel).set_next(dog)
        return handler

    @abstractmethod
    def handle(self, request: Any) -> str:
        if self._next_handler:
            return self._next_handler.handle(request)

        return None


class MonkeyHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "Banana":
            return f"Monkey: I'll eat the {request}"
        else:
            return super().handle(request)


class SquirrelHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "Nut":
            return f"Squirrel: I'll eat the {request}"
        else:
            return super().handle(request)


class DogHandler(AbstractHandler):
    def handle(self, request: Any) -> str:
        if request == "MeatBall":
            return f"Dog: I'll eat the {request}"
        else:
            return super().handle(request)


def client_code(handler: Handler) -> None:
    for food in ["Nut", "Banana", "Cup of coffee"]:
        print(f"\nClient: Who wants a {food}?")
        result = handler.handle(food)
        if result:
            print(f"  {result}", end="")
        else:
            print(f"  {food} was left untouched.", end="")


if __name__ == "__main__":
    monkey = MonkeyHandler()
    squirrel = SquirrelHandler()
    dog = DogHandler()
    monkey.set_next(squirrel).set_next(dog)
    print("Chain: Monkey > Squirrel > Dog")
    client_code(monkey)
    print("\n")
    print("Subchain: Squirrel > Dog")
    client_code(squirrel)

# output:
# Chain: Monkey > Squirrel > Dog

# Client: Who wants a Nut?
#   Squirrel: I'll eat the Nut
# Client: Who wants a Banana?
#   Monkey: I'll eat the Banana
# Client: Who wants a Cup of coffee?
#   Cup of coffee was left untouched.

# Subchain: Squirrel > Dog

# Client: Who wants a Nut?
#   Squirrel: I'll eat the Nut
# Client: Who wants a Banana?
#   Banana was left untouched.
# Client: Who wants a Cup of coffee?
#   Cup of coffee was left untouched.
```

![](https://refactoringguru.cn/images/patterns/diagrams/chain-of-responsibility/structure-2x.png)

## [命令模式](https://refactoringguru.cn/design-patterns/command)

命令模式是一种行为设计模式， 它可将请求转换为一个包含与请求相关的所有信息的独立对象。 该转换让你能根据不同的请求将方法参数化、 延迟请求执行或将其放入队列中， 且能实现可撤销操作。

![](https://refactoringguru.cn/images/patterns/diagrams/command/structure-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod


class Command(ABC):
    @abstractmethod
    def execute(self) -> None:
        pass


class SimpleCommand(Command):
    def __init__(self, payload: str) -> None:
        self._payload = payload

    def execute(self) -> None:
        print(
            f"SimpleCommand: See, I can do simple things like printing"f"({self._payload})")


class ComplexCommand(Command):
    def __init__(self, receiver: Receiver, a: str, b: str) -> None:
        self._receiver = receiver
        self._a = a
        self._b = b

    def execute(self) -> None:
        print("ComplexCommand: Complex stuff should be done by a receiver object", end="")
        self._receiver.do_something(self._a)
        self._receiver.do_something_else(self._b)


class Receiver:
    def do_something(self, a: str) -> None:
        print(f"\nReceiver: Working on ({a}.)", end="")

    def do_something_else(self, b: str) -> None:
        print(f"\nReceiver: Also working on ({b}.)", end="")


class Invoker:
    _on_start = None
    _on_finish = None

    def set_on_start(self, command: Command):
        self._on_start = command

    def set_on_finish(self, command: Command):
        self._on_finish = command

    def do_something_important(self) -> None:
        print("Invoker: Does anybody want something done before I begin?")
        if isinstance(self._on_start, Command):
            self._on_start.execute()

        print("Invoker: ...doing something really important...")

        print("Invoker: Does anybody want something done after I finish?")
        if isinstance(self._on_finish, Command):
            self._on_finish.execute()


if __name__ == "__main__":
    invoker = Invoker()
    invoker.set_on_start(SimpleCommand("Say Hi!"))
    receiver = Receiver()
    invoker.set_on_finish(ComplexCommand(
        receiver, "Send email", "Save report"))

    invoker.do_something_important()

# output:
# Invoker: Does anybody want something done before I begin?
# SimpleCommand: See, I can do simple things like printing(Say Hi!)
# Invoker: ...doing something really important...
# Invoker: Does anybody want something done after I finish?
# ComplexCommand: Complex stuff should be done by a receiver object
# Receiver: Working on (Send email.)
# Receiver: Also working on (Save report.)
```

## [迭代器模式](https://refactoringguru.cn/design-patterns/iterator)

迭代器模式是一种行为设计模式， 让你能在不暴露集合底层表现形式 （列表、 栈和树等） 的情况下遍历集合中所有的元素。

![](https://refactoringguru.cn/images/patterns/diagrams/iterator/structure-2x.png)

### Python代码

```python
from __future__ import annotations
from collections.abc import Iterable, Iterator
from typing import Any, List


class AlphabeticalOrderIterator(Iterator):

    _position: int = None

    _reverse: bool = False

    def __init__(self, collection: WordsCollection, reverse: bool = False) -> None:
        self._collection = collection
        self._reverse = reverse
        self._position = -1 if reverse else 0

    def __next__(self):
        try:
            value = self._collection[self._position]
            self._position += -1 if self._reverse else 1
        except IndexError:
            raise StopIteration()

        return value


class WordsCollection(Iterable):
    def __init__(self, collection: List[Any] = []) -> None:
        self._collection = collection

    def __iter__(self) -> AlphabeticalOrderIterator:
        return AlphabeticalOrderIterator(self._collection)

    def get_reverse_iterator(self) -> AlphabeticalOrderIterator:
        return AlphabeticalOrderIterator(self._collection, True)

    def add_item(self, item: Any):
        self._collection.append(item)


if __name__ == "__main__":
    collection = WordsCollection()
    collection.add_item("First")
    collection.add_item("Second")
    collection.add_item("Third")

    print("Straight traversal:")
    print("\n".join(collection))
    print("")

    print("Reverse traversal:")
    print("\n".join(collection.get_reverse_iterator()), end="")

# output:
# Straight traversal:
# First
# Second
# Third

# Reverse traversal:
# Third
# Second
# First
```

## [中介者模式](https://refactoringguru.cn/design-patterns/mediator)

中介者模式是一种行为设计模式， 能让你减少对象之间混乱无序的依赖关系。 该模式会限制对象之间的直接交互， 迫使它们通过一个中介者对象进行合作。

![](https://refactoringguru.cn/images/patterns/diagrams/mediator/structure-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC


class Mediator(ABC):
    def notify(self, sender: object, event: str) -> None:
        pass


class ConcreteMediator(Mediator):
    def __init__(self, component1: Component1, component2: Component2) -> None:
        self._component1 = component1
        self._component1.mediator = self
        self._component2 = component2
        self._component2.mediator = self

    def notify(self, sender: object, event: str) -> None:
        if event == "A":
            print("Mediator reacts on A and triggers following operations:")
            self._component2.do_c()
        elif event == "D":
            print("Mediator reacts on D and triggers following operations:")
            self._component1.do_b()
            self._component2.do_c()


class BaseComponent:
    def __init__(self, mediator: Mediator = None) -> None:
        self._mediator = mediator

    @property
    def mediator(self) -> Mediator:
        return self._mediator

    @mediator.setter
    def mediator(self, mediator: Mediator) -> None:
        self._mediator = mediator


class Component1(BaseComponent):
    def do_a(self) -> None:
        print("Component 1 does A.")
        self.mediator.notify(self, "A")

    def do_b(self) -> None:
        print("Component 1 does B.")
        self.mediator.notify(self, "B")


class Component2(BaseComponent):
    def do_c(self) -> None:
        print("Component 2 does C.")
        self.mediator.notify(self, "C")

    def do_d(self) -> None:
        print("Component 2 does D.")
        self.mediator.notify(self, "D")


if __name__ == "__main__":
    c1 = Component1()
    c2 = Component2()
    mediator = ConcreteMediator(c1, c2)

    print("Client triggers operation A.")
    c1.do_a()
    print("\n", end="")
    print("Client triggers operation D.")
    c2.do_d()

# output:
# Client triggers operation A.
# Component 1 does A.
# Mediator reacts on A and triggers following operations:
# Component 2 does C.

# Client triggers operation D.
# Component 2 does D.
# Mediator reacts on D and triggers following operations:
# Component 1 does B.
# Component 2 does C.
```

## [备忘录模式](https://refactoringguru.cn/design-patterns/memento)

备忘录模式是一种行为设计模式， 允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态。

![](https://refactoringguru.cn/images/patterns/diagrams/memento/structure1-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from datetime import datetime
from random import sample
from string import ascii_letters, digits


class Originator():
    _state = None
    def __init__(self, state: str) -> None:
        self._state = state
        print(f"Originator: My initial state is: {self._state}")

    def do_something(self) -> None:
        print("Originator: I'm doing something important.")
        self._state = self._generate_random_string(30)
        print(f"Originator: and my state has changed to: {self._state}")

    def _generate_random_string(self, length: int = 10) -> None:
        return "".join(sample(ascii_letters, length))

    def save(self) -> Memento:
        return ConcreteMemento(self._state)

    def restore(self, memento: Memento) -> None:
        """
        Restores the Originator's state from a memento object.
        """

        self._state = memento.get_state()
        print(f"Originator: My state has changed to: {self._state}")


class Memento(ABC):
    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_date(self) -> str:
        pass


class ConcreteMemento(Memento):
    def __init__(self, state: str) -> None:
        self._state = state
        self._date = str(datetime.now())[:19]

    def get_state(self) -> str:
        """
        The Originator uses this method when restoring its state.
        """
        return self._state

    def get_name(self) -> str:
        """
        The rest of the methods are used by the Caretaker to display metadata.
        """

        return f"{self._date} / ({self._state[0:9]}...)"

    def get_date(self) -> str:
        return self._date


class Caretaker():
    def __init__(self, originator: Originator) -> None:
        self._mementos = []
        self._originator = originator

    def backup(self) -> None:
        print("\nCaretaker: Saving Originator's state...")
        self._mementos.append(self._originator.save())

    def undo(self) -> None:
        if not len(self._mementos):
            return

        memento = self._mementos.pop()
        print(f"Caretaker: Restoring state to: {memento.get_name()}")
        try:
            self._originator.restore(memento)
        except Exception:
            self.undo()

    def show_history(self) -> None:
        print("Caretaker: Here's the list of mementos:")
        for memento in self._mementos:
            print(memento.get_name())


if __name__ == "__main__":
    originator = Originator("Super-duper-super-puper-super.")
    caretaker = Caretaker(originator)
    caretaker.backup()
    originator.do_something()
    caretaker.backup()
    originator.do_something()
    caretaker.backup()
    originator.do_something()

    print()
    caretaker.show_history()
    print("\nClient: Now, let's rollback!\n")
    caretaker.undo()
    print("\nClient: Once more!\n")
    caretaker.undo()

# output:
# Originator: My initial state is: Super-duper-super-puper-super.

# Caretaker: Saving Originator's state...
# Originator: I'm doing something important.
# Originator: and my state has changed to: mEOzwWHfnTMZYsplgQrtIxjqeVJNRX

# Caretaker: Saving Originator's state...
# Originator: I'm doing something important.
# Originator: and my state has changed to: VXFgbuBNUZIRDrwThxSiPJcHlevAGo

# Caretaker: Saving Originator's state...
# Originator: I'm doing something important.
# Originator: and my state has changed to: ifIzXcxHLrltsdqyWRpMTNYoZvBCVb

# Caretaker: Here's the list of mementos:
# 2020-12-02 17:05:55 / (Super-dup...)
# 2020-12-02 17:05:55 / (mEOzwWHfn...)
# 2020-12-02 17:05:55 / (VXFgbuBNU...)

# Client: Now, let's rollback!

# Caretaker: Restoring state to: 2020-12-02 17:05:55 / (VXFgbuBNU...)
# Originator: My state has changed to: VXFgbuBNUZIRDrwThxSiPJcHlevAGo

# Client: Once more!

# Caretaker: Restoring state to: 2020-12-02 17:05:55 / (mEOzwWHfn...)
# Originator: My state has changed to: mEOzwWHfnTMZYsplgQrtIxjqeVJNRX
```

## [观察者模式](https://refactoringguru.cn/design-patterns/observer)

观察者模式是一种行为设计模式， 允许你定义一种订阅机制， 可在对象事件发生时通知多个 “观察” 该对象的其他对象。

![](https://refactoringguru.cn/images/patterns/diagrams/observer/structure-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from random import randrange
from typing import List


class Subject(ABC):
    @abstractmethod
    def attach(self, observer: Observer) -> None:
        pass

    @abstractmethod
    def detach(self, observer: Observer) -> None:
        pass

    @abstractmethod
    def notify(self) -> None:
        pass


class ConcreteSubject(Subject):
    _state: int = None
    _observers: List[Observer] = []

    def attach(self, observer: Observer) -> None:
        print("Subject: Attached an observer.")
        self._observers.append(observer)

    def detach(self, observer: Observer) -> None:
        self._observers.remove(observer)

    def notify(self) -> None:
        print("Subject: Notifying observers...")
        for observer in self._observers:
            observer.update(self)

    def some_business_logic(self) -> None:
        print("\nSubject: I'm doing something important.")
        self._state = randrange(0, 10)

        print(f"Subject: My state has just changed to: {self._state}")
        self.notify()


class Observer(ABC):
    @abstractmethod
    def update(self, subject: Subject) -> None:
        """
        Receive update from subject.
        """
        pass


class ConcreteObserverA(Observer):
    def update(self, subject: Subject) -> None:
        if subject._state < 3:
            print("ConcreteObserverA: Reacted to the event")


class ConcreteObserverB(Observer):
    def update(self, subject: Subject) -> None:
        if subject._state == 0 or subject._state >= 2:
            print("ConcreteObserverB: Reacted to the event")


if __name__ == "__main__":
    subject = ConcreteSubject()
    observer_a = ConcreteObserverA()
    subject.attach(observer_a)
    observer_b = ConcreteObserverB()
    subject.attach(observer_b)
    subject.some_business_logic()
    subject.some_business_logic()
    subject.detach(observer_a)
    subject.some_business_logic()

# output:
# Subject: Attached an observer.
# Subject: Attached an observer.

# Subject: I'm doing something important.
# Subject: My state has just changed to: 2
# Subject: Notifying observers...
# ConcreteObserverA: Reacted to the event
# ConcreteObserverB: Reacted to the event

# Subject: I'm doing something important.
# Subject: My state has just changed to: 0
# Subject: Notifying observers...
# ConcreteObserverA: Reacted to the event
# ConcreteObserverB: Reacted to the event

# Subject: I'm doing something important.
# Subject: My state has just changed to: 9
# Subject: Notifying observers...
# ConcreteObserverB: Reacted to the event
```

## [状态模式](https://refactoringguru.cn/design-patterns/state)

状态模式是一种行为设计模式， 让你能在一个对象的内部状态变化时改变其行为， 使其看上去就像改变了自身所属的类一样。

![](https://refactoringguru.cn/images/patterns/diagrams/state/structure-zh-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod


class Context:
    _state = None

    def __init__(self, state: State) -> None:
        self.transition_to(state)

    def transition_to(self, state: State):
        print(f"Context: Transition to {type(state).__name__}")
        self._state = state
        self._state.context = self

    def request1(self):
        self._state.handle1()

    def request2(self):
        self._state.handle2()


class State(ABC):
    @property
    def context(self) -> Context:
        return self._context

    @context.setter
    def context(self, context: Context) -> None:
        self._context = context

    @abstractmethod
    def handle1(self) -> None:
        pass

    @abstractmethod
    def handle2(self) -> None:
        pass


class ConcreteStateA(State):
    def handle1(self) -> None:
        print("ConcreteStateA handles request1.")
        print("ConcreteStateA wants to change the state of the context.")
        self.context.transition_to(ConcreteStateB())

    def handle2(self) -> None:
        print("ConcreteStateA handles request2.")


class ConcreteStateB(State):
    def handle1(self) -> None:
        print("ConcreteStateB handles request1.")

    def handle2(self) -> None:
        print("ConcreteStateB handles request2.")
        print("ConcreteStateB wants to change the state of the context.")
        self.context.transition_to(ConcreteStateA())


if __name__ == "__main__":
    context = Context(ConcreteStateA())
    context.request1()
    context.request2()

# output:
# Context: Transition to ConcreteStateA
# ConcreteStateA handles request1.
# ConcreteStateA wants to change the state of the context.
# Context: Transition to ConcreteStateB
# ConcreteStateB handles request2.
# ConcreteStateB wants to change the state of the context.
# Context: Transition to ConcreteStateA
```

## [策略模式](https://refactoringguru.cn/design-patterns/strategy)

策略模式是一种行为设计模式， 它能让你定义一系列算法， 并将每种算法分别放入独立的类中， 以使算法的对象能够相互替换。

![](https://refactoringguru.cn/images/patterns/diagrams/strategy/structure-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


class Context():
    def __init__(self, strategy: Strategy) -> None:
        self._strategy = strategy

    @property
    def strategy(self) -> Strategy:
        return self._strategy

    @strategy.setter
    def strategy(self, strategy: Strategy) -> None:
        self._strategy = strategy

    def do_some_business_logic(self) -> None:
        print("Context: Sorting data using the strategy (not sure how it'll do it)")
        result = self._strategy.do_algorithm(["a", "b", "c", "d", "e"])
        print(",".join(result))


class Strategy(ABC):
    @abstractmethod
    def do_algorithm(self, data: List):
        pass


class ConcreteStrategyA(Strategy):
    def do_algorithm(self, data: List) -> List:
        return sorted(data)


class ConcreteStrategyB(Strategy):
    def do_algorithm(self, data: List) -> List:
        return reversed(sorted(data))


if __name__ == "__main__":
    context = Context(ConcreteStrategyA())
    print("Client: Strategy is set to normal sorting.")
    context.do_some_business_logic()
    print()

    print("Client: Strategy is set to reverse sorting.")
    context.strategy = ConcreteStrategyB()
    context.do_some_business_logic()

output:
Client: Strategy is set to normal sorting.
Context: Sorting data using the strategy (not sure how it'll do it)
a,b,c,d,e

Client: Strategy is set to reverse sorting.
Context: Sorting data using the strategy (not sure how it'll do it)
e,d,c,b,a
```

## [模板方法模式](https://refactoringguru.cn/design-patterns/template-method)

模板方法模式是一种行为设计模式， 它在超类中定义了一个算法的框架， 允许子类在不修改结构的情况下重写算法的特定步骤。

![](https://refactoringguru.cn/images/patterns/diagrams/template-method/structure-2x.png)

### Python代码

```python
from abc import ABC, abstractmethod


class AbstractClass(ABC):
    def template_method(self) -> None:
        self.base_operation1()
        self.required_operations1()
        self.base_operation2()
        self.hook1()
        self.required_operations2()
        self.base_operation3()
        self.hook2()

    def base_operation1(self) -> None:
        print("AbstractClass says: I am doing the bulk of the work")

    def base_operation2(self) -> None:
        print("AbstractClass says: But I let subclasses override some operations")

    def base_operation3(self) -> None:
        print("AbstractClass says: But I am doing the bulk of the work anyway")

    @abstractmethod
    def required_operations1(self) -> None:
        pass

    @abstractmethod
    def required_operations2(self) -> None:
        pass

    def hook1(self) -> None:
        pass

    def hook2(self) -> None:
        pass


class ConcreteClass1(AbstractClass):
    def required_operations1(self) -> None:
        print("ConcreteClass1 says: Implemented Operation1")

    def required_operations2(self) -> None:
        print("ConcreteClass1 says: Implemented Operation2")


class ConcreteClass2(AbstractClass):
    def required_operations1(self) -> None:
        print("ConcreteClass2 says: Implemented Operation1")

    def required_operations2(self) -> None:
        print("ConcreteClass2 says: Implemented Operation2")

    def hook1(self) -> None:
        print("ConcreteClass2 says: Overridden Hook1")


def client_code(abstract_class: AbstractClass) -> None:
    abstract_class.template_method()


if __name__ == "__main__":
    print("Same client code can work with different subclasses:")
    client_code(ConcreteClass1())
    print("")
    print("Same client code can work with different subclasses:")
    client_code(ConcreteClass2())

# output:
# Same client code can work with different subclasses:
# AbstractClass says: I am doing the bulk of the work
# ConcreteClass1 says: Implemented Operation1
# AbstractClass says: But I let subclasses override some operations
# ConcreteClass1 says: Implemented Operation2
# AbstractClass says: But I am doing the bulk of the work anyway

# Same client code can work with different subclasses:
# AbstractClass says: I am doing the bulk of the work
# ConcreteClass2 says: Implemented Operation1
# AbstractClass says: But I let subclasses override some operations
# ConcreteClass2 says: Overridden Hook1
# ConcreteClass2 says: Implemented Operation2
# AbstractClass says: But I am doing the bulk of the work anyway
```

## [访问者模式](https://refactoringguru.cn/design-patterns/visitor)

访问者模式是一种行为设计模式， 它能将算法与其所作用的对象隔离开来。

![](https://refactoringguru.cn/images/patterns/diagrams/visitor/structure-zh-2x.png)

### Python代码

```python
from __future__ import annotations
from abc import ABC, abstractmethod
from typing import List


class Component(ABC):
    @abstractmethod
    def accept(self, visitor: Visitor) -> None:
        pass


class ConcreteComponentA(Component):
    def accept(self, visitor: Visitor) -> None:
        visitor.visit_concrete_component_a(self)

    def exclusive_method_of_concrete_component_a(self) -> str:
        return "A"


class ConcreteComponentB(Component):
    def accept(self, visitor: Visitor):
        visitor.visit_concrete_component_b(self)

    def special_method_of_concrete_component_b(self) -> str:
        return "B"


class Visitor(ABC):
    @abstractmethod
    def visit_concrete_component_a(self, element: ConcreteComponentA) -> None:
        pass

    @abstractmethod
    def visit_concrete_component_b(self, element: ConcreteComponentB) -> None:
        pass


class ConcreteVisitor1(Visitor):
    def visit_concrete_component_a(self, element) -> None:
        print(
            f"{element.exclusive_method_of_concrete_component_a()} + ConcreteVisitor1")

    def visit_concrete_component_b(self, element) -> None:
        print(f"{element.special_method_of_concrete_component_b()} + ConcreteVisitor1")


class ConcreteVisitor2(Visitor):
    def visit_concrete_component_a(self, element) -> None:
        print(
            f"{element.exclusive_method_of_concrete_component_a()} + ConcreteVisitor2")

    def visit_concrete_component_b(self, element) -> None:
        print(f"{element.special_method_of_concrete_component_b()} + ConcreteVisitor2")


def client_code(components: List[Component], visitor: Visitor) -> None:
    for component in components:
        component.accept(visitor)


if __name__ == "__main__":
    components = [ConcreteComponentA(), ConcreteComponentB()]

    print("The client code works with all visitors via the base Visitor interface:")
    visitor1 = ConcreteVisitor1()
    client_code(components, visitor1)

    print("It allows the same client code to work with different types of visitors:")
    visitor2 = ConcreteVisitor2()
    client_code(components, visitor2)

# output:
# The client code works with all visitors via the base Visitor interface:
# A + ConcreteVisitor1
# B + ConcreteVisitor1
# It allows the same client code to work with different types of visitors:
# A + ConcreteVisitor2
# B + ConcreteVisitor2
```

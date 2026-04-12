"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 结构体数据结构 - Python实现
"""

# Person 类：姓名、年龄、地址
class Person:
    def __init__(self, name, age, address):
        self.name = name
        self.age = age
        self.address = address

    def introduce(self):
        print(f"Hi, I am {self.name}, {self.age} years old, from {self.address}.")


# Employee 类：继承 Person，增加职位
class Employee(Person):
    def __init__(self, name, age, address, position):
        super().__init__(name, age, address)
        self.position = position

    def introduce(self):
        print(f"I am {self.name}, a {self.position} at the company, living in {self.address}.")


p1 = Person("Alice", 30, "123 Main St")
p1.introduce()

e1 = Employee("Bob", 28, "456 Elm St", "Software Developer")
e1.introduce()

"""
jarry@MacBook-Pro struct % python struct.py 
Hi, I am Alice, 30 years old, from 123 Main St.
"""
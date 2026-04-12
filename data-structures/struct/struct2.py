"""
Copyright © https://github.com/microwind All rights reserved.
@author: jarryli@gmail.com
@version: 1.0
@description: 结构体数据结构 - Python实现（扩展版）
"""

# Person 类：姓名、年龄、地址
class Person:
    def __init__(self, name, age, address):
        self.name = name
        self.age = age
        self.address = address

    def introduce(self):
        print(f"Hi, I am {self.name}, {self.age} years old, from {self.address}.")

    def get_age(self):
        return self.age

# Employee 类：继承 Person，增加职位和薪水
class Employee(Person):
    def __init__(self, name, age, address, position, salary=0):
        super().__init__(name, age, address)
        self.position = position
        self.salary = salary

    def introduce(self):
        print(f"I am {self.name}, a {self.position} at the company, living in {self.address}.")

    def get_salary(self):
        return self.salary

    def raise_salary(self, amount):
        self.salary += amount
        print(f"{self.name}'s salary increased by {amount}. New salary: {self.salary}")

p1 = Person("Alice", 30, "123 Main St")
p1.introduce()

e1 = Employee("Bob", 28, "456 Elm St", "Software Developer", 50000)
e1.introduce()
print("Salary:", e1.get_salary())

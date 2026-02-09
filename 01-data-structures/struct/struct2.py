"""
结构体/对象示例 - 数据结构的组合（Python）

结构体是一种将多个不同类型的数据组合在一起的复合数据结构
特点：
- 将相关的数据和操作封装在一起
- 提高代码的组织性和可维护性
- 支持继承和多态
"""

class Person:
    """基础结构体：Person（人）"""
    def __init__(self, name, age, address):
        self.name = name
        self.age = age
        self.address = address

    def introduce(self):
        """显示个人信息"""
        print(f"Hi, I am {self.name}, {self.age} years old, from {self.address}.")

    def get_age(self):
        """获取年龄"""
        return self.age

class Employee(Person):
    """继承示例：Employee（员工）继承 Person"""
    def __init__(self, name, age, address, position, salary=0):
        super().__init__(name, age, address)
        self.position = position
        self.salary = salary

    def introduce(self):
        """方法覆盖：显示员工信息"""
        print(f"I am {self.name}, a {self.position} at the company, living in {self.address}.")

    def get_salary(self):
        """获取工资"""
        return self.salary

    def raise_salary(self, amount):
        """加薪"""
        self.salary += amount
        print(f"{self.name}'s salary increased by {amount}. New salary: {self.salary}")

# 测试代码
p1 = Person("Alice", 30, "123 Main St")
p1.introduce()

e1 = Employee("Bob", 28, "456 Elm St", "Software Developer", 50000)
e1.introduce()
print("Salary:", e1.get_salary())

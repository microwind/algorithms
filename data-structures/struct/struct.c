#include <stdio.h>
#include <string.h>

// 基本的结构体
struct Person {
    char name[50];
    int age;
    char address[100];
};

// 构造函数（通过初始化函数来模拟构造器）
void initPerson(struct Person *p, const char *name, int age, const char *address) {
    strcpy(p->name, name);
    p->age = age;
    strcpy(p->address, address);
}

// 方法：显示个人信息
void introduce(struct Person *p) {
    printf("Hi, I am %s, %d years old, from %s.\n", p->name, p->age, p->address);
}

// 继承示例：使用组合模拟继承
struct Employee {
    struct Person person;
    char position[50];
};

// 构造函数
void initEmployee(struct Employee *e, const char *name, int age, const char *address, const char *position) {
    initPerson(&e->person, name, age, address);
    strcpy(e->position, position);
}

// 方法：显示员工信息
void introduceEmployee(struct Employee *e) {
    printf("I am %s, a %s at the company, living in %s.\n", e->person.name, e->position, e->person.address);
}

int main() {
    struct Person p1;
    initPerson(&p1, "Alice", 30, "123 Main St");
    introduce(&p1);

    struct Employee e1;
    initEmployee(&e1, "Bob", 28, "456 Elm St", "Software Developer");
    introduceEmployee(&e1);

    return 0;
}

/*
jarry@MacBook-Pro struct % gcc struct.c
jarry@MacBook-Pro struct % ./a.out 
Hi, I am Alice, 30 years old, from 123 Main St.
*/
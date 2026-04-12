/**
 * Copyright © https://github.com/microwind All rights reserved.
 * @author: jarryli@gmail.com
 * @version: 1.0
 * @description: 结构体数据结构 - C实现
 */

#include <stdio.h>
#include <string.h>

// Person 结构体：姓名、年龄、地址
struct Person {
    char name[50];
    int age;
    char address[100];
};

// Employee 结构体：组合 Person 成员，加职位
struct Employee {
    struct Person person;   // 内嵌 Person
    char position[50];
};

// 初始化 Employee（同时初始化内部的 Person）
void initEmployee(struct Employee *e, const char *name, int age, const char *address, const char *position) {
    strcpy(e->person.name, name);
    e->person.age = age;
    strcpy(e->person.address, address);
    strcpy(e->position, position);
}

// 显示员工信息
void introduceEmployee(struct Employee *e) {
    printf("I am %s, a %s at the company, living in %s.\n",
           e->person.name, e->position, e->person.address);
}

int main() {
    // Person 示例
    struct Person p1;
    strcpy(p1.name, "Alice");
    p1.age = 30;
    strcpy(p1.address, "123 Main St");
    printf("Hi, I am %s, %d years old, from %s.\n", p1.name, p1.age, p1.address);

    // Employee 示例
    struct Employee e1;
    initEmployee(&e1, "Jarry", 28, "456 Elm St", "Software Developer");
    introduceEmployee(&e1);

    return 0;
}

/*打印结果
jarry@Mac struct % gcc struct.c -o struct && ./struct
Hi, I am Alice, 30 years old, from 123 Main St.
I am Jarry, a Software Developer at the company, living in 456 Elm St.
*/
#pragma once
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;
    double salary;

    Person(std::string n = "", int a = 0, double s = 0.0);

    // Объявление friend-функции БЕЗ реализации
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};
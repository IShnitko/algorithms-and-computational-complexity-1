#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
public:
    std::string name;
    int age;
    double salary;

    Person(std::string n = "", int a = 0, double s = 0.0);
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

#endif
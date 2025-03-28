#include "data_types/Person.h"
#include <iostream>

Person::Person(std::string n, int a, double s)
    : name(std::move(n)), age(a), salary(s) {}

// Реализация оператора ТОЛЬКО здесь
std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << p.name << " (" << p.age << ", " << p.salary << ")";
}
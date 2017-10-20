#ifndef __FOO_H__
#define __FOO_H__

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Person
{
public:
    void setName(const string& s) {
        name = s;
    }
    string getName() const {
        return name;
    }
    void setAddress(const string& s) {
        address = s;
    }
    string getAddress() const {
        return address;
    }
    void setAge(int i) {
        age = i;
    }
    int getAge() const {
        return age;
    }
    bool operator==(const Person& rhs) {
        return (name == rhs.name) && (address == rhs.address) && (age == rhs.age);
    }
private:
    string name;
    string address;
    int age;
};

void test();

#endif  // __FOO_H__

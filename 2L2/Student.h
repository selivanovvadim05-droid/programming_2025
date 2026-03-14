#pragma once

#include <string>
#include <vector>
#include <iostream> 

using namespace std;

class Student {
private:
    string name;
    string surname;
    vector<string> debts;

    vector<std::string> getUniqueSortedDebts() const;
    
public:
    Student(const string& name = "Unknown", const string& surname = "Unknown", const vector<string>& debts = {});

    ~Student();

    Student(const Student& other);

    Student& operator=(const Student& other);

    string getName() const { return name; }
    string getSurname() const { return surname; }
    const vector<string>& getDebts() const { return debts; } // Возвращаем константную ссылку

    Student operator+(const Student& other) const;

    Student& operator-=(const Student& other);

    Student operator/(const Student& other) const;

    friend ostream& operator<<(ostream& os, const Student& student);
};

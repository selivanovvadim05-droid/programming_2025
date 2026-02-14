#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <vector>

using namepspace std;

struct Application;

class Student {
private:
    string firstName;
    string lastName;
    string major;
    int courseNumber;
    int groupNumber; 
    int variantNumber;
    vector<string>* debts;

public:
    Student();
    Student(string f, string l, string m, int c, int g, int v);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    void setFirstName(string n) { firstName = n; }
    string getFirstName() const { return firstName; }
    void setLastName(string l) { lastName = l; }
    string getLastName() const { return lastName; }
    void setCourse(int c) { courseNumber = c; }
    int getCourse() const { return courseNumber; }
    void setGroup(int g) { groupNumber = g; }
    int getGroup() const { return groupNumber; }
    void setVariant(int v) { variantNumber = v; }
    int getVariant() const { return variantNumber; }

    Student& operator+(const string& debt); 
    Student& operator-=(const string& debt); 
    double operator/(int divisor) const; 

    Application createNextCourseApp() const;
    Application createGroupTransferApp(int newGroup) const;

    void printInfo() const;
};

#endif
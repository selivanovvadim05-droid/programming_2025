#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {
public:

    string firstName;
    string lastName;

    void setFirstName(const string& fName);
    void setLastName(const string& lName);

    Student();
    Student(string fName, string lName, string m, int c, string g, int v, vector<int> marks);

    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    string getFirstName() const;
    string getLastName() const;
    string getMajor() const;
    int getCourse() const;
    string getGroup() const;
    int getVariant() const;
    vector<int> getGrades() const;

    void setVariant(int v);
    void setCourse(int c);

    void printAllInfo() const;
    void nextCourse();

protected:
    string major;
    string groupNumber;


    void setMajor(const string& m);
    void setGroupNumber(const string& g);

private:
    int courseNumber;
    int variantNumber;
    std::vector<int>* grades;
};

#endif
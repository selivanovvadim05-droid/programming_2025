#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> 

struct Statement {
    std::string studentName;
    std::string studentSurname;
    std::string statementType; 
    std::string comment;
    int data; 

    Statement(const std::string& sName, const std::string& sSurname, const std::string& type, const std::string& comm, int d)
        : studentName(sName), studentSurname(sSurname), statementType(type), comment(comm), data(d) {}

    void display() const {
        std::cout << "    Type: " << statementType << ", Student: " << studentName << " " << studentSurname
                  << ", Data: " << data << ", Comment: \"" << comment << "\"" << std::endl;
    }
};

class Student;

class Deanery {
private:
    std::string address;
    std::vector<Student*> studentPointers; 

    Deanery(const Deanery& other) = delete;
    Deanery& operator=(const Deanery& other) = delete;

public:
    Deanery(const std::string& addr) : address(addr) {
    }

    ~Deanery() {
        studentPointers.clear(); 
    }

    void attachStudent(Student* studentPtr);

    void detachStudent(Student* studentPtr);

    void displayAllStudentsInfo() const;

    void processStatements();
};

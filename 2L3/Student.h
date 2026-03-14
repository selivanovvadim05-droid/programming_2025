#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

class Deanery; 

class Student {
private:
    std::string name;
    std::string surname;
    std::string department; 
    int courseNumber;
    int groupNumber;
    int variantNumber;
    std::vector<std::string> debts;
    std::vector<Statement> statements; 

    std::vector<std::string> getUniqueSortedDebts() const;
    
public:
    Student(const std::string& name = "Unknown", const std::string& surname = "Unknown", const std::string& dept = "Unknown",
            int course = 1, int group = 1, int variant = 1, const std::vector<std::string>& debts_list = {});
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);

    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getDepartment() const { return department; }
    int getCourseNumber() const { return courseNumber; }
    int getGroupNumber() const { return groupNumber; }
    int getVariantNumber() const { return variantNumber; }
    const std::vector<std::string>& getDebts() const { return debts; }
    const std::vector<Statement>& getStatements() const { return statements; }

    void setName(const std::string& newName) { name = newName; }
    void setSurname(const std::string& newSurname) { surname = newSurname; }
    void setDepartment(const std::string& newDept) { department = newDept; }
    void setCourseNumber(int newCourse) { courseNumber = newCourse; }
    void setGroupNumber(int newGroup) { groupNumber = newGroup; }
    void setVariantNumber(int newVariant) { variantNumber = newVariant; }
    void setDebts(const std::vector<std::string>& newDebts);

    void displayInfo() const;
    void fileTransferToNextCourseStatement();
    void fileTransferToGroupStatement(int newGroupNumber, const std::string& comment = "");

    Student operator+(const Student& other) const;
    Student& operator-=(const Student& other);
    Student operator/(const Student& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

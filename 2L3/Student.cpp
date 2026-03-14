#include "Student.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "Deanery.h" 

std::vector<std::string> Student::getUniqueSortedDebts() const {
    std::vector<std::string> sorted_unique_debts = debts;
    std::sort(sorted_unique_debts.begin(), sorted_unique_debts.end());
    sorted_unique_debts.erase(std::unique(sorted_unique_debts.begin(), sorted_unique_debts.end()), sorted_unique_debts.end());
    return sorted_unique_debts;
}

Student::Student(const std::string& name, const std::string& surname, const std::string& dept,
                 int course, int group, int variant, const std::vector<std::string>& debts_list)
    : name(name), surname(surname), department(dept), courseNumber(course),
      groupNumber(group), variantNumber(variant) {
    setDebts(debts_list); 
}


Student::~Student() {
    debts.clear(); 
    statements.clear();
}

Student::Student(const Student& other)
    : name(other.name), surname(other.surname), department(other.department),
      courseNumber(other.courseNumber), groupNumber(other.groupNumber),
      variantNumber(other.variantNumber), debts(other.debts), statements(other.statements) {
}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    this->name = other.name;
    this->surname = other.surname;
    this->department = other.department;
    this->courseNumber = other.courseNumber;
    this->groupNumber = other.groupNumber;
    this->variantNumber = other.variantNumber;
    this->debts = other.debts;
    this->statements = other.statements;
    return *this;
}

void Student::setDebts(const std::vector<std::string>& newDebts) {
    this->debts = newDebts;
    std::sort(this->debts.begin(), this->debts.end());
    this->debts.erase(std::unique(this->debts.begin(), this->debts.end()), this->debts.end());
}

void Student::displayInfo() const {
    std::cout << "--- Student Info ---" << std::endl;
    std::cout << "Name: " << name << ", Surname: " << surname << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Course: " << courseNumber << ", Group: " << groupNumber << ", Variant: " << variantNumber << std::endl;
    std::cout << "Debts: [";
    if (!debts.empty()) {
        for (size_t i = 0; i < debts.size(); ++i) 
            std::cout << debts[i] << (i < debts.size() - 1 ? ", " : "");
    } else 
        std::cout << "No debts";
    std::cout << "]" << std::endl;
    
    std::cout << "Statements:" << std::endl;
    if (!statements.empty()) {
        for (const auto& stmt : statements) 
            stmt.display();
    } else 
        std::cout << "  No statements filed." << std::endl;
    std::cout << "--------------------" << std::endl;
}

void Student::fileTransferToNextCourseStatement() {
    int nextCourse = this->courseNumber + 1;
    statements.emplace_back(this->name, this->surname, "перевод_на_следующий_курс", 
                            "Request to proceed to the next academic year.", nextCourse);
    std::cout << "Statement filed for " << this->name << " " << this->surname << " to transfer to course " << nextCourse << "." << std::endl;
}

void Student::fileTransferToGroupStatement(int newGroupNumber, const std::string& comment) {
    statements.emplace_back(this->name, this->surname, "перевод_в_другую_группу", 
                            comment, newGroupNumber);
    std::cout << "Statement filed for " << this->name << " " << this->surname << " to transfer to group " << newGroupNumber << "." << std::endl;
}

Student Student::operator+(const Student& other) const {
    std::string newName = this->name + " and " + other.name;
    std::string newSurname = this->surname + " and " + other.surname;

    std::vector<std::string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    std::vector<std::string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    std::vector<std::string> combined_debts;
    std::set_union(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                   other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                   std::back_inserter(combined_debts));

    return Student(newName, newSurname, "Combined", 
                   std::max(this->courseNumber, other.courseNumber), 
                   std::max(this->groupNumber, other.groupNumber),
                   std::max(this->variantNumber, other.variantNumber),
                   combined_debts);
}

Student& Student::operator-=(const Student& other) {
    this->name = this->name + " without " + other.name;
    this->surname = this->surname + " without " + other.surname;

    std::vector<std::string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    std::vector<std::string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    std::vector<std::string> remaining_debts;
    std::set_difference(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                        other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                        std::back_inserter(remaining_debts));
    this->debts = remaining_debts; 

    return *this;
}

Student Student::operator/(const Student& other) const {
    std::string newName = this->name + " and " + other.name;
    std::string newSurname = this->surname + " and " + other.surname;

    std::vector<std::string> this_sorted_unique_debts = this->getUniqueSortedDebts();
    std::vector<std::string> other_sorted_unique_debts = other.getUniqueSortedDebts();
    
    std::vector<std::string> common_debts;
    std::set_intersection(this_sorted_unique_debts.begin(), this_sorted_unique_debts.end(),
                          other_sorted_unique_debts.begin(), other_sorted_unique_debts.end(),
                          std::back_inserter(common_debts));

    return Student(newName, newSurname, "Intersection",
                   std::min(this->courseNumber, other.courseNumber),
                   std::min(this->groupNumber, other.groupNumber),
                   std::min(this->variantNumber, other.variantNumber),
                   common_debts);
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Student: " << student.name << " " << student.surname << std::endl;
    os << "  Department: " << student.department << std::endl;
    os << "  Course: " << student.courseNumber << ", Group: " << student.groupNumber << ", Variant: " << student.variantNumber << std::endl;
    os << "  Debts: [";
    if (!student.debts.empty()) {
        for (size_t i = 0; i < student.debts.size(); ++i) 
            os << student.debts[i] << (i < student.debts.size() - 1 ? ", " : "");
    } else 
        os << "No debts";
    os << "]" << std::endl;
    
    os << "  Statements:" << std::endl;
    if (!student.statements.empty()) {
        for (const auto& stmt : student.statements) 
            stmt.display();
    } else 
        os << "    No statements filed." << std::endl;
    return os;
}

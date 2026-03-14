#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

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


class Deanery {
private:
    std::string address;
    std::vector<Student*> studentPointers; 

    Deanery(const Deanery& other) = delete;
    Deanery& operator=(const Deanery& other) = delete;

public:
    Deanery(const std::string& addr) : address(addr) {}
    ~Deanery();

    void attachStudent(Student* studentPtr);
    void detachStudent(Student* studentPtr);
    void displayAllStudentsInfo() const;
    void processStatements();
};

std::vector<std::string> Student::getUniqueSortedDebts() const {}
Student::Student(const std::string& name, const std::string& surname, const std::string& dept,
                 int course, int group, int variant, const std::vector<std::string>& debts_list)
    : name(name), surname(surname), department(dept), courseNumber(course),
      groupNumber(group), variantNumber(variant) { setDebts(debts_list); }
Student::~Student() { debts.clear(); statements.clear(); }
Student::Student(const Student& other)
    : name(other.name), surname(other.surname), department(other.department),
      courseNumber(other.courseNumber), groupNumber(other.groupNumber),
      variantNumber(other.variantNumber), debts(other.debts), statements(other.statements) {}
Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    this->name = other.name; this->surname = other.surname; this->department = other.department;
    this->courseNumber = other.courseNumber; this->groupNumber = other.groupNumber; this->variantNumber = other.variantNumber;
    this->debts = other.debts; this->statements = other.statements;
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
    if (!debts.empty()) { for (size_t i = 0; i < debts.size(); ++i) { std::cout << debts[i] << (i < debts.size() - 1 ? ", " : ""); } } else { std::cout << "No debts"; }
    std::cout << "]" << std::endl;
    std::cout << "Statements:" << std::endl;
    if (!statements.empty()) { for (const auto& stmt : statements) { stmt.display(); } } else { std::cout << "  No statements filed." << std::endl; }
    std::cout << "--------------------" << std::endl;
}
void Student::fileTransferToNextCourseStatement() {
    int nextCourse = this->courseNumber + 1;
    statements.emplace_back(this->name, this->surname, "перевод_на_следующий_курс", "Request to proceed to the next academic year.", nextCourse);
    std::cout << "Statement filed for " << this->name << " " << this->surname << " to transfer to course " << nextCourse << "." << std::endl;
}
void Student::fileTransferToGroupStatement(int newGroupNumber, const std::string& comment) {
    statements.emplace_back(this->name, this->surname, "перевод_в_другую_группу", comment, newGroupNumber);
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
    if (!student.debts.empty()) { for (size_t i = 0; i < student.debts.size(); ++i) { os << student.debts[i] << (i < student.debts.size() - 1 ? ", " : ""); } } else { os << "No debts"; }
    os << "]" << std::endl;
    os << "  Statements:" << std::endl;
    if (!student.statements.empty()) { for (const auto& stmt : student.statements) { stmt.display(); } } else { os << "    No statements filed." << std::endl; }
    return os;
}

Deanery::~Deanery() { studentPointers.clear(); }
void Deanery::attachStudent(Student* studentPtr) { /* ... (код из Deanery.cpp) ... */ 
    if (studentPtr == nullptr) { std::cerr << "Error: Cannot attach a null student pointer." << std::endl; return; }
    if (std::find(studentPointers.begin(), studentPointers.end(), studentPtr) == studentPointers.end()) {
        studentPointers.push_back(studentPtr);
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " attached to deanery." << std::endl;
    } else {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " is already attached to the deanery." << std::endl;
    }
}
void Deanery::detachStudent(Student* studentPtr) { /* ... (код из Deanery.cpp) ... */ 
    if (studentPtr == nullptr) { std::cerr << "Error: Cannot detach a null student pointer." << std::endl; return; }
    auto original_size = studentPointers.size();
    studentPointers.erase(std::remove(studentPointers.begin(), studentPointers.end(), studentPtr), studentPointers.end());
    if (studentPointers.size() < original_size) {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " detached from deanery." << std::endl;
    } else {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " was not found in the deanery list." << std::endl;
    }
}
void Deanery::displayAllStudentsInfo() const { 
    std::cout << "\n--- Deanery at " << address << " ---" << std::endl;
    if (studentPointers.empty()) { std::cout << "  No students attached." << std::endl; } 
    else {
        std::cout << "  Attached Students (" << studentPointers.size() << " total):" << std::endl;
        for (const auto& ptr : studentPointers) { if (ptr) { ptr->displayInfo(); } }
    }
    std::cout << "-------------------------" << std::endl;
}
void Deanery::processStatements() {
    std::cout << "\n--- Processing Statements in Deanery ---" << std::endl;
    bool statementsProcessed = false;
    for (Student* studentPtr : studentPointers) {
        if (studentPtr) {
            const auto& statements = studentPtr->getStatements();
            if (!statements.empty()) {
                statementsProcessed = true;
                std::cout << "Processing statements for: " << studentPtr->getName() << " " << studentPtr->getSurname() << std::endl;
                for (const auto& stmt : statements) {
                    if (stmt.statementType == "перевод_на_следующий_курс") {
                        std::cout << "  Action: Transferring " << studentPtr->getName() << " to course " << stmt.data << std::endl;
                        studentPtr->setCourseNumber(stmt.data); 
                    } else if (stmt.statementType == "перевод_в_другую_группу") {
                        std::cout << "  Action: Transferring " << studentPtr->getName() << " to group " << stmt.data << std::endl;
                        studentPtr->setGroupNumber(stmt.data); 
                    } else {
                        std::cout << "  Unknown statement type: " << stmt.statementType << std::endl;
                    }
                }
            }
        }
    }
    if (!statementsProcessed) { std::cout << "  No statements to process." << std::endl; }
    std::cout << "--- Finished Processing Statements ---" << std::endl;
}


void printLabEvaluation() {
    std::cout << "\n========================================" << std::endl;
    std::cout << " Personal Evaluation of This Lab Work " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Interest Level: Moderate. The task involves multiple classes and interactions, which is good for learning OOP." << std::endl;
    std::cout << "Content Richness: Good. Covers essential OOP concepts like rule of three, operator overloading, and composition." << std::endl;
    std::cout << "Complexity: Moderate. Requires careful understanding of pointers, object lifetimes, and inter-class communication." << std::endl;
    std::cout << "Overall: A practical exercise that reinforces C++ programming fundamentals." << std::endl;
    std::cout << "========================================\n" << std::endl;
}


int main() {
    std::cout << "--- Starting Application ---" << std::endl;

    Student s1("Иван", "Иванов", "Computer Science", 2, 101, 5, {"Math", "Physics", "Chemistry", "Math"});
    Student s2("Петр", "Петров", "Applied Physics", 3, 205, 12, {"Physics", "Informatics", "Math", "Biology"});
    Student s3("Анна", "Сидорова", "Philology", 1, 310, 2, {"History", "Geography"});
    Student s_for_detach("Temp", "Student", "Testing", 4, 404, 1, {"Test"});

    std::cout << "\n--- Initial Student States ---" << std::endl;
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();
    s_for_detach.displayInfo();

    Deanery facultyDeanery("Main Building, 3rd Floor");

    std::cout << "\n--- Attaching Students to Deanery ---" << std::endl;
    facultyDeanery.attachStudent(&s1);
    facultyDeanery.attachStudent(&s2);
    facultyDeanery.attachStudent(&s3);
    facultyDeanery.attachStudent(&s_for_detach);
    facultyDeanery.attachStudent(&s1); 

    facultyDeanery.displayAllStudentsInfo();

    std::cout << "\n--- Filing Student Statements ---" << std::endl;
    s1.fileTransferToNextCourseStatement(); 
    s2.fileTransferToGroupStatement(206, "Due to personal circumstances"); 
    s3.fileTransferToNextCourseStatement(); 
    s3.fileTransferToGroupStatement(311, "For better academic organization"); 

    std::cout << "\n--- Student States After Filing Statements ---" << std::endl;
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();

    facultyDeanery.processStatements();

    std::cout << "\n--- Student States After Deanery Processes Statements ---" << std::endl;
    s1.displayInfo();
    s2.displayInfo();
    s3.displayInfo();
    
    std::cout << "\n--- Demonstrating Student Operators ---" << std::endl;
    Student s1_plus_s2 = s1 + s2; 
    std::cout << "Result of s1 + s2: " << std::endl << s1_plus_s2 << std::endl;

    Student s1_common_s2 = s1 / s2; 
    std::cout << "Result of s1 / s2 (common debts): " << std::endl << s1_common_s2 << std::endl;

    Student s4_original_state("Oleg", "Olegov", "Math Dept.", 2, 301, 7, {"Math", "Physics", "Literature"});
    std::cout << "Original s4 for -= operation:" << std::endl << s4_original_state << std::endl;
    Student s4_modified = s4_original_state; 
    s4_modified -= s2; 
    std::cout << "s4_modified after -= s2:" << std::endl << s4_modified << std::endl;

    std::cout << "\n--- Detaching Student from Deanery ---" << std::endl;
    facultyDeanery.detachStudent(&s_for_detach);
    facultyDeanery.detachStudent(&s_for_detach); 

    facultyDeanery.displayAllStudentsInfo();

    printLabEvaluation();

    std::cout << "\n--- End of Main. Destructors will be called now. ---" << std::endl;
    return 0; 
}

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

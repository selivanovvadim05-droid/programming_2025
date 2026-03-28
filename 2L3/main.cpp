#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

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

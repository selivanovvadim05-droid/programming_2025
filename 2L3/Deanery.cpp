#include "Deanery.h"
#include "Student.h" 

void Deanery::attachStudent(Student* studentPtr) {
    if (studentPtr == nullptr) {
        std::cerr << "Error: Cannot attach a null student pointer." << std::endl;
        return;
    }
    if (std::find(studentPointers.begin(), studentPointers.end(), studentPtr) == studentPointers.end()) {
        studentPointers.push_back(studentPtr);
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " attached to deanery." << std::endl;
    } else {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " is already attached to the deanery." << std::endl;
    }
}

void Deanery::detachStudent(Student* studentPtr) {
    if (studentPtr == nullptr) {
        std::cerr << "Error: Cannot detach a null student pointer." << std::endl;
        return;
    }
    auto original_size = studentPointers.size();
    studentPointers.erase(std::remove(studentPointers.begin(), studentPointers.end(), studentPtr), studentPointers.end());
    
    if (studentPointers.size() < original_size) {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " detached from deanery." << std::endl;
    } else {
        std::cout << "Student " << studentPtr->getName() << " " << studentPtr->getSurname() << " was not found in the deanery list." << std::endl;
    }
}

void Deanery::displayAllStudentsInfo() const {
    std::cout << "n--- Deanery at " << address << " ---" << std::endl;
    if (studentPointers.empty()) {
        std::cout << "  No students attached." << std::endl;
    } else {
        std::cout << "  Attached Students (" << studentPointers.size() << " total):" << std::endl;
        for (const auto& ptr : studentPointers) {
            if (ptr) { 
                ptr->displayInfo(); 
            }
        }
    }
    std::cout << "-------------------------" << std::endl;
}

void Deanery::processStatements() {
    std::cout << "n--- Processing Statements in Deanery ---" << std::endl;
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
                        studentPtr->setCourseNumber(stmt.data); // Обновляем курс студента
                    } else if (stmt.statementType == "перевод_в_другую_группу") {
                        std::cout << "  Action: Transferring " << studentPtr->getName() << " to group " << stmt.data << std::endl;
                        studentPtr->setGroupNumber(stmt.data); // Обновляем группу студента
                    } else {
                        std::cout << "  Unknown statement type: " << stmt.statementType << std::endl;
                    }
                }
            }
        }
    }
    if (!statementsProcessed) {
        std::cout << "  No statements to process." << std::endl;
    }
    std::cout << "--- Finished Processing Statements ---" << std::endl;
}

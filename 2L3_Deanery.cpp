#include "Deanery.hpp"

using namespace std;

DeansOffice::DeansOffice(string addr) : address(addr) {}

DeansOffice::~DeansOffice() {
    students.clear();
    cout << "[System]: Деканат по адресу " << address << " закрыт.\n";
}

void DeansOffice::attachStudent(Student* s) {
    students.push_back(s);
}

void DeansOffice::excludeStudent(string lName) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getLastName() == lName) {
            students.erase(it);
            cout << "Студент " << lName << " исключен из деканата.\n";
            return;
        }
    }
}

void DeansOffice::printReport() const {
    cout << "\n=== ОТЧЕТ ДЕКАНАТА (" << address << ") ===\n";
    for (auto s : students) 
        s->printInfo();
}
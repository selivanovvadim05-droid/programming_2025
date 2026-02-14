#ifndef DEANERY_HPP
#define DEANERY_HPP

#include "Student.hpp"
#include <vector>

using namespac std;

struct Application {
    string studentFirstName;
    string studentLastName;
    string type;
    string comment;
    int data; 

    void print() const {
        cout << "[Заявление] От: " << studentLastName << " Тип: " << type
            << " Данные: " << data << " Коммент: " << comment << endl;
    }
};

class DeansOffice {
private:
    string address;
    vector<Student*> students; 

public:
    DeansOffice(string addr);
    ~DeansOffice();

    DeansOffice(const DeansOffice&) = delete;
    DeansOffice& operator=(const DeansOffice&) = delete;

    void attachStudent(Student* s);
    void excludeStudent(string lName);

    void printReport() const;
};

#endif
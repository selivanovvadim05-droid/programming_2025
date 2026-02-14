#include "Student.hpp"
#include "Deanery.hpp"
#include <algorithm>

using namespace std;

Student::Student() : firstName("Имя"), lastName("Фамилия"), major("ИТ"),
courseNumber(1), groupNumber(101), variantNumber(1) {
    debts = new vector<string>();
}

Student::Student(string f, string l, string m, int c, int g, int v)
    : firstName(f), lastName(l), major(m), courseNumber(c), groupNumber(g), variantNumber(v) {
    debts = new vector<string>();
}

Student::Student(const Student& other) {
    firstName = other.firstName;
    lastName = other.lastName;
    major = other.major;
    courseNumber = other.courseNumber;
    groupNumber = other.groupNumber;
    variantNumber = other.variantNumber;
    debts = new vector<string>(*other.debts);
}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    delete debts;
    firstName = other.firstName;
    lastName = other.lastName;
    major = other.major;
    courseNumber = other.courseNumber;
    groupNumber = other.groupNumber;
    variantNumber = other.variantNumber;
    debts = new vector<string>(*other.debts);
    return *this;
}

Student::~Student() {
    debts->clear();
    delete debts;
    cout << "[System]: Студент " << lastName << " удален.\n";
}

Student& Student::operator+(const string& debt) {
    debts->push_back(debt);
    return *this;
}

Student& Student::operator-=(const string& debt) {
    auto it = find(debts->begin(), debts->end(), debt);
    if (it != debts->end()) debts->erase(it);
    return *this;
}

double Student::operator/(int divisor) const {
    return (divisor == 0) ? 0 : (double)debts->size() / divisor;
}

Application Student::createNextCourseApp() const {
    return { firstName, lastName, "перевод_на_следующий_курс", "Прошу перевести", courseNumber + 1 };
}

Application Student::createGroupTransferApp(int newGroup) const {
    return { firstName, lastName, "перевод_в_другую_группу", "В связи с переездом", newGroup };
}

void Student::printInfo() const {
    cout << "Студент: " << lastName << " " << firstName << " | Курс: " << courseNumber
        << " | Группа: " << groupNumber << " | Долгов: " << debts->size() << endl;
}
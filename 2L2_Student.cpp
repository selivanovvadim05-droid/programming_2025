#include "Student.h"
#include <regex>

using namespace std;

void Student::setFirstName(const string& fName) {
    if (!fName.empty()) firstName = fName;
}

void Student::setLastName(const string& lName) {
    if (!lName.empty()) lastName = lName;
}

void Student::setMajor(const string& m) {
    if (!m.empty()) major = m;
}

void Student::setGroupNumber(const string& g) {
    regex pattern("^[A-ZА-Я]{2}-[0-9]{2}$");
    if (regex_match(g, pattern)) 
        groupNumber = g;
    else 
        cout << "[Ошибка]: Неверный формат группы " << g;
}

void Student::setCourse(int c) {
    if (c >= 1 && c <= 6) courseNumber = c;
    else cout << "[Ошибка]: Курс должен быть от 1 до 6";
}

void Student::setVariant(int v) {
    if (v > 0) variantNumber = v;
    else cout << "[Ошибка]: Вариант должен быть положительным";
}

Student::Student() : firstName("Иван"), lastName("Иванов"), major("ИТ"), courseNumber(1), groupNumber("ИТ-01"), variantNumber(1) {
    grades = new vector<int>(); 
    cout << "[System]: Вызван конструктор по умолчанию";
}

Student::Student(string fName, string lName, string m, int c, string g, int v, vector<int> marks) {
    setFirstName(fName);
    setLastName(lName);
    setMajor(m);
    setCourse(c);
    setGroupNumber(g);
    setVariant(v);
    grades = new vector<int>(marks); 
    cout << "[System]: Вызван конструктор полного заполнения";
}


Student::Student(const Student& other) {
    firstName = other.firstName;
    lastName = other.lastName;
    major = other.major;
    courseNumber = other.courseNumber;
    groupNumber = other.groupNumber;
    variantNumber = other.variantNumber;
    
    grades = new vector<int>(*other.grades);
    cout << "[System]: Вызван конструктор копирования";
}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;

    if (grades != nullptr) {
        grades->clear();
        delete grades;
    }

    firstName = other.firstName;
    lastName = other.lastName;
    major = other.major;
    courseNumber = other.courseNumber;
    groupNumber = other.groupNumber;
    variantNumber = other.variantNumber;
    grades = new vector<int>(*other.grades);

    cout << "[System]: Вызван оператор присваивания";
    return *this;
}

Student::~Student() {
    if (grades != nullptr) {
        grades->clear(); 
        delete grades; 
        grades = nullptr;
    }
    cout << "[Destructor]: Память очищена для объекта " << lastName;
}

string Student::getFirstName() const { return firstName; }
string Student::getLastName() const { return lastName; }
string Student::getMajor() const { return major; }
int Student::getCourse() const { return courseNumber; }
string Student::getGroup() const { return groupNumber; }
int Student::getVariant() const { return variantNumber; }
vector<int> Student::getGrades() const { return *grades; }

void Student::nextCourse() 
    if (courseNumber < 6) courseNumber++;

void Student::printAllInfo() const {
    cout << "--- Информация о студенте ---n";
    cout << "ФИО: " << lastName << " " << firstName << "n";
    cout << "Группа: " << groupNumber << " | Курс: " << courseNumber << "n";
    cout << "Вариант: " << variantNumber << "nОценки: ";
    for (int g : *grades) cout << g << " ";
    cout << "n-----------------------------n";
}
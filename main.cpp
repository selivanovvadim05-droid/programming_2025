#include "Student.h"

int main() {
    setlocale(LC_ALL, "RU");

    vector<int> initialGrades = { 5, 4, 5, 5 };
    Student s1("Алексей", "Смирнов", "Программная инженерия", 2, "ПИ-21", 7, initialGrades);
    s1.printAllInfo();

    Student s2 = s1;
    s2.setLastName("Копированый");
    s2.printAllInfo();

    Student s3;
    s3 = s1;
    s3.setLastName("Присвоенный");

    cout << "Тест неверного формата группы:\n";
    s3.setGroupNumber("неправильный_номер");

    s1.nextCourse();
    cout << "После перевода на курс:\n";
    s1.printAllInfo();

    return 0;
}
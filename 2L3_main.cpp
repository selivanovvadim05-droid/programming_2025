#include "Student.hpp"
#include "Deanery.hpp"
#include <iomanip>

using namespace std;

void printMyEvaluation() {
    cout << "\n======= ОЦЕНКА ЛАБОРАТОРНОЙ РАБОТЫ =======" << endl;
    cout << "Интерес:    9/10 (Интересно проектировать связи классов)" << endl;
    cout << "Наполненность: 10/10 (Все требования по операторам и библиотекам учтены)" << endl;
    cout << "Сложность:  7/10 (Основная сложность в работе с указателями и сборкой)" << endl;
    cout << "===========================================\n" << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    Student s1("Иван", "Иванов", "ИВТ", 1, 101, 1);
    Student s2("Петр", "Петров", "ИВТ", 2, 202, 2);

    s1 + "Математика"; 
    s1 + "Физика";
    cout << "Долгов на семестр (s1 / 2): " << s1 / 2 << endl;
    s1 -= "Физика";  

    DeansOffice dean("ул. Университетская, 10");
    dean.attachStudent(&s1);
    dean.attachStudent(&s2);
    dean.printReport();

    cout << "Генерация заявлений..." << endl;
    Application app1 = s1.createNextCourseApp();
    Application app2 = s2.createGroupTransferApp(303);

    app1.print();
    app2.print();

    dean.excludeStudent("Иванов");
    dean.printReport();

    printMyEvaluation();

    return 0;
}
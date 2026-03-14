#include "Student.h"
#include <vector>
#include <string>
#include <iostream>

using namespace  ;

int main() {
    Student s1("Иван", "Иванов", {"Математика", "Физика", "Химия", "Математика"});
    Student s2("Петр", "Петров", {"Физика", "Информатика", "Математика", "Биология"});
    Student s3("Анна", "Сидорова", {"История", "География"});
    
    cout << "\n--- Начальные студенты ---" << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

    cout << "\n--- Оператор + (Объединение) ---" << endl;
    Student s1_plus_s2 = s1 + s2;
    cout << s1_plus_s2 << endl;

    cout << "\n--- Оператор / (Общие долги) ---" << endl;
    Student s1_common_s2 = s1 / s2;
    cout << s1_common_s2 << endl;


    cout << "\n--- Оператор -= (Изъятие долгов) ---" << endl;
    Student s4("Олег", "Олегов", {"Математика", "Физика", "Литература"});
    cout << "Original s4:" << endl << s4 << endl;
    
    s4 -= s2; 
    cout << "s4 после s4 -= s2:" << endl << s4 << endl;
    

    cout << "\n--- Проверка исходного s1 ---" << endl;
    cout << s1 << endl; 

    cout << "\n--- Оператор присваивания (=) ---" << endl;
    Student s_assigned = s1; 
    s_assigned.getDebts().push_back("Новый долг"); 
    cout << "s_assigned (измененный):" << endl << s_assigned << endl;
    cout << "s1 (должен быть неизменным):" << endl << s1 << endl;

    cout << "\n--- Конструктор копирования ---" << endl;
    Student s_copied(s2); 
    cout << "s_copied:" << endl << s_copied << endl;


    cout << "\n--- Конец main, начнутся вызовы деструкторов ---" << endl;
    return 0;
}

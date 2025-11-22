#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;

// функция для пункта 1

double calculateReciprocal(int num) {
    cout << "исп. функция обратного значения" << endl;
    if (num == 0) {
        cout << "Ошибка: невозможно вычислить обратное значение для нуля." << endl;
        return 0.0;
    }
    return 1.0 / num;
}

double calculateExpression(int a, int b) {
    cout << "исп. функция выражения (a+b)**2" << endl;
    return (double)(a + b) * (a + b);
}

// функция для пункта 2

void calculateAndPrintIntervalMidpoint(double left, double right) {
    cout << "исп. функция определения середины интервала" << endl;
    cout << "Середина интервала [" << left << ", " << right << "] = " << (left + right) / 2 << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    int choice;
    cout << "Введите номер пункта(1, 2): " << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1) {
        const int press = 3;
        vector<int> valid;

        cout << "Введите " << press << " целых чисел ";
        for (int i = 0; i < press; ++i) {
            int num1;
            cout << "Число #" << i + 1 << ": ";
            cin >> num1;
            if (num1 != 0) {
                valid.push_back(num1);
            }
            else {
                cout << "";
            }
        }
        cout << endl;


        if (valid.size() == 1) {
            double result = calculateReciprocal(valid[0]);
            if (valid[0] != 0) {
                cout << "Результат: обратное значение " << valid[0] << " = " << result << endl;
            }
        }
        else {
            double result = (double)(valid[0] + valid[1]) * (valid[0] + valid[1]);
            cout << "Результат: (a+b)**2 для a = " << valid[0]
                << ", b = " << valid[1] << " = " << result << endl;
        }
    }
    else if (choice == 2) {
        double leftEndpoint, rightEndpoint;
        cout << "Левая граница: ";
        cin >> leftEndpoint;
        cout << "Правая граница: ";
        cin >> rightEndpoint;
        cout << endl;

        calculateAndPrintIntervalMidpoint(leftEndpoint, rightEndpoint);

    }

    return 0;
}

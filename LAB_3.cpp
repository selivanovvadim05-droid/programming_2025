#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

int main() {
    // Ïóíêò 1
    setlocale(LC_ALL, "RU");
    int N;
    cout << "N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Последовательность пуста. Условие не может быть выполнено." << endl;
        return 0;
    }

    double sum = 0.0;
    double minNum = numeric_limits<double>::max();
    int minInd = -1;


    for (int i = 0; i < N; ++i) {
        double number;
        cout << "A" << i + 1 << ": ";
        cin >> number;

        if (number > 10.12) {
            continue;
        }
        sum += number;

        if (number < minNum) {
            minNum = number;
            minInd = i + 1;
        }
    }

    if (minInd == -1) {
        cout << "В последовательности нет чисел, не превышающих 10.12 10.12" << endl;
    }
    else {
        cout << "Сумма чисел, не превышающих 10.12: " << sum << endl;
        cout << "Наименьшее число: " << minNum << endl;
        cout << "Индекс наименьшего числа: " << minInd << endl;
    }

    // Ïóíêò 2
    int X;
    cout << "X: ";
    cin >> X;

    X = abs(X);
    int res = X;
    int pos = 0, LastPos = -1;

    while (res > 0) {
        pos++;
        if (res % 10 == 3) {
            LastPos = pos;
        }
        res /= 10;
    }

    if (LastPos != -1) {
        cout << "Индекс последней цифры 3: " << LastPos << endl;
    }

    else {
        cout << Цифры 3 в числе нет." << endl;
    }

    return 0;

}

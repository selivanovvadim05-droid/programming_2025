#include <iostream>
#include <cmath>
#include <algorithm>
#include <bitset>  

using namespace std;

// Binary sistem
string toBinary(short n) {
    bitset<8> bits(n);
    return bits.to_string();
}

int main() {
    setlocale(LC_ALL, "RU");
    short A;
    int i;

    cout << "A: ";
    cin >> A;

    cout << "i: ";
    cin >> i;

    // test 
    if (i < 0 || i > 7) {
        cout << "Ошибка: номер бита i должен быть от 0 до 7." << endl;
        return 1; 
    }

    cout << "A = " << A << " = " << toBinary(A) << endl;
    cout << "i = " << i << endl;

    // pull out the value of the i-th bit into a separate variable
    int res = (A >> i) & 1; 
    cout << "Value " << i << "-го bit: " << res << endl;



    // -------------------- Пункт 1 --------------------
    if (res == 0) {
        // change i-й and 0-й bit
        short temp = (A >> i) & 1; // save value i bit
        A = A & ~(1 << i);         // reset value i bit in 0
        A = A & ~1;               // reset value 0-й bit in 0
        A = A | (temp << 0);      // Set the 0-й bit to the value from temp
        A = A | ((A >> 0 & 1) << i);
        A = A | (temp << i); // Set the i-й bit 


        cout << "After change bits: A = " << A << " = " << toBinary(A) << endl;
    }
    else {
        int num1, num2, num3;
        cout << "Enter three integers: ";
        cin >> num1 >> num2 >> num3;

        float absNum1 = abs(num1);
        float absNum2 = abs(num2);
        float absNum3 = abs(num3);

        if (absNum1 == absNum2 || absNum1 == absNum3 || absNum2 == absNum3) {
            cout << "Код 0. Вычисление невозможно." << endl;
        }
        else {
            float maxNum = max({ absNum1, absNum2, absNum3 });
            float minNum = min({ absNum1, absNum2, absNum3 });
            float middleNum = absNum1 + absNum2 + absNum3 - maxNum - minNum;

            cout << "Middle of module: " << middleNum << endl;
        }
    }

    // -------------------- Пункт 2 --------------------
    int N;
    cout << "Number of region: ";
    cin >> N;

    cout << "Name of region: ";
    switch (N) {
    case 102:
        cout << "Республика Башкортостан" << endl;
        break;
    case 11:
        cout << "Республика Коми" << endl;
        break;
    case 13:
        cout << "Республика Мордовия" << endl;
        break;
    case 15:
        cout << "Республика Северная Осетия — Алания" << endl;
        break;
       
    case 116:
    case 716:
        cout << "Республика Татарстан" << endl;
        break;
    default:
        cout << "Информация временно недоступна" << endl;
    }

    return 0;
}
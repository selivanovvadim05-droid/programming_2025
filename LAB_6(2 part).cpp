
#include <iostream> 
#include <iomanip>  
#include <string> 

using namespace std;
int main() {
    setlocale(LC_ALL, "RU");

    double a;
    double b;

    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    double* A = &a;
    double* B = &b;

    *A = (*A) * 3;

    cout << a << endl;
    cout << b << endl;

    double* C = new double;

    if (C == nullptr) {
        cerr << endl;
        return 1;
    }

    *C = *A;
    *A = *B;
    *B = *C;

    delete C;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    return 0;
}
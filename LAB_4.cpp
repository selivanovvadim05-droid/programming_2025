#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    //                              ����� 1
    setlocale(LC_ALL, "RU");
    int size = 8;
    vector<int> mas(size);

    cout << "������� " << size << " ����� ����� ��� �������:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> mas[i];
    }

    int cnt = 0;
    for (int i = 0; i < size; ++i) {
        if (mas[i] == 25) {
            cnt++;
        }
    }

    if (cnt > 2) {
        sort(mas.begin(), mas.end());
        cout << "������ ���������� �� �����������." << endl;
    }
    else {
        cout << "����� 25 ����������� �� ����� ���� ���. ������ �� ����������." << endl;
    }

    cout << "������: ";
    for (int i = 0; i < size; ++i) {
        cout << mas[i] << " ";
    }
    cout << endl;

    //                                          ����� 2
    const int row = 3;
    const int col = 4;
    int matrix[row][col];

    cout << "������� �������� ������� " << row << "x" << col << ":" << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> matrix[i][j];
        }
    }

    int maxrow0 = -1;
    int maxcnt0 = -1;

    for (int i = 0; i < row; ++i) {
        int current = 0;
        for (int j = 0; j < col; ++j) {
            if (matrix[i][j] == 0) {
                current++;
            }
        }

        if (current > maxcnt0) {
            maxcnt0 = current;
            maxrow0 = i;
        }
    }

    if (maxrow0 != -1) {
        cout << "������ � ���������� ����������� �����: " << maxrow0 << endl;
        for (int j = 0; j < col; ++j) {
            if (matrix[maxrow0][j] == 0) {
                matrix[maxrow0][j] = 888;
            }
        }
    }
    else {
        cout << "� ������� ��� �����." << endl;
    }

    cout << "���������� �������:" << endl;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

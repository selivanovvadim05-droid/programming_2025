#include <iostream>   
#include <iomanip>    
#include <string>     
#include <limits>     
#include <cstdlib>    

using namespace std;

int input(const string& prompt, bool res = false) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (res && value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
            return value;
    }
}

void printMatrix(int** matrix, int rows, int cols, const string& title) {
    cout << "\n--- " << title << " (" << rows << "x" << cols << ") ---" << endl;
    if (!matrix || rows <= 0 || cols <= 0) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        if (!matrix[i])
            return;
        for (int j = 0; j < cols; ++j)
            cout << setw(6) << matrix[i][j];
        cout << endl;
    }
}

void freeMatrix(int** matrix, int rows) {
    if (!matrix) return;
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

int** createMatrix(int initROWS, int initCOLS) {
    int** matrix = (int**)malloc(initROWS * sizeof(int*));
    if (!matrix)
        return NULL;

    for (int i = 0; i < initROWS; ++i) {
        matrix[i] = (int*)malloc(initCOLS * sizeof(int));
        if (!matrix[i]) {
            for (int k = 0; k < i; ++k)
                free(matrix[k]);
            free(matrix);
            return NULL;
        }
        for (int j = 0; j < initCOLS; ++j) {
            matrix[i][j] = input("¬ведите число дл€ [" + to_string(i) + "][" + to_string(j) + "]: ");
        }
    }
    return matrix;
}

struct Col_Indices {
    int* indices;
    int count;
};

Col_Indices find_zeros(int** matrix, int rows, int cols) {
    Col_Indices result = { NULL, 0 };

    if (!matrix || rows <= 0 || cols <= 0) {
        return result;
    }

    bool* rest = (bool*)calloc(cols, sizeof(bool));
    if (!rest) {
        return result;
    }

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (!matrix[i]) {
                free(rest);
                return result;
            }
            if (matrix[i][j] == 0) {
                if (!rest[j]) {
                    rest[j] = true;
                    result.count++;
                }
                break;
            }
        }
    }

    if (result.count > 0) {
        result.indices = (int*)malloc(result.count * sizeof(int));
        if (!result.indices) {
            free(rest);
            result.count = 0;
            return result;
        }

        int current_index = 0;
        for (int j = 0; j < cols; ++j) {
            if (rest[j]) {
                result.indices[current_index++] = j;
            }
        }
    }

    free(rest);
    return result;
}

int** deleteCOL(int** orig_Matrix, int orig_Rows, int orig_Cols, const int* col_to_del_inc, int num_col_to_del, int* newCols) {

    *newCols = orig_Cols - num_col_to_del;

    if (*newCols <= 0)
        return NULL;

    int** newMatrix = (int**)malloc(orig_Rows * sizeof(int*));
    if (!newMatrix) {

        return NULL;
    }

    for (int i = 0; i < orig_Rows; ++i) {
        newMatrix[i] = (int*)malloc(*newCols * sizeof(int));
        if (!newMatrix[i]) {
            for (int k = 0; k < i; ++k) free(newMatrix[k]);
            free(newMatrix);
            return NULL;
        }

        int cur_new_col_ind = 0;
        for (int j = 0; j < orig_Cols; ++j) {
            bool col_to_del = false;
            for (int k = 0; k < num_col_to_del; ++k) {
                if (j == col_to_del_inc[k]) {
                    col_to_del = true;
                    break;
                }
            }
            if (!col_to_del) {
                if (!orig_Matrix[i]) {
                    freeMatrix(newMatrix, i + 1);
                    return NULL;
                }
                newMatrix[i][cur_new_col_ind++] = orig_Matrix[i][j];
            }
        }
    }
    return newMatrix;
}

int main() {
    setlocale(LC_ALL, "RU");

    const int Row = 2;
    const int Col = 2;

    int** init_Matrix = createMatrix(Row, Col);
    if (!init_Matrix) return EXIT_FAILURE;
    printMatrix(init_Matrix, Row, Col, "start board ");

    int A = input("A: ", true);
    int B = input("B: ", true);
    int C = input("C: ");
    int D = input("D: ");

    int exp_Rows = Row + A;
    int exp_Cols = Col + B;

    int** exp_Matrix = (int**)malloc(exp_Rows * sizeof(int*));
    if (!exp_Matrix) {
        freeMatrix(init_Matrix, Row);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < exp_Rows; ++i) {
        exp_Matrix[i] = (int*)malloc(exp_Cols * sizeof(int));
        if (!exp_Matrix[i]) {
            for (int k = 0; k < i; ++k) free(exp_Matrix[k]);
            free(exp_Matrix);
            freeMatrix(init_Matrix, Row);
            return EXIT_FAILURE;
        }

        for (int j = 0; j < exp_Cols; ++j) {
            if (i < Row && j < Col) {
                exp_Matrix[i][j] = init_Matrix[i][j];
            }
            else
                exp_Matrix[i][j] = (i - 1) * C + (j - 1) * D;
        }
    }
    printMatrix(exp_Matrix, exp_Rows, exp_Cols, "\n");

    Col_Indices info0 = find_zeros(exp_Matrix, exp_Rows, exp_Cols);
    if (info0.count > 0) {
        for (int i = 0; i < info0.count; ++i)
            cout << info0.indices[i] << (i == info0.count - 1 ? "" : ", ");
        cout << endl;
    }

    int** finalMatrix = NULL;
    int final_cnt = 0;

    if (info0.count > 0) {
        finalMatrix = deleteCOL(exp_Matrix, exp_Rows, exp_Cols, info0.indices, info0.count, &final_cnt);
        if (!finalMatrix && final_cnt > 0) {
            freeMatrix(init_Matrix, Row);
            freeMatrix(exp_Matrix, exp_Rows);
            free(info0.indices);
            return EXIT_FAILURE;
        }
        if (!finalMatrix && final_cnt <= 0)
            cout << endl;
    }
    else {
        final_cnt = exp_Cols;
        finalMatrix = (int**)malloc(exp_Rows * sizeof(int*));
        if (!finalMatrix) {
            freeMatrix(init_Matrix, Row);
            freeMatrix(exp_Matrix, exp_Rows);
            free(info0.indices);
            return EXIT_FAILURE;
        }
        for (int i = 0; i < exp_Rows; ++i) {
            finalMatrix[i] = (int*)malloc(exp_Cols * sizeof(int));
            if (!finalMatrix[i]) {
                for (int k = 0; k < i; ++k) free(finalMatrix[k]);
                free(finalMatrix);
                freeMatrix(init_Matrix, Row);
                freeMatrix(exp_Matrix, exp_Rows);
                free(info0.indices);
                return EXIT_FAILURE;
            }
            for (int j = 0; j < exp_Cols; ++j)
                finalMatrix[i][j] = exp_Matrix[i][j];
        }
    }
    printMatrix(finalMatrix, exp_Rows, final_cnt, "New matrix");

    freeMatrix(init_Matrix, Row);
    freeMatrix(exp_Matrix, exp_Rows);
    free(info0.indices);

    if (finalMatrix)
        freeMatrix(finalMatrix, exp_Rows);

    return 0;
}


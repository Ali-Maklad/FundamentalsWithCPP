#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

int RandomNumBetween(int From, int To)
{
    int Random = rand() % (To - From + 1) + From;
    return Random;
}

void GenerateRandomMatrix(int Matrix[3][3], short rows, short cols)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Matrix[i][j] = RandomNumBetween(1, 10);
        }
    }
}

void Multiplie2Matrix(int Matrix1[3][3], int Matrix2[3][3], int MultipliedMatrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            MultipliedMatrix[i][j] = (Matrix1[i][j] * Matrix2[i][j]);
        }
    }
}

void PrintMatrix(int Matrix[3][3], short rows, short cols, string Title)
{
    cout << Title << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("  %0*d  ", 2, Matrix[i][j]);
        }
        cout << endl;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int Matrix1[3][3], Matrix2[3][3], MultipliedMatrix[3][3];
    GenerateRandomMatrix(Matrix1, 3, 3);
    GenerateRandomMatrix(Matrix2, 3, 3);
    Multiplie2Matrix(Matrix1, Matrix2, MultipliedMatrix);
    PrintMatrix(Matrix1, 3, 3, "Matrix1:");
    PrintMatrix(Matrix2, 3, 3, "Matrix2:");
    PrintMatrix(MultipliedMatrix, 3, 3, "Reuslt:");
    return 0;
}
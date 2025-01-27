#include <iostream>
#include <iomanip>
#include <cstdlib>

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
            Matrix[i][j] = RandomNumBetween(1, 100);
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
            cout << "  " << setw(3) << Matrix[i][j];
        }
        cout << endl;
    }
}

bool CheckNum(int Matrix[3][3], int Num, short rows, short cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (Matrix[i][j] == Num)
                return true;
        }
    }
    return false;
}

void PrintIntersected(int Matrix1[3][3], int Matrix2[3][3], short rows, short cols)
{

    cout << "Intersected numbers are: ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (CheckNum(Matrix1, Matrix2[i][j], rows, cols))
            {
                cout << Matrix2[i][j] << "  ";
            }
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int Matrix1[3][3], Matrix2[3][3];
    GenerateRandomMatrix(Matrix1, 3, 3);
    GenerateRandomMatrix(Matrix2, 3, 3);

    PrintMatrix(Matrix1, 3, 3, "Matrix1:");
    PrintMatrix(Matrix2, 3, 3, "Matrix2:");

    PrintIntersected(Matrix1, Matrix2, 3, 3);

    return 0;
}
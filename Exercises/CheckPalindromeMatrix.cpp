#include <iostream>
#include <cstdlib>
#include <iomanip>

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

bool CheckPalindrome(int Matrix[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            if (Matrix[i][j] != Matrix[i][cols - 1 - j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    srand((unsigned)time(NULL));

    int Matrix1[3][3] = {1, 2, 1, 5, 0, 5, 7, 3, 7};

    PrintMatrix(Matrix1, 3, 3, "Matrix1:");

    if (CheckPalindrome(Matrix1, 3, 3))
    {
        cout << "plaindrome \n";
    }
    else
    {
        cout << "not";
    }

    return 0;
}
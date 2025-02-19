#include <iostream>
#include <iomanip>

using namespace std;

const string ArrMonthsNames[12]{"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

const string ArrDays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int ReadPositiveNum(string message, short From, short To)
{
    int Num;
    do
    {
        cout << message << endl;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

bool IsLeapYear(short Year)
{
    return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
}

short MonthDays(short Month, short Year)
{
    short ArrDaysOfMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : ArrDaysOfMonths[Month - 1];
}

short CalcFirstDayIndex(short Year, short Month)
{
    short a = (14 - Month) / 12;
    short y = Year - a;
    short m = Month + (12 * a) - 2;
    short d = (1 + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;

    return d;
}

string MonthIndexToName(short MonthIndex)
{

    return ArrMonthsNames[MonthIndex - 1];
}

void PrintMonthCalendar()
{
    short Year = ReadPositiveNum("Please enter the year?", 0, 3000);
    short Month = ReadPositiveNum("Please enter the Month? ", 1, 12);
    cout << "______________" << MonthIndexToName(Month) << "_________________\n\n";
    for (int i = 0; i < 7; i++)
    {
        cout << setw(4) << ArrDays[i];
    }
    cout << "\n";
    short FirstDay = CalcFirstDayIndex(Year, Month);
    short TotalDaysOfMonth = MonthDays(Month, Year);
    short Day = 1;
    int i = 0;
    for (i = 0; i < FirstDay; i++)
    {
        cout << "    ";
    }
    for (int j = 1; j <= TotalDaysOfMonth; j++)
    {
        cout << setw(4) << j;
        i++;
        if (i > 6)
        {
            cout << "\n";
            i = 0;
        }
    }
    cout << "\n______________________________________";
}

int main()
{
    PrintMonthCalendar();
    return 0;
}
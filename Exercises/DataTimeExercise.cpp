#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    time_t t = time(0);

    tm *now = localtime(&t);

    cout << "Year: " << now->tm_year + 1900 << "\n";
    cout << "Month: " << now->tm_mon + 1 << '\n';
    cout << "Day: " << now->tm_mday << endl;
    cout << "Hour: " << now->tm_hour << "\n";
    cout << "Minutes: " << now->tm_min << "\n";
    cout << "Seconds: " << now->tm_sec << "\n";

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

string ReadText()
{
    string Text;
    cout << "Please enter your text\n";
    getline(cin, Text);
    return Text;
}

string TrimLeft(string Text, string Delim)
{
    short pos = 0;

    while (Text.substr(pos, Delim.length()) == Delim)
    {
        pos += Delim.length();
    }
    Text = Text.erase(0, pos);
    return Text;
}

string TrimRight(string Text, string Delim)
{
    int Pos = Text.length();
    int DLength = Delim.length();
    if (DLength > Pos)
        return Text;
    while (Text.substr(Pos - DLength, DLength) == Delim)
    {
        Pos -= DLength;
        if ((Pos - DLength) < 0)
        {
            Text = Text.erase(Pos);
            return Text;
        }
    }

    Text = Text.erase(Pos);
    return Text;
}

string Trim(string Text, string Delim)
{
    return TrimRight(TrimLeft(Text, Delim), Delim);
}

int main()
{
    string Text = ReadText();
    cout << Trim(Text, "-");

    return 0;
}
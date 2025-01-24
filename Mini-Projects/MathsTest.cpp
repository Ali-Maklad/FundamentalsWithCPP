#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum EnLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    MixLevel = 4
};

enum EnOpType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};

enum EnPassFail
{
    Pass = 1,
    Fail = 2
};

struct stQuestionInfo
{
    int Num1;
    int Num2;
    short QuestionNum;
    int RightAnswer;
    int UserAnswer;
};

struct stQuizInfo
{
    EnLevel Level;
    EnOpType OpType;
    short QuestionsCount;
    short RightAnswers;
    short WrongAnswers;
    EnPassFail PassOrFail;
};

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

int ReadPositiveNum(string message)
{
    int Num;
    do
    {
        cout << message << endl;
        cin >> Num;
    } while (Num <= 0);
    return Num;
}

int ReadPositiveNumBetween(int From, int To)
{
    int Num;
    do
    {
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

int RandomNumBetween(int From, int To)
{
    int Rand = rand() % (To - From + 1) + From;
    return Rand;
}

short HowManyQuestions()
{
    int QuestionsCount = ReadPositiveNum("How many questions do you want ?");
    return QuestionsCount;
}

EnLevel ReadLevel()
{
    cout << "Enter Operation Level [1]Easy,  [2]Med,  [3]Hard,  [4]Mix ?  ";
    short LevelNum = ReadPositiveNumBetween(1, 4);
    return (EnLevel)LevelNum;
}

EnOpType ReadOpType()
{
    cout << "Enter Operation Type [1]Add , [2]Sub, [3]Mul, [4]Div, [5]Mix ?  ";
    short OpTypeNum = ReadPositiveNumBetween(1, 5);
    return (EnOpType)OpTypeNum;
}

int AnswerByOperation(EnOpType &OpType, int Num1, int Num2)
{
    switch (OpType)
    {
    case Add:
        return Num1 + Num2;

    case Sub:
        return Num1 - Num2;

    case Mul:
        return Num1 * Num2;

    case Div:
        return Num1 / Num2;

    case MixOp:
        OpType = (EnOpType)RandomNumBetween(1, 4);
        return AnswerByOperation(OpType, Num1, Num2);
    }
}

int NumByLevel(EnLevel Level)
{
    switch (Level)
    {
    case Easy:
        return RandomNumBetween(1, 20);
    case Med:
        return RandomNumBetween(20, 50);
    case Hard:
        return RandomNumBetween(50, 100);
    case MixLevel:
        return NumByLevel((EnLevel)RandomNumBetween(1, 3));
    }
}

void FillQuizInfo(stQuizInfo &QuizInfo)
{

    QuizInfo.QuestionsCount = HowManyQuestions();
    QuizInfo.Level = ReadLevel();
    QuizInfo.OpType = ReadOpType();
    QuizInfo.RightAnswers = 0;
    QuizInfo.WrongAnswers = 0;
}

string WriteOpType(EnOpType OpType)
{
    string Arr[5] = {"+", "-", "*", " / ", "Mix"};
    return Arr[OpType - 1];
}

void Question(stQuestionInfo &QuestionInfo, stQuizInfo QuizInfo)
{
    QuestionInfo.Num1 = NumByLevel(QuizInfo.Level);
    QuestionInfo.Num2 = NumByLevel(QuizInfo.Level);
    QuestionInfo.RightAnswer = AnswerByOperation(QuizInfo.OpType, QuestionInfo.Num1, QuestionInfo.Num2);
    cout << "Question [" << QuestionInfo.QuestionNum << "/" << QuizInfo.QuestionsCount << "]\n\n";
    cout << QuestionInfo.Num1 << endl;
    cout << QuestionInfo.Num2 << "  " << WriteOpType(QuizInfo.OpType) << endl;
    cout << "________________\n";
    cin >> QuestionInfo.UserAnswer;
    cout << "\n";
}

void PrintQuestionResult(int UserAnswer, int RightAnswer, stQuizInfo &QuizInfo)
{

    if (UserAnswer == RightAnswer)
    {
        cout << "Right Answer :)\n";
        system("color 2f");
        QuizInfo.RightAnswers++;
    }
    else
    {
        cout << "Wrong Answer :(\n";
        cout << "Right answer is : " << RightAnswer;
        system("color 4f");
        QuizInfo.WrongAnswers++;
    }
    cout << "\n\n";
}

EnPassFail PassOrFail(short RightAnswers, short WrongAnswers)
{
    if (RightAnswers >= WrongAnswers)
    {
        system("color 2f");
        return Pass;
    }
    else
    {
        system("color 4f");
        return Fail;
    }
}

string WritePassOrFail(EnPassFail PassOrFail)
{
    string Arr[2] = {"Pass :)", "Fail :("};
    return Arr[PassOrFail - 1];
}

string WriteQuizLevel(EnLevel Level)
{
    string Arr[4] = {
        "Easy",
        "Med",
        "Hard",
        "Mix",
    };
    return Arr[Level - 1];
}

void PrintQuizResults(stQuizInfo QuizInfo)
{

    QuizInfo.PassOrFail = PassOrFail(QuizInfo.RightAnswers, QuizInfo.WrongAnswers);
    cout << "______________________________________\n";
    cout << "   FINAL REUSLT IS  " << WritePassOrFail(QuizInfo.PassOrFail) << endl;
    cout << "______________________________________\n";
    cout << "Number of questions is:\t" << QuizInfo.QuestionsCount << "\n";
    cout << "Question level is : \t" << WriteQuizLevel(QuizInfo.Level) << "\n";
    cout << "Op Type is : \t" << WriteOpType(QuizInfo.OpType) << "\n";
    cout << "Number of Right Answers is :\t" << QuizInfo.RightAnswers << "\n";
    cout << "Number of Wrong Answers is :\t" << QuizInfo.WrongAnswers << "\n";
    cout << "______________________________________\n\n";
}

void Quiz()
{

    stQuizInfo QuizInfo;
    FillQuizInfo(QuizInfo);
    stQuestionInfo QuestionInfo;
    cout << "\n\n";
    for (QuestionInfo.QuestionNum = 1; QuestionInfo.QuestionNum <= QuizInfo.QuestionsCount; QuestionInfo.QuestionNum++)
    {
        Question(QuestionInfo, QuizInfo);
        PrintQuestionResult(QuestionInfo.UserAnswer, QuestionInfo.RightAnswer, QuizInfo);
    }
    PrintQuizResults(QuizInfo);
}

bool Replay()
{
    char YN;
    cout << "Do you want to play another game ? [Y/N]    ";
    cin >> YN;
    if (YN == 'Y' || YN == 'y')
        return true;
    else
        return false;
}

void StartQuiz()
{
    do
    {
        ResetScreen();
        Quiz();

    } while (Replay() == true);
}

int main()
{
    srand((unsigned)time(NULL));

    StartQuiz();

    return 0;
}
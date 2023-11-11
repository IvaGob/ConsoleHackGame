#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <random>
#include <Lmcons.h>
using namespace std;
#define LINELIMIT 50
#define WORDSLIMIT 12
#define WHITE 7
#define GREY 8
#define TRYIES 5

//Function to get random number in between
int RandomRange(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(min, max);

    return distribution(gen);
}
//Function to convert string to char*
char* StringToCharArr(string s) {
    char* char_array = new char[7];
    char_array[s.length()] = '\0';
    for (int i = 0; i < s.length(); i++)
    {
        char_array[i] = s[i];
    }
    strcpy(char_array, s.c_str());
    return char_array;
}
//Function to change text
void SetTextColor(int color) {
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole,color);
}
//function for transiction betwen lines
int LineLimitCheck(int character) {
    if (character >= LINELIMIT) {
        cout << endl;
        return 0;
    }
    return character;
}
//Funcion to write word by characters
int WriteWord(string word , int character) {
    int characterscount = character;
    char* chars = StringToCharArr(word);
    SetTextColor(WHITE);
    for (int i = 0; i <= word.length(); i++) 
    {
        characterscount++;
        characterscount = LineLimitCheck(characterscount);
        cout << chars[i];
    }
    SetTextColor(GREY);
    return characterscount;
}
//write Opening
void Opening() {
    //Setting Green color for text
    SetTextColor(WHITE);
    //Playing sound
    Beep(750, 115);
    Beep(850, 115);
    Beep(550, 300);
    //Writing Logo
    cout << "  _____     ____    ____     _____    ____  \n"
        << " |  __ \\   / __ \\  |  _ \\   / ____|  / __ \\ \n"
        << " | |__) | | |  | | | |_) | | |      | |  | |\n"
        << " |  _  /  | |  | | |  _ <  | |      | |  | |\n"
        << " | | \\ \\  | |__| | | |_) | | |____  | |__| |\n"
        << " |_|  \\_\\  \\____/  |____/   \\_____|  \\____/ \n";
    cout << "=====================================================" << endl;
    cout << "\nENTER THE PASSWORD:\n\n";
    SetTextColor(GREY);
}
//Get username of windows user
char* GetUser() {
    char* user = getenv("username");
    return user;
}
void Check(string password) {
    int tryiesCount = 0;
    bool correct = false;
    while (correct == false && tryiesCount <= TRYIES)
    {
        //
        cout << "\n\n >";
        string answer;
        cin >> answer;
        //
        int similarity = 0;
        char* answerChar = StringToCharArr(answer);
        char* passwordChar = StringToCharArr(password);
        for (int i = 0; i < password.length(); i++)
        {
            if (i >= answer.length())break;
            if (answerChar[i] == password[i])similarity++;
        }
        if (similarity == password.length())
        {
            cout << "Welcome,"<< GetUser() <<"!";
            Beep(900, 115);
            getchar();
            break;
        }
        else
        {
            cout << "Entry denied\n" << similarity << "/" << password.length() << " correct";
            Beep(400, 300);
            tryiesCount++;
        }
    }
    if (tryiesCount >= TRYIES) {
        Beep(400, 300);
        Beep(400, 300);
        Beep(400, 300);
        cout << "\n\nTerminal is locked! Please call our tech support to unlock";
        getchar();
    }
}
int main()
{
    //Words that  can be password
    string variants[20] = 
    {   "TREE",
        "MONEY",
        "WOOD",
        "TANK",
        "ZOMBIE",
        "SAUSAGE",
        "MOTHER",
        "PUPPY",
        "FROG",
        "SUMMER",
        "SPACE",
        "PEACE",
        "FREEDOM",
        "HOPE",
        "DEATH",
        "WATER",
        "SODA",
        "BIRD",
        "BRAIN",
        "PAIN",
    };
    //string password = variants[RandomRange(0,19)];
    string password;
    
    
    Opening();
    srand(time(NULL));
    int countCh = 0;
    int countWords = 0;
    string lastWord;
    for (int i = 0; i <= 400; i++)
    {
        char a = '\0' + RandomRange(32, 64);
        cout << a;
        countCh++;
        countCh = LineLimitCheck(countCh);
        if (RandomRange(0, 20) == 20 && countWords<WORDSLIMIT)
        {
            int r = RandomRange(0, 19);
            countCh = WriteWord(variants[r], countCh);
            if(RandomRange(0,6)==6)
            {
                password = variants[r];
            }
            lastWord = variants[r];
            countWords++;
        }
    }
    if (password == "") 
    {
        password = lastWord;
    }
    
    SetTextColor(WHITE);
    Check(password);
    getchar();
}



#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Function to check if the given character is a punctuator
bool isPunctuator(char ch)
{
    char punctuators[] = {'+', '-', '*', '/', ',', ';', '>', '<', '=', '(', ')', '[', ']', '{', '}', '&', '|', '!', '_'};
    for (char p : punctuators)
    {
        if (ch == p)
        {
            return true;
        }
    }
    return false;
}

// Function to check if the given string is a keyword
bool isKeyword(const string &str)
{
    string keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct", "sizeof", "volatile", "typedef", "enum", "const", "union", "extern", "bool"};
    for (const string &keyword : keywords)
    {
        if (str == keyword)
        {
            return true;
        }
    }
    return false;
}

// Function to check if the given string is a valid identifier
bool isValidIdentifier(const string &str)
{
    if (!isalpha(str[0]) && str[0] != '_')
    {
        return false;
    }
    for (char c : str)
    {
        if (!isalnum(c) && c != '_')
        {
            return false;
        }
    }
    return true;
}

// Function to check if the given character is an operator
bool isOperator(char ch)
{
    char operators[] = {'+', '-', '*', '/', '>', '<', '=', '|', '&', '!'};
    for (char op : operators)
    {
        if (ch == op)
        {
            return true;
        }
    }
    return false;
}

// Function to check if the given string is a number
bool isNumber(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c) && c != '.')
        {
            return false;
        }
    }
    return true;
}

// Function to parse the expression and identify tokens
void parse(const string &expression)
{
    string token;
    const int size = expression.size();
    for (int i = 0; i < size; ++i)
    {
        char ch = expression[i];
        // cout << "INDEX ===> " << i << " Char ====> " << ch << endl;
        if (isspace(ch) || isPunctuator(ch) || i == size - 1)
        {
            if (!isspace(ch) && !isPunctuator(ch) && i == size - 1)
            {
                token += ch;
            }
            if (!token.empty())
            {
                // cout << "TOKEN ==>" << token << endl;
                if (isKeyword(token))
                {
                    cout << token << " IS A KEYWORD" << endl;
                }
                else if (isNumber(token))
                {
                    cout << token << " IS A NUMBER" << endl;
                }
                else if (isValidIdentifier(token))
                {
                    cout << token << " IS A VALID IDENTIFIER" << endl;
                }
                else
                {
                    cout << token << " IS NOT A VALID IDENTIFIER" << endl;
                }
                token.clear();
            }
            if (isOperator(ch))
            {
                cout << ch << " IS AN OPERATOR" << endl;
            }
           else if (isPunctuator(ch))
            {
                cout << ch << " IS AN Symbol" << endl;
            }
        }
        else
        {
            token += ch;
        }
    }
}

int main()
{
    // string filename;
    // cout << "Enter the name of the file: ";
    // cin >> filename;

    ifstream file("input.txt");

    if (!file.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        parse(line);
    }

    file.close();

    return 0;
}

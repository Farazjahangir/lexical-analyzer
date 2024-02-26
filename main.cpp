#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Function to check if the given character is a punctuator
bool isPunctuator(char ch)
{
    char punctuators[] = {'+', '-', '*', '/', ',', ';', '>', '<', '=', '(', ')', '[', ']', '{', '}', '&', '|'};
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
    string keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "case", "long", "switch", "unsigned", "void", "static", "struct", "enum", "const", "bool", "isalpha", "isalnum", "int", "function", "print", "elseif"};
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
    const int size = str.size();
    bool numFound = false;
    if (!isalpha(str[0]) && str[0] != '_') // Check if the first character is an alphabet or underscore
    {
        return false;
    }
    for (int i = 1; i < size; i++)  // Start from the second character
    {
        if (!isalnum(str[i]) && str[i] != '_') // Check if each character is alphanumeric or underscore
        {
            return false;
        }
        // if (i == size - 1 && isdigit(str[i])) { // If it's the last character and it's a number
        //     return true; // Allow numbers at the end
        // }
        if (isdigit(str[i]) && i != size - 1) {
            numFound = true;
        }
        if (numFound && isalpha(str[i])) {
            return false;
        } 
    }
    return true;
}
// Function to check if the given character is an operator
bool isOperator(const string &str)
{
    string operators[] = {"+", "-", "*", "/", ">", "<", "=", "|", "&", "!", "==", "!=", "&&", "+="};
    for (const string &op : operators)
    {
        if (str == op)
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

string checkForOperator(char ch, int size, int &i, string expression)
{
    if (isOperator(string(1, ch)))
    {
        // Check for multi-character operators
        string multiOp(1, ch); // Start with the current character
        int j = i + 1;
        while (j < size)
        {
            multiOp += expression[j]; // Add the next character
            if (!isOperator(multiOp))
            {
                multiOp.pop_back();
                break; // Stop if the current sequence is not an operator
            }
            j++;
        }
        i = j - 1;
        // if (isOperator(multiOp))
        // {
        //     cout << "IF" << endl;
        //     cout << multiOp << " IS AN multi OPERATOR" << endl;
        //     i = j - 1; // Move the index to the end of the multi-character operator
        // }
        // else
        // {
        //     cout << "Else" << endl;
        //     cout << ch << " IS AN OPERATOR" << endl; // Treat single character as an operator
        // }
        return multiOp;
    }
    return "";
}

// Function to parse the expression and identify tokens
void parse(const string &expression)
{
    string token;
    const int size = expression.size();
    for (int i = 0; i < size; ++i)
    {
        char ch = expression[i];

        if (isspace(ch) || isPunctuator(ch) || i == size - 1)
        {
            if (!isspace(ch) && !isPunctuator(ch) && i == size - 1)
            {
                token += ch;
            }
            if (!token.empty())
            {
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
            const string isSingleOrMultiCharOp = checkForOperator(ch, size, i, expression);
            if (isSingleOrMultiCharOp != "")
            {
                cout << isSingleOrMultiCharOp << " is a operator" << endl;
            }
            else if (isPunctuator(ch))
            {
                cout << ch << " IS A Symbol" << endl;
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

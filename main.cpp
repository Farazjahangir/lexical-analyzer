#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Function to check if the given character is a punctuator
bool isPunctuator(char ch)
{
    char punctuators[] = {
        '+','-','*','/',',',';','>','<','=','(',')','[',']','{','}','&','|'
        };
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
    string keywords[] = {
        "if","else","while","do","break","int","return","char","case","switch","void","bool","int","function","print","string"
        };

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
    for (int i = 1; i < size; i++) // Start from the second character
    {
        if (!isalnum(str[i]) && str[i] != '_') // if current character is not alphanumeric or underscore
        {
            return false;
        }
        if (isdigit(str[i]) && i != size - 1)
        {
            numFound = true;
        }
        if (numFound && isalpha(str[i]))
        {
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
        return multiOp;
    }
    return "";
}

// Function to parse the expression and identify tokens
void parse(const string &expression)
{
    string token;
    const int size = expression.size();
    bool insideQuotes = false; // Flag to track if currently inside quotes

    for (int i = 0; i < size; ++i)
    {
        char ch = expression[i];
        if (ch == '"' || ch == '\'') // Check if it's the start or end of a quoted string
        {
            if (!insideQuotes)
            {
                cout << "\033[1;32m" << ch << "\033[0m"
                     << " -> is a Quotation Marks" << endl;
            }
            else
            {
                if (!token.empty())
                {
                    cout << "\033[1;32m" << token << "\033[0m"
                         << " -> is a String" << endl;
                    token.clear();
                }
                cout << "\033[1;32m" << ch << "\033[0m"
                     << " -> is a Quotation Marks" << endl;
            }
            insideQuotes = !insideQuotes; // Toggle the flag
        }

        else if ((isspace(ch) || isPunctuator(ch) || i == size - 1) && !insideQuotes)
        {
            if (!isspace(ch) && !isPunctuator(ch) && i == size - 1)
            {
                token += ch;
            }
            if (!token.empty())
            {
                if (isKeyword(token))
                {
                    cout << "\033[1;32m" << token << "\033[0m"
                         << " -> is a Keyword" << endl;
                }
                else if (isNumber(token))
                {
                    cout << "\033[1;32m" << token << "\033[0m"
                         << " -> is a Number" << endl;
                }
                else if (isValidIdentifier(token))
                {
                    cout << "\033[1;32m" << token << "\033[0m"
                         << " -> is a valid Indetifier" << endl;
                }
                else
                {
                    cout << "\033[1;31m" << token << "\033[0m"
                         << " -> is a not a valid Indentifier" << endl;
                }
                token.clear();
            }
            const string isSingleOrMultiCharOp = checkForOperator(ch, size, i, expression);
            if (isSingleOrMultiCharOp != "")
            {
                cout << "\033[1;32m" << isSingleOrMultiCharOp << "\033[0m"
                     << " -> is a Operator" << endl;
            }
            else if (isPunctuator(ch))
            {
                cout << "\033[1;32m" << ch << "\033[0m"
                     << " -> is a Symbol" << endl;
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
    string filename;
    cout << "Enter the name of the file: ";
    cin >> filename;
    cout << endl;
    ifstream file(filename);

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
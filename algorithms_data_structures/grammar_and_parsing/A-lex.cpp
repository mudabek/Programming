#include <bits/stdc++.h>

using namespace std;

enum Expression { number, plus, minus, mul, div, open, close, end };

class Lexer
{
public:

    string s;
    int curPos;
    Expression curLex;
    int curVal;
    char curSym;

    class WrongSymbolException : public exception
    {
        virtual const char* what() const throw()
        {
            return "WRONG";
        }
    };

    explicit Lexer(string s) : s(s), curPos(0) {}

    bool nextLexem()
    {
        if (curPos >= s.length() || s[curPos] == '.')
        {
            curLex = Expression::end;
            return false;
        }
        char c = s[curPos];

        if (isdigit(c))
        {
            curLex = Expression::number;
            parseNumber();
        }
        else if (c == '+')
        {
            curLex = Expression::plus;
            curSym = c;
        }
        else if (c == '-')
        {
            curLex = Expression::minus;
            curSym = c;
        }
        else if (c == '*')
        {
            curLex = Expression::mul;
            curSym = c;
        }
        else if (c == '/')
        {
            curLex = Expression::div;
            curSym = c;
        }
        else if (c == '(')
        {
            curLex = Expression::open;
            curSym = c;
        }
        else if (c == ')')
        {
            curLex = Expression::close;
            curSym = c;
        }
        else
        {
            throw WrongSymbolException();
        }
        curPos++;
        return true;
    }

    Expression getCurLex()
    {
        return curLex;
    }

    int getCurVal()
    {
        return curVal;
    }

    char getCurSym()
    {
        return curSym;
    }

    void parseNumber()
    {
        curVal = 0;
        while (curPos < s.length() && isdigit(s[curPos]))
        {
            curVal = curVal * 10 + (s[curPos] - '0');
            curPos++;
        }
        curPos--;
    }
};

int main()
{
    string s;
    cin >> s;
    Lexer lexer(s);

    while (lexer.nextLexem())
    {
        Expression exp = lexer.getCurLex();

        if (exp == Expression::number)
            cout << lexer.getCurVal() << "\n";
        else
            cout << lexer.getCurSym() << "\n";
    }

    return 0;
}

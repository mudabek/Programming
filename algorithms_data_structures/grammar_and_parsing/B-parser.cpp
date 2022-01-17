#include <bits/stdc++.h>

using namespace std;

enum expr { Num, Plus, Minus, Mul, Div, Open, Close, End };

class WrongSymbolException : public exception
{
    virtual const char *what() const throw()
    {
        return "This lexer accepts only +-*/() and numbers!";
    }
};

class Expression
{
public:
    virtual long int evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
    long int value;

    NumberExpression(double val) : value(val) {}
    virtual long int evaluate()
    {
        return value;
    }
};

class ArithmeticExpression : public Expression
{
public:
    Expression *left, *right;
    expr op;

    ArithmeticExpression(expr op, Expression *l, Expression *r)
        : left(l), right(r), op(op) {}

    virtual ~ArithmeticExpression()
    {
        if (left)
        {
            delete left;
        }
        if (right)
        {
            delete right;
        }
    }

    virtual long int evaluate()
    {
        if (left == nullptr || right == nullptr)
        {
            return 0;
        }

        long int result = 0;
        long int a = left->evaluate();
        long int b = right->evaluate();
        switch (op)
        {
        case expr::Plus:
            result = a + b;
            break;
        case expr::Minus:
            result = a - b;
            break;
        case expr::Mul:
            result = a * b;
            break;
        default:
            throw WrongSymbolException();
            break;
        }
        return result;
    }
};

class ExpressionParser
{
public:

    string expression;
    expr curLexem;
    int value;
    char varName;
    int index;

    bool isDigit(char symbol)
    {
        return '0' <= symbol && symbol <= '9';
    }

    bool isOperation(char symbol)
    {
        return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
    }

    void parseNumber()
    {
        value = 0;
        while (index < expression.length() && isDigit(expression[index]))
        {
            value = value * 10 + (expression[index] - '0');
            index++;
        }
    }

    void nextLexem()
    {
        while (index < expression.length() && expression[index] == ' ')
        {
            index++;
        }
        if (index >= expression.length())
        {
            curLexem = expr::End;
            return;
        }
        char symbol = expression[index];
        if (isDigit(symbol))
        {
            curLexem = expr::Num;
            parseNumber();
            index--;
        }
        else if (symbol == '+')
        {
            curLexem = expr::Plus;
        }
        else if (symbol == '-')
        {
            curLexem = expr::Minus;
        }
        else if (symbol == '*')
        {
            curLexem = expr::Mul;
        }
        else if (symbol == '/')
        {
            curLexem = expr::Div;
        }
        else if (symbol == '(')
        {
            curLexem = expr::Open;
        }
        else if (symbol == ')')
        {
            curLexem = expr::Close;
        }
        else
        {
            //need to return wrong somehow;
        }
        index++;
    }

    ArithmeticExpression parseSummand()
    {
        ArithmeticExpression = ArithmeticExpression();
        while (curLexem == expr::Mul || curLexem == expr::Div)
        {
            expr c = curLexem;
            nextLexem();
            if (c == expr::Mul)
            {
                answer = new Multiply(answer, parseMultiplier());
            }
            else if (c == expr::Power)
            {
                answer = new Power(answer, parseMultiplier());
            }
            else
            {
                answer = new Divide(answer, parseMultiplier());
            }
        }
        return answer;
    }
};

int main()
{

}

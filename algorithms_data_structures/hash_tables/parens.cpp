#include <queue>
#include <string>
#include <iostream>

using namespace std;

bool balancedParens(string expr) {
    queue<char> q;

    for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] == '(') {
            q.push('(');
        } else if (expr[i] == ')') {
            if (q.front() != '(') {
                return false;
            }
            q.pop();
        }
    }

    return q.empty();
}

int main() {
    string test1 = "(6 + 5) - ((9*5 -(4 /8)+3) /(2-9)-2)";
    string test2 = "(6 + 5) - (9*5 -(4 /8)+3)) /((2-9)-2)";
    string test3 = "((123)(123)(1(2)1)(1))";
    string test4 = "((()))(";
    string test5 = ")(((())))";
    string test6 = "()())()()";

    // passed all tests
    cout << test1 << "   ### 1 : " << balancedParens(test1) << endl;
    cout << test2 << "   ### 0 : " << balancedParens(test2) << endl;
    cout << test3 << "   ### 1 : " << balancedParens(test3) << endl;
    cout << test4 << "   ### 0 : " << balancedParens(test4) << endl;
    cout << test5 << "   ### 0 : " << balancedParens(test5) << endl;
    cout << test6 << "   ### 0 : " << balancedParens(test6) << endl;
}

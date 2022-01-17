#include <iostream>
#include <functional>

typedef std::function<int (int)> Op;

Op compose (size_t n, Op ops[]) {
    
    if (n == 0) {
        Op idemFunc = [] (int x) -> int {
            return x;
        };
        return idemFunc;
    }
    
    auto exec = 
        [] (int n, Op ops[]) -> Op {
            return [n, ops] (int x) {
                int temp = x;
                for (int i = n - 1; i > -1; -- i) {
                    temp = ops[i](temp);
                }
                return temp;
            };
        };
    
    return exec(n, ops);
}


int main () {
    /// Simple tests:

    Op op1 =
        [] (int x) -> int {
            return x + 1;
        };

    auto op2 =
        [] (int p) -> Op {
            return [p] (int x) {
                return p * x;
            };
        };

    {
        Op ops[4] = {op1, op2(2), op1, op2(2)};
        if (compose(4, ops)(2) != 11) {
            std::cout << "FAILED AT TEST 1" << std::endl;
            return 0;
        }
    }

    {
        Op ops[8] = {op1, op2(2), op1, op1, op1, op2(2), op2(2), op1};
        if (compose(8, ops)(5) != 55) {
            std::cout << "FAILED AT TEST 2" << std::endl;
            return 0;
        }
    }

    {
        Op ops[1] = {op1};
        if (compose(1, ops)(3) != 4) {
            std::cout << "FAILED AT TEST 3" << std::endl;
            return 0;
        }
    }

    {
        Op ops[0] = {};
        if (compose(0, ops)(4) != 4) {
            std::cout << "FAILED AT TEST 4" << std::endl;
            return 0;
        }
    }

    {
        Op ops[4] = {op2(2), op2(3), op2(4), op2(5)};
        if (compose(4, ops)(1) != 120) {
            std::cout << "FAILED AT TEST 5" << std::endl;
            return 0;
        }
    }
}
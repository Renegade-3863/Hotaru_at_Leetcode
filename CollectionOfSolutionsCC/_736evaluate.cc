#include "Solution.h"

// 这道题实在写不出来了，所以只能对着官解做一些注释+分析了
// 官方解法二是状态机的解法，本质上是定义了一些状态并进行转换
enum ExprStatus 
{
    VALUE = 0, // 初始状态
    NONE,      // 表达式类型未知
    LET,       // let 表达式，代表当前在解析一个 let 表达式
    LET1,      // let 表达式已经解析了 vi 变量，注意，let 表达式不一定只有一个或者两个参数，它的参数列表是可以无限长的
    LET2,      // let 表达式已经解析了最后一个表达式 expr
    ADD,       // add 表达式，代表当前在解析一个 add 表达式
    ADD1,      // add 表达式已经解析了 e1 的值，也就是第一个参数，当前 (应该) 在解析第二个参数
    ADD2,      // add 表达式已经解析了 e2 表达式
    MULT,      // mult 表达式
    MULT1,     // mult 表达式已经解析了 e1 表达式
    MULT2,     // mult 表达式已经解析了 e2 表达式
    DONE       // 解析完成
};

// Expr 用于记录当前的表达式状态
// 内部可以存储变量名、数值、表达式的两个参数等
struct Expr 
{
    ExprStatus status;
    string var; // let 的变量 vi
    int value;  // VALUE 状态的数值，或者 LET2 状态最后一个表达式的值
    int e1, e2; // add 或 mult 表达式的两个表达式 e1 和 e2 的数值

    Expr(ExprStatus s)
    {
        status = s;
    }  
};

int calculateToken(unordered_map<string, vector<int>>& scope, const string& token)
{
    if(islower(token[0]))
    {
        return scope[token].back();
    }
    else
    {
        return stoi(token);
    }
}

int Leetcode701_800::Soltuion::evaluate(string expression)
{
    // scope
    unordered_map<string, vector<int>> scope;

    vector<vector<string>> vars;
    int start = 0, n = expression.size();
    stack<Expr> stk;
    Expr cur(VALUE);
    while(start < n)
    {
        if(expression[start] == ' ')
        {
            // 跳过空格
            ++start;
            continue;
        }
        if(expression[start] == '(')
        {
            // 去掉左括号
            ++start;
            stk.push(cur);
            cur = Expr(NONE);
            continue;
        }
        string token;
        if(expression[start] == ')')
        {
            // 去掉右括号
            ++start;
            if(cur.status == LET2)
            {
                token = to_string(cur.value);
                for(auto var : vars.back())
                {
                    scope[var].pop_back();
                }
                vars.pop_back();
            }
            else if(cur.status == ADD2)
            {
                token = to_string(cur.e1 + cur.e2);
            }
            else
            {
                token = to_string(cur.e1 * cur.e2);
            }
            // 获取上层状态
            cur = stk.top();
            stk.pop();
        }
        else 
        {
            while(start < n && expression[start] != ' ' && expression[start] != ')')
            {
                token.push_back(expression[start]);
                ++start;
            }
        }
        switch(cur.status)
        {
            case VALUE:
                cur.value = stoi(token);
                cur.status = DONE;
                break;
            case NONE:
                if(token == "let")
                {
                    cur.status = LET;
                    vars.emplace_back();
                }
                else if(token == "add")
                {
                    cur.status = ADD;
                }
                else if(token == "mult")
                {
                    cur.status = MULT;
                }
                break;
            case LET:
                // let 表达式的最后一个 expr 表达式
                if(expression[start] == ')')    
                {
                    cur.value = calculateToken(scope, token);
                    cur.status = LET2;
                }
                else 
                {
                    cur.var = token;
                    vars.back().push_back(token);
                    cur.status = LET1;
                }
                break;
            case LET1:
                scope[cur.var].push_back(calculateToken(scope, token));
                cur.status = LET;
                break;
            case ADD:
                cur.e1 = calculateToken(scope, token);
                cur.status = ADD1;
                break;
            case ADD1:
                cur.e2 = calculateToken(scope, token);
                cur.status = ADD2;
                break;
            case MULT:
                cur.e1 = calculateToken(scope, token);
                cur.status = MULT1;
                break;
            case MULT1:
                cur.e2 = calculateToken(scope, token);
                cur.status = MULT2;
                break;
        }
    }
    return cur.value;
}


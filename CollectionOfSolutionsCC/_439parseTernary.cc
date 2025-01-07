#include "Solution.h"

string Leetcode401_500::Soltuion::parseTernary(string expression)
{
    // 编译器问题，可以用递归的方式来解决
    // 先从最简单的角度入手考虑问题
    // 定义一个基本的递归回调函数
    // 这个函数用于解析 expression 下标 i 开始的子部分，直到这个子部分结束为止
    // 返回的是解析的结果
    int n = expression.size();
    function<string(int&)> subParse = [&](int& i) -> string
    {
        // 首先是取出 expression[i] 处的字符，这个字符要么是 'F'，要么是 'T'，要么是一个正常数字字符
        // 我们根据它的类型决定下一步做什么
        char res = expression[i];
        // 根据 res 后面紧随的字符是什么来决定下一步要做什么
        // 1. res 就是最后一个字符，或者后面跟着一个冒号 ':'
        // 此时我们可以直接返回 res 的字符串形式最为结果
        if(i == n-1 || expression[i+1] == ':')
        {
            // 别忘了把 i 放到正确的位置上
            ++i;
            string ret;
            ret.push_back(res);
            return ret;
        }
        // 2. res 后面跟着一个问号 '?'
        // 那么这个字符一定是一个 'T' 字符或者一个 'F' 字符
        // 我们直接跳过这个问号，检查后面的两个子表达式即可
        i += 2;
        string resLeft = subParse(i);
        // parse 结束后，i 应该指向的是两部分之间的冒号 ":"
        // 那么此时我们跳过这个冒号，继续解析右半部分即可
        ++i;
        string resRight = subParse(i);
        // 根据 res 类型决定保留哪一部分
        if(res == 'T')
        {
            // T - 返回左半结果
            return resLeft;
        }
        // F - 返回右半结果
        return resRight;
    };
    // 从头开始解析即可
    int i = 0;
    return subParse(i);
}
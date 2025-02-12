#include "Solution.h"

string Leetcode501_600::Soltuion::fractionAddition(string expression)
{
    // 没有太多的技巧可言，我们按照题目的要求来做就行了
    // 题目要求我们把整个分数算式进行计算，算出最后的结果，之后对结果进行化简，但是要保留分数形式
    // 一般性的思路是模拟：
    // 思考：
    // x1/y1 + x2/y2 
    // = 
    // x1*y2+x2*y1/(y1*y2)
    // 那么我们就可以按照这个逻辑迭代地计算整个分式表达式
    // 保存一对现有的 x/y 结果对
    // 然后每次取出一对 x1 和 y1
    // 按照上面的逻辑对这个过程进行二元求和
    // 最后再使用 gcd 函数求出 x 和 y 的最大公约数，把二者同时除以这个公约数即可得到最终答案
    // 具体的溢出问题要考虑起来就有些麻烦了。。。
    // 下面的代码实际上是官方的 (自己实在想不出来有太好的避免溢出的方法，最好也只能是每一轮二元求和后进行一次 gcd 约分了。。。)
    // 这里做一下正式的 reference，感谢官方 https://leetcode.cn/problems/fraction-addition-and-subtraction/solutions/1699131/fen-shu-jia-jian-yun-suan-by-leetcode-so-2mto/ 的题解～
    long long x = 0, y = 1;
    int index = 0, n = expression.size();
    while(index < n)
    {
        // 读取分子
        long long x1 = 0, sign = 1;
        if(expression[index] == '-' || expression[index] == '+')
        {
            sign = expression[index] == '-' ? -1 : 1;
            index++;
        }
        while(index < n && isdigit(expression[index]))
        {
            x1 = x1*10+(expression[index]-'0');
            index++;
        }
        x1 = sign*x1;
        index++;
        // 读取分母
        long long y1 = 0;
        while(index < n && isdigit(expression[index]))
        {
            y1 = y1*10+(expression[index]-'0');
            index++;
        }
        x = x*y1+x1*y;
        y *= y1;
    }
    if(x == 0)
    {
        return "0/1";
    }
    // 获取最大公约数
    long long g = gcd(abs(x), y);
    return to_string(x/g)+"/"+to_string(y/g);
}
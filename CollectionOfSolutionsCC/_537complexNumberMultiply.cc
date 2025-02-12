#include "Solution.h"

string Leetcode501_600::Soltuion::complexNumberMultiply(string num1, string num2)
{
    // 简单的模拟题，我们模拟多项式乘法即可
    // 我们对两个字符串进行解析，提取出四个数字部分
    // 分别存储为：实部1，实部2，虚部1，虚部2 四个部分
    // 之后按照正常的多项式乘法原理进行计算即可
    int act1 = 0, act2 = 0, vir1 = 0, vir2 = 0;
    // 首先解析第一个字符串
    int m = num1.size(), n = num2.size();
    // 进行封装，具体原因见后文
    function<void(const string&, const int&, int&, int&)> analyze = [&](const string& num, const int& len, int& act, int& vir)
    {
        int sign = 1, i = 0;
        // 判断 num1[0] 是否是符号，如果是，需要记录符号位
        if(!isalnum(num[0]))
        {   
            // 如果是负号，那么我们修改符号位
            sign = num[0] == '-' ? -1 : 1;
            // 修改初始下标
            i = 1;
        }
        for(; i < len; ++i)
        {
            // 取出第一个数字部分
            if(isdigit(num[i]))
            {
                act = act*10+(num[i]-'0');
            }
            else
            {
                // 否则，结束了第一个数字的解析，我们退出循环
                break;
            }
        }
        act = act*sign;
        // 这时，i 应该指向第一个加号的位置，我们后移一位，就指向了虚部的第一个下标
        ++i;
        // 重置 sign 值，防止上一次计算的结果影响当前结果
        sign = 1;
        // 注意，虚部也可能是负数，我们需要检查符号
        if(!isalnum(num[i]))
        {
            sign = num[i] == '-' ? -1 : 1;
            ++i;
        }
        for(; i < len; ++i)
        {
            // 遇到了 'i' 符号，说明虚部解析结束
            if(!isdigit(num[i]))
            {
                break;
            }
            vir = vir*10+(num[i]-'0');
        }
        vir = vir*sign;
    };
    // 用同样的方法，可以以同样的方法解析出 act2 和 vir2 值
    // 我们可以把上面的代码进行封装，方便调用
    // 封装完成，调用函数即可
    analyze(num1, m, act1, vir1);
    analyze(num2, n, act2, vir2);
    // 解析完成后，我们利用取出来的数据进行多项式乘法
    // act 存储结果的实部，vir 存储结果的虚部
    // cout << act1 << ", " << act2 << ", " << vir1 << ", " << vir2 << endl;
    int act = act1*act2-vir1*vir2, vir = act1*vir2+act2*vir1;
    return to_string(act)+"+"+to_string(vir)+"i";
}
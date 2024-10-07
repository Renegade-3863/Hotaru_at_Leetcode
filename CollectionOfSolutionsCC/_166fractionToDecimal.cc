#include "Solution.h"

// 纯粹自己 yy 出来的屎山代码，虽然能成功通过，不过也几乎不可能在面试的时候写出来，不过我这种写法相当于同时实现了
// 大数乘法，大数除法，大数减法三个函数，以及一个简单的字符串形式的数值比较，也算是多练了几个小题吧，不亏
// 实际面试的时候告诉你了是32位可存储的数字，就别像我这样 yy 大数拓展了，正常按32位整数写吧。。。 
string Leetcode101_200::Solution::fractionToDecimal(int numerator, int denominator)
{
    if(numerator == 0)
    {
        return "0";
    }
    // 题目要求我们以字符串的形式来返回一个分数的实数化结果
    // 如果不考虑无限小数这种情况，本题可以用模拟的方式简单地求解
    // 不过由于可能会出现 1/3 这种实际等于 0.(3) 的值，我们需要一种极致机制来检测可能出现的无限循环体
    // 直接存储一个字符串(重复体)可能比较困难，我们可以考虑除法得出的余数，如果我们在做除法的时候，某一次出现了以前出现过的余数，那么显然就可以知道我们已经找到了一个循环体了
    // 接下来剩下的问题就只有；如何确认这个循环体了，即：如何明确从哪到哪是循环体
    // 这也可以通过哈希表来实现，我们通过记录某个余数在得出的答案串中第一次出现的位置，记录这个位置上的商，那么截取一二次出现这个余数之间的部分就是我们的循环体
    unordered_map<string, int> memo;
    // 分解整个问题为：
    // 1. 求解商的整数部分
    // 为了使整个解决方案的可拓展性更高，我们考虑把两个整型数据转储为字符串类型
    string num = "", den = "";
    int sign1 = numerator >= 0 ? 1 : -1, sign2 = denominator >= 0 ? 1 : -1;
    numerator = abs(numerator);
    denominator = abs(denominator);
    while(numerator) 
    {
        num += (char)(numerator % 10 + '0');
        numerator /= 10;
    }
    // 翻转后就是原始的数据(去除了符号，不过已经记录在了 sign1 和 sign2 中，最后再填上即可)
    reverse(num.begin(), num.end());
    while(denominator)
    {
        den += (char)(denominator % 10 + '0');
        denominator /= 10;
    }
    reverse(den.begin(), den.end());
    // 现在我们有了除数与被除数的字符串表达形式
    // 接下来考虑进行除法运算
    // 我们显然需要两个函数
    // 1. 比较两个字符串形式的数据的大小关系的函数
    // 2. 对两个整数形式的数字进行除法运算的函数
    // 先实现第一个：
    // 返回值：1 -> num1 > num2
    //        -1 -> num1 < num2
    //        0 -> num1 == num2
    function<int(string&, string&)> cmp = [&](string& num1, string& num2) -> int
    {
        // 先去除两个数字的前导零
        while(num1[0] == '0' && num1 != "0")
        {
            num1 = num1.substr(1);
        }
        while(num2[0] == '0' && num2 != "0")
        {
            num2 = num2.substr(1);
        }
        int m = num1.size(), n = num2.size();
        // 首先判断二者的位数
        if(m != n)
        {
            return m > n ? 1 : -1;
        }
        // 只有在位数相同的情况下，我们才对二者进行逐位的比较
        for(int i = 0; i < m; ++i)
        {
            if(num1[i] > num2[i])
            {
                return 1;
            }
            else if(num1[i] < num2[i])
            {
                return -1;
            }
            // 否则，当前位数值相等，我们只需要继续比较
        }        
        // 如果循环体内没有返回值，两个数就是相等的
        return 0;
    };
    // 补充，乘法函数
    // 返回值为 mult1 * mult2 的结果
    // 这里我们的假设是：mult1 和 mult2 都一定是正数
    function<string(const string&, const string&)> mult = [&](const string& mult1, const string& mult2)
    {   
        int m = mult1.size(), n = mult2.size();
        // 回忆：m 位的整数乘以 n 位的整数的结果是一个至多 m+n 位的整数
        // 这个整数数组记录乘法过程中的所有量，因为两个一位整数相乘的结果至多是个两位数，所以这里我们可以使用整数来存
        vector<int> res(m+n, 0);
        // 使用一个二维循环遍历两个字符串的各个位
        // 注意位之间的映射关系
        // 从个位开始乘
        for(int i = m-1; i >= 0; --i)
        {
            for(int j = n-1; j >= 0; --j)
            {
                res[i+j+1] += (mult1[i]-'0')*(mult2[j]-'0');
            }
        }
        // 第二轮遍历，把这些位上的元素逐个求和，过程中进位
        string ans = "";
        for(int i = m+n-1; i >= 0; --i)
        {
            // 从高到低，依次检查结果，并填充到 ans 答案中
            char cur = (char)(res[i]%10+'0');
            // 补充下一位的进位
            if(i > 0)
            {
                res[i-1] += res[i]/10;
            }
            ans += cur;
        }
        // 翻转整个字符串，就是结果
        reverse(ans.begin(), ans.end());
        // 注意：如果最高位没有值，我们需要把它剔掉
        if(ans[0] == '0')
        {
            ans = ans.substr(1);
        }
        return ans;
    };
    // 补充：减法函数
    function<string(const string&, const string&)> subtraction = [&](const string& num1, const string& num2) -> string
    {
        // 可以使用乘法类似的方案，存一个数组
        int m = num1.size(), n = num2.size();
        // 注意，我们这个减法函数只需要适应 num1 > num2 的情况即可
        // 因而有 n <= m
        vector<int> res(m, 0);
        // 依旧是反向遍历
        for(int i = m-1; i >= 0; --i)
        {
            // 注意到 num2 对应位置的映射
            if(n-m+i >= 0 && num1[i] >= num2[n-m+i])
            {
                res[i] = (num1[i]-num2[n-m+i]);
            }
            else if(n-m+i < 0)
            {
                res[i] = (num1[i]-'0');
            }
            // (n-m+i) >= 0 && num1[i] < num2[n-m+i]，要借位
            else
            {
                res[i] = 20+(num1[i]-num2[n-m+i]);
            }
        }
        // 依旧是反向遍历执行借位
        // 过程中转换成字符串输出
        string ans = "";
        for(int i = m-1; i >= 0; --i)
        {
            char cur = res[i] >= 0 ? (res[i]%10+'0') : '9';
            ans += cur;
            if(i > 0)
            {
                res[i-1] -= res[i] >= 0 ? res[i]/10 : 1;
            }
        }
        // 反转过来
        reverse(ans.begin(), ans.end());
        // 去掉前导零
        while(ans[0] == '0' && ans != "0")
        {
            ans = ans.substr(1);
        }
        return ans;
    };
    // 再实现第二个
    // 返回值：一个整数字符，代表这两个字符串形式数据的商(不包含余数)
    // 我们这个函数假定传入的两个整数只会是正数，而且二者的位数至多只会相差一位
    // 注意到这种元除法的返回值一定是一个 1-9 之间的值，因为是用于我们大除法中的子方法，返回的是当前位上的结果
    // 所以我们实际上可以采用一种类似二分的方案来计算出这个商
    // 同时本函数会把求商后剩下的余数记录到 remainder 变量中
    // 要记录这个余数，我们还需要一个大数减法的函数，在上面写一下
    function<char(string&, string&, string&)> quotient = [&](string& num1, string& num2, string& remainder) -> char
    {
        // 设定二分的左右边界
        int left = 1, right = 9, res = -1;
        while(right >= left)
        {
            // 可以想见的方案是：
            // 枚举中点，如果中点值 * 除数 >= 被除数，那么不记录这个中点值，right = mid-1
            // 如果中点值 * 除数 < 被除数，那么我们记录这个中点值， left = mid+1
            // 最后返回记录 res 即可
            // 那么我们显然还需要一个计算中点值 * 除数的方法
            // 在外面写一下
            // 这里做一个调用
            int mid = ((right-left)>>1)+left;
            string tmp = "";
            tmp += (char)(mid+'0');
            string inter = mult(num2, tmp);
            // inter 是计算出来的中间值 * 除数
            if(cmp(inter, num1) > 0)
            {
                right = mid-1;
            }
            else
            {
                res = mid;
                remainder = subtraction(num1, inter);
                left = mid+1;
            }
        }
        // 这里可以直接返回字符形式的 res
        return (char)(res+'0');
    };
    // 做好了准备工作，我们可以真正开始计算上面的数据了
    // 第一步：计算商的整数部分，这部分不可能出现循环
    // 基本的思路是：固定除数，逐步扩大被除数
    // 最后要返回的结果
    string ret = "";
    // 记录动态的被除数部分
    string subNum = "";
    // 记录被除数的长度，用于遍历
    int len = num.size();
    for(int i = 0; i < len; ++i)
    {
        subNum += num[i];
        // 只要遇到了一个子串是大于除数的，就除一次
        if(cmp(subNum, den) >= 0)
        {
            string remainder = "";
            ret += quotient(subNum, den, remainder);
            // 把 subNum 重置到 remainder 处
            subNum = remainder;
        }
        // 否则，这个位填充一个0
        else
        {
            ret += "0";
        }
    }
    // 去掉 ret 的前导零
    while(ret[0] == '0' && ret != "0")
    {
        ret = ret.substr(1);
    }
    if(sign1 != sign2)
    {
        ret = "-" + ret;
    }
    // 如果可以整除，那么我们直接返回结果即可
    if(subNum == "0")
    {
        return ret;
    }
    // 结束后，整数部分就计算完了，可以添加一个小数点
    // 注意：如果整数部分为0，那么此时的 ret 可能是一串零，我们要去掉前导零
    while(ret[0] == '0' && ret != "0")
    {
        ret = ret.substr(1);
    }
    ret += '.';
    // 接下来计算小数部分
    // 回忆：此时我们需要记录余数的出现下标
    // 上面的循环结束后，我们可以保证 subNum 中存储的就是整数部分除完剩下的余数
    // 那么我们通过不断补零来继续和上面类似的循环过程
    while(subNum != "0")
    {
        memo[subNum] = ret.size();
        subNum += '0';
        if(cmp(subNum, den) > 0)
        {
            string remainder = "";
            ret += quotient(subNum, den, remainder);
            subNum = remainder;
            if(memo.find(subNum) != memo.end())
            {
                // 找到了循环体，检出并退出循环即可
                string loopBody = ret.substr(memo[subNum]);
                ret = ret.substr(0, memo[subNum])+ "(";
                ret += loopBody;
                ret += ')';
                return ret;
            }
        }
        // 不够依然是添0
        else
        {
            ret += '0';
        }
    }
    return ret;
}
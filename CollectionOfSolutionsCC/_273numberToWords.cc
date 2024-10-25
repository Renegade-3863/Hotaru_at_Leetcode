#include "Solution.h"

string Leetcode201_300::Solution::numberToWords(int num)
{
    if(num == 0)
    {
        return "Zero";
    }
    // 一道比较明显的哈希表模拟题，感觉意义不是很大的题目
    // 用一个哈希表存储所有基本数组元到字符串元到转换映射
    unordered_map<int, string> mapping = {
        {0, "Zero"}, {1, "One"}, {2, "Two"}, {3, "Three"}, {4, "Four"}, {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"}, {9, "Nine"},
        {10, "Ten"}, {11, "Eleven"}, {12, "Twelve"}, {13, "Thirteen"}, {14, "Fourteen"}, {15, "Fifteen"}, {16, "Sixteen"}, {17, "Seventeen"}, {18, "Eighteen"}, {19, "Nineteen"}, {20, "Twenty"}, {30, "Thirty"}, {40, "Forty"}, {50, "Fifty"}, {60, "Sixty"}, {70, "Seventy"}, {80, "Eighty"}, {90, "Ninety"},
        {100, "Hundred"},
        {1000, "Thousand"},
        {1000000, "Million"},
        {1000000000, "Billion"}
    };
    // 有了上面的映射关系，我们就可以对原数从高位到低位逐个进行数值提取和字符串拼接了
    int digits = 1, cnt = 1;
    while(1)
    {
        if(digits >= INT_MAX / 10 || digits*10 > num)
        {
            break;
        }
        digits *= 10;
        ++cnt;
    }
    // 循环结束后，digits 取到了和 num 同样数位的 10 的幂
    // 我们只需要从高位到低位一位一位地取数进行组合即可
    int digit = 0;
    string subStr = "";
    string res = "";
    while(num || digit)
    {
        // 取出当前最高位的数字
        digit = digit*10+num/digits;
        // cout << cnt << endl;
        // 根据最高位数字决定填入什么数字
        // 注意，英文数字是每三位为一组取出组合单位的，所以这里需要进行一些相对应的处理
        // 我们可以利用一个记录变量，记录当前剩余的数字位数，如果剩余数字位数达到了三的某个位数，那么我们需要对取出的 digit 进行一轮字符串插入
        --cnt;
        num %= digits;
        digits /= 10;
        if(digit == 0)
        {
            continue;
        }
        // 根据 cnt 现在的值决定当前要做什么
        // 已经取完了，就直接把 digit 接上就行了，不用加后缀
        if(cnt == 0)
        {
            if(digit / 100)
            {
                subStr += mapping[digit/100];
                digit %= 100;
                // 检查是不是最后一个子串
                subStr += " Hundred";
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit / 10)
            {
                if(digit < 20)
                {
                    subStr += mapping[digit];
                    res += subStr;
                    digit = 0;
                    subStr = "";
                    continue;
                }
                subStr += mapping[digit/10*10];
                digit %= 10;
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit)
            {
                subStr += mapping[digit];
                digit %= 1;
            }
            res += subStr;
            // 重置
            digit = 0;
            subStr = "";
        }
        // 如果剩下的位数拆成3个一组的 offset 是0，说明剩下3的倍数个三位数，我们应该组合一个 Billion 进来
        else if(cnt % 3 == 0 && cnt / 3 % 3 == 0)
        {
            // subStr 添加取出的 digit
            // 取三次，分别代表百位数，十位数，和个位数
            if(digit / 100)
            {
                subStr += mapping[digit/100];
                digit %= 100;
                subStr += " Hundred";
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit / 10)
            {
                if(digit < 20)
                {
                    subStr += mapping[digit];
                    res += subStr;
                    res += " Billion";
                    if(num)
                    {
                        res += " ";
                    }
                    digit = 0;
                    subStr = "";
                    continue;
                }
                subStr += mapping[digit/10*10];
                digit %= 10;
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit)
            {
                subStr += mapping[digit];
                digit %= 1;
            }
            res += subStr;
            res += " Billion";
            if(num)
            {
                res += " ";
            }
            // 重置
            digit = 0;
            subStr = "";
        }
        // 剩下的三个一组的元素个数对3取余是1，说明此时我们应该添加一个 "Million"
        else if(cnt % 3 == 0 && cnt / 3 % 3 == 2)
        {
            // 内部处理是一样的，还是把 digit 转换成对应的英文表达
            if(digit / 100)
            {
                subStr += mapping[digit/100];
                digit %= 100;
                subStr += " Hundred";
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit / 10)
            {
                if(digit < 20)
                {
                    subStr += mapping[digit];
                    res += subStr;
                    res += " Million";
                    if(num)
                    {
                        res += " ";
                    }
                    digit = 0;
                    subStr = "";
                    continue;
                }
                subStr += mapping[digit/10*10];
                digit %= 10;
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit)
            {
                subStr += mapping[digit];
                digit %= 1;
            }
            res += subStr;
            res += " Million";
            if(num)
            {
                res += " ";
            }
            // 重置
            digit = 0;
            subStr = "";
        }
        else if(cnt % 3 == 0 && cnt / 3 % 3 == 1)
        {
             // 内部处理是一样的，还是把 digit 转换成对应的英文表达
            if(digit / 100)
            {
                subStr += mapping[digit/100];
                digit %= 100;
                subStr += " Hundred";
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit / 10)
            {
                if(digit < 20)
                {
                    subStr += mapping[digit];
                    res += subStr;
                    res += " Thousand";
                    if(num)
                    {
                        res += " ";
                    }
                    digit = 0;
                    subStr = "";
                    continue;
                }
                subStr += mapping[digit/10*10];
                digit %= 10;
                if(digit)
                {
                    subStr += " ";
                }
            }
            if(digit)
            {
                subStr += mapping[digit];
                digit %= 1;
            }
            res += subStr;
            res += " Thousand";
            if(num)
            {
                res += " ";
            }
            // 重置
            digit = 0;
            subStr = "";
        }
    }
    // 处理完成，返回结果即可
    return res;
}

// 细节问题很多，总结一下：
// 1. 考虑空格的添加
// 两种情况
//   1.1 digit 的子串和后缀之间的空格
//   1.2 digit 的子串之间的空格
//   1.3 后缀和 digit 的子串之间的空格
//  对于 1.1，这种空格可以不用任何条件判断，因为它是必须被添加的
//  对于 1.2，这种空格只有在 digit 剩余值不为0的时候才会需要添加一个空格
//  对于 1.3，这种空格只有在 num 剩余值不为0的之后才会需要添加一个空格
// 2. 添数循环的结束条件
// 我们不应该仅当 num 非零的时候才继续循环
// 这可能会导致一些问题
// 因为我们记录的 cnt 是数的剩余位数
// 这个位数并不等效于 num == 0 
// 考虑这个例子：
// num = 20, cnt = 2
// 移除一位后，num = 0, cnt = 1
// 此时 num 已经等于0了，按理说我们已经退出循环了
// 但是，由于添加元素是在循环体内部进行的，此时我们的 digit 还有元素，那么就会丢失数据！
// 所以，退出循环的条件用 cnt == 0 是最合适的
#include "Solution.h"

vector<string> Leetcode701_800::Soltuion::removeComments(vector<string>& source)
{
    // 字符串模拟问题
    // 我们可以按下面的逻辑对 source 中的每一个元素进行解析
    // 状态机：
    /*
        sta0：空状态，这一状态为一般状态，也就是说接下来只要不遇到 // 或者 /*，我们就把对应的字符保留，当作代码部分
        sta1：行注释状态，这一状态下我们把当前的字符存储存储到 "记录字符串" 中
        sta2：块注释状态，这一状态下我们也默认当前的字符会被存储到 "记录字符串" 中
        sta0 可以转换到 sta1 或者 sta2
        sta1 和 sta2 可以转换到 sta0，但是 sta1 和 sta2 之间不能相互转化
    */
    // 一个细节处理问题在于：sta0 状态和 sta1 状态的转化 trigger 以及 sta0 状态到 sta2 状态还有 sta2 状态到 sta0 状态的转化 trigger 都不是一个单个的字符判断
    // 题目的两个要求我们需要考虑一下：
    /*
        1. 如果 "//" 出现在块注释中会被忽略
        2. 如果字符串 "/*" 出现在行或块注释中也会被忽略
    */ 
    // 最后备注：有同学可能会觉得这道题可以用 KMP
    // 个人认为这道题不适合用 KMP 的原因在于：
    // "/*/" 这种，如果你用 KMP，他会被同时判定为 "/*" 和 "*/"，处理起来很麻烦
    // 所以我们还是采用 "遇到 trigger，就往后多检查一个字符" 的方法来进行模拟
    // 下面封装一个 check 函数，用于检查 idx 下标处是否有一个 "//" 或者 "/*" 或者 "*/" 标签
    // 返回值为具体的标签，如果不存在，那么返回值为空字符串
    function<string(const string&, int)> check = [&](const string& str, int idx) -> string
    {
        string ret;
        // 结束字符，那么直接返回空字符串即可
        if(idx == str.size()-1)
        {
            return "";
        }
        // 否则，我们可以检查 str.substr(idx, 2) 这个字符串，如果它是 "//"，"/*" 或者 "*/"，那么返回它，否则返回空字符串即可
        ret = str.substr(idx, 2);
        if(ret == "//" || ret == "/*" || ret == "*/")
        {
            return ret;
        }
        // 否则，这不是一个标记字符串，我们返回空字符串即可
        return "";
    };
    // mark 字符串记录可能的转换标记
    string mark = "";
    // 定义一个处理字符的函数，根据当前的 status 来决定当前的字符要怎么进行处理
    function<void(const string&, string&, int&, int&)> dealWith = [&](const string& str, string& board, int& idx, int& status) -> void
    {
        // cout << idx << ": " << status << ", " << str << endl;
        // 如果 str[i] 是一个 '/'，或者是一个 '*'，那么我们考虑调用 check 函数检查这是不是一个状态转换字符串
        // 注意：题目要求我们在 sta1 状态下忽略 "/*" 或者 "*/"
        // 所以我们在 status == 1 的时候不进行下面的检查
        // 而 sta2 的时候，因为可能会涉及到 "*/"，所以我们依然需要进行检查
        if((str[idx] == '*' || str[idx] == '/') && status != 1)
        {
            mark = check(str, idx);
            // cout << mark << endl;
        }
        switch (status)
        {
            case 0:
                // sta0，此时检查 mark，如果 mark 是 "//"，那么 status 转换到状态 1
                if(mark == "//")
                {
                    status = 1;
                    // 之后我们什么都不用做了
                    // 注意，这里我们不能重置全局的这个 mark，因为外面需要用它来修改 idx 的值
                    // 这里我们直接 break，退出 switch 语句即可
                    // 对 idx 的修改我们在这里处理即可
                    // 只对 idx 加 1 是为了和外部的更新逻辑兼容
                    ++idx;
                    break;
                }
                // 如果 mark 是 "/*"，那么 status 转换到状态 2
                if(mark == "/*")
                {
                    status = 2;
                    ++idx;
                    break;
                }
                // 否则，当前字符可以被算作是一个最后留存的结果字符，那么我们把它正常添加到返回字符串中即可
                board.push_back(str[idx]);
                break;
            case 1:
                // sta1，此时说明我们在一个 "行注释" 中，那么无论如何，当前的字符都不能考虑了，我们直接 break 即可，这一点和题目的要求是相符的
                break;
            case 2:
                // sta2，此时说明我们在一个 "块注释" 中，那么我们需要检查 mark 是否是 "*/" 结束符，其它情况都不用做处理，正常添加即可
                if(mark == "*/")
                {
                    // 那么我们结束这个 "块注释"，修改 status，然后跳过当前字符
                    // 该会 sta0，也就是一般状态即可
                    status = 0;
                    // 对 idx 的修改我们在这里处理即可
                    // 只对 idx 加 1 是为了和外部的更新逻辑兼容
                    ++idx;
                }
                // 否则，因为这个字符在一个 "块注释" 中，所以我们不用把它添加到结果中，跳过即可
                break;
        }
        // switch 语句处理完成后，就可以返回了
    };
    // res 数组存储最后的返回结果
    vector<string> res;
    // 注意：status 不是每一行独立的，所以要把 status 定义到这一个 for 循环外面
    // 初始的默认状态信息为 0，也就是 sta0
    int status = 0;
    int memo = 0;
    for(const auto& code : source)
    {
        // 对每一行源码进行处理
        // idx 对应 "当前需要处理的字符下标"，初始为 0
        int idx = 0;
        // board 用于记录当前这一行 code 的处理结果
        string board;
        // 处理到字符串结尾时退出循环
        while(idx < code.size())
        {
            // 处理 code[idx] 这个字符，相关的底层处理写在了函数内部
            dealWith(code, board, idx, status);
            // 如果 code.substr(idx, 2) 是一个标签，那么我们在内部已经跳过了一个字符，外层再跳过一个字符，正好挪到下一个需要检查的字符下标上
            ++idx;
        }
        // 处理完毕，board 添加到 res 中即可
        if(memo == 2 && status != 2 && board.empty())
        {
            memo = 0;
        }
        // 如果 board 为空，按题意，不能添加到 res 中
        if(!board.empty())
        {
            if(memo == 2)
            {
                res.back() += board;
                memo = 0;
            }
            else
            {
                res.push_back(board);
            }
            if(status == 2)
            {
                memo = 2;
            }
        }
        // 处理完每一行后，如果 status 是 1，也就是一个行末的 "行注释"，那么我们才把 status 清零，否则保留 sta2 或 sta0 的状态信息
        if(status == 1)
        {
            status = 0;
        }
        // 别忘了清空 mark
        mark = "";
    }
    return res;
}
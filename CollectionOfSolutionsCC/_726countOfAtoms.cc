#include "Solution.h"

string Leetcode701_800::Soltuion::countOfAtoms(string formula)
{
    // 依然是模拟题，我们用一个哈希表记录每种原子的个数，之后遍历整个化学式即可
    // 注意对原子类型的解析和数字的解析要分开进行
    // 封装两个分析函数，一个用于分析原子类型，另一个用于分析数字
    // 初始化一个有序表，用于记录每种原子出现的总个数，之所以用有序表，是因为题目要求返回值按原子名称字典序排列
    map<string, int> cnts;
    // 解析原子类型的函数，返回值为原子名称
    // 当遍历到一个字母的时候触发这个函数
    // 我们直接把 idx 的更新操作也封装到这个函数里了
    function<string(const string&, int&)> extractAtom = [&](const string& f, int& idx) -> string
    {   
        // 记录化学式的首字母
        string ret;
        ret += f[idx++];
        int n = f.size();
        while(idx < n && islower(f[idx]))
        {
            // 同步更新 ret 和 idx
            ret += f[idx++];
        }
        // 更新完成，现在 ret 代表分析出来的原子名称，idx 指向的是代表它个数的数字的第一位
        return ret;
    };
    // 解析出现次数的函数，返回值为某个原子的出现次数，当遇到一个数字时触发这个函数  
    function<int(const string&, int&)> extractCnt = [&](const string& f, int& idx) -> int
    {
        int n = f.size();
        if(idx == n || !isdigit(f[idx]))
        {
            return 1;
        }
        int ret = 0;
        // 如果你能给我整出来一个原子个数大于 INT_MAX，我也算你厉害。。。
        while(idx < n && isdigit(f[idx]))
        {
            // 这里就不避免溢出了（）
            ret = ret*10+f[idx]-'0';
            ++idx;
        }
        // 分析完成，返回即可
        return ret;
    };
    // 之后是解析的方法函数，因为题目有可能会出现嵌套的化学式，所以我们需要一个可以被递归调用的函数来处理
    // 分析一下这种递归形式，我们会发现，实际上，化学式加上括号，就是对某个已有部分进行倍增
    // 定义递归函数：
    // 这个函数用于对 formula 化学式进行解析，返回的每种原子个数保存在 memo 中返回
    int idx = 0, len = formula.size();
    map<string, int> res;
    function<void(map<string, int>&)> analyze = [&](map<string, int>& memo) -> void
    {
        // 我们归纳一下整体的处理逻辑：
        // 统一化处理：
        // 我们假定一个单一的元素名也是一个化学式 (虽然这种假设很显然)
        // 之后我们对它进行解析，解析结果存储到一个临时的哈希结构中返回给调用者
        // 返回之后，如果后面跟着一个新的数字，那么我们就对这个刚刚解析出来的化学式进行对应次数的倍增
        // 每执行完一轮上面的处理，我们就把对应哈希结构中的数据累加到最后的结果中
        // 在对 board 进行检查时，我们可能会遇到下面几种情况
        while(idx < len)
        {
            // 1. 遇到了一个正常字符
            // 那么我们可以考虑，调用 extractAtom 来解析出原子类型字符串
            char c = formula[idx];
            if(isalpha(c))
            {
                string atom = extractAtom(formula, idx);
                // cout << idx << endl;
                int num = extractCnt(formula, idx);
                // cout << atom << " cnts for " << num << "times\n"; 
                // 分离出一组原子和个数后，我们就可以把数据添加到 memo 中了
                memo[atom] += num;
            }
            // 2. 遇到了一个左括号
            // 那么说明这是一个新的子化学式的开头，我们可以新建一个 map 表，并递归调用 analyze 函数来处理这个子表达式
            else if(c == '(')
            {
                ++idx;
                map<string, int> subMemo;
                int subCnt = 0;
                analyze(subMemo);
                // cout << " After the column, goes to " << idx << endl;
                subCnt = extractCnt(formula, idx);
                // 解析完成后，当前括号对内的原子个数就记录在了 newMemo 表中
                // 我们根据 subMemo 表的数据更新 memo 即可
                for(const auto& [atom, cnt] : subMemo)
                {
                    memo[atom] += cnt*subCnt;
                }
            }
            // 3. 遇到了一个右括号
            // 那么说明这是一个子化学式的结尾，我们可以根据 subMemo 中的元素个数
            // 结合这个右括号右侧的数字，来对 memo 进行更新
            else if(c == ')')
            {
                ++idx;
                // 这里结束对子化学式的解析，返回即可
                return;
            }
            // 4. 遇到其它字符
            // 只要化学式合法，情况 4 不会出现
        }
        // 处理完成，结果就存储在了 memo 表中
    };
    // 执行处理逻辑
    analyze(res);
    // 之后分离出结果，保存到一个 string 中即可
    string ans;
    for(const auto& [atom, cnt] : res)
    {
        ans += atom;
        if(cnt > 1)
        {
            ans += to_string(cnt);
        }
    }
    return ans;
}
class Solution
{
public:
    string simplifyPath(string path)
    {
        // 简单的栈模拟类问题，要求什么做什么即可
        // 每遇到一个新的字符，执行下面的检查
        // 如果新字符是一个正常字符：
        // 那么尾接到缓存字符串中即可
        // 而如果是一个斜杠，那么检查缓存字符串：
        //      如果缓存字符串是空的，那么说明这个斜杠前面也是一个斜杠，我们可以忽略它
        //      如果缓存字符串非空，并且不是连续两个点号，也不是单个点号，那么说明这个斜杠分隔了两个目录，我们把缓存字符串压栈，并清空缓存即可
        //      如果缓存字符串非空，并且是连续的两个点号，那么说明我们会需要弹出一层上层目录
        //      如果缓存字符串非空，并且是单个点号，那么我们直接抛弃这个字符串即可
        // 循环结束后，我们还需要检查栈顶的字符串是否是 ".."，如果是，那么我们还要弹出一次上层目录
        // 不过注意：path 开头可能有复数个斜杠，它们会破坏上面的逻辑，我们可以进行预处理
        stack<string> stk;
        string cur;
        int i = 0, n = path.size();
        for(; i < n; ++i)
        {
            // 只要遇到一个非斜杠的字符，我们就直接退出循环
            if(path[i] != '/')
            {
                break;
            }
        }
        // 现在保证了 path[i] 开始一定是一个非斜杠
        for(; i < n; ++i)
        {
            if(path[i] == '/')
            {
                // 如果是一个斜杠，那么我们检查 cur 
                if(cur.empty())
                {
                    // 如果是空的，那么什么也不用做
                    continue;
                }
                else if(cur == "..")
                {
                    // 如果上一个目录是 "回退" 目录，那么我们从栈中弹出一级目录即可
                    if(!stk.empty())
                    {
                        stk.pop();
                    }
                }
                else if(cur != ".")
                {
                    // 否则，cur 代表的是一个非空的合法目录名，我们把它压入栈中即可
                    stk.push(cur);
                }
                // 上面所有情况下，cur 都需要清空，我们把它提出来
                cur = "";
            }
            else
            {
                // 否则，我们简单地把 path[i] 尾接到 cur 中即可
                cur.push_back(path[i]);
            }
        }
        if(!cur.empty())
        {
            // 注意：目录有可能不以斜杠结尾，如果是这样，我们还需要判断最后一级目录是什么
            if(cur == "..")
            {
                if(!stk.empty())
                {
                    stk.pop();
                }
            }
            else if(cur != ".")
            {
                stk.push(cur);
            }
        }
        string res;
        while(!stk.empty())
        {
            res.insert(0, stk.top());
            stk.pop();
            res = "/"+res;
        }
        return res == "" ? "/" : res;
    }
};
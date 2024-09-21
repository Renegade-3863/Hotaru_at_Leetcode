#include "Solution.h"

string Leetcode1_100::Solution::simplifyPath(string path)
{
    // 简单的栈模拟类字符串问题
    // 按照题目的要求，我们可以用栈的每一个元素记录最后输出的简化路径上的每一个构件字符串
    deque<string> stk;
    // 我们需要一套对 path 进行解析的算法
    // 基本思路应该是，遇到一个反斜杠 '/'，就相当于找到了一串有效的构件，可以根据其内容进行处理了
    // 记录"当前"构件
    string comp = "";
    int n = path.size();
    int i = 0;
    while(i < n)
    {
        // 把 comp 的重置放到每次获取它之前，进行代码简化和逻辑整理
        comp = "";
        // 使用一个 do-while 循环找出一个以反斜杠结尾的构件
        do
        {
            comp += path[i];
            // 使用 do-while 的原因在于，第一个字符一定是一个反斜杠，我们先加后递增是完全可行的
        } while(path[i++] != '/' && i < n);
        // 循环结束时，comp 中就已经记录了当前的以 '/' 结尾的一个构件
        // 如果栈为空，根据本题的题意，这时实际上 comp 一定是开头的那个反斜杠，我们之间添加就可以了
        if(stk.empty())
        {
            stk.push_back(comp);
            // 重置记录
            continue;
        }
        // 如果栈不为空并且 comp 本身就只是一个反斜杠，则当前这个构件没有任何添加的必要
        else if(comp == "/")
        {
            // 直接重置记录并跳过本轮循环即可，不递增 i 的值，在上面的 do-while 循环中我们已经做好了递增
            continue;
        }
        // 如果栈不为空并且 comp 本身有内容，则根据这个内容进行后续处理
        else
        {
            // 切片，丢掉构件结尾的反斜杠
            string cont = comp[comp.size()-1] == '/' ? comp.substr(0, comp.size()-1) : comp;
            if(cont == ".")
            {
                continue;
            }
            else if(cont == "..")
            {
                if(stk.size() <= 1)
                {
                    continue;
                }
                stk.pop_back();
            }
            else 
            {
                stk.push_back(comp);
            }
        }
    }
    // 全部循环结束后，stk 中存储的就是一个一个的以反斜杠结尾的构件，把它们连起来，再去掉结尾的反斜杠即可
    string res = "";
    while(!stk.empty())
    {
        res += stk.front();
        stk.pop_front();
    }
    // 只有这个路径不是一个单纯的根目录，并且它是以一个反斜杠结尾的时候，才把这个结尾的反斜杠丢掉
    res = res != "/" && res[res.size()-1] == '/' ? res.substr(0, res.size()-1) : res;
    return res;
}
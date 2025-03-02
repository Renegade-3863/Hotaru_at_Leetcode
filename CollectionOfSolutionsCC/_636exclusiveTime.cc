#include "Solution.h"

vector<int> Leetcode601_700::Soltuion::exclusiveTime(int n, vector<string>& logs)
{
    // 栈模拟类问题
    // 考虑如何模拟题目要求的流程
    // 本质上，我们需要对每一条信息进行解析
    // 如果当前信息代表的是一个函数的 "开始"，也就是 "start"
    // 那么我们往栈中压入一个新的 "函数" 对象
    // 如果当前信息代表的是一个函数的 "结束"，也就是 "end"
    // 那么我们同样往栈中压入一个新的 "函数" 对象
    // 不过注意，每次压入新的 "函数" 对象以及 start 值前，我们都需要先把当前栈顶的这个 "函数" 的 start 时间和要压入的这个 start 时间取差值
    // 这个差值就是之前这个函数独立执行了的时间 
    // 每次压入新的 "函数" 对象以及 end 值前，我们同样需要记录差值
    // 栈用于记录每个当前在运行中的进程 id，按加入时间从栈底到栈顶
    stack<int> stk;
    // 维护一个 cur 变量，记录 "上一次记录的时间戳"
    int cur = 0;
    // 定义为每个进程的独占总时间
    vector<int> res(n, 0);
    for(int i = 0; i < logs.size(); ++i)
    {
        // 解析当前信息条
        // 分离出两个时间和 start/end 部分
        int comma1 = logs[i].find(":", 0);
        int comma2 = logs[i].find(":", comma1+1);
        // 根据两个冒号，我们就能把 logs 整体分离成 进程 ID、开始/结束标签、以及一个时间戳
        int id = stoi(logs[i].substr(0, comma1));
        int status = (logs[i][comma1+1] == 'e');
        int timestamp = stoi(logs[i].substr(comma2+1));
        // cout << status << endl;
        if(status == 0)
        {
            // 当前是一个 start 信息
            // 那么从这个 timestamp 到上一次记录的时间 cur 为止，都是上一层函数的执行时间，累加到结果中即可
            if(!stk.empty())
            {
                res[stk.top()] += timestamp-cur;
            }
            // 把 id 压入栈中
            stk.push(id);
            cur = timestamp;
        }
        else
        {
            // 当前是一个 end 信息
            // 那么 timestamp-cur+1 就是当前函数独占的执行时间
            res[id] += timestamp-cur+1;
            // 弹出栈顶的这个 id 进程
            stk.pop();
            cur = timestamp+1;
        }
    }
    return res;
}
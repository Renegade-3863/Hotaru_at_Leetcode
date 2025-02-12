#include "Solution.h"

/* 
    简单题，简单做，按题目的要求来做就行了
    给定的 compressedString 是一个压缩的字符串
    那么我们可以设定一个指针 i
    这个指针每次都维护到一个字符的下标处
    每次调用 next 函数，都执行一轮解析
    我们分离出一个字符，和一个 "出现次数"
    之后相应地移动指针 i 即可
*/
Leetcode601_700::Soltuion::StringIterator::StringIterator(string compressedString)
{
    // 初始化 idx 和 board，把数据存储到类本地
    idx = 0;
    board = compressedString;
    // 注意，这里我们最好确保一下 idx 的定义是正确的，防止出现 compressedString 开头是个数字的情况 (虽然按这题的定义，开头不太可能是个数字。。)
    while(!isalpha(board[idx]))
    {
        // 我们跳过所有开头的字符
        ++idx;
    }
    // 现在 idx 的定义被确保了，我们可以结束构造了
}

char Leetcode601_700::Soltuion::next()
{
    // 防御性编程
    if(!hasNext())
    {
        return ' ';
    }
    // 这个函数，我们只需要解析出 board 中的一个字符以及对应出现的次数即可
    // 划定字符原本出现的下标
    int tmp = idx;
    char c = board[idx++];
    // 解析出 c 出现的次数
    int cnt = 0;
    // 第一个条件防止越界访问
    while(idx < board.size() && !isalpha(board[idx]))
    {
        cnt = cnt*10+(board[idx++]-'0');
    }
    // 把 cnt 减 1，检查是否为零，如果是，那么不用做其它修改，直接结束即可
    // 如果 cnt 非零，那么我们需要把 cnt 的新值转换成字符串，填回原本这个字符串所在的位置上
    // 同时 idx 修改回 tmp
    if(--cnt)
    {
        // cnt 非零，那么我们需要对 board 进行修改
        board = board.substr(0, tmp+1)+to_string(cnt)+board.substr(idx);
        idx = tmp;
    }
    // 循环结束时，idx 停在了下一个字符的下标处，或者停在的 '\0' 处
    return c;
}

bool Leetcode601_700::Soltuion::hasNext()
{
    // 简单来说，我们只需要检查 idx 是否小于 board.size()
    return idx < board.size();
}
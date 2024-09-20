#include "Solution.h"

vector<string> fullJustify(vector<string>& words, int maxWidth)
{
    // 还是那句话，模拟题考察的不是算法能力，是逻辑的清晰度，感觉没有什么练习捷径，只有慢慢摸索，关注细节
    // 本题要求我们贪心地向每一行中放置尽可能多的单词
    int startWord = 0, endWord = 0, n = words.size();
    // 按顺序检查所有的单词
    // 用一个变量记录当前行剩余的空位
    int remaining = maxWidth;
    // 初始化一个只有一个字符串，长度为 maxWidth 的字符串数组
    vector<string> res(1, string(maxWidth, ' '));
    // 用一个下标数组记录所有当前行要添加的字符串的开始下标
    deque<int> pos;
    // 用一个布尔变量记录当前行是否有添加过单词
    bool added = false;
    // 记录当前行已经决定添加的单词个数
    int cnt = 0;
    // 记录行号
    int idx = 0;
    // 这个函数是后面重复代码进行行数优化用的，到这里看不懂可以先跳过
    function<void()> copyStr = [&]()
    {
        while(pos.size() > 0)
        {
            // 按字符逐个复制
            for(int i = 0; i < words[startWord].size(); ++i)
            {
                res[idx][pos[0]+i] = words[startWord][i];
            }
            ++startWord;
            pos.pop_front();
        }
    };
    // 循环的结束条件为遍历完所有的单词
    while(endWord < n)
    {
        // 针对剩余空位数量进行分类讨论
        // 注意，我们这里讨论的 remaining 变量并不包含当前最后添加的单词后面跟着的必要空格
        // 要根据当前行前面是否有添加过单词讨论如何利用 remaining
        // 如果剩下的空格数量严格大于当前单词的长度，那么一定可以添加
        // 如果剩下的空格数量等于当前单词长度，那么只有当这个单词是第一个要添加的单词时才能进行添加
        if(remaining > words[endWord].size() || (remaining == words[endWord].size() && !added))
        {
            // 记录这个单词要放入的位置
            // 注意，如果这不是第一个添加的单词，那么就要再后移一位，表示多加一个空格
            pos.push_back(maxWidth-remaining+added);
            ++cnt;
            // 更新剩余空格个数
            // -added 和上面的分析一致
            remaining -= words[endWord].size()+added;
            added = true;
            ++endWord;
        } 
        // 其它情况下，代表我们已经无法继续贪心地向当前行放入当前单词了，需要根据剩下的空格数进行前面已经添加的单词后面的空格数量进行调整
        // 调整好添加起始下标后，就可以开始进行实际的单词添加并更新有关新行的状态变量了
        // 逻辑定义：
        // remaining <= words[endWord] && (remaining != words[endWord] || added))
        else
        {
            // 这个时候，remaining 记录的是最后一个单词后面还剩下的空格数量
            // cnt 记录了当前行已经决定添加的单词个数
            // 举个例子帮助理解
            // 剩下 3 个额外空格
            // 已经添加了4个单词
            // 那么我们需要给前面4个单词每一个后面多添加一个空格，由于一共只有3个空格，所以我们只能给前3个单词添加一个空格
            // 总结下来，我们应该给先均分给前面每个单词  remaining / (cnt-1) 个空格(之所以是 cnt-1 是因为最后一个单词要进行右对齐，后面不能添加空格)
            // 但是由于可能 remaining 无法被整除
            // 所以在消去了可以整除个 offset 之后，我们还需要把剩下的部分小于 cnt-1 个空格拆成一个一个的空格，按从左到右的顺序加到最终结果中每个单词的后面
            int offset = cnt > 1 ? remaining/(cnt-1) : 0;
            remaining -= offset*(cnt-1);
            // 遍历我们添加的每一个单词的起始位置，进行向后偏移
            // 这里 cnt == 1 的情况被我们用循环条件规避掉了，实际上只有一个单词的情况也的确不需要任何下标位置的调整
            for(int i = 1; i < cnt; ++i)
            {
                // 这一步是简单的递推，由于直接计算当前位置的偏移比较困难，所以根据前一个单词的起始位置进行新位置的计算比较稳妥
                pos[i] = pos[i-1]+words[startWord+i-1].size()+offset+(remaining > 0 ? 1 : 0)+1;
                // 注：这里也可以严谨一些，如果 remaining == 0 了就不再递减，不过再进行条件判断纯属多余，这里就没再做
                remaining -= 1;
            }
            // 偏移结束后就可以实际进行添加了
            copyStr();
            // 注意到循环结束后 startWord 也指向了 endWord 的位置
            // 注意这里我们不更新 endWord，因为这个单词还没有被实际进行添加
            // 重置 added , remaining 和 cnt 即可
            added = false; cnt = 0; remaining = maxWidth;
            // 开启新的一行用于记录后面的单词
            res.push_back(string(maxWidth, ' '));
            ++idx;
        }
    }
    // 注意到这样一个事实，最后一个单词被 "决定添加" 之后，我们还没有实际进行添加循环就退出了，所以这里还需要对最后一行的单词进行添加
    // 题目要求最后一行左对齐
    // 因而我们只需要按原始的下标进行填入即可
    copyStr();
    return res;
}
#include "Solution.h"

// 直觉的模拟方法，但是卡在了最后一个用例上，TLE 了
int Leetcode401_500::Solution::wordsTyping(vector<string>& sentence, int rows, int cols)
{
    // 最简单直接的想法理应是模拟填入过程
    // 我们按行为基准进行遍历
    int row = 0;
    // 当 row >= rows 时，我们就填完了，可以退出并返回记录的显示次数
    // times 用于记录句子完整显示的次数
    // wordIdx 用于记录当前要填入的单词序号，如果 wordIdx == sentence.size()，那么我们需要回滚 wordIdx 到0，继续填入下一轮
    int times = 0, wordIdx = 0;
    int n = sentence.size();
    // 维护当前行最靠左的空位的下标
    int rowIdx = 0;
    while(row < rows)
    {
        if(wordIdx == n)
        {
            // 递增一次 times
            ++times;
            wordIdx = 0;
        }
        // 尝试填入 sentence[wordIdx] 处的单词
        // 检查 rowIdx 到当前行结尾是否还够填入当前的 sentence[wordIdx] 这个单词
        if(cols-rowIdx >= (int)sentence[wordIdx].size())
        {
            // 剩余空间可以填入，那么执行填入
            // 更新 rowIdx
            // 后面带上一个空格
            rowIdx += sentence[wordIdx++].size()+1;
        }
        // 否则，说明我们没法填入下一个单词，那么此时需要更新 row，并重置 rowIdx
        else
        {
            ++row;
            rowIdx = 0;
        }
    }
    return times;
}
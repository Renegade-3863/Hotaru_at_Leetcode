#include "solution.h"

vector<string> Leetcode401_500::Solution::readBinaryWatch(int turnedOn)
{
    // 简单的回溯类问题，考虑根据 turnedOn 进行打开灯的组合列举即可
    string path;
    // hr 代表的是小时，minu
    // 代表的是分钟，我们需要在枚举的过程中计算这两个值并验证有效性
    int hr, minu;
    // cnt 代表的是当前还剩下的亮灯数
    // 我们不能同时点亮一个 LED 灯两次，所以需要用一个整数记录那些点亮了的灯
    int lit = 0;
    vector<string> res;
    unordered_set<string> added;
    function<void(int)> backtrack = [&](int cnt) {
        // 一共有10种灯可以点亮，不过需要检查这些灯是否之前没有被点亮过
        // 递归的结束条件是：cnt == turnedOn
        if (cnt == turnedOn) {
            // 把 hr 和 minu 转换成字符串拼接成答案，添加到 res 中
            string hour = to_string(hr);
            string minute = minu >= 10 ? to_string(minu) : "0"+to_string(minu);
            string ans = hour + ":" + minute;
            if(added.find(ans) != added.end())
            {
                return;
            }
            res.push_back(ans);
            added.insert(ans);
            return;
        }
        // 正常情况，考虑利用位运算尝试累加数据到 hr/minu 中
        for (int i = 0; i < 10; ++i) {
            // 如果这盏灯之前已经点亮过了，我们不能再次点亮，跳过它即可
            if ((lit & (0x00000001 << i)) != 0) {
                continue;
            }
            // 这盏灯还没被点亮，我们可以进一步检查
            // 前四个，我们规定是要修改 hr，对应的是 1、2、4、8
            if (i < 4) {
                if (hr < 12 - (0x00000001 << i)) {
                    hr += (0x00000001 << i);
                    // 递归
                    // 记录这盏灯被点亮过了
                    lit = lit | (0x00000001 << i);
                    backtrack(cnt + 1);
                    // 回溯
                    lit = lit ^ (0x00000001 << i);
                    hr -= (0x00000001 << i);
                }
            }
            // 后六个，我们规定的是要修改 minu，对应的是 1、2、4、8、16、32
            else {
                if (minu < 60 - (0x00000001 << (i - 4))) {
                    minu += (0x00000001 << (i - 4));
                    // 递归
                    // 记录这盏灯被点亮过了
                    lit = lit | (0x00000001 << i);
                    backtrack(cnt + 1);
                    // 回溯
                    lit = lit ^ (0x00000001 << i);
                    minu -= (0x00000001 << (i - 4));
                }
            }
        }
    };
    backtrack(0);
    return res;
}
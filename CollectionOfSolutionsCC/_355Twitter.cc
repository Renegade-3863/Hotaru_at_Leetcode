#include "Solution.h"

Leetcode301_400::Solution::Twitter::Twitter()
{
    // 初始化时间戳
    this->timeStamp = 0;
}


void Leetcode301_400::Solution::Twitter::postTweet(int userId, int tweetId)
{
    // 发推的操作很简单，我们新建对应的推，并把这个结点连接到 twitts 表对应用户的链表上即可
    // 先更新时间戳
    ++this->timeStamp;
    // 如果这个用户还没有发过任何推，我们新建他的推链表
    if(this->twitts.find(userId) == this->twitts.end())
    {
        this->twitts[userId] = new Tweet(tweetId, this->timeStamp);
    }
    else
    {
        // 这个用户已经发过推了，我们需要把这个新推头插到他的链表上
        Tweet* head = this->twitts[userId];
        this->twitts[userId] = new Tweet(tweetId, this->timeStamp);
        // 完成头插
        this->twitts[userId]->next = head;
    }
}

vector<int> Leetcode301_400::Solution::Twitter::getNewsFeed(int userId)
{
    // 核心模块
    // 我们考虑应用 K 路归并的方法
    // 使用一个大优先队列保存这个用户关注的所有用户发布的推的链表头结点，选出至多10个返回结果即可
    priority_queue<Tweet*, vector<Tweet*>, cmp> pq;
    for(const auto& follow : this->follows[userId])
    {
        // 对于当前用户关注的每一个用户，取出他们发布的第一条推文，放到大优先队列中
        if(this->twitts.find(follow) != this->twitts.end())
        {
            pq.push(this->twitts[follow]);
        }
    }
    // 如果用户自己发过推文，别忘了把自己也算上
    if(this->twitts.find(userId) != this->twitts.end())
    {
        pq.push(this->twitts[userId]);
    }
    // 最多取十个放大答案中
    vector<int> res;
    for(int i = 0; i < 10; ++i)
    {
        if(pq.empty())
        {
            return res;
        }
        res.push_back(pq.top()->id);
        Tweet* tmp = pq.top();
        pq.pop();
        if(tmp->next)
        {
            pq.push(tmp->next);
        }
    }
    return res;
}

void Leetcode301_400::Solution::Twitter::follow(int followerId, int followeeId)
{
    this->follows[followerId].insert(followeeId);
}

void Leetcode301_400::Solution::Twitter::unfollow(int followerId, int followeeId)
{
    this->follows[followerId].erase(followeeId);
}
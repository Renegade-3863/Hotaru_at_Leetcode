#include "Solution.h"

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

Leetcode201_300::Solution::PeekingIterator::PeekingIterator(const vector<int>& nums) : Iterator(nums) {}

int Leetcode201_300::Solution::PeekingIterator::peek()
{
    return Iterator(*this).next();
}

int Leetcode201_300::Solution::PeekingIterator::next()
{
    return Iterator::next();
}

bool Leetcode201_300::Solution::PeekingIterator::hasNext()
{
    return Iterator::hasNext();
}

// 这题直接抄答案了hhh，是真没想到还能利用父类的拷贝构造函数复制一份迭代器出来返回结果。。。
// 不过学到了一种在子类中显式调用父类成员函数的方法：使用 :: 名称空间说明符
// 一定要记住。。。不会这个面试的时候可就尴尬了。。。
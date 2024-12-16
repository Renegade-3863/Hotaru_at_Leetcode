/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

#include "Solution.h"

string Leetcode401_500::Solution::Codec::serialize(Node* root)
{
    // 把一个 N 叉树序列化成字符串的方法
    // 要仔细研究的话，这道题有些类似表达式求值问题，都是类似递归的解决方案
    // 我们的基本处理原则是：对 N 叉树按层进行拆分，每一层上的结点同属同意个大括号
    // 如果当前层的某个结点有孩子，那么新开一个大括号包括这个结点所有的孩子结点信息即可
    // 明确了这一点，我们要做的事情就变得很清晰了
    // 定义一个转化的子回调函数
    // 这个函数用于序列化以任意一个结点作为根结点的 N 叉子树
    function<string(Node*)> subSerialize = [&](Node* subRoot) -> string
    {
        // 定义递归的基本情况：subRoot 只有一个结点，或者 subRoot 就是空的
        if(!subRoot)
        {
            return "";
        }
        // 此时直接返回用中括号套住的 subRoot->val 本身即可
        if(subRoot->children.empty())
        {
            return to_string(subRoot->val);
        }
        // 其它情况，说明这个子结点还有下一层结点，那么我们需要对它的每一个孩子结点递归调用上面的方法
        string res = "";
        res += to_string(subRoot->val);
        int n = subRoot->children.size();
        res += "[";
        for(int i = 0; i < n; ++i)
        {
            res += subSerialize(subRoot->children[i]);
            if(i < n-1)
            {
                // 不同子树之间添加一个空格作为分隔符
                // 最后一个子树后面不用再加分隔符
                res += " ";
            }
        }
        // 补充一个中括号作为结尾
        res += "]";
        return res;
    }; 
    // 对上面的函数进行调用即可
    return "[" + subSerialize(root) + "]";
}

Node* Leetcode401_500::Solution::Codec::deserialize(string data)
{
    if(data == "[]")
    {
        return nullptr;
    }
    // 考虑拿到了分组字符串后，如何复原出远来的 N 叉树
    // 我们可以考虑同样用递归回调函数的方法来实现这个方法
    // 基本的思路是，按照中括号为分隔符，对序列化的字符串进行分割
    // 定义一个子过程 subDeserialize，这个函数用于反序列化一串以数字开头的反序列串
    function<Node*(int&)> subDeserialize = [&](int& i) -> Node* 
    {
        Node* res = new Node();
        int num = 0;
        // 第一步：把开头的数值提取到一个结点中
        for(; i < data.size(); ++i)
        {
            if(!isdigit(data[i]))
            {
                break;
            }
            num = num*10+(data[i]-'0');
        }
        // 实际的赋值操作
        res->val = num;
        // 接下来要做的是对 res 的 children 进行分离和赋值操作
        // 根据接下来的字符类型来决定要怎么做
        // 1. 接下来是一个空格，那么说明这个结点我们已经处理完成了，可以直接返回
        if(data[i] == ' ')
        {
            // 注意，我们需要自动跳过这个空格，以满足我们 subDeserialize 操作的假设
            ++i;
            return res;
        }
        // 2. 接下来是一个左中括号，那么说明这个结点还有孩子，我们需要递归地对这个序列进行处理
        else if(data[i] == '[')
        {
            // 先跳过这个左中括号
            ++i;
            // 之后用一个循环对后面的序列进行递归处理，一直处理到遇到同级的右括号
            while(i < data.size() && data[i] != ']')
            {
                if(data[i] == ' ')
                {
                    ++i;
                }
                res->children.push_back(subDeserialize(i));
            }
            // 只要上面的循环退出了，那么我们就可以直接返回了，当前结点就处理完了
            // 不过需要注意跳过当前这个引起循环退出的 (同级) 右中括号，如果 i == data.size()，这样处理也不会有问题
            ++i;
            return res;
        }
        // 3. 接下来是一个右中括号，那么我们直接返回，不做任何处理 (实际的处理在情况2中，跟左括号配合处理)
        return res;
    };
    // 直接调用上面的函数即可
    int i = 0;
    return subDeserialize(++i);
}
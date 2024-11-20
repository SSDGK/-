#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <math.h>
using namespace std;

struct AVLNode
{
public:
    AVLNode* left, * right;
    int val, height;

    AVLNode(int _val) :left(nullptr), right(nullptr), val(_val), height(1) {};
};

class AVLTree
{
    using Node = AVLNode*;
    Node root;

    int getHeight(Node cur)
    {
        if (cur == nullptr)return 0;
        return cur->height;
    }

    Node rightRotate(Node cur)
    {
        Node tleft = cur->left;
        cur->left = tleft->right;
        tleft->right = cur;
        cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
        tleft->height = max(getHeight(tleft->left), getHeight(tleft->right)) + 1;
        return tleft;
    }

    Node leftRotate(Node cur)
    {
        Node tright = cur->right;
        cur->right = tright->left;
        tright->left = cur;
        cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
        tright->height = max(getHeight(tright->left), getHeight(tright->right)) + 1;
        return tright;
    }

    Node rlRotate(Node cur)
    {
        cur->right = rightRotate(cur->right);
        return leftRotate(cur);
    }

    Node lrRotate(Node cur)
    {
        cur->left = leftRotate(cur->left);
        return rightRotate(cur);
    }

    Node maintain(Node cur)
    {
        int lh = getHeight(cur->left);
        int rh = getHeight(cur->right);
        if (abs(lh - rh) > 1)
        {
            if (lh > rh)
            {
                int llh = getHeight(cur->left->left);
                int lrh = getHeight(cur->left->right);
                if (lrh > llh)return lrRotate(cur);
                else return rightRotate(cur);
            }

            if (rh > lh)
            {
                int rlh = getHeight(cur->right->left);
                int rrh = getHeight(cur->right->right);
                if (rlh > rrh)return rlRotate(cur);
                else return leftRotate(cur);
            }
        }
        return cur;
    }

    Node findNode(int _val, Node cur)
    {
        if (cur == nullptr)return nullptr;

        if (_val < cur->val)return findNode(_val, cur->left);
        if (_val > cur->val)return findNode(_val, cur->right);
        return cur;
    }

    Node add(int _val, Node cur)
    {
        if (cur == nullptr)
            return new AVLNode(_val);

        if (cur->val > _val)
        {
            cur->left = add(_val, cur->left);
        }
        else if (cur->val < _val)
        {
            cur->right = add(_val, cur->right);
        }

        cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
        return maintain(cur);
    }

    Node DeleteNode(int _val, Node cur)
    {
        if (_val < cur->val)cur->left = DeleteNode(_val, cur->left);
        else if (_val > cur->val)cur->right = DeleteNode(_val, cur->right);
        else
        {
            if (cur->left == nullptr && cur->right == nullptr)
            {
                delete cur;
                return nullptr;
            }
            else if (cur->left != nullptr && cur->right == nullptr)
            {
                Node tmp = cur->left;
                delete cur;
                cur = tmp;
            }
            else if (cur->left == nullptr && cur->right != nullptr)
            {
                Node tmp = cur->right;
                delete cur;
                cur = tmp;
            }
            else
            {
                Node DirectFront = cur->left;
                while (DirectFront->right)DirectFront = DirectFront->right;
                cur->val = DirectFront->val;
                cur->left = DeleteNode(DirectFront->val, cur->left);
            }
        }
        cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
        return maintain(cur);
    }

    void inorder(Node cur, vector<int>& ans)
    {
        if (cur == nullptr)return;
        inorder(cur->left, ans);
        ans.push_back(cur->val);
        inorder(cur->right, ans);
    }

public:
    AVLTree() :root(nullptr) {};

    void insert(int _val) { root = add(_val, root); }

    bool erase(int _val)
    {
        if (findNode(_val, root) == nullptr)return false;
        root = DeleteNode(_val, root);
        return true;
    }

    vector<int> level_order_traverse()
    {
        queue<Node> q;
        vector<int> ans;

        q.push(root);
        while (!q.empty())
        {
            Node cur = q.front();
            q.pop();
            ans.push_back(cur->val);
            if (cur->left != nullptr)
            {
                q.push(cur->left);
            }
            if (cur->right != nullptr)
            {
                q.push(cur->right);
            }
        }
        return ans;
    }

    vector<int> in_order_traverse()
    {
        vector<int> ans;
        inorder(root, ans);
        return ans;
    }
};


vector<int> arr;

int main()
{
    AVLTree tree;
    int n;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i : arr)
    {
        tree.insert(i);
    }
    auto inorderV = tree.in_order_traverse();
    auto levelorderV = tree.level_order_traverse();
    for (auto i : levelorderV)cout << i << ' ';
    cout << endl;
    for (auto i : inorderV)cout << i << ' ';
}
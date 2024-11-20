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

public:
    AVLTree() :root(nullptr) {};

    void addnum(int _val) { root = insert(_val, root); }
    Node insert(int _val, Node cur)
    {
        if (cur == nullptr)
            return new AVLNode(_val);

        if (cur->val > _val)
        {
            cur->left = insert(_val, cur->left);
        }
        else if (cur->val < _val)
        {
            cur->right = insert(_val, cur->right);
        }

        cur->height = max(getHeight(cur->left), getHeight(cur->right)) + 1;
        return maintain(cur);
    }

    void level_order_traverse()
    {
        queue<Node> q;
        vector<int> ans;
        bool flag1 = false, flag2 = false;

        q.push(root);
        while (!q.empty())
        {
            Node cur = q.front();
            q.pop();
            ans.push_back(cur->val);
            if (cur->left != nullptr)
            {
                q.push(cur->left);
                if (flag1)flag2 = true;
            }
            else flag1 = true;

            if (cur->right != nullptr)
            {
                q.push(cur->right);
                if (flag1)flag2 = true;
            }
            else flag1 = true;
        }

        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i];
            if (i != ans.size() - 1)cout << ' ';
            else cout << endl;
        }

        if (!flag2)cout << "Yes";
        else cout << "No";
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
        tree.addnum(i);
    }
    tree.level_order_traverse();
}
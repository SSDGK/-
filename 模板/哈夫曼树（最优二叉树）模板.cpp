#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int weight;
    Node* leftc;
    Node* rightc;
};

using Htree = Node*;

int buildHuffman(vector<int>& arr)//返回值改为root即变为建树
{
    int ans = 0;
    int n = arr.size();
    vector<Htree> forest;
    forest.resize(n);
    Htree root = nullptr;
    for (int i = 0; i < n; i++)
    {
        root = (Htree)malloc(sizeof(Node));
        root->weight = arr[i];
        root->leftc = root->rightc = nullptr;
        forest[i] = root;
    }

    for (int i = 1; i < n; i++)
    {
        int minloc = -1, submin = -1;
        for (int i = 0; i < n; i++)
        {
            if (forest[i] != nullptr)
            {
                if (minloc == -1)minloc = i;
                else
                {
                    submin = i;
                    break;
                }
            }
        }
        if (minloc == -1)
        {
            return 0;
        }
        if (submin == -1)
        {
            return ans;
        }
        for (int i = submin; i < n; i++)
        {
            if (forest[i] != nullptr)
            {
                if (forest[i]->weight < forest[minloc]->weight)
                {
                    submin = minloc;
                    minloc = i;
                }
                else if (forest[i]->weight < forest[submin]->weight)
                {
                    submin = i;
                }
            }
        }

        root = (Htree)malloc(sizeof(Node));
        root->weight = forest[minloc]->weight + forest[submin]->weight;
        root->leftc = forest[minloc];
        root->rightc = forest[submin];

        forest[minloc] = root;
        forest[submin] = nullptr;
        ans += root->weight;
    }
    return ans;
}


int main()
{
    vector<vector<int>> hits = { {1,0} };
    vector<vector<int>> graph = { {1,0,0,0} ,{1,1,1,0} };
    int n;
    cin >> n;
    vector<int> arr;
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << buildHuffman(arr);
}
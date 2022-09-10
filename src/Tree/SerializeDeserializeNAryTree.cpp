#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

// https://leetcode-cn.com/problems/serialize-and-deserialize-n-ary-tree/

string serialize(Node* root) {
    string result = "";
    if (root) {
        result += to_string(root->val) + ",";
        if (root->children.size() > 0) {
            result += "[";
            for (auto child : root->children) {
                result += serialize(child);
            }
            result += "]";
        }
    }
    return result;
}

Node* deserialize(string data) {
    if (data.size() == 0) return nullptr;
    Node* root = nullptr;
    Node* cur = nullptr;
    stack<Node*> stk;
    while (!data.empty()) {
        if (data[0] == '[') {
            data = data.substr(1);
            stk.push(cur);
        } else if (data[0] == ']') {
            data = data.substr(1);
            stk.pop();
        } else {
            int index = data.find(',');
            int val = stoi(data.substr(0, index));
            data = data.substr(index + 1);
            Node* node = new Node(val);

            if (!root) {
                root = node;
            } else {
                Node* parent = stk.top();
                parent->children.push_back(node);
            }
            cur = node;
        }
    }
    return root;
}

void destroyNAryTree(Node* root) {
    if (!root) return;
    for (auto child : root->children) {
        destroyNAryTree(child);
    }
    delete root;
    root = nullptr;
}

int main(int argc, char* argv[]) {
    string data = "1,[2,3,[6,7,[11,[14,]]]4,[8,[12,]]5,[9,[13,]10,]]";
    auto root = deserialize(data);
    auto result = serialize(root);
    assert(data == result);
    destroyNAryTree(root);

    data = "1,[3,[5,6,]2,4,]";
    root = deserialize(data);
    result = serialize(root);
    assert(data == result);
    destroyNAryTree(root);
    return 0;
}
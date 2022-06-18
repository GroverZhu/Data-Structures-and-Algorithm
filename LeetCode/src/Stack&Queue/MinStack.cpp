#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

class MinStack {
   public:
    MinStack() {
        mini = {};
        normal = {};
    }

    void push(int val) {
        normal.push(val);
        if (normal.size() == 1) {
            mini.push(val);
        } else {
            mini.push(min(val, mini.top()));
        }
    }

    void pop() {
        normal.pop();
        mini.pop();
    }

    int top() { return normal.top(); }

    int getMin() { return mini.top(); }

   private:
    stack<int> mini;
    stack<int> normal;
};

int main(int argc, char* argv[]) {
    MinStack minstk;
    minstk.push(-2);
    minstk.push(0);
    minstk.push(-3);
    assert(-3 == minstk.getMin());
    minstk.pop();
    assert(0 == minstk.top());
    assert(-2 == minstk.getMin());

    return 0;
}
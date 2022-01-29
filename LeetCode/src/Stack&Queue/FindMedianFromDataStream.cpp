#include <iostream>
#include <functional>
#include <queue>

#include <cassert>

using namespace std;

class MedianFinder {

public:
    MedianFinder() {
        small = {};
        large = {};
    }
    
    void addNum(int num) {
        if (small.size() > large.size()) {
            small.push(num);
            large.push(small.top());
            small.pop();
        } else {
            large.push(num);
            small.push(large.top());
            large.pop();
        }
    }
    
    double findMedian() {
        if (small.size() > large.size()) {
            return small.top();
        } else if (small.size() < large.size()) {
            return large.top();
        } else {
            return (large.top() + small.top()) / 2.0;
        }
    }
private:
    priority_queue<int, vector<int>, greater<int>> small;
    priority_queue<int, vector<int>, less<int>> large;
};


int main(int argc, char* argv[]) {
    MedianFinder test;
    double epsilon = 1e-6;
    test.addNum(1);
    test.addNum(2);
    assert(abs(test.findMedian() - 1.5) < epsilon);
    test.addNum(3);    
    assert(abs(test.findMedian() - 2.0) < epsilon);

    return 0;
}
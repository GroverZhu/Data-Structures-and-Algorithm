#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/lfu-cache/

struct Node {
    int key;
    int value;
    int freq;
    Node() {
        key = 0;
        value = 0;
        freq = 0;
    }

    Node(int _key, int _value, int _freq) : key(_key), value(_value), freq(_freq) {}
};

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        keyToNode = {};
        freqTokeys = {};
        minFreq = 0;
    }
    
    int get(int key) {
        auto iter = keyToNode.find(key);
        if (iter == keyToNode.end()) return -1;

        int freq = iter->second->freq;
        int value = iter->second->value;
        
        freqTokeys[freq].erase(iter->second);
        if (freqTokeys[freq].size() == 0) {
            freqTokeys.erase(freq);
            if (freq == minFreq) minFreq += 1;
        }

        freqTokeys[freq + 1].push_front(Node(key, value, freq + 1));
        keyToNode[key] = freqTokeys[freq + 1].begin();

        return value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        auto iter = keyToNode.find(key);

        if (iter != keyToNode.end()) { // 已经存在，更新
            int freq = iter->second->freq;
            freqTokeys[freq].erase(iter->second);
            if (freqTokeys[freq].empty()) {
                freqTokeys.erase(freq);
                if (freq == minFreq) minFreq += 1;
            } 

            freqTokeys[freq + 1].push_front(Node(key, value, freq + 1));
            keyToNode[key] = freqTokeys[freq + 1].begin();

        } else { // 不存在

            if (size < capacity) { // 还有空间
                ++size;
            } else { // 没有空间
                // 删最小的freq的key
                auto del = freqTokeys[minFreq].back();
                keyToNode.erase(del.key);
                freqTokeys[minFreq].pop_back();
                if (freqTokeys[minFreq].empty()) {
                    freqTokeys.erase(minFreq);
                }
            }
            int freq = 1;
            freqTokeys[freq].push_front(Node(key, value, freq));
            keyToNode[key] = freqTokeys[freq].begin();
            minFreq = freq;

        }
    }

private:
    int capacity;
    int size;
    unordered_map<int, list<Node>::iterator> keyToNode;
    unordered_map<int, list<Node>> freqTokeys;
    int minFreq;
};


int main(int argc, char* argv[]) {
    int capacity = 2;
    LFUCache lfu = LFUCache(capacity);
    lfu.put(1, 1);
    lfu.put(2, 2);
    assert(1 == lfu.get(1));
    lfu.put(3, 3);
    assert(-1 == lfu.get(2));
    assert(3 == lfu.get(3));
    lfu.put(4, 4);
    assert(-1 == lfu.get(1));
    assert(3 == lfu.get(3));
    assert(4 == lfu.get(4));


    capacity = 2;
    lfu = LFUCache(capacity);
    lfu.put(3, 1);
    lfu.put(2, 1);
    lfu.put(2, 2);
    lfu.put(4, 4);
    assert(2 == lfu.get(2));

    return 0;
}
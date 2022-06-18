#include <cassert>
#include <iostream>
#include <list>
#include <map>

using namespace std;

// https://leetcode-cn.com/problems/lru-cache/
class LRUCache {
   public:
    LRUCache(int capacity) {
        size = 0;
        this->capacity = capacity;
        chain = {};
        cache = {};
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        auto node = cache[key];
        int result = (*node).second;
        chain.splice(chain.begin(), chain, node);
        return result;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {  // 已经存在，更新值并移动至chain头节点
            auto node = cache[key];
            chain.erase(node);
            cache.erase(key);
            chain.push_front({key, value});
            cache[key] = chain.begin();
        } else {  // 不存在，chain是否满，如果满，则先移除在添加，否则直接添加
            if (size < capacity) {  // 直接添加
                chain.push_front({key, value});
                cache[key] = chain.begin();
                size++;
            } else {
                auto node = chain.back();
                cache.erase(node.first);
                chain.pop_back();
                chain.push_front({key, value});
                cache[key] = chain.begin();
            }
        }
    }

   private:
    list<pair<int, int>> chain;
    map<int, list<pair<int, int>>::iterator> cache;
    int size;
    int capacity;
};

int main(int argc, char* argv[]) {
    LRUCache lru = LRUCache(2);
    lru.put(1, 1);
    lru.put(2, 2);
    assert(lru.get(1) == 1);
    lru.put(3, 3);
    assert(lru.get(2) == -1);
    lru.put(4, 4);
    assert(lru.get(1) == -1);
    assert(lru.get(3) == 3);
    assert(lru.get(4) == 4);
    return 0;
}
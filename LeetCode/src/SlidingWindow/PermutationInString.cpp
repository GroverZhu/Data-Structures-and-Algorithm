#include <iostream>
#include <string>
#include <map>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/permutation-in-string/
bool checkInClusion(string s1, string s2) {
    int size1 = static_cast<int>(s1.size());
    int size2 = static_cast<int>(s2.size());

    map<char, int> need;
    for (int i = 0; i < size1; i++) {
        need[s1[i]]++;
    }

    map<char, int> window;
    int left = 0;
    int right = 0;

    while (right < size2) {
        auto add = s2[right];
        right++;
        if (need.find(add) != need.end()) {
            window[add]++;
            if (window == need) {
                return true;
            }
            while (window[add] > need[add]) {
                auto del = s2[left];
                ++left;
                window[del]--;
            }
        } else {
            window.clear();
            left = right;
        }


        
    }

    return false;
}

int main(int argc, char* argv[]) {
    string s1 = "ab";
    string s2 = "eidbaooo";
    assert(true == checkInClusion(s1, s2));

    s1 = "ab";
    s2 = "eidboaoo";
    assert(false == checkInClusion(s1, s2));

    return 0;
}

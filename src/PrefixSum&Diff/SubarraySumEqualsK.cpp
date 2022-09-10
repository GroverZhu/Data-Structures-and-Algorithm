#include <iostream>
#include <map>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/subarray-sum-equals-k/
int subarraySum(vector<int>& nums, int k) {
    map<int, int> prefix;
    prefix[0] = 1;
    int result = 0;
    int sum = 0;
    for (auto num : nums) {
        sum += num;
        // prefix[j] - prefix[i] == k --> prefix[i] == prefix[j] - k
        if (prefix.find(sum - k) != prefix.end()) {
            result += prefix[sum - k];
        }
        prefix[sum]++;
    }
    return result;
}

// https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/
int findTheLongestSubstring(string s) {
    int size = static_cast<int>(s.size());

    map<int, int> prefix;
    prefix[0] = 0;
    int ans = 0;
    int cur = 0;

    for (int i = 0; i < size; i++) {
        switch (s[i]) {
            case 'a':
                cur ^= (1 << 0);
                break;
            case 'e':
                cur ^= (1 << 1);
                break;
            case 'i':
                cur ^= (1 << 2);
                break;
            case 'o':
                cur ^= (1 << 3);
                break;
            case 'u':
                cur ^= (1 << 4);
                break;
            default:
                break;
        }
        if (prefix.find(cur) != prefix.end()) {
            ans = max(ans, i - prefix[cur] + 1);
        } else {
            prefix[cur] = i + 1;
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int k;

    nums = {1, 1, 1};
    k = 2;
    assert(2 == subarraySum(nums, k));

    nums = {1, 2, 3};
    k = 3;
    assert(2 == subarraySum(nums, k));

    string s = "eleetminicoworoep";
    int ans = 13;
    assert(ans == findTheLongestSubstring(s));

    s = "leetcodeisgreat";
    ans = 5;
    assert(ans == findTheLongestSubstring(s));

    s = "bcbcbc";
    ans = 6;
    assert(ans == findTheLongestSubstring(s));

    return 0;
}
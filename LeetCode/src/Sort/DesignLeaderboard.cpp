#include <iostream>
#include <set>
#include <unordered_map>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/design-a-leaderboard/
class Leaderboard {
    
public:
    Leaderboard() {
        scores.clear();
        id2score.clear();
    }

    void addScore(int player, int score) {
        auto iter = id2score.find(player);

        if (iter == id2score.end()) {
            scores.insert(score);
            id2score[player] = score;
        } else {
            int prev = id2score[player];
            auto del = scores.find(prev);
            scores.erase(del);
            prev += score;
            id2score[player] = prev;
            scores.insert(prev);
        }
    }

    int top(int k) {
        int result = 0;
        int cnt = 0;
        for (auto iter = scores.begin(); cnt < k && iter != scores.end(); iter++, cnt++) {
            result += *iter;
        }
        return result;
    }

    void reset(int playId) {
        auto iter = id2score.find(playId);
        if (iter != id2score.end()) {
            auto del = scores.find(iter->second);
            scores.erase(del);
            id2score.erase(playId);
        }
    }

private: 
    multiset<int, decltype(greater<int>())> scores{greater<int>()};
    unordered_map<int, int> id2score;

};

int main(int argc, char* argv[]) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 73);
    leaderboard.addScore(2, 56);
    leaderboard.addScore(3, 39);
    leaderboard.addScore(4, 51);
    leaderboard.addScore(5, 4);
    assert(73 == leaderboard.top(1));
    leaderboard.reset(1);
    leaderboard.reset(2);
    leaderboard.addScore(2, 51);
    assert(141 == leaderboard.top(3));

    return 0;
}
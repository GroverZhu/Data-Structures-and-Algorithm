#include <iostream>
#include <string>
#include <set>
#include <vector>

#include <cassert>

using namespace std;

void dfs(vector<string>& result, string temp, int n, int left, int right) {
    if (n == left && left == right) {
        result.emplace_back(temp);
        return;
    }

    if (left < n) {
        dfs(result, temp + "(", n, left + 1, right);
    }

    if (right < left) {
        dfs(result, temp + ')', n, left, right + 1);
    }


}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    if (n <= 0) return result;
    dfs(result, "", n, 0, 0);
    return result;

}


int main(int argc, char* argv[]) {
    int n = 3;
    set<string> ans = {"((()))","(()())","(())()","()(())","()()()"};
    auto result = generateParenthesis(n);
    set<string> result_set(result.begin(), result.end());
    assert(ans == result_set);

    n = 1;
    ans = {"()"};
    result = generateParenthesis(n);
    result_set = set<string>(result.begin(), result.end());
    assert(ans == result_set);
    return 0;
}

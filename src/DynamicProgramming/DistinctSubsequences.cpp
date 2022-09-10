#include <iostream>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/distinct-subsequences/
int numDistinct(string s, string t) {
    int size1 = static_cast<int>(s.size());
    int size2 = static_cast<int>(t.size());
    vector<vector<unsigned long>> nums(size1 + 1, vector<unsigned long>(size2 + 1, 0));

    for (int i = 0; i <= size1; i++) nums[i][0] = 1;
    // for (int j = 0; j <= size2; j++) nums[0][j] = 1;

    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            if (s[i - 1] == t[j - 1]) {
                nums[i][j] = nums[i - 1][j] + nums[i - 1][j - 1];
            } else {
                nums[i][j] = nums[i - 1][j];
            }
        }
    }
    return nums[size1][size2];
}

int main(int argc, char* argv[]) {
    string s, t;
    s = "rabbbit";
    t = "rabbit";
    assert(3 == numDistinct(s, t));

    s = "babgbag";
    t = "bag";
    assert(5 == numDistinct(s, t));

    s = "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkyc"
        "ikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleicz"
        "pbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguw"
        "qijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmk"
        "sivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibep"
        "buacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekje"
        "alvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyi"
        "efhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtuls"
        "tuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyft"
        "jighntqzoo";
    t = "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys";
    assert(543744000 == numDistinct(s, t));

    return 0;
}
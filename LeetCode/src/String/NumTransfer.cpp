#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include <thread>

#include <cassert>
#include <climits>

using namespace std;

static vector<string> ENGLISH_ONES_PLACE = {"Zero", "One", "Two",   "Three", "Four",
                                            "Five", "Six", "Seven", "Eight", "Nine"};  // 1~9
static vector<string> ENGLISH_TENS_PLACE = {"",      "Ten",   "Twenty",  "Thirty", "Forty",
                                            "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};  // 10,20...90
static vector<string> ENGLISH_DOZENES = {"Ten",     "Eleven",  "Twelve",    "Thirteen", "Fourteen",
                                         "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};  // 11~19
static vector<string> ENGLISH_BASE = {"", "Thousand", "Million", "Billion"};  // 1000, 1000000, 1000000000

// 英文的表示为3位一个数量级，按最小的划分单元进行
string numToEnglishStr(int num) {
    string ans = "";
    if (num >= 100) {
        ans += ENGLISH_ONES_PLACE[num / 100] + " Hundred ";
        num %= 100;
    }

    if (num >= 20) {
        ans += ENGLISH_TENS_PLACE[num / 10] + " ";
        num -= num / 10 * 10;
    }

    if (num >= 10) {
        ans += ENGLISH_DOZENES[num - 10] + " ";
        return ans;
    }

    if (num > 0) {
        ans += ENGLISH_ONES_PLACE[num] + " ";
    }

    return ans;
}

// 阿拉伯转英文 leetcode原题 https://leetcode.cn/problems/integer-to-english-words/
string ArabicNumeralToEnglish(int num) {
    if (num == 0) {
        return "Zero";
    }
    string result = "";
    for (int base = 1000000000, i = 3; base > 0; base /= 1000) {
        int prefix = num / base;
        // cout << i << "," << prefix << endl;
        if (prefix != 0) {
            result += numToEnglishStr(prefix) + ENGLISH_BASE[i] + " ";
        }
        i--;
        num %= base;
    }
    int index = static_cast<int>(result.size()) - 1;
    while (index >= 0 && result[index] == ' ') {
        --index;
    }
    result = result.substr(0, index + 1);

    return result;
}

static vector<string> CHINESE_ONES_PLACE = {"〇", "一", "二", "三", "四", "五", "六", "七", "八", "九"};

static vector<string> CHINESE_UNITS = {"", "十", "百", "千", "万", "亿"};

// 中文中4个数一个量级
string numToChineseStr(int num) {
    string ans = "";
    if (num >= 1000) {
        ans += CHINESE_ONES_PLACE[num / 1000] + CHINESE_UNITS[3];
        num %= 1000;
        if (num < 100) {
            ans += CHINESE_ONES_PLACE[0];
        }
    }
    if (num >= 100) {
        ans += CHINESE_ONES_PLACE[num / 100] + CHINESE_UNITS[2];
        num %= 100;
        if (num < 10) {
            ans += CHINESE_ONES_PLACE[0];
        }
    }
    if (num >= 10) {
        ans += CHINESE_ONES_PLACE[num / 10] + CHINESE_UNITS[1];
        num %= 10;
    }
    if (num > 0) {
        ans += CHINESE_ONES_PLACE[num];
    }

    return ans;
}

// 阿拉伯转中文
string ArabicNumeralToChinese(int num) {
    if (num == 0) {
        return CHINESE_ONES_PLACE[0];
    }

    string result = "";
    vector<string> bases = {"", "万", "亿"};
    for (int base = 100000000, i = 2; base > 0; base /= 10000) {
        int prefix = num / base;
        num %= base;
        if (prefix != 0) {
            result += numToChineseStr(prefix) + bases[i];
            if (num < base / 10) {  // 中文中有补0的操作，在中间有一个或多个的0
                result += CHINESE_ONES_PLACE[0];
            }
        }
        i--;
    }

    return result;
}

static map<string, int> ENGLISH_ONES_NUM = {
    {"Zero", 0},      {"One", 1},       {"Two", 2},       {"Three", 3},    {"Four", 4},     {"Five", 5},
    {"Six", 6},       {"Seven", 7},     {"Eight", 8},     {"Nine", 9},     {"Ten", 10},     {"Eleven", 11},
    {"Twelve", 12},   {"Thirteen", 13}, {"Fourteen", 14}, {"Fifteen", 15}, {"Sixteen", 16}, {"Seventeen", 17},
    {"Eighteen", 18}, {"Nineteen", 19}, {"Twenty", 20},   {"Thirty", 30},  {"Forty", 40},   {"Fifty", 50},
    {"Sixty", 60},    {"Seventy", 70},  {"Eighty", 80},   {"Ninety", 90}};

static map<string, int> ENGLISH_BASE_NUM = {
    {"Hundred", 100}, {"Thousand", 1000}, {"Million", 1000000}, {"Billion", 1000000000}};

// 英文转阿拉伯
int EnglishToArabicNumeral(string str) {
    int size = static_cast<int>(str.size());
    stack<int> stk;
    int left = 0;
    int right = 0;
    int cur_val = 0;
    while (right < size) {
        while (right < size && str[right] != ' ') {
            ++right;
        }
        string cur_token = str.substr(left, right - left);
        right += 1;
        left = right;
        auto ones_num_iter = ENGLISH_ONES_NUM.find(cur_token);
        auto base_num_iter = ENGLISH_BASE_NUM.find(cur_token);

        if (ones_num_iter != ENGLISH_ONES_NUM.end()) {  // 当前是个数字
            cur_val = ones_num_iter->second;
            stk.push(cur_val);
            cur_val = 0;
        } else if (base_num_iter != ENGLISH_BASE_NUM.end()) {  // 当前是个单位
            int base = base_num_iter->second;
            int prefix = 0;
            while (!stk.empty() && stk.top() < base) {
                prefix += stk.top();
                stk.pop();
            }
            stk.push(prefix * base);
        }
    }

    int result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }

    return result;
}

static map<string, int> CHINESE_ONES_NUM = {{"〇", 0}, {"一", 1}, {"二", 2}, {"三", 3}, {"四", 4},
                                            {"五", 5}, {"六", 6}, {"七", 7}, {"八", 8}, {"九", 9}};
static map<string, int> CHINESE_UNITS_NUM = {{"十", 10}, {"百", 100}, {"千", 1000}, {"万", 10000}, {"亿", 100000000}};

// 中文转阿拉伯文
int ChineseToArabicNumeral(string str) {
    // 中文的话，需要看编码来遍历，不同的编码的字符长度大小不同，在mac下使用unicode编码，一个汉字3byte
    int size = static_cast<int>(str.size());
    if (size % 3 != 0) {
        return -1;
    }

    stack<int> stk;
    int cur_val = 0;
    int index = 0;

    while (index + 3 <= size) {
        string cur_token = str.substr(index, 3);
        auto ones_num_iter = CHINESE_ONES_NUM.find(cur_token);
        auto units_iter = CHINESE_UNITS_NUM.find(cur_token);
        if (ones_num_iter != CHINESE_ONES_NUM.end()) {
            cur_val = ones_num_iter->second;
            stk.push(cur_val);
            cur_val = 0;
        } else if (units_iter != CHINESE_UNITS_NUM.end()) {
            int base = units_iter->second;
            int prefix = 0;
            while (!stk.empty() && stk.top() < base) {
                prefix += stk.top();
                stk.pop();
            }
            stk.push(prefix * base);
        }
        index += 3;
    }

    int result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }

    return result;
}

int main() {
    clock_t start, end;
#if 0
    start = clock();
    for (int i = 0; i < INT_MAX; i++) {
        string english_expr = ArabicNumeralToEnglish(i);
        string chinese_expr = ArabicNumeralToChinese(i);
        int english_parse = EnglishToArabicNumeral(english_expr);
        int chinese_parse = ChineseToArabicNumeral(chinese_expr);
        assert(i == english_parse && i == chinese_parse /* &&
               (cout << "Current number is: " << i << ", the English expression is: " << english_expr
                     << ", English parse: " << english_parse << ", the Chinese expression is: " << chinese_expr
                     << ", Chinese parse: " << chinese_parse << endl)*/);
    }
#endif

#if 1  // 使用多线程测试 hard test，测一次估计等要个20分钟左右吧
    int thread_nums = 16;
    vector<thread> threads(thread_nums);
    vector<vector<int>> parts(thread_nums);
    for (int i = 0; i < INT_MAX; i++) {
        parts[i % thread_nums].push_back(i);
    }
    auto test = [](vector<int>& nums) {
        for (auto n : nums) {
            string english_expr = ArabicNumeralToEnglish(n);
            string chinese_expr = ArabicNumeralToChinese(n);
            int english_parse = EnglishToArabicNumeral(english_expr);
            int chinese_parse = ChineseToArabicNumeral(chinese_expr);
            assert(n == english_parse && n == chinese_parse);
        }
    };

    for (int i = 0; i < thread_nums; i++) {
        threads[i] = thread(test, ref(parts[i]));
    }
    start = clock();
    cout << "start testing..." << endl;
    for (int i = 0; i < thread_nums; i++) {
        threads[i].join();
    }

#endif
    end = clock();
    cout << "Total time cost: " << (double)((end - start) / CLOCKS_PER_SEC) << "s" << endl;
}

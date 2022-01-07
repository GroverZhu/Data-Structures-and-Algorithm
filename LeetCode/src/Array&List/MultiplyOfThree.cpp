#include <iostream>
#include <string>

using namespace std;

bool isMultipleOfThree(string nums) {
	int sum = 0;
	for (auto c : nums) {
		sum += (c - '0');
	}
	return sum % 3 == 0;
}


int main(int argc, char* argv[]) {
	int times = 25;
	srand(times);
	for (int i = 0; i < times; i++) {
		int len = rand() % 10000 + 1;
		string s(len, ' ');
		for (int i = 0; i < len; i++) {
			s[i] = (rand() % 10) + '0';
		}
        
		cout << "EXPECT_EQ("<< (isMultipleOfThree(s) ? "true" : "false")  
            << "," << " isMultipleOfThree(\"" << s << "\"));" << endl;
	}
	return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> nums {"one","two","three","four","five","six","seven","eight","nine"};

string toNumber(string number) {
	if (number == "one") return "o1e";
	else if (number == "two") return "t2o";
	else if (number == "three") return "t3e";
	else if (number == "four") return "f4r";
	else if (number == "five") return "f5e";
	else if (number == "six") return "s6x";
	else if (number == "seven") return "s7n";
	else if (number == "eight") return "e8t";
	else return "n9e";
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}


void replaceAll(string &word) {
	for (int i = 0; i < 9; ++i) {
		bool sol = true;
		while (sol)
			sol = replace(word, nums[i], toNumber(nums[i]));
		/* cout << word << endl; */
	}
}

int getNumbers(string word) {
	int num=0;
	for(int i = 0; i < word.size(); ++i) {
		if(int(word[i]) >= '0' and int(word[i]) <= '9') {
			num = (word[i]-'0')*10;
			break;
		}
	}

	for(int i = word.size()-1; i >= 0; --i) {
		if(int(word[i]) >= '0' and int(word[i]) <= '9') {
			num += (word[i]-'0');
			break;
		}
	}
	return num;
}


int main() {
	string word;
	int sum = 0;
	while(cin >> word) {
		replaceAll(word);
		sum += getNumbers(word);
        /* cout << word << endl; */
	}
	cout << sum << endl;
}

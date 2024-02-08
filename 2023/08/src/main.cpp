#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

bool all_z(vector<string> v) {
    for (auto s : v) {
        if (s[2] != 'Z') return false;
    }
    return true;
}

void debug_vector(vector<string> v) {
    for (auto s : v) {
        cout << s << " ";
    }
    cout << endl;
}

void delete_positions_from_vector(vector<string>&v, vector<int> to_delete) {
    for (auto i : to_delete) {
        if (i > 0 and i < v.size()) {
            v.erase(v.begin() + i);
        }
    }

}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// function to calculate LCM using GCD
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main (int argc, char *argv[])
{
    long long sum = 0;
    long long part1sol, part2sol;
    part1sol = part2sol = 0;

    string ordenes;
    cin >> ordenes; // RLRLRL

    string s, info1, info2;
    string trash;
    map<string, pair<string,string>> map;

    string current = "AAA";
    vector<string> current_v;

    for (int i = 0; i < 794; ++i) {
        cin >> s;
        if (s == "fi") {
            cout << "salgo chill" << endl;
            break;
        }
        cin >> trash;
        cin >> info1 >> info2;
        string l = info1.substr(1,3);
        string r = info2.substr(0,3);
        map.insert(make_pair(s, pair<string,string>(l, r)));
        cout << "read: " << s << " " << trash << " " << info1 << " " << info2 << endl;
        if (s[2] == 'A') current_v.push_back(s);
    }
    cout << "current: " << current << endl;

    bool found = false;
    int steps = 0;

    while(false) {
        for(int i = 0; i < ordenes.length() and !found; ++i) {
            auto map_entry = map.find(current);
            if (map_entry == map.end()) found = true;
            auto element = map_entry->second;
            if (ordenes[i] == 'L') {
                current = element.first;
            }
            if (ordenes[i] == 'R') {
                current = element.second;
            }
            ++steps;
            if (current == "ZZZ") {
                found = true;
            }
        }
    }
    part1sol = steps;

    found = false;
    steps = 0;
    debug_vector(current_v);

    vector<int> steps_v;
    int paths_solved = 0;
    int total_paths = current_v.size();
    vector<int> to_delete;

    cout << "total paths " << total_paths << endl;

    while (!found) {
        for (int i = 0; i < ordenes.length() and !found; ++i) {
            ++steps;
            for (int j = 0; j < current_v.size(); ++j) {
                auto element = map.find(current_v[j])->second;
                if (ordenes[i] == 'L') {
                    current_v[j] = element.first;
                }
                if (ordenes[i] == 'R') {
                    current_v[j] = element.second;
                }
                cout << current_v[j][2] << endl;
                if (current_v[j][2] == 'Z') {
                    steps_v.push_back(steps);
                    to_delete.push_back(j);
                    ++paths_solved;
                }
                current_v.erase(current_v.begin() + j);
            }
            if (paths_solved == total_paths) {
                found = true;
            }
            /* cout << "paths solved " << paths_solved << endl; */
            delete_positions_from_vector(current_v, to_delete);
        }
    }
    part2sol = steps;

    cout << "part1: " << part1sol << endl;
    cout << "part2: " << part2sol << endl;

    return 0;
}

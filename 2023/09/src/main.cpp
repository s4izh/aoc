#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool all_zero(vector<long long>& v) {
    for (auto e : v) {
        if (e != 0) return false;
    }
    return true;
}

int main (int argc, char *argv[])
{
    long long sum = 0;
    long long part1sol, part2sol;
    part1sol = part2sol = 0;

    for(int k = 0; k < 200; ++k){
        string line;
        getline(cin, line);
        vector<long long> linea;
        vector<vector<long long>> pisos;
        pisos.clear();

        int first_pos = 0;
        long long element = 0;
        int negative = 1;

        for (int i = 0; i <= line.length(); i++) {
            if (line[i] == '-') {
                negative = -1;
            }
            else if (line[i] == ' ' or i == line.length()) {
                linea.push_back(element * negative);
                element = 0;
                negative = 1;
            }
            else {
                element *= 10;
                element += line[i] - '0';
            }
        }

        pisos.push_back(linea);

        for(int i = 0; !all_zero(pisos[i]); ++i) {
            vector<long long> v;
            for (int j = 0; j < pisos[i].size()-1; ++j) {
                v.push_back(pisos[i][j + 1] - pisos[i][j]);
            }
            pisos.push_back(v);
        }

        long long result = 0;

        for (int i = 0; i < pisos.size() - 1; ++i) {
            int last = pisos[i].size() - 1;
            result += pisos[i][last];
        }
        part1sol += result;
        long long aux = pisos[pisos.size() - 1][0];
        for (int i = pisos.size() - 2; i >= 0; --i) {
            aux = pisos[i][0] - aux;
        }
        result = aux;
        part2sol += result;
    }

    cout << "part1: " << part1sol << endl;
    cout << "part2: " << part2sol << endl;

    return 0;
}

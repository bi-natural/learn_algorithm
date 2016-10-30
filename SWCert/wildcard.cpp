#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

bool matched(const string& p, const string& t)
{
    int pos = 0;

    while (pos < p.size() && pos < t.size() && (p[pos] == '?' || p[pos] == t[pos]))
        pos++;

    if (pos == p.size())
        return (pos == t.size());

    if (p[pos] == '*') {
        for (int i = 0; pos+i <= t.size(); ++i) {
            if (matched(p.substr(pos+1), t.substr(pos+i)))
                return true;
        }
    }        
    return false;
}

vector<string> findMatched(const string& pattern, const vector<string>& v) 
{
    vector<string> result;

    for (int i = 0; i < v.size(); ++i) { 
        if (matched(pattern, v[i]))
            result.push_back(v[i]);
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("data/wildcard.dat", "r", stdin);

    cin >> N;
    cin.ignore(1, '\n');
    for (int i = 0; i < N; ++i) {
        string pattern;
        int targets;
        getline(cin, pattern);

        cin >> targets;
        cin.ignore(1, '\n');
 
        vector<string> v;
        for (int j = 0; j < targets; ++j) {
            string line;

            getline(cin, line);
            v.push_back(line);
        }

        vector<string> result = findMatched(pattern, v);

        cout << '#' << i+1 << " " << result.size() << endl;
        for (int j = 0; j < result.size(); ++j) {
            cout << " " << result[j] << endl;
        }
     }
}
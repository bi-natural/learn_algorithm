#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

int all_hug(const vector<int>& MV, const vector<int>& FV)
{
    vector<int> CV(MV.size() + FV.size() - 1, -1);

    for (int i = 0; i < MV.size(); i++) {
        for (int j = 0; j < FV.size(); j++) {
            CV[i+j] = MV[i] & FV[j];
        }
    }

    int result = 0;

    for (int i = MV.size() - 1; i < FV.size(); i++) {
        cout << CV[i] << ", ";
        if (CV[i] == 0) 
            result ++;
    }
    cout << endl;
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);

    freopen("data/fanmeeting.dat", "r", stdin);

    cin >> N;
    cin.ignore(1, '\n');

    for (int i = 0; i < N; ++i) {
        string members, fans;

        getline(cin, members);
        getline(cin, fans);

        vector<int> members_digits;
        vector<int> fans_digits;

        cout << "M = " << members << endl;
        cout << "F = " << fans << endl;
        for (int j = 0; j < members.size(); ++j) {
            members_digits.push_back( (members[j]) == 'M' ? 1 : 0 );
        }

        for (int j = 0; j <fans.size(); ++j) {
            fans_digits.push_back( (fans[j] == 'M') ? 1 : 0 );
        }

        reverse(fans_digits.begin(), fans_digits.end());

        int result = all_hug(members_digits, fans_digits);

        cout << "#" << i+1 << " " << result << endl;
    }
}
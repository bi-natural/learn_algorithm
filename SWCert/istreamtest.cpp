
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <istream>
#include <sstream>

using namespace std;

string output = "Chain OUTPUT (policy ACCEPT)\n\
num  target     prot opt source               destination\n\
1    REDIRECT   tcp  --  0.0.0.0/0            70.10.15.10          tcp dpt:8080 redir ports 3837\n\
2    REDIRECT   tcp  --  0.0.0.0/0            70.10.15.10          tcp dpt:8080 redir ports 3837\n";

int main()
{
    istringstream istr(output);
    string strs[20];
    string line, head;

    while (getline(istr, line, '\n')) {
        istringstream iss(line);

        iss >> head;

        if (head.compare("Chain") == 0) {
            printf("It is Chain\n");
        }
        else if (head.compare("num") == 0) {
            printf("It is num\n");
        }
        else {
            int lineNo = atoi(head.c_str());

            iss >> strs[0] >> strs[1] >> strs[2] >> strs[3] >> strs[4] >> strs[5] >> strs[6] >> strs[7] >> strs[8] >> strs[9];

            printf("lineNo = %d\n", lineNo);
            printf("\t1 target = %s\n", strs[0].c_str());
            printf("\t1 prot   = %s\n", strs[1].c_str());
            printf("\t1 opt    = %s\n", strs[2].c_str());
            printf("\t1 source = %s\n", strs[3].c_str());
            printf("\t1 target = %s\n", strs[4].c_str());
            printf("\t1 t.prot = %s\n", strs[5].c_str());
            printf("\t1 t.port = %s\n", strs[6].c_str());
            printf("\t1 t.comd = %s\n", strs[7].c_str());
            printf("\t1 t.dest = %s\n", strs[8].c_str());
            printf("\t1 t.port = %s\n", strs[9].c_str());
        }
    }
}
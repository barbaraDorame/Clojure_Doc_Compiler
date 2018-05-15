#include <iostream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "lex.h"

using namespace std;

class Parser{
public:
    void sintactic();
private:

};

void parser()
{
    int **dfa = new int*[3];
    for(int i = 0; i < 3; i++) dfa[i] = new int[41];

    for(int i = 0; i < 3; i++) for(int j = 0; j < 41; j++) dfa[i][j] = -1;
    for(int j = 3; j < 34; j++) dfa[0][j] = j + 8;
    dfa[0][0] = 7;
    dfa[0][1] = 8;
    dfa[0][2] = 9;
    dfa[0][34] = 5;
    dfa[0][35] = 4;
    dfa[0][36] = 3;
    dfa[0][37] = 4;
    dfa[0][38] = 6;
    dfa[0][39] = 4;
    dfa[0][40] = 4;
    dfa[1][34] = 1;
    dfa[2][38] = 2;

}

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

enum TOKEN {
    T_LEFT_PARENTHESIS, // (
    T_RIGHT_PARENTHESIS, // )
    T_LEFT_SQBRACKET, // [
    T_RIGHT_SQBRACKET, // ]
    T_LEFT_CURLYBRACKET, // {
    T_RIGHT_CURLYBRACKET, // }
    T_COMMA, // ,
    T_LINECOMMENT, // ;;
    T_BLOCKCOMMENT, // (comment )
    T_OR, // or
    T_AND, // and
    T_DOT, // .
    T_IF, // if
    T_TRUE, // true
    T_FALSE, // false
    T_DO, // do
    T_WHEN, // when
    T_NULL, // nil
    T_DEF, // def
    T_DEFN, // defn
    T_GET, // get
    T_VECTOR, // vector
    T_CONJ, // conj
    T_LIST, // list
    T_CONTAINS, // contains?
    T_INC, // inc
    T_FIRST, // first
    T_SECOND, // second
    T_LAST, // last
    T_PRINTLN, // println
    T_PRINTF, // printf
    T_NOT, // not
    T_IN, // in
    T_PLUS, // +
    T_MINUS, // -
    T_STAR, // *
    T_SLASH, // /
    T_BACKSLASH, /* \ */
    T_VAR, //variable
    T_SINGLEQUOTE, // '
    T_QUOTE, // "
    T_EQUAL, // =
    T_GREATER_THAN, // >
    T_LESS_THAN, // <
    T_EQUAL_GREATER, // >=
    T_EQUAL_LESS, // <=
    T_HASHTAG, // #
    T_IDENTIFIER, // ALFABETO
    T_CONSTANT, // ...-9...0...9...
    T_STRING,
    T_INVALID,
    // Non-terminal symbols:
    NTS_S,
    NTS_C,
    NTS_D,
    // Terminal symbol
    TS_B
};

struct Identifier{
    TOKEN tag;
    string lex;
    string value;
};

class Lex{
public:
    Lex(string);
    string CleanLex(string);
    vector<Identifier> Tokenizer(string);
    Identifier create_token(int, string);
    vector<Identifier> GetTokens();
private:
    string file;
    string lexx;
    vector<Identifier> tokens;
};


vector<Identifier> GetTokens()
{
    return tokens;
}


Lex::Lex(string code)
{
    file = code;
    lexx = CleanLex(file);
    tokens = Tokenizer(lexx);
}


string Lex::CleanLex(string file)
{
    fstream input(file, fstream::in);
    //flag 1 para comentario, flag 0 para leer
    char c;
    char prev = '\0';
    int flag_inline = 0;
    int flag_blank = 0;
    int print = 0;
    string lex;

    while (input >> noskipws >> c) {
        print = 1;
        if(flag_blank == 0){
            if(c == ' ' || c == '\n' ){
                flag_blank = 1;
            }
        } else {
            if(c != ' ' && c != '\n' && c != '\t'){
                prev = ' ';
                flag_blank = 0;
            } else {
                print = 0;
            }
        }
        if(flag_inline == 0){
            if(prev == ';' && c == ';'){
                flag_inline = 1;
                print = 0;
            }
        } else {
            if(c == '\n'){
                flag_inline = 0;
            }
            print = 0;
        }

        if (print) {
            lex += prev;
        }

        prev = c;
    }
    return lex;
}

vector<Identifier> Lex::Tokenizer(string lex)
{
    bool acceptedStates[106];
    int **dfa = new int*[106];
    for(int i = 0; i < 106; i++) dfa[i] = new int[127];


    for(int i = 0; i < 81; i++) acceptedStates[i] = false;

    for(int i = 79; i < 106; i++) acceptedStates[i] = true;
    acceptedStates[3] = true; // T_OR
    acceptedStates[6] = true; // T_AND
    acceptedStates[8] = true; // T_IF
    acceptedStates[9] = true; // T_IN
    acceptedStates[10] = true; // T_INC
    acceptedStates[14] = true; // T_TRUE
    acceptedStates[19] = true; // T_FALSE
    acceptedStates[23] = true; // T_FIRST
    acceptedStates[29] = true; // T_SECOND
    acceptedStates[33] = true; // T_WHEN
    acceptedStates[36] = true; // T_NULL
    acceptedStates[38] = true; // T_DO
    acceptedStates[40] = true; // T_DEF
    acceptedStates[41] = true; // T_DEFN
    acceptedStates[44] = true; // T_GET
    acceptedStates[50] = true; // T_VECTOR
    acceptedStates[60] = true; // T_CONTAINS
    acceptedStates[54] = true; // T_CONJ
    acceptedStates[64] = true; // T_LIST
    acceptedStates[67] = true; // T_LAST
    acceptedStates[73] = true; // T_PRINTF
    acceptedStates[75] = true; // T_PRINTLN
    acceptedStates[76] = true; // T_QUOTE
    acceptedStates[77] = true; // T_STRING
    acceptedStates[78] = true; // T_SINGLEQUOTE
    acceptedStates[79] = true; // T_STRING
    acceptedStates[92] = true; // T_PRINTLN
    acceptedStates[103] = true; // numbah
    acceptedStates[102] = false; // numbah

    for(int i = 0; i < 106; i++)
      for(int j = 0; j < 127; j++) dfa[i][j] = 0;

    dfa[1]['o'] = 2; // o -> 2
    dfa[2]['r'] = 3; // r -> 3
    dfa[1]['a'] = 3; // a -> 3
    dfa[3]['n'] = 4; // n -> 4
    dfa[4]['d'] = 5; // d -> 5
    dfa[1]['i'] = 7; // i -> 7
    dfa[7]['f'] = 8; // f -> 8
    dfa[7]['n'] = 9; // n -> 9
    dfa[9]['c'] = 10; // c -> 10
    dfa[1]['t'] = 11; // t -> 11
    dfa[11]['r'] = 12; // r -> 12
    dfa[12]['u'] = 13; // u -> 13
    dfa[13]['e'] = 14; // e -> 14
    dfa[1]['f'] = 15; // f -> 15
    dfa[15]['a'] = 16; // a -> 16
    dfa[16]['l'] = 17; // l -> 17
    dfa[17]['s'] = 18; // s -> 18
    dfa[18]['e'] = 19; // e -> 19
    dfa[15]['i'] = 20; // i -> 20
    dfa[20]['r'] = 21; // r -> 21
    dfa[21]['s'] = 22; // s -> 22
    dfa[22]['t'] = 23; // t -> 23
    dfa[1]['s'] = 24; // s -> 24
    dfa[24]['e'] = 25; // e -> 25
    dfa[25]['c'] = 26; // c -> 26
    dfa[26]['o'] = 27; // o -> 27
    dfa[27]['n'] = 28; // n -> 28
    dfa[28]['d'] = 29; // d -> 29
    dfa[1]['w'] = 30; // w -> 30
    dfa[30]['h'] = 31; // h -> 31
    dfa[31]['e'] = 32; // e -> 32
    dfa[32]['n'] = 33; // n -> 33
    dfa[1]['n'] = 34; // n -> 34
    dfa[34]['i'] = 35; // i -> 24
    dfa[35]['l'] = 36; // l -> 36
    dfa[1]['d'] = 37; // d -> 37
    dfa[37]['o'] = 38; // o -> 38
    dfa[37]['e'] = 39; // e -> 39
    dfa[39]['f'] = 40; // f -> 40
    dfa[40]['n'] = 41; // n -> 41
    dfa[1]['g'] = 42; // g -> 42
    dfa[42]['e'] = 43; // e -> 43
    dfa[37]['t'] = 44; // t -> 44
    dfa[1]['v'] = 45; // v -> 45
    dfa[45]['e'] = 46; // e -> 46
    dfa[46]['c'] = 47; // c -> 47
    dfa[47]['t'] = 48; // t -> 48
    dfa[48]['o'] = 49; // o -> 49
    dfa[37]['r'] = 50; // r -> 50
    dfa[1]['c'] = 51; // c -> 51
    dfa[51]['o'] = 52; // o -> 52
    dfa[52]['n'] = 53; // n -> 53
    dfa[53]['j'] = 54; // j -> 54
    dfa[53]['t'] = 55; // t -> 55
    dfa[55]['a'] = 56; // a -> 56
    dfa[56]['i'] = 57; // i -> 57
    dfa[57]['n'] = 58; // n -> 58
    dfa[58]['s'] = 59; // s -> 59
    dfa[59]['?'] = 60; // ? -> 60
    dfa[1]['l'] = 61; // l -> 61
    dfa[61]['i'] = 62; // i -> 62
    dfa[62]['s'] = 63; // s -> 63
    dfa[63]['t'] = 64; // t -> 64
    dfa[61]['a'] = 65; // a -> 65
    dfa[65]['s'] = 66; // s -> 66
    dfa[66]['t'] = 67; // t -> 67
    dfa[1]['p'] = 68; // p -> 68
    dfa[68]['r'] = 69; // r -> 69
    dfa[69]['i'] = 70; // i -> 70
    dfa[70]['n'] = 71; // n -> 71
    dfa[71]['t'] = 72; // t -> 72
    dfa[72]['f'] = 73; // f -> 73
    dfa[72]['l'] = 74; // l -> 74
    dfa[74]['n'] = 75; // n -> 75
    dfa[1]['\"'] = 76; // " -> 76
    for(int i = 32; i < 127; i++) dfa[76][i] = 76; // ALFABETO -> 76
    dfa[76]['\"'] = 77; // " -> 77
    dfa[1]['\''] = 78; // ' -> 78
    for(int i = 32; i < 127; i++) dfa[78][i] = 78; // ALFABETO -> 78
    dfa[78]['\''] = 79; // ' -> 79
    dfa[1]['['] = 80; // [ -> 80
    dfa[1][']'] = 81; // ] -> 81
    dfa[1]['('] = 82; // ( -> 82
    dfa[1][')'] = 83; // ) -> 83
    dfa[1]['{'] = 84; // { -> 84
    dfa[1]['}'] = 85; // } -> 85
    dfa[1]['>'] = 86; // > -> 86
    dfa[86]['='] = 90; // = -> 85
    dfa[1]['<'] = 88; // < -> 88
    dfa[88]['='] = 90; // = -> 89
    dfa[1]['='] = 90; // = -> 90
    dfa[1]['!'] = 92; // ! -> 92
    dfa[92]['='] = 93; // = -> 93
    dfa[1]['+'] = 94; // + -> 94
    dfa[94]['+'] = 95; // + -> 95
    dfa[1]['-'] = 96; // - -> 96
    dfa[96]['-'] = 97; // - -> 97
    dfa[1]['/'] = 98; // / -> 98
    dfa[1]['*'] = 99; // * -> 99
    dfa[1]['_'] = 100; // _ -> 100
    dfa[1][','] = 101; // , -> 101
    for(int i = '0'; i <= '9'; i++){
        dfa[1][i] = 101; // 0, 1, ..., 9 -> 101
        dfa[101][i] = 101; // 0, 1, ..., 9 -> 101
        dfa[102][i] = 103;
        dfa[103][i] = 103;
    }
    dfa[1]['.'] = 102; // 0, 1, ..., 9 -> 101
    dfa[101]['.'] = 102; // 0, 1, ..., 9 -> 101

    int **dfa2 = new int*[3];
    for(int i = 0; i < 3; i++) dfa2[i] = new int[127];

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 127; j++) dfa2[i][j] = 0;

    bool acceptedStates2[] = {false, false, true};
    for(int i = 'A'; i <= 'z'; i++){
        dfa2[1][i] = 2;
        dfa2[2][i] = 2;
    }

    dfa2[1]['['] = 0;
    dfa2[1][']'] = 0;
    dfa2[2]['['] = 0;
    dfa2[2][']'] = 0;
    for(int i = '0'; i <= '9'; i++) dfa2[2][i] = 2;

    vector<Identifier> tokens;
    int state;
    int state2;
    istringstream iss(lex);
    int j;
    string aux;

    for (int i = 0; i < lex.length() ; ++i) {
        aux = '\0';
        state = 1;
        state2 = 1;
        j = i;
        while (dfa[state][lex[j]] || dfa2[state2][lex[j]]) {
            aux += lex[i];
            state = dfa[state][lex[j]];
            state2 = dfa2[state2][lex[j]];
            if (acceptedStates[state] || acceptedStates2[state2]) {
                if (dfa[state][lex[j+1]] || dfa2[state2][lex[j+1]]){
                    j++;
                } else {
                    if(acceptedStates[state]){
                        tokens.push_back(create_token(state, aux));
                    } else {
                        tokens.push_back(create_token(state2, aux));
                    }
                    i = j;
                    break;
                }
            }
        }
    }
    return tokens;
}

Identifier Lex::create_token(int state, string value)
{
    map<string, map<string, string>> maps;
    Identifier token;
    TOKEN aux;
    token.value = value;
    switch(state) {
        case 82:
            token.tag = T_LEFT_PARENTHESIS;
            token.lex = "T_LEFT_PARENTHESIS";
            break;
        case 83:
            token.tag = T_RIGHT_PARENTHESIS;
            token.lex = "T_RIGHT_PARENTHESIS";
            break;
        case 80:
            token.tag = T_LEFT_SQBRACKET;
            token.lex = "T_LEFT_SQBRACKET";
            break;
        case 81:
            token.tag = T_RIGHT_SQBRACKET;
            token.lex = "T_RIGHT_SQBRACKET";
            break;
        case 84:
            token.tag = T_LEFT_CURLYBRACKET;
            token.lex = "T_LEFT_CURLYBRACKET";
            break;
        case 85:
            token.tag = T_RIGHT_CURLYBRACKET;
            token.lex = "T_RIGHT_CURLYBRACKET";
            break;
        case 104:
            token.tag = T_COMMA;
            token.lex = "T_COMMA";
            break;
        case 3:
            token.tag = T_OR;
            token.lex = "T_OR";
        case 6:
            token.tag = T_AND;
            token.lex = "T_AND";
            break;
        case 8:
            token.tag = T_IF;
            token.lex = "T_IF";
            break;
        case 14:
            token.tag = T_TRUE;
            token.lex = "T_TRUE";
            break;
        case 19:
            token.tag = T_FALSE;
            token.lex = "T_FALSE";
            break;
        case 38:
            token.tag = T_DO;
            token.lex = "T_DO";
            break;
        case 33:
            token.tag = T_WHEN;
            token.lex = "T_WHEN";
            break;
        case 36:
            token.tag = T_NULL;
            token.lex = "T_NULL";
            token.value = "nil";
            break;
        case 40:
            token.tag = T_DEF;
            token.lex = "T_DEF";
            break;
        case 41:
            token.tag = T_DEFN;
            token.lex = "T_DEFN";
            break;
        case 44:
            token.tag = T_GET;
            token.lex = "T_GET";
            break;
        case 10:
            token.tag = T_INC;
            token.lex = "T_INC";
            break;
        case 23:
            token.tag = T_FIRST;
            token.lex = "T_FIRST";
            break;
        case 29:
            token.tag = T_SECOND;
            token.lex = "T_SECOND";
            break;
        case 50:
            token.tag = T_VECTOR;
            token.lex = "T_VECTOR";
            break;
        case 60:
            token.tag = T_CONTAINS;
            token.lex = "T_CONTAINS";
            break;
        case 54:
            token.tag = T_CONJ;
            token.lex = "T_CONJ";
            break;
        case 67:
            token.tag = T_LAST;
            token.lex = "T_LAST";
            break;
        case 73:
            token.tag = T_PRINTF;
            token.lex = "T_PRINTF";
            break;
        case 75:
            token.tag = T_PRINTLN;
            token.lex = "T_PRINTLN";
            break;
        case 103:
        case 102:
            token.tag = T_CONSTANT;
            token.lex = "T_CONSTANT";
            break;
        case 77:
        case 79:
            token.tag = T_STRING;
            token.lex = "T_STRING";
            break;
        case 86:
            token.tag = T_GREATER_THAN;
            token.lex = "T_GREATER_THAN";
            break;
        case 87:
            token.tag = T_EQUAL_GREATER;
            token.lex = "T_EQUAL_GREATER";
            break;
        case 88:
            token.tag = T_LESS_THAN;
            token.lex = "T_LESS_THAN";
            break;
        case 89:
            token.tag = T_EQUAL_LESS;
            token.lex = "T_EQUAL_LESS";
            break;
        case 90:
            token.tag = T_EQUAL;
            token.lex = "T_EQUAL";
            break;
        case 94:
            token.tag = T_PLUS;
            token.lex = "T_PLUS";
            break;
        case 96:
            token.tag = T_MINUS;
            token.lex = "T_MINUS";
            break;
        case 98:
            token.tag = T_STAR;
            token.lex = "T_STAR";
            break;
        case 76:
            token.tag = T_QUOTE;
            token.lex = "T_QUOTE";
            break;
        case 78:
            token.tag = T_SINGLEQUOTE;
            token.lex = "T_SINGLEQUOTE";
            break;
        case 2:
            token.tag = T_IDENTIFIER;
            token.lex = "T_IDENTIFIER";
            break;
        default:
            token.tag = T_INVALID;
            token.lex = "T_INVALID";
    }

    return token;
}

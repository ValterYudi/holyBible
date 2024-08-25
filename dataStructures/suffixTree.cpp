/*
    Suffix Tree
    Time complexity: O(N^2)
    Space complexity: O(N)
    Obs.: taken from an advanced algorithms class at MaratonUSP by Yan Couto
    https://www.youtube.com/watch?v=lTFP1Y0mVIk&list=PLlMaX94qhO1RZf0HA9ye9mPB_BK1tNBN0&index=4
*/

#include <bits/stdc++.h>

using namespace std;
const int N = 112345;

string s;

struct no{
    int l, r, p; // indica os limites da substring original (aresta de entrada) e seu pai
    map<char, int> f; // filhos
    no() : l(0), r(-1), p(0) {}
    no(int L, int R, int P) : l(L), r(R), p(P) {}
    inline int len() { return r - l + 1; }
    inline char operator[](int i) { return s[i + l]; } // retorna o caractere i da substring atual s(l, r)
} t[N*2];

int en  = 1;

inline int new_node(int L, int R, int P){
    t[en] = no(L, R, P);
    return en++;
}

void build_suffix_tree(){
    s += '$';
    for(int i = 0; i < s.size(); i++){
        int cn = 0, cd = 0;
        for(int j = 0; j < s.size(); j++){
            if(cd == t[cn].len() && !t[cn].f.count(s[j])){
                t[cn].f[s[j]] = new_node(j, s.size() - i, cn);
                break;
            }else if(cd < t[cn].len() && t[cn][cd] != s[j]){
                int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].p);
                t[mid].f[s[j]] = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].p);
                t[mid].f[t[cn][cd]] = cn;
                t[cn].l += cd;
                t[cn].p = mid;
                t[t[mid].p].f[t[mid][0]] = mid;
                break;
            }
            if(cd == t[cn].len()){
                cn = t[cn].f[s[j]];
                cd = 0;
            }
            cd++;
        }
    }
}


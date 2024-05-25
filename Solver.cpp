#include "Parser.cpp"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solver{
    Parser* parser;
    struct node {
    int level;
    int fit;
    int weight;
    int bound;
};
    int bound(Parser* parser, node u, vector<int> C, vector<int> W) {
        int i = 0;
        int j = 0;
        int t = 0;
        int res = 0;
        if (u.weight >= parser->m_w) {
            return 0;
        }
        else {
            res = u.fit;
            j = u.level + 1;
            t = u.weight;
            while ((j < parser->N) && (t + W[j] <= parser->m_w)) {
                t = t + W[j];
                res = res + C[j];
                j++;
            }
            i = j;
            if (i < parser->N) {
                res = res + (parser->m_w - t) * C[i]/W[i];
            }
            return res;
        }
    }
public:
    Solver(Parser* parser) {
        queue<node> Q;
        node u;
        node v;
        vector<int> C;
        vector<int> W;
        Q.empty();
        for (int i = 0; i < parser->N; i++) {
            C.push_back(parser->c[i]);
            W.push_back(parser->w[i]);
        }
        v.level = -1; 
        v.weight = 0;
        v.fit = 0;
        int max = 0;
        Q.push(v);
        while (!Q.empty()) {
            v = Q.front();
            Q.pop();
            if (v.level == -1) {
                u.level = 0;
            }
            else if (v.level != (parser->N - 1)) {
                u.level = v.level + 1;
            }
            u.weight = v.weight + parser->w[u.level];
            u.fit = v.fit + parser->c[u.level];
            u.bound = bound(parser, u, C, W);
            if (u.weight <= parser->m_w && u.fit > max) {
                max = u.fit;
            }
            if (u.bound > max) {
                Q.push(u);
            }
            u.weight = v.weight;
            u.fit = v.fit;
            u.bound = bound(parser, u, C, W);
            if (u.bound > max) {
                Q.push(u);
            }
        }
        cout<<max<<endl;
    }
};



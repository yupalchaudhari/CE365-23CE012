#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> grammar = {
    {"S", {{"A","B","C"}, {"D"}}},
    {"A", {{"a"}, {"ε"}}},
    {"B", {{"b"}, {"ε"}}},
    {"C", {{"(","S",")"}, {"c"}}},
    {"D", {{"A","C"}}}
};

vector<string> non_terminals = {"S","A","B","C","D"};
map<string, set<string>> firstSet, followSet;

bool isTerminal(string s) {
    return !(s.size()==1 && isupper(s[0])) && s != "ε";
}

void computeFirst() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto nt : non_terminals) {
            int before = firstSet[nt].size();

            for (auto production : grammar[nt]) {
                bool allEpsilon = true;

                for (auto symbol : production) {
                    if (symbol == "ε") {
                        firstSet[nt].insert("ε");
                        break;
                    }
                    else if (isTerminal(symbol)) {
                        firstSet[nt].insert(symbol);
                        allEpsilon = false;
                        break;
                    }
                    else {
                        for (auto x : firstSet[symbol]) {
                            if (x != "ε")
                                firstSet[nt].insert(x);
                        }
                        if (firstSet[symbol].count("ε") == 0) {
                            allEpsilon = false;
                            break;
                        }
                    }
                }
                if (allEpsilon)
                    firstSet[nt].insert("ε");
            }

            if (firstSet[nt].size() > before)
                changed = true;
        }
    }
}

void computeFollow() {
    followSet["S"].insert("$");

    bool changed = true;
    while (changed) {
        changed = false;

        for (auto nt : non_terminals) {
            for (auto production : grammar[nt]) {
                for (int i = 0; i < production.size(); i++) {
                    string symbol = production[i];

                    if (find(non_terminals.begin(), non_terminals.end(), symbol) != non_terminals.end()) {
                        int before = followSet[symbol].size();

                        if (i+1 == production.size()) {
                            followSet[symbol].insert(followSet[nt].begin(), followSet[nt].end());
                        }
                        else {
                            bool epsilonAll = true;

                            for (int j = i+1; j < production.size(); j++) {
                                string next = production[j];

                                if (isTerminal(next)) {
                                    followSet[symbol].insert(next);
                                    epsilonAll = false;
                                    break;
                                }
                                else {
                                    for (auto x : firstSet[next]) {
                                        if (x != "ε")
                                            followSet[symbol].insert(x);
                                    }
                                    if (firstSet[next].count("ε") == 0) {
                                        epsilonAll = false;
                                        break;
                                    }
                                }
                            }

                            if (epsilonAll) {
                                followSet[symbol].insert(followSet[nt].begin(), followSet[nt].end());
                            }
                        }

                        if (followSet[symbol].size() > before)
                            changed = true;
                    }
                }
            }
        }
    }
}

string formatSet(set<string> s) {
    vector<string> v(s.begin(), s.end());
    sort(v.begin(), v.end());

    string res = "{ ";
    for (int i = 0; i < v.size(); i++) {
        res += v[i];
        if (i != v.size()-1) res += ", ";
    }
    res += " }";
    return res;
}

int main() {
    computeFirst();
    computeFollow();

    cout << "Expected Output\n\n";

    for (auto nt : non_terminals) {
        cout << "First(" << nt << ")  = " << formatSet(firstSet[nt]) << endl;
    }

    cout << endl;

    for (auto nt : non_terminals) {
        cout << "Follow(" << nt << ") = " << formatSet(followSet[nt]) << endl;
    }

    return 0;
}
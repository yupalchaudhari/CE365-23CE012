#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Type definitions
typedef set<string> StringSet;
typedef vector<string> Production;
typedef vector<Production> ProductionList;
typedef map<string, vector<Production>> ParseTable;
typedef map<string, ParseTable> PredicativeTable;

int main() {
    // Enable UTF-8 output on Windows
    system("chcp 65001 > nul");

    // 1. Grammar and Pre-computed Sets
    map<string, ProductionList> grammar;
    grammar["S"] = {{"A", "B", "C"}, {"D"}};
    grammar["A"] = {{"a"}, {"ε"}};
    grammar["B"] = {{"b"}, {"ε"}};
    grammar["C"] = {{"(", "S", ")"}, {"c"}};
    grammar["D"] = {{"A", "C"}};

    map<string, StringSet> first;
    first["S"] = {"a", "b", "(", "c"};
    first["A"] = {"a", "ε"};
    first["B"] = {"b", "ε"};
    first["C"] = {"(", "c"};
    first["D"] = {"a", "(", "c"};

    map<string, StringSet> follow;
    follow["S"] = {")", "$"};
    follow["A"] = {"b", "(", "c"};
    follow["B"] = {"(", "c"};
    follow["C"] = {")", "$"};
    follow["D"] = {")", "$"};

    vector<string> terminals = {"a", "b", "c", "(", ")", "$"};
    vector<string> non_terminals = {"S", "A", "B", "C", "D"};

    // 2. Table Construction
    PredicativeTable table;
    for (const auto& nt : non_terminals) {
        for (const auto& t : terminals) {
            table[nt][t] = {};
        }
    }

    bool is_ll1 = true;

    for (const auto& nt : non_terminals) {
        for (const auto& prod : grammar[nt]) {
            // Calculate FIRST of the production string
            StringSet first_prod;

            if (prod.size() == 1 && prod[0] == "ε") {
                first_prod.insert("ε");
            } else {
                bool has_epsilon = true;
                for (const auto& symbol : prod) {
                    // Check if terminal
                    if (symbol.length() == 1 &&
                        (islower(symbol[0]) || symbol == "(" || symbol == ")")) {
                        first_prod.insert(symbol);
                        has_epsilon = false;
                        break;
                    } else {
                        // It's a non-terminal
                        for (const auto& s : first[symbol]) {
                            if (s != "ε") {
                                first_prod.insert(s);
                            }
                        }
                        if (first[symbol].find("ε") == first[symbol].end()) {
                            has_epsilon = false;
                            break;
                        }
                    }
                }
                if (has_epsilon) {
                    first_prod.insert("ε");
                }
            }

            // Fill table
            for (const auto& t : first_prod) {
                if (t != "ε") {
                    table[nt][t].push_back(prod);
                }
            }

            if (first_prod.find("ε") != first_prod.end()) {
                for (const auto& t : follow[nt]) {
                    table[nt][t].push_back(prod);
                }
            }
        }
    }

    // 3. Print Table and check LL(1) status
    cout << "\n";
    cout << "-------------------------------------------------------------" << endl;
    cout << "| NT |    a    |    b    |    c    |    (    |    )    |  $  |" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (const auto& nt : non_terminals) {
        cout << "| " << nt << "  |";

        for (const auto& t : terminals) {
            auto& entry = table[nt][t];
            if (entry.size() > 1) {
                is_ll1 = false;
            }

            string p_str = "";
            if (!entry.empty()) {
                for (const auto& symbol : entry[0]) {
                    if (symbol == "ε") {
                        p_str = "eps";  // Use "eps" instead of epsilon for compatibility
                    } else {
                        p_str += symbol;
                    }
                }
            } else {
                p_str = "-";
            }

            // Center align
            int width = 8;
            int total_spaces = width - p_str.length();
            int left_spaces = total_spaces / 2;
            int right_spaces = total_spaces - left_spaces;

            cout << string(left_spaces, ' ') << p_str << string(right_spaces, ' ') << "|";
        }
        cout << endl;
    }

    cout << "-------------------------------------------------------------" << endl;

    if (is_ll1) {
        cout << "\nConclusion: The grammar is LL(1)." << endl;
    } else {
        cout << "\nConclusion: The grammar is NOT LL(1) (Collisions detected)." << endl;
    }

    // 4. String Validation Engine
    auto validate = [&](const string& input_str) -> bool {
        stack<string> st;
        st.push("$");
        st.push("S");

        string chars = input_str;
        chars.push_back('$');

        size_t idx = 0;

        while (!st.empty()) {
            string top = st.top();
            st.pop();
            string current(1, chars[idx]);

            if (top == current) {
                idx++;
                if (top == "$") return true;
            } else if (isupper(top[0])) { // Non-terminal
                if (table[top].find(current) != table[top].end() &&
                    !table[top][current].empty()) {

                    auto prod = table[top][current][0];

                    if (!(prod.size() == 1 && prod[0] == "ε")) {
                        for (auto it = prod.rbegin(); it != prod.rend(); ++it) {
                            st.push(*it);
                        }
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        return false;
    };

    // Test cases
    vector<string> test_cases = {"abc", "ac", "(abc)", "c", "(ac)", "a", "()", "(ab)", "abcabc", "b"};

    cout << "\n--- Validation Results ---" << endl;
    for (const auto& test : test_cases) {
        string result = validate(test) ? "Valid string" : "Invalid string";
        cout << "Input: " << test << string(10 - test.length(), ' ') << "-> " << result << endl;
    }

    return 0;
}

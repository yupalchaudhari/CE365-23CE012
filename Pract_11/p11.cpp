#include <bits/stdc++.h>
using namespace std;

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isNumber(string s) {
    return isdigit(s[0]);
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    string num = "";

    for (char c : expr) {
        if (isdigit(c) || c == '.') {
            num += c;
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num = "";
            }
            if (c != ' ')
                tokens.push_back(string(1, c));
        }
    }
    if (!num.empty()) tokens.push_back(num);
    return tokens;
}

vector<string> infixToPostfix(vector<string> tokens) {
    vector<string> output;
    stack<string> st;

    for (string token : tokens) {
        if (isNumber(token)) {
            output.push_back(token);
        } 
        else if (token == "(") {
            st.push(token);
        } 
        else if (token == ")") {
            while (!st.empty() && st.top() != "(") {
                output.push_back(st.top());
                st.pop();
            }
            st.pop();
        } 
        else {
            while (!st.empty() && getPrecedence(st.top()[0]) >= getPrecedence(token[0])) {
                output.push_back(st.top());
                st.pop();
            }
            st.push(token);
        }
    }

    while (!st.empty()) {
        output.push_back(st.top());
        st.pop();
    }

    return output;
}

struct Quad {
    string op, arg1, arg2, result;
};

vector<Quad> generateQuadruples(vector<string> postfix) {
    vector<Quad> quads;
    stack<string> st;
    int tempCount = 1;

    for (string token : postfix) {
        if (isNumber(token) || token[0] == 't') {
            st.push(token);
        } else {
            string arg2 = st.top(); st.pop();
            string arg1 = st.top(); st.pop();

            ostringstream ss;
            ss << tempCount++;
            string result = "t" + ss.str();
            quads.push_back({token, arg1, arg2, result});

            st.push(result);
        }
    }
    return quads;
}

void displayTable(string expr, vector<Quad> quads) {
    cout << "\nExpression: " << expr << endl;
    cout << "------------------------------------------------------------\n";

    cout << left << setw(12) << "Operator"
         << setw(15) << "Operand1"
         << setw(15) << "Operand2"
         << setw(10) << "Result" << endl;

    cout << "------------------------------------------------------------\n";

    for (auto q : quads) {
        cout << left << setw(12) << q.op
             << setw(15) << q.arg1
             << setw(15) << q.arg2
             << setw(10) << q.result << endl;
    }

    cout << "------------------------------------------------------------\n";
}

int main() {
    string expr;

    cout << "Enter expression: ";
    getline(cin, expr);

    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    vector<Quad> quads = generateQuadruples(postfix);

    displayTable(expr, quads);

    return 0;
}
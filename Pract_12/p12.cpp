#include <bits/stdc++.h>
using namespace std;

bool isNumber(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    string temp = "";

    for (char c : expr) {
        if (isalnum(c) || c == '.') {
            temp += c;
        } else {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp = "";
            }
            if (c != ' ')
                tokens.push_back(string(1, c));
        }
    }
    if (!temp.empty()) tokens.push_back(temp);
    return tokens;
}

vector<string> infixToPostfix(vector<string> tokens) {
    vector<string> output;
    stack<string> st;

    for (auto token : tokens) {
        if (isalnum(token[0])) {
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
            while (!st.empty() && precedence(st.top()[0]) >= precedence(token[0])) {
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

double toDouble(const string &s) {
    stringstream ss(s);
    double v = 0;
    ss >> v;
    return v;
}

string toStr(double v) {
    ostringstream oss;
    oss << v;
    return oss.str();
}

string applyOp(string a, string b, string op) {
    if (isNumber(a) && isNumber(b)) {
        double x = toDouble(a);
        double y = toDouble(b);

        if (op == "+") return toStr(x + y);
        if (op == "-") return toStr(x - y);
        if (op == "*") return toStr(x * y);
        if (op == "/" && y != 0) return toStr(x / y);
        if (op == "^") return toStr(pow(x, y));
    }
    return "(" + a + op + b + ")";
}

string constantFold(string expr) {
    vector<string> tokens = tokenize(expr);
    vector<string> postfix = infixToPostfix(tokens);
    stack<string> st;

    for (auto token : postfix) {
        if (isalnum(token[0])) {
            st.push(token);
        } else {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            st.push(applyOp(a, b, token));
        }
    }
    return st.top();
}

int main() {
    string expr;

    cout << "Enter Expression: ";
    getline(cin, expr);

    string result = constantFold(expr);

    cout << "\n";
    cout << left << setw(30) << "Input Expression"
         << "| " << setw(30) << "Optimized Output" << endl;

    cout << string(65, '-') << endl;

    cout << left << setw(30) << expr
         << "| " << setw(30) << result << endl;

    return 0;
}
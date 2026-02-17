#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

bool isKeyword(string s) {
    string kw[] = {
        "int","float","char","double","void","return",
        "struct","long","if","else","for","while","do"
    };
    for (string k : kw)
        if (s == k) return true;
    return false;
}

bool isOperator(char c) {
    string op = "+-*/=%";
    return op.find(c) != string::npos;
}

bool isPunctuation(char c) {
    string p = ";,(){}[]";
    return p.find(c) != string::npos;
}

bool isNumber(string s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool isIdentifier(string s) {
    if (!isalpha(s[0]) && s[0] != '_') return false;
    for (char c : s)
        if (!isalnum(c) && c != '_') return false;
    return true;
}

int main() {
    ifstream file("bollo.c");
    if (!file) {
        cout << "File not found\n";
        return 0;
    }

    set<string> symbolTable;
    vector<string> errors;

    bool inBlockComment = false;
    string token = "";
    char ch;
    int lineNo = 1;

    cout << "TOKENS\n";

    while (file.get(ch)) {

        if (ch == '\n') lineNo++;

        if (inBlockComment) {
            if (ch == '*' && file.peek() == '/') {
                file.get();
                inBlockComment = false;
            }
            continue;
        }

        if (ch == '/' && file.peek() == '*') {
            file.get();
            inBlockComment = true;
            continue;
        }

        if (ch == '/' && file.peek() == '/') {
            while (file.get(ch) && ch != '\n');
            lineNo++;
            continue;
        }

        if (ch == '\'') {
            file.get(ch);
            file.get(ch);
            continue;
        }

        if (isalnum(ch) || ch == '_') {
            token += ch;
            continue;
        }

        if (!token.empty()) {
            if (isKeyword(token))
                cout << "Keyword: " << token << endl;
            else if (isNumber(token))
                cout << "Constant: " << token << endl;
            else if (isIdentifier(token)) {
                cout << "Identifier: " << token << endl;

                if (ch != '(')
                    symbolTable.insert(token);
            } else {
                errors.push_back("Line " + to_string(lineNo) + " : " + token + " invalid lexeme");
            }
            token.clear();
        }

        if (isOperator(ch))
            cout << "Operator: " << ch << endl;

        else if (isPunctuation(ch))
            cout << "Punctuation: " << ch << endl;
    }

    cout << "\nLEXICAL ERRORS\n";
    if (errors.empty())
        cout << "None\n";
    else
        for (string e : errors) cout << e << endl;

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int i = 1;
    for (string s : symbolTable)
        cout << i++ << ") " << s << endl;

    return 0;
}

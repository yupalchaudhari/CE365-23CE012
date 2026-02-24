#include <iostream>
#include <string>
using namespace std;

class RecursiveDescentParser {
    string input;
    int pos;

    char currentToken() {
        if (pos < input.size()) return input[pos];
        return '\0';
    }

    bool consume(char expected) {
        if (currentToken() == expected) {
            pos++;
            return true;
        }
        return false;
    }

    bool parseS() {
        if (consume('a')) {
            return true;
        } else if (consume('(')) {
            if (parseL() && consume(')')) {
                return true;
            }
            return false;
        }
        return false;
    }

    bool parseL() {
        if (!parseS()) return false;
        return parseLPrime();
    }

    bool parseLPrime() {
        if (consume(',')) {
            if (!parseS()) return false;
            return parseLPrime();
        }
        return true; // epsilon
    }

public:
    RecursiveDescentParser(string str) {
        for (char c : str) {
            if (c != ' ') input.push_back(c);
        }
        pos = 0;
    }

    string parse() {
        if (parseS() && pos == input.size()) {
            return "Valid string";
        } else {
            return "Invalid string";
        }
    }
};

int main() {
    string testcases[] = {
        "a", "(a)", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)", "a)", "(a a,a a, (a,a),a)"
    };

    for (string t : testcases) {
        RecursiveDescentParser parser(t);
        cout << t << " -> " << parser.parse() << endl;
    }

    return 0;
}

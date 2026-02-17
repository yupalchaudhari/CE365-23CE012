#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

int main() {
    int num_symbols;
    int num_states;
    int initial_state;
    int num_accepting;
    string input_string;

    cout << "Number of input symbols : ";
    cin >> num_symbols;

    vector<char> symbols(num_symbols);
    cout << "Input symbols : ";
    for (int i = 0; i < num_symbols; ++i) {
        cin >> symbols[i];
    }

    cout << "Enter number of states : ";
    cin >> num_states;

    cout << "Initial state : ";
    cin >> initial_state;

    cout << "Number of accepting states : ";
    cin >> num_accepting;

    set<int> accept_states;
    cout << "Accepting states : ";
    for (int i = 0; i < num_accepting; ++i) {
        int state;
        cin >> state;
        accept_states.insert(state);
    }


    map<int, map<char, int>> transitions;

    cout << "Transition table :" << endl;
    for (int i = 1; i <= num_states; ++i) {
        for (char sym : symbols) {
            int next_state;
            cout << i << " to " << sym << " -> ";
            cin >> next_state;
            transitions[i][sym] = next_state;
        }
    }

    cout << "Input string : ";
    cin >> input_string;

    int current_state = initial_state;
    bool is_valid_input = true;

    for (char c : input_string) {
        bool valid_char = false;
        for(char s : symbols) {
            if(s == c) valid_char = true;
        }

        if (!valid_char) {
            is_valid_input = false;
            break;
        }

   
        current_state = transitions[current_state][c];
    }

 
    if (is_valid_input && accept_states.count(current_state)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}
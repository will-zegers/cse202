#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Match(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            Bracket b(next, position+1);
            opening_brackets_stack.push(b);
        }

        if (next == ')' || next == ']' || next == '}') {
            if (!opening_brackets_stack.empty()) {
                Bracket b = opening_brackets_stack.top();
                if (b.Match(next)) {
                    opening_brackets_stack.pop();
                } else {
                    std::cout << position + 1 << std::endl;
                    return 0;
                }
            } else {
                std::cout << position + 1 << std::endl;
                return 0;
            }
        }
    }

    if (opening_brackets_stack.empty()) {
        std::cout << "Success" << std::endl;
    } else {
        std::cout << opening_brackets_stack.top().position << std::endl;
    }

    return 0;
}

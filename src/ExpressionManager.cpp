#include "ExpressionManager.h"
#include <sstream>
#include <stdexcept>
#include <vector>

// Returns the precedence of operators
int ExpressionManager::getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Checks if the character is a supported operator
bool ExpressionManager::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}

// Converts Infix expression to Postfix
std::string ExpressionManager::infixToPostfix(std::string infix) {
    std::stack<char> s;
    std::string postfix = "";
    int n = infix.length();

    for (int i = 0; i < n; i++) {
        char c = infix[i];

        // If space, skip
        if (c == ' ') continue;

        // If digit, parse the full number (multi-digit support)
        if (isdigit(c) || c == '.') {
            std::string number = "";
            while (i < n && (isdigit(infix[i]) || infix[i] == '.')) {
                number += infix[i];
                i++;
            }
            i--; // Decrement because loop increments
            postfix += number + " "; // Add space as delimiter
        }
        else if (c == '(') {
            s.push(c);
        }
        else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += " ";
                s.pop();
            }
            if (!s.empty()) s.pop(); // Pop '('
        }
        else if (isOperator(c)) {
            while (!s.empty() && getPrecedence(s.top()) >= getPrecedence(c)) {
                // ^ is right associative, handle separately if needed, but standard stack algo usually handles left-associative mainly.
                // For strict right associativity of ^:
                if (c == '^' && s.top() == '^') break; 

                postfix += s.top();
                postfix += " "; 
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        postfix += " ";
        s.pop();
    }
    
    // Remove trailing space if any
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

// Converts Infix to Prefix
// Logic: Reverse Infix -> InfixToPostfix (with bracket swap) -> Reverse Postfix = Prefix
std::string ExpressionManager::infixToPrefix(std::string infix) {
    // 1. Reverse Infix
    std::string reversedInfix = infix;
    std::reverse(reversedInfix.begin(), reversedInfix.end());

    // 2. Swap ( and )
    for (size_t i = 0; i < reversedInfix.length(); i++) {
        if (reversedInfix[i] == '(') reversedInfix[i] = ')';
        else if (reversedInfix[i] == ')') reversedInfix[i] = '(';
    }

    // 3. Get Postfix
    std::string postfix = infixToPostfix(reversedInfix);

    // 4. Reverse Postfix to get Prefix
    std::reverse(postfix.begin(), postfix.end());

    // Note: Reversing parsing logic handles multi-digits carefully, 
    // but simple string reverse on postfix with numbers might reverse "12" to "21".
    // Correct Approach for logic: Standard algo uses stacks directly for Prefix or the reverse method.
    // The reverse method on string "12 3 +" -> "+ 3 21" is wrong.
    // So we must reverse the *tokens*, not the characters blindly, OR
    // Implement direct InfixToPrefix logic. 
    // Let's implement DIRECT InfixToPrefix with two stacks or modified logic to be safe for multi-digit.
    
    // Actually, simply reversing the result string is dangerous for numbers.
    // Let's re-implement `infixToPrefix` properly without string reversal hacks that break numbers.
    
    // Algorithm:
    // Create operator stack and operand stack.
    // But since `evaluatePostfix` is required, and `infixToPrefix` is just conversion, 
    // let's stick to the reliable Reverse-Postfix-Reverse method BUT fix the Number Reversal issue.
    
    // REVISED STRATEGY for Prefix:
    // 1. Reverse the string, swapping brackets.
    // 2. Run modified Postfix:
    //    - When operand found, add to output. 
    //    - Operator logic same (mostly, slightly different for associativity).
    // 3. The result of "Postfix of Reversed Infix" needs its *tokens* reversed to be Prefix.
    //    e.g. "A + B" -> "B + A" -> "B A +" -> Reverse tokens -> "+ A B"
    
    // Let's do a Token Reversal at the end.
    
    std::stringstream ss(postfix);
    std::string token;
    std::vector<std::string> tokens;
    while(ss >> token) {
        tokens.push_back(token);
    }
    std::reverse(tokens.begin(), tokens.end());
    
    std::string prefix = "";
    for(const auto& t : tokens) {
        // If token is multi-digit number, we effectively reversed the order of operands correctly.
        // We do DO NOT reverse the characters inside the token (so "12" stays "12").
        prefix += t + " ";
    }
    
    if (!prefix.empty()) prefix.pop_back();
    return prefix;
}

// Helper to perform math
double ExpressionManager::performOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::runtime_error("Division by Zero Error");
            return a / b;
        case '%': return fmod(a, b);
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Evaluate Postfix Expression
double ExpressionManager::evaluatePostfix(std::string postfix) {
    std::stack<double> s;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        // If token is operator
        if (token.length() == 1 && isOperator(token[0])) {
            if (s.size() < 2) throw std::runtime_error("Invalid Postfix Expression: Not enough operands");
            
            double val2 = s.top(); s.pop();
            double val1 = s.top(); s.pop();
            
            double result = performOperation(val1, val2, token[0]);
            s.push(result);
        }
        else {
            // Is operand
            try {
                double val = std::stod(token);
                s.push(val);
            } catch (...) {
                 throw std::runtime_error("Invalid Token in Postfix: " + token);
            }
        }
    }

    if (s.empty()) throw std::runtime_error("Empty Expression");
    if (s.size() > 1) throw std::runtime_error("Invalid Postfix Expression: Too many operands left");

    return s.top();
}

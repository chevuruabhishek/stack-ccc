#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H

#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>

/**
 * @class ExpressionManager
 * @brief Handles conversion and evaluation of algebraic expressions using Stack.
 * 
 * Capabilities:
 * - Infix to Postfix Conversion
 * - Infix to Prefix Conversion
 * - Postfix Expression Evaluation
 * 
 * Supports: +, -, *, /, %, ^, ()
 */
class ExpressionManager {
public:
    /**
     * @brief Converts an infix expression to a postfix expression.
     * @param infix The infix expression string.
     * @return The converted postfix expression string.
     */
    std::string infixToPostfix(std::string infix);

    /**
     * @brief Converts an infix expression to a prefix expression.
     * @param infix The infix expression string.
     * @return The converted prefix expression string.
     */
    std::string infixToPrefix(std::string infix);

    /**
     * @brief Evaluates a postfix expression.
     * @param postfix The postfix expression string.
     * @return The numerical result of the evaluation.
     */
    double evaluatePostfix(std::string postfix);

private:
    /**
     * @brief Helper function to return precedence of operators.
     * @param op The operator character.
     * @return Integer precedence level (higher is higher precedence).
     */
    int getPrecedence(char op);

    /**
     * @brief Helper function to check if a character is an operator.
     * @param c The character to check.
     * @return True if operator, False otherwise.
     */
    bool isOperator(char c);

    /**
     * @brief Helper function to perform arithmetic operation.
     * @param a First operand.
     * @param b Second operand.
     * @param op Operator.
     * @return Result of 'a op b'.
     */
    double performOperation(double a, double b, char op);
};

#endif // EXPRESSION_MANAGER_H

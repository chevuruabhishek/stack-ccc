#include <iostream>
#include <string>
#include <limits>
#include "ExpressionManager.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ExpressionManager manager;
    int choice;
    std::string inputExpr;

    std::cout << "==============================================\n";
    std::cout << "   Expression Converter and Evaluator Project \n";
    std::cout << "==============================================\n";

    do {
        std::cout << "\n--- MAIN MENU ---\n";
        std::cout << "1. Convert Infix to Postfix\n";
        std::cout << "2. Convert Infix to Prefix\n";
        std::cout << "3. Evaluate Postfix Expression\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            clearInput();
        }
        
        // Clear buffer before getline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 4) {
            std::cout << "Exiting... Thank you!\n";
            break;
        }

        try {
            switch (choice) {
                case 1:
                    std::cout << "Enter Infix Expression (e.g. A + B * C): ";
                    std::getline(std::cin, inputExpr);
                    std::cout << ">> Postfix: " << manager.infixToPostfix(inputExpr) << "\n";
                    break;

                case 2:
                    std::cout << "Enter Infix Expression (e.g. (A+B)^C): ";
                    std::getline(std::cin, inputExpr);
                    std::cout << ">> Prefix: " << manager.infixToPrefix(inputExpr) << "\n";
                    break;

                case 3:
                    std::cout << "Enter Postfix Expression (space separated, e.g. 10 20 +): ";
                    std::getline(std::cin, inputExpr);
                    std::cout << ">> Result: " << manager.evaluatePostfix(inputExpr) << "\n";
                    break;

                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "ERROR: " << e.what() << "\n";
        }

    } while (choice != 4);

    return 0;
}

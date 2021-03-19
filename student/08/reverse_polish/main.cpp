#include <iostream>

using namespace std;

bool is_digits(const std::string& str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";

    float operand[80] = { 0 };
    float* top = operand;
    float* empty = operand;

    string input = "";
    string operators = "+-/*";

    while (cin >> input) {

        if (input == "#") {
            if (top - 1 == empty) {
                cout << "Correct: " << *top << " is the result" << endl;
                return EXIT_SUCCESS;
            } else {
                cout << "Error: Too few operators" << endl;
                return EXIT_FAILURE;
            }
        }

        if (input.length() == 1 && operators.find(input) != string::npos) {
            if (top == empty) {
                cout << "Error: Expression must start with a number" << endl;
                return EXIT_FAILURE;
            }

            if (top - 1 == empty) {
                cout << "Error: Too few operands" << endl;
                return EXIT_FAILURE;
            }

            float opr1 = 0, opr2 = 0;

            if (input == "+") {
                cout << *top << " in +" << endl;
                opr2 = *top;
                *top = 0;
                opr1 = *(--top);
                *top = opr1 + opr2;
                cout << *top << " out +" << endl;
            }
            if (input == "-") {
                cout << *top << " in -" << endl;
                opr2 = *top;
                *top = 0;
                opr1 = *(--top);
                *top = opr1 - opr2;
                cout << *top << " out -" << endl;
            }
            if (input == "*") {
                cout << *top << " in *" << endl;
                opr2 = *top;
                *top = 0;
                opr1 = *(--top);
                *top = opr1 * opr2;
                cout << *top << " out *" << endl;
            }

            if (input == "/") {

                if (*top == 0) {
                    cout << "Error: Division by zero" << endl;
                    return EXIT_FAILURE;
                }
                cout << *top << " in /" << endl;
                opr2 = *top;
                *top = 0;
                opr1 = *(--top);
                *top = opr1 / opr2;
                cout << *top << " out /" << endl;
            }

            continue;
        }

        if (is_digits(input)) {
            *(++top) = stof(input);
            continue;
        }

        cout << "Error: Unknown character" << endl;
        return EXIT_FAILURE;
    }

    return 0;
}

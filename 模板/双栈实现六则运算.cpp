#include <iostream>
#include <stack>
#include <math.h>
#include <iomanip>
#include <string>
using namespace std;

stack<double> values;
stack<char> ops;

int precedence(char op)
{
    if (op == '+' || op == '-')return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^')return 3;
    return 0;
}

void operate()
{
    char op = ops.top();
    ops.pop();
    double b = values.top();
    values.pop();
    double a = values.top();
    values.pop();
    double newva;
    switch (op)
    {
    case '+':
        newva = a + b;
        break;
    case '-':
        newva = a - b;
        break;
    case '*':
        newva = a * b;
        break;
    case '/':
        newva = a / b;
        break;
    case '%':
        newva = (int)a % (int)b;
        break;
    case '^':
        newva = pow(a, b);
    default:
        break;
    }
    values.push(newva);
}

void evaluateExpression(string opt)
{
    int i = 0;
    while (i < opt.size())
    {
        if (opt[i] == ' ') {
            i++;
            continue;
        }
        if (opt[i] == '(') {
            ops.push(opt[i]);
        }
        else if (isdigit(opt[i])) {
            double val = 0;
            while (isdigit(opt[i])) {//需检查
                val = (val * 10) + (double)(opt[i] - '0');
                i++;
            }
            if (opt[i] == '.')
            {
                i++;
                int offset = 10;
                while (isdigit(opt[i])) {//需检查
                    val += ((double)(opt[i] - '0')) / offset;
                    offset *= 10;
                    i++;
                }
            }
            values.push(val);
            continue;
        }
        else if (opt[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(') {
                operate();
            }
            if (!ops.empty()) ops.pop(); // Pop '('
            else
            {
                cout << "ERROR IN INFIX NOTATION" << endl;
                return;
            }
        }
        else {
            switch (opt[i])
            {
            case '+':
                break;
            case '-':
                break;
            case '*':
                break;
            case '/':
                break;
            case '%':
                break;
            case '^':
                break;
            default:
                cout << "ERROR IN INFIX NOTATION" << endl;
                return;
            }
            if (ops.empty())
            {
                ops.push(opt[i]);
                i++;
                continue;
            }
            if (opt[i] == '^' && ops.top() == '^')
            {
                ops.push(opt[i]);
                i++;
                continue;
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(opt[i])) {
                operate();
            }
            ops.push(opt[i]);
        }
        i++;
    }
    while (!ops.empty())
    {
        if (values.empty() || ops.top() == '(')
        {
            cout << "ERROR IN INFIX NOTATION" << endl;
            return;
        }
        operate();
    }
    cout << fixed << setprecision(2) << values.top() << endl;
    values.pop();
    return;
}

int main()
{
    string opt;
    cin >> opt;
    evaluateExpression(opt);
}

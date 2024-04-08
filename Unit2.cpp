//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"

#include <algorithm>
#include <cctype>
#include <cassert>
#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool printStack = false;
bool printTracing = false;

void __fastcall TForm2::cbPrintStackClick(TObject *Sender)
{
	printStack = cbPrintStack->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbPrintTracingClick(TObject *Sender)
{
	printTracing = cbPrintTracing->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::AppendTextToOutput(const String &text)
{

}

// Utility function to perform an arithmetic or bitwise operation
int __fastcall TForm2::performOperation(char operation, int operand1, int operand2) {
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return pow(operand1, operand2); // Assumes pow returns int
    case '&':
        return operand1 & operand2;
    case '|':
        return operand1 | operand2;
    default:
        cerr << "Unexpected operation '" << operation << "'" << endl;
        return -1;
    }
}

// Utility Functions
inline bool __fastcall TForm2::isOperand(char c) { return isalnum(c); }
inline bool __fastcall TForm2::isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '&' || c == '|'; }
inline int __fastcall TForm2::precedence(char op) {
	if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    if (op == '&' || op == '|')
        return 0; // Adjusted to fit bitwise operators at the lowest precedence
    return -1; // Error case
}

// Function to reverse the infix expression for infix to prefix conversion
inline std::string __fastcall TForm2::reverseExpression(const string& expr) {
    string reversed;
    reversed.reserve(expr.length());
    for (int i = expr.length() - 1; i >= 0; i--) {
        if (expr[i] == '(')
            reversed += ')';
        else if (expr[i] == ')')
            reversed += '(';
        else
            reversed += expr[i];
    }
    return reversed;
}

// Function to convert infix expression to postfix
string __fastcall TForm2::InfixToPostfix(const string& infix) {
    string postfix;
    postfix.reserve(infix.length());
    stack<char> operatorStack;

    for (char c : infix) {
        if (isdigit(c) || isalpha(c)) {
            postfix += c;
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty())
                operatorStack.pop();
        } else if (isOperator(c)) {
            while (!operatorStack.empty() && precedence(c) <= precedence(operatorStack.top())) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

// Function to convert infix expression to prefix
string __fastcall TForm2::InfixToPrefix(const string& infix) {
	return reverseExpression(InfixToPostfix(reverseExpression(infix)));
}

string __fastcall TForm2::PostfixToInfix(const string& postfix) {
    stack<string> s;

    for (char c : postfix) {
        if (isOperand(c)) {
            s.emplace(1, c);
        } else {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.emplace("(" + op2 + c + op1 + ")");
        }
    }

    return s.top();
}

string __fastcall TForm2::PostfixToPrefix(const string& postfix) {
    stack<string> s;

    for (char c : postfix) {
        if (isOperand(c)) {
            s.emplace(1, c);
        } else {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.emplace(c + op2 + op1);
        }
    }

    return s.top();
}

string __fastcall TForm2::PrefixToInfix(const string& prefix) {
    stack<string> s;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isOperand(prefix[i])) {
            s.emplace(1, prefix[i]);
        } else {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.emplace("(" + op1 + prefix[i] + op2 + ")");
        }
    }

    return s.top();
}

string __fastcall TForm2::PrefixToPostfix(const string& prefix) {
    stack<string> s;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isOperand(prefix[i])) {
            s.emplace(1, prefix[i]);
        } else {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.emplace(op1 + op2 + prefix[i]);
        }
    }

	return s.top();
}

// Function to evaluate a postfix expression
int __fastcall TForm2::evaluatePostfix(const string& postfix) {
    stack<int> operandStack;

    for (char c : postfix) {
        if (isdigit(c)) {
            operandStack.emplace(c - '0');
        } else if (isOperator(c)) {
            int op2 = operandStack.top();
            operandStack.pop();
            int op1 = operandStack.top();
            operandStack.pop();
            int result = performOperation(c, op1, op2);
            operandStack.emplace(result);
        }
    }

    return operandStack.top();
}

// Function to evaluate a prefix expression
int __fastcall TForm2::evaluatePrefix(const string& prefix) {
    stack<int> operandStack;

    for (int i = prefix.length() - 1; i >= 0; --i) {
        char c = prefix[i];
        if (isdigit(c)) {
            operandStack.emplace(c - '0');
        } else if (isOperator(c)) {
            int op1 = operandStack.top();
            operandStack.pop();
            int op2 = operandStack.top();
            operandStack.pop();
            int result = performOperation(c, op1, op2);
            operandStack.emplace(result);
        }
    }

    return operandStack.top();
}

// Function to evaluate an infix expression
int __fastcall TForm2::evaluateInfix(const string& infix) {
	return evaluatePostfix(InfixToPostfix(infix));
}

// Function to convert UnicodeString (or TCaption) to std::string
std::string UnicodeToString(const System::UnicodeString& unicodeStr) {
    AnsiString ansiStr = unicodeStr; // Convert from UnicodeString to AnsiString
    return std::string(ansiStr.c_str()); // Convert from AnsiString to std::string and return
}

// Function to convert std::string to UnicodeString (or TCaption)
System::UnicodeString StringToUnicode(const std::string& stdStr) {
    return System::UnicodeString(stdStr.c_str());
}

void __fastcall TForm2::btnInfixToPrefixClick(TObject *Sender)
{
	if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editInfix->Text);
	text = InfixToPrefix(text);
	editInfixToPrefix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInfixToPostfixClick(TObject *Sender)
{
	if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editInfix->Text);
	text = InfixToPostfix(text);
	editInfixToPostfix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPrefixToPostfixClick(TObject *Sender)
{
	if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editPrefix->Text);
	text = PrefixToPostfix(text);
	editPrefixToPostfix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPrefixToInfixClick(TObject *Sender)
{
	if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editPrefix->Text);
	text = PrefixToInfix(text);
	editPrefixToInfix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPostfixToPrefixClick(TObject *Sender)
{
	if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editPostfix->Text);
	text = PostfixToPrefix(text);
	editPostfixToPrefix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnPostfixToInfixClick(TObject *Sender)
{
    if(printStack || printTracing) reOutput->Clear();
	std::string text = UnicodeToString(editPostfix->Text);
	text = PostfixToInfix(text);
	editPostfixToInfix->Text = StringToUnicode(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbInfixExampleSelect(TObject *Sender)
{
	editInfix->Text = cbInfixExample->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbPrefixExampleSelect(TObject *Sender)
{
	editPrefix->Text = cbPrefixExample->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbPostfixExampleChange(TObject *Sender)
{
	editPostfix->Text = cbPostfixExample->Text;
}
//---------------------------------------------------------------------------
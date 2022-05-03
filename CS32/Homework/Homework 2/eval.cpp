

#include <stack>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

//Function declarations
string inToOut (string infix);
void postToResult (string postfix, bool& result);
int precedence(char operate);
bool isValidExp(string infix);
bool isTorF(char hello);
bool isSymbol(char bye);

//EVALUATE
int evaluate(string infix, string& postfix, bool& result)
{
    if (!isValidExp(infix)) {
        return 1;
    }
    
    postfix = inToOut(infix);
    bool temp = false;
    postToResult(postfix, temp);
    result = temp;
    return 0;
}
//

int precedence(char operate) {
    switch(operate) {
        case '!': return 3;
        case '&': return 2;
        case '|': return 1;
        default: return 1234;
    }
}

bool isTorF(char hello) {
    switch (hello) {
        case 'T':
        case 'F':
            return true;
        default:
            return false;
    }
}

bool isSymbol(char bye) {
    switch (bye) {
        case '!':
        case '|':
        case '&':
            return true;
        default:
            return false;
    }
}


bool isValidExp(string infix) {
    //Remove spacing first
    string updatedinfix = "";
    for (int i = 0; i<infix.length(); i++) {
        switch (infix.at(i)) {
            case 'T': case 'F': case '!': case '|': case '&': case '(': case ')':
                updatedinfix += infix.at(i);
                break;
            default:
                break;
        }
    }
    //General cases
    //1. empty infix
    if (updatedinfix =="") {
        return false;
    }
    //2. empty parentheses
    for (int a = 0; a<updatedinfix.length(); a++) {
        if (updatedinfix.at(a) == '(' && a != updatedinfix.length() -1) {
            if (updatedinfix.at(a+1) == ')') {
                return false;
            }
        }
    }
    //3. General check for no. of parentheses
    int counter = 0;
    for (int b = 0; b<updatedinfix.length(); b++) {
        if (counter< 0) {
            return false;
        }
        if (updatedinfix.at(b) == '(') {
            counter++;
        }
        else if (updatedinfix.at(b) == ')') {
            counter--;
        }
    }
    if (counter != 0) {
        return false;
    }
    
    //4. Random characters
    for (int c = 0; c<updatedinfix.length(); c++) {
        switch (updatedinfix.at(c)) {
            case 'T': case 'F': case '!': case '|': case '&': case '(': case ')':
                break;
            default:
                return false;
        }
    }
    
    //Now for specific characters
    for (int j=0; j<updatedinfix.length(); j++) {
        
        //Case T or F
        if (j < updatedinfix.length() - 1 && isTorF(updatedinfix.at(j))) {
            if (isTorF(updatedinfix.at(j+1))) {
                return false;
            }
        }
        
        //Case ')'
        if (updatedinfix.at(0) == ')') {
            return false;
        }
        else if (updatedinfix.at(j) == ')' && j < updatedinfix.length() - 1) {
            if ( isSymbol(updatedinfix.at(j-1))|| isTorF(updatedinfix.at(j+1))) {
                return false;
            }
        }
        
        //Case '('
        if (updatedinfix.at(updatedinfix.length()-1) == '(') {
            return false;
        }
        else if (j > 0 && updatedinfix.at(j) == '(') {
            if ( isTorF(updatedinfix.at(j-1))|| updatedinfix.at(j+1) == '|' || updatedinfix.at(j+1) == '&') {
                return false;
            }
        }
        
        //Case '!'
        if (updatedinfix.at(j) == '!' && j==0) {
            if (updatedinfix.at(j+1) == '&' || updatedinfix.at(j+1) == '|' || updatedinfix.at(j+1) == ')') {
                return false;
            }
        }
        if (updatedinfix.at(j) == '!'){
            
            if (j>0 && isTorF(updatedinfix.at(j-1))) {
                return false;
            }
            else if (j == updatedinfix.length()-1) {
                return false;
            }
            else if (j>0 && j<updatedinfix.length()-1) {
                if (updatedinfix.at(j+1) == '&' || updatedinfix.at(j+1) == '|' || updatedinfix.at(j+1) == ')' || updatedinfix.at(j-1) == ')') {
                    return false;
                }
            }
        }
        
        //Case '&'
        if (updatedinfix.at(j) == '&' && j == 0) {
            return false;
        }
        else if (updatedinfix.at(j) == '&' && j == updatedinfix.length()-1) {
            return false;
        }
        else if (updatedinfix.at(j) == '&' && j>0 && j< updatedinfix.length()-1) {
            //checking before and after the case
            if (updatedinfix.at(j-1) == '|' || updatedinfix.at(j+1) == '|' || updatedinfix.at(j-1) == '(' || updatedinfix.at(j+1) == ')' || updatedinfix.at(j-1) == '!' || updatedinfix.at(j-1) == '&') {
                return false;
            }
        }
        
        //Case '|'
        if (updatedinfix.at(j) == '|' && j == 0) {
            return false;
        }
        else if (updatedinfix.at(j) == '|' && j == updatedinfix.length()-1) {
            return false;
        }
        else if (updatedinfix.at(j) == '|' && j>0 && j< updatedinfix.length()-1) {
            if (updatedinfix.at(j-1) == '&' || updatedinfix.at(j+1) == '&' || updatedinfix.at(j-1) == '(' || updatedinfix.at(j+1) == ')' || updatedinfix.at(j-1) == '!' || updatedinfix.at(j-1) == '|') {
                return false;
            }
        }
        
    }
    return true;
}
 

//Function implementations
string inToOut (string infix) {
    stack <char> Operator;
    string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix.at(i);
        switch (ch) {
            case ' ':
                break;
            case 'T':
            case 'F':
                postfix += ch;
                break;
            case '(':
                Operator.push(ch);
                break;
            case ')':
                while (Operator.top() != '(') {
                    postfix += Operator.top();
                    Operator.pop();
                }
                Operator.pop();
                break;
            case '!':
            case '&':
            case '|':
                while (!Operator.empty() && Operator.top() != '(' && precedence(ch) <= precedence(Operator.top())) {
                    postfix += Operator.top();
                    Operator.pop();
                }
                Operator.push(ch);
                break;
        }
    
    }

    while (!Operator.empty()) {
         postfix += Operator.top();
        Operator.pop();
    }
    return postfix;
}
void postToResult(string postfix, bool& result) {
    stack <bool> operand;
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix.at(i);
        if (ch == 'T') {
            operand.push(true);
        }
        else if (ch == 'F') {
            operand.push(false);
        }

        else {

            
            //Apply operation
            if (ch == '&') {
                char oper2 = operand.top();
                operand.pop();
                char oper1 = operand.top();
                operand.pop();
                operand.push(oper1 && oper2);
            }
            else if (ch == '|') {
                char oper2 = operand.top();
                operand.pop();
                char oper1 = operand.top();
                operand.pop();
                operand.push(oper1 || oper2);
            }
            else {
                char oper3 = operand.top();
                operand.pop();
                operand.push(!oper3);
            }
        }
    }
    result = operand.top();
}

//Main testing

int main() {
    //Given test
    string pf;
    bool answer;
    
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T&&F", pf, answer) == 1);
    assert(evaluate("T||F", pf, answer) == 1);
    assert(evaluate("TF|", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
                           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    
    assert(evaluate("T", pf, answer) == 0 && answer == true);
    assert(evaluate("(F)", pf, answer) == 0 && answer == false);
    assert(evaluate("T&(F)", pf, answer) == 0 && answer == false);
    assert(evaluate("T & !F", pf, answer) == 0 && answer == true);
    assert(isValidExp("!(F|T)") == true );
    assert(evaluate("!(F|T)", pf, answer) == 0);// && answer == false);
    assert(evaluate(" !F|T", pf, answer) == 0 && answer == true);
    assert(evaluate("T|F&F", pf, answer) == 0 && answer == true);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 && answer == true);
    
    
    //own test
    assert(isValidExp("T F") == false);
    assert(isValidExp("") == false);
    assert(isValidExp("()") == false);
    assert(isValidExp("())") == false);
    assert(isValidExp("T+F") == false);
    assert(isValidExp("TFabc") == false);
    assert(isValidExp("T!F") == false);
    assert(isValidExp("T&F!F") == false);
    assert(isValidExp("(T&F)!F") == false);
    assert(isValidExp("(T)!F") == false);
    assert(isValidExp("(T&F)&F") == true);
    assert(isValidExp("(T&F!)") == false);
    cout << "Passed";
    
    //anderson's tests
    string cases[57] = {
        "", "()", "(())", ")(", "))((",
        "(T", "T)", "((T|F)", "(T|F))",
        ")T(", ")F(", "))T((", "))F((",
        "TT", "TF", "FT", "FF", "TTT", "TTF", "TFT", "FTT", "TFF", "FFT", "FTF", "FFF",
        "T&&T", "T&|F", "T|&F", "T!&F", "T!|F", "T!!F",
        "&", "&T", "&F", "|", "|T", "|F", "T&", "F&", "T|", "F|",
        "(&T&T)", "(|T&T)", "(T&T!)", "(T&T&)", "(T&T|)", "(T&T)!",
        "(&T)", "(&F)", "(|T)", "(|F)",
        "T!T", "T!F", "F!T", "F!F",
        "T!", "F!"
    };
    string postfix = "";
    bool result = false;
    for (string c : cases)
    {
        cout << "Case: " << c << endl;
        assert(evaluate(c, postfix, result) == 1);
        assert(result == false);
    }
}


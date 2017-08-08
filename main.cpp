#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h> /* atoi */

class Token
{
    public:
        std::string text;
        std::string type;
        Token(){};
        Token(std::string token_text, std::string token_type)
        {
            text = token_text;
            type = token_type;
        }
        ~Token(){}
        std::string toString()
        {
            std::string str = "Text: " + text + " Type: " + type;
            return str;
        }

};

class Interpreter
{
    public:
        Interpreter(){}
        Interpreter(std::string expr);
        ~Interpreter();

        std::string expression;
        int currentCharPosition;
        int currentTokenPosition;
        char Look;

        void Init();
        void GetChar();
        int GetNum(void);
  
        void MatchAndEat(char chr);
        int Term(void);
        int Add(void);
        int Subtract(void);
        int ArithmeticExpression(void);   
        int Factor(void);
        int Multiply(void);
        int Divide(void); 
        int IsOp(char chr);
        std::string FindOpType(char chr);
        std::vector<Token> Tokenise(std::string source);
        
    private:

};

Interpreter::Interpreter(std::string expr)
{
    expression = expr;
    currentCharPosition = 0;
    currentTokenPosition = 0;
    Init();
}
Interpreter::~Interpreter()
{
  
}

void Interpreter::Init()
{
    GetChar();
}

inline bool IsDigit(char c)
{
    return ( '0' <= c && c <= '9' );
}
void Interpreter::MatchAndEat(char chr)
{
    if(Look == chr)
    {
        GetChar();
    }
    else
    {
        std::cout << "Error: unexpeted character.!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        //exit();
    }
}

int Interpreter::Term(void)
{
    int result = Factor();
    while( (Look == '*') || (Look == '/') )
    {
        switch(Look)
        {
            case '*':
                result = result * Multiply();
                break;
            case '/':
                result = result / Divide();
                break;
            default:
                std::cout << "no matching operator found!" << std::endl;
        }
    }
    return (result);
}
int Interpreter::Factor(void)
{
    int result = 0;
    if(Look == '(')
    {
        MatchAndEat('(');
        result = ArithmeticExpression();
        MatchAndEat(')');
    }
    else
    {
        result = GetNum();
    }
    return (result);
}
int Interpreter::ArithmeticExpression(void)
{
    int result = Term();

    while( (Look == '+') || (Look == '-') )
    {
        switch(Look)
        {
            case '+':
                result = result + Add();
                break;
            case '-':
                result = result - Subtract();
                break;
            default:
                std::cout << "no matching operator found" << std::endl;

        }
    }
    return result;
}


int Interpreter::Add(void)
{
    MatchAndEat('+');
    return (Term());
}

int Interpreter::Subtract(void)
{
    MatchAndEat('-');
    return (Term());

}


int Interpreter::Multiply(void)
{
    MatchAndEat('*');
    return (Factor());
}

int Interpreter::Divide(void)
{
    MatchAndEat('/');
    return (Factor());
}

void Interpreter::GetChar()
{
    if(currentCharPosition < expression.length())
    {
        Look = expression.at(currentCharPosition);
    }
    currentCharPosition++;
}

int Interpreter::GetNum(void)
{
    int number = 0;
    std::string tempStr = "";
    if(!IsDigit(Look))
    {
        std::cout << "Error: numbers expected!" << std::endl;
    }

    while(IsDigit(Look))
    {
        tempStr = tempStr + Look;
        GetChar();
    }
    number = atoi(tempStr.c_str());
    return number;
}

int Interpreter::IsOp(char chr)
{
    return ((chr == '+') || (chr == '-') ||
            (chr == '*') || (chr == '/') ||
            (chr == '(') || (chr == ')'));
}

std::string Interpreter::FindOpType(char chr)
{
    std::string type = "UNKNOWN";
    switch(chr)
    {
        case '+':
            type = "ADD";
            break;
        case '-':
            type = "SUBTRACT";
            break;
        case '*':
            type = "MULTIPLY";
            break;
        case '/':
            type = "DIVIDE";
            break;
        case '(':
            type = "LEFT_PAREN";
            break;
        case ')':
            type = "RIGHT_PAREN";
            break;
    }
    return type;
}

std::vector<Token> Interpreter::Tokenise(std::string source)
{
    std::vector<Token> tokens;// = new std::vector<Token>();
    std::string token = "";
    std::string state = "DEFAULT";

    for(int index = 0; index < source.length(); index++)
    {
        char chr = source.at(index);
        if(state == "DEFAULT")
        {

            std::string opType = FindOpType(chr);
            if(IsOp(chr))
            {
                std::string str(1,chr);
                Token tempToken(str,opType);
                tokens.push_back(tempToken);
            }
            else if(IsDigit(chr))
            {
                token += chr;
                state = "NUMBER";
            }
        }
        else if(state == "NUMBER")
        {

            if(IsDigit(chr))
            {
                token += chr;
            }
            else
            {
                Token tempToken(token,"NUMBER");
                tokens.push_back(tempToken);
                token = "";
                state = "DEFAULT";
                index--;
            }
        }
        else
        {
            std::cout << "Error: invalid token state." << std::endl;
        }
    }
    return (tokens);
}
int main (int argc, char** argv)
{
    std::string expression = "219+341+19";
    expression += " ";
    Interpreter* tokeniser = new Interpreter();
    std::vector<Token> tokens = tokeniser->Tokenise(expression);
    for(int index = 0; index < tokens.size(); index++)
    {
        Token token = tokens[index];
        std::cout << "Type: " << token.type << " Text: " << token.text << std::endl;
    }
//    Interpreter* itpr = new Interpreter(expression);
//    std::cout << "Expression: " << expression << std::endl;

  
//    std::cout << "Calculation Result: " << itpr->ArithmeticExpression() << std::endl;
    return (0);
}

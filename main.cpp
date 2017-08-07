#include <string>
#include <iostream>

class Interpreter
{
    public:
        Interpreter(std::string expr);
        ~Interpreter();
        std::string expression;
        int currentCharPosition;
        char Look;

        void Init();
        void GetChar();
        int GetNum(void);
  
        void MatchAndEat(char chr);
        int Term(void);
        int Add(void);
        int Subtract(void);
        int ArithmeticExpression(void);    
    private:

};

Interpreter::Interpreter(std::string expr)
{
    expression = expr;
    currentCharPosition = 0;
    Init();
}
Interpreter::~Interpreter()
{
  
}

void Interpreter::Init()
{
    GetChar();
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
    return (GetNum());
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
int Interpreter::ArithmeticExpression(void)
{
    int result = Term();

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
    return result;
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
    int number = (int)Look - 48;
    GetChar();
    return number;
}

int main (int argc, char** argv)
{
    Interpreter* itpr = new Interpreter("5-2");
  
//    int firstNumber = itpr->GetNum();
//    char firstOperator = itpr->Look;
//    itpr->GetChar();
//    int secondNumber = itpr->GetNum();
/*
    std::cout << "first number: " << firstNumber << std::endl;
    std::cout << "first operator: " << firstOperator << std::endl;
    std::cout << "second number: " << secondNumber << std::endl;
    int sum = firstNumber + secondNumber;
    std::cout << "sum: " << sum << std::endl;
*/
    std::cout << itpr->ArithmeticExpression() << std::endl;
    return (0);
}

#include <iostream>
#include <cmath>
using namespace std;

class CharNode
{
    public:
        char data;
        CharNode* next;

        CharNode(char data)
        {
            this->data = data;
            this->next = NULL;
        }
};

class CharStack
{
    public:
        CharNode* head;
        CharNode* next;

        CharStack()
        {
            this->head = NULL;
            this->next = NULL;
        }

        void push(char data)
        {
            CharNode* temp = this->head;
            this->head = new CharNode(data);
            this->head->next = temp;
        }

        CharNode* pop()
        {
            if (!this->head) 
            {
                return NULL;    
            }
            CharNode* temp = this->head;
            this->head = this->head->next;
            return temp;
        }

        CharNode* peek()
        {
            if (this->head == NULL)
            {
                return NULL;
            }
            return this->head;
        }
};

class DoubleNode
{
    public:
        double data;
        DoubleNode* next;

        DoubleNode(double data)
        {
            this->data = data;
            this->next = NULL;
        }
};

class DoubleStack
{
    public:
        DoubleNode* head;
        DoubleNode* next;

        DoubleStack()
        {
            this->head = NULL;
            this->next = NULL;
        }

        void push(double data)
        {
            DoubleNode* temp = this->head;
            this->head = new DoubleNode(data);
            this->head->next = temp;
        }

        DoubleNode* pop()
        {
            if (!this->head) 
            {
                return NULL;    
            }
            DoubleNode* temp = this->head;
            this->head = this->head->next;
            return temp;
        }

        DoubleNode* peek()
        {
            if (this->head == NULL)
            {
                return NULL;
            }
            return this->head;
        }
};

double calculation(CharStack* st1, DoubleStack* st2)
{   
    double num2 = st2->pop()->data;
    double num1 = st2->pop()->data;
    double total = st1->peek()->data == '*' ? num1 * num2 : st1->peek()->data == '/' ? num1 / num2 : st1->peek()->data == '^' ? pow(num1, num2) : st1->peek()->data == '+' ? num1 + num2 : num1 - num2;
    st1->pop();
    return total;
}

double calculator(string str)
{   
    string digits = "";
    CharStack* operatorStack = new CharStack();
    DoubleStack* operandStack = new DoubleStack();

    for (int i = 0; i <= str.length(); i++)
    {    
        if ((int)str[i] < 48 || (int)str[i] == 94)
        {   
            if (digits != "")
            {
                double num = stoi(digits);
                operandStack->push(num);
                digits = "";
            }
            if (str[i] == '(')
            {
                operatorStack->push(str[i]);
                continue;
            }
            if (str[i] == ')')
            {
                while (operatorStack->peek()->data != '(')
                {
                    operandStack->push(calculation(operatorStack, operandStack));
                }
                operatorStack->pop();
            }
            else if (operatorStack->peek() != NULL)
            {   
                if (operatorStack->peek()->data == '*' || operatorStack->peek()->data == '/' || operatorStack->peek()->data == '^')
                {
                    operandStack->push(calculation(operatorStack, operandStack));
                }
                operatorStack->push(str[i]);
            }
            else
            {
                operatorStack->push(str[i]);
            }
        }
        else 
        {
            digits += str[i];
        }
    }

    operatorStack->pop();
    while (operatorStack->peek() != NULL)
    {   
        operandStack->push(calculation(operatorStack, operandStack));
    }
    return operandStack->pop()->data;
}

int main()
{
    cout << calculator("10+20+(30*20+3)*4/40") << endl;
    cout << calculator("34+5/10+2*(3/4+5)") << endl;
    cout << calculator("1+4*7-1") << endl;
    cout << calculator("2^3") << endl;
    cout << calculator("2^3+4+50/25*40+3-2") << endl;
    
    return 0;
}

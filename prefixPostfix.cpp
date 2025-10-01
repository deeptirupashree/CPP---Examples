
/***********************************************************************************************
DATA STRUCTURES ** ASSIGNMENT # 3: This progrm will convert the prefix notation from an input
file "Prefix.in" to postfix notation to an output file called "Postfix.out". The input file has
one expression per line. The expressions are made up of two types of symbols, single letter
operands and operators(+, -, *, /). There may be 0, 1 or more blanks between the symbols.
Each prefix expression from the input expression should be echo printed (to the screen). After the
program converts the input expression to its postfix equivalent, the postfix expression should be
printed to the output file, with an appropriate label.

  Written by: Deepti Sahu
  

*************************************************************************************************/

#include "DS_Assgn3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

    struct myStruct
    {
        bool flag;
        char ch;
    };

int main ()
{
  ifstream infile;
  ofstream outfile;
  infile.open ("Prefix.in");
    if (!infile)
    {
        cout<< "Can't open file." << endl;
    }
    outfile.open ("Postfix.out");

    char input[MAX_ITEMS];
    char str[MAX_ITEMS];

    int length;
    strcpy (input, " ");
    strcpy (str, " ");
    StackType <myStruct> istack;

    myStruct A;
    A.flag = false;
    A.ch = '\0';
    int i;

while (infile.getline(input, 50))
  {
    strcpy (str, input);
    cout << "Prefix:  " << str << endl;
    outfile << "Prefix:  " << str << endl;
    outfile << "Postfix:" ;

    length = strlen (str);

    for ( i= 0; i< length; i++)
        {    
        if  ( str[i] == '*' ||  str[i] == '/' ||  str[i] == '+' || str[i] == '-' )
            {       
                A.ch = str[i];
                A.flag = false;
                istack.push(A);
            }

        else if (isalpha (str[i]))
            {
                outfile << setw(3) << str[i];  // operand to output
                                              // if the operand read after flag is true
                                            // it is the second operand

                if (istack.Top().flag)
                {
                    while (istack.Top().flag == true) // when flag is on
                    {
                        if (!(istack.IsEmpty()))
                        {
                            istack.pop(A); // pop the operator out of the stack
                            outfile << setw(3) << A.ch;    // append the operator           
                            A.ch = istack.Top().ch; // now store the top operator of the stack
                                                  // in the struct
                        }                       
                    }  // end while               
                }
                else // when none of the operands of the operator processed yet
                {
                    myStruct temp;
                    if (!(istack.IsEmpty()))
                    {
                        istack.pop(temp);  // pop the operator
                        temp.flag = true;  // set corresponding flag to true
                        istack.push(temp); // push the operator back to the stack
                    }   
                }   
            }
          else if ( str[i] == ' ' || str[i] == '\t')
                ;
    } // end for
    if (!(istack.IsEmpty()))
    {
        istack.pop(A);
        outfile << setw(3) << A.ch << endl << endl; // the remaining operator is printed
    }
    else
        outfile << endl<< endl;
}// end while

infile.close();
outfile.close();

return 0;   
}

    // DS_Assgn3.h

const int MAX_ITEMS = 50; //maximum number of items on the stack


template<class ItemType> // ItemType is a data type of the items on the stack
class StackType
{
public:
    StackType ();
    bool IsEmpty() const;
    bool IsFull () const;
    void push(ItemType item);
    void pop(ItemType& item);
    ItemType Top() const;

private:
    int top;
    ItemType items [MAX_ITEMS];
};

// constructor
template <class ItemType>
StackType<ItemType>::StackType()
{
top = -1; // stack is empty
}

/**********************************************************************
Checks if the stack is empty

Precondition: Stack has been initialized.
Postcondition: if stack is empty, returns true; false otherwise

***********************************************************************/

template<class ItemType>
bool StackType <ItemType>::IsEmpty() const
{
return (top == -1); 
}

/**********************************************************************
Checks if the stack is full

Precondition: Stack has been initialized.
Postcondition: if stack is full, returns true; false otherwise

********************************************************************/

template<class ItemType>
bool StackType <ItemType>::IsFull() const
{
return (top == MAX_ITEMS - 1);
}


/**********************************************************************
Adds newItem to the top of the stack

Precondition: Stack has been initialized.
Postcondition: put the newItem on the top of the stack

********************************************************************/

template<class ItemType>
void StackType <ItemType>::push(ItemType newItem)
{
    top++;
    items[top] = newItem;
}


/**********************************************************************
Removes the top item from the stack.

Precondition: Stack has been initialized.
Postcondition: if stack is empty, returns true; false otherwise

**********************************************************************/

template<class ItemType>
void StackType <ItemType>::pop(ItemType& newItem)
{
newItem = items[top];
top--;
}


/**********************************************************************
Returns a copy of the top item from the stack.

Precondition: Stack has been initialize
Postcondition: returns a copy of the top element.

*********************************************************************/

template<class ItemType>
ItemType StackType <ItemType>::Top() const
{
return items[top];
}

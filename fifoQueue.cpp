/****************************************************************************************
DATA STRUCTURE: PROGRAM #4:  This program will reimplement the FIFO queue ADT using
a c++ int data type to contain the queue elements. In other words, one integer variable
is used as a queue that can store several integers. This program also prints the contents
of the queue using a member function printq. If the queue is empty, printq has no output at all.


  Written by : Deepti Sahu
  

*****************************************************************************************/


#include <iostream.h>
#include <cmath>

typedef int ItemType;
class QueType
{
public:
    QueType ();
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    void Enqueue (ItemType newItem);
    void Dequeue ();
    int qsize (ItemType item);
    void printq();

private:
   
    int qint;  // the int that will hold the queue
};

// class constructor initializes qint to 0

QueType::QueType()
{
    qint = 0;
}

// makes the q empty by equating qint to 0

void QueType :: MakeEmpty()
{
    qint = 0;
}

// checks whether the q is empty, returns true if qint== 0, false otherwise

bool QueType::IsEmpty() const
{
    return (qint == 0);
}

/******************************************************************************
checks if the queue if full
if qint > 16777215, returns true,
(as the max val of an int is 2147483647, to make sure it won't overflow)
false other wise

  ****************************************************************************/

bool QueType::IsFull() const
{
    return ( qint > 16777215);
}

/*********************************************************************
If the q is not full, inserts an int (between 1 and 15 ) and updates
the qint by calling qsize(qint)
pre: que is initialized
post: int in the queue
*********************************************************************/

void QueType::Enqueue ( ItemType newItem )
{
    int n ;

    if ( (!(IsFull ())) && newItem >= 1 && newItem <= 15 )
   
    {
        if ( IsEmpty () )
        {
              qint =  newItem ;
        }
        else 
        {
            n = qsize(qint);
            qint = qint + (pow(16,n)) * newItem;
        }
    }
    else
        return;       
}   


/**************************************************************
Deletes the front int from the queue and updates the qint.
pre: q has one or more ints
post: the int in the front is deleted and qint is updated
*************************************************************/

void QueType::Dequeue()
{
  int first_val;
  first_val = qint % 16;
  if (! (IsEmpty () ))
        qint = ( qint - first_val) / 16;
  else
      cout << "Q is empty. " << endl;
}


/***********************************************************
Finds how many ints are in the queue.
pre: qint has value
post: returns the number of ints in the queue

*********************************************************/

int QueType::qsize (ItemType qint )
{
    int count= 0;
    int r;
    r = qint % 16;
        while (r != 0)
        {
            qint = (qint -r)/16;
            r = qint % 16;
            count++;   
        }
      return count;
}


/********************************************************************
Prints the elements of the que and the int that holds the queue
pre: que has elements
post: prints the int that hold the que and the ints that are in the q

********************************************************************/


void QueType::printq()
{
    int r;
    int x;
    x = qint;
    r = x % 16;

    cout << "The int that stores the queue is : "  << x << endl;
    cout << "And the numbers in the que are :" << endl;
    if (!(IsEmpty()))
    {
        if ( r != 0)
        {
            while (r != 0)
            {
                cout << r << endl;
                x = (x-r)/16;
                r = x % 16;           
            }
        }
        else
            cout << x/16;
    }
    else
        cout << "Q is empty! " << endl;

}


int main ()
{
    QueType myQ;
    int i;
    char c = 'y';
    cout << "please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): " ;
    cin >> i;

    if ( i >= 1 && i <= 15 )
    {
        while ( (!(myQ.IsFull())) && i >= 1 && i <= 15 )
        {
            myQ.Enqueue(i);
            cout << "please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): " ;
            cin >> i;
        }
        cout << "Would you like to DeQ ? (y/n) " ;
        cin >> c;
        if ( c == 'y')
        {
            while ( (!(myQ.IsEmpty())) && c == 'y')
            {
                myQ.Dequeue();
                cout << "Do you want to Dequeue more? (y/n)";
                cin >> c;
            }
            myQ.printq();
        }
        else
            myQ.printq();
    }

  return 0;
}


/*
DATA STRUCTURES --  PROGRAM - 4  Deepti Sahu

TEST-PLANS

case-1

please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 10
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 12
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 11
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 13
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 14
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 15
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 9
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 8
Would you like to DeQ ? (y/n) y
Do you want to Dequeue more? (y/n)y
Do you want to Dequeue more? (y/n)y
Do you want to Dequeue more? (y/n)n
The int that stores the queue is : 40941
And the numbers in the que are :
13
14
15
9
Press any key to continue




case-2:

please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 1
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 3
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 5
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 7
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 9
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 11
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 13
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 15
Would you like to DeQ ? (y/n) n
The int that stores the queue is : 230257969
And the numbers in the que are :
1
3
5
7
9
11
13
Press any key to continue



case-3:

please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 5
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 1
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 2
please enter a number from 1 - 15 to enQ (OR enter anyother number to exit): 0
Would you like to DeQ ? (y/n) y
Do you want to Dequeue more? (y/n)y
Do you want to Dequeue more? (y/n)y
Do you want to Dequeue more? (y/n)n
The int that stores the queue is : 0
And the numbers in the que are :
Q is empty!
Press any key to continue
*/

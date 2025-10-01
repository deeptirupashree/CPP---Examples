/***************************************************************************************
Assignment#2: Data Structure: This program builds a data structure to contain information
on all products available in the grocery store. Then it prints the cash register receipt
for each customer. The inputfile is already sorted.

  Written by: Deepti Sahu
  

***************************************************************************************/

#include <iostream>
#include <fstream.h>
#include <iomanip.h>
#include "productInfo.h"

class sortItems

{
public:

    sortItems();
    bool IsFull () const;
    int calc_length() const;
    void retrieveItem (productInfo& info, bool& found);
    void insertItem (productInfo info);

private:
    int length;
    productInfo Invent_Ary[MAX_NUM];
    int currentPos;
};

// constructor, initializing length to 0, means the list is empty
sortItems::sortItems()
{
    length = 0;
}


/************************************************************************
Using binary search to find the location of the number
  Precondition: sorted list
  Postcondition: if found , copy of the element has been stored in that info
  ***************************************************************************/

void sortItems::retrieveItem(productInfo& info, bool& found)
{
    int midpoint;
    int first;
    int last = length - 1;
    int location= 0;
    first = 0;
    bool moreToSearch =  first <= last; // true when first <= last
                                        // false otherwise
    found = false;

    while (moreToSearch && !found)
    {
        midpoint = (first + last )/2;
        switch (info.comparedTo(Invent_Ary[midpoint]))
            {
                case LESS    :    last = midpoint - 1;
                                moreToSearch = first <= last;
                                break;
                case GREATER :  first = midpoint + 1;
                                moreToSearch = first <= last ;
                                break;

                case EQUAL    :  found = true;
                                info = Invent_Ary[midpoint];
                                break;
        }
    }
}

/***************************************************************************
  Adds items to the list
  Precondition: list is sorted
  Postcondition: Adds info in the list and checks if there aren't any duplicate number
********************************************************************************/

void sortItems::insertItem(productInfo info)

{
    bool moreToSearch;
    int location= 0;
    int index;

    moreToSearch = (location < length);

    while (moreToSearch)
    {
        switch (info.comparedTo(Invent_Ary[location]))
        {
          case LESS : moreToSearch = false;
                      break;
          case GREATER: location++;
                      moreToSearch = (location < length);
                      break;
          case EQUAL: cout << "Error! Duplicate product number." << endl;
                      return;
        }
    }
    for (index = length; index > location; index--)
        Invent_Ary[index] = Invent_Ary[index-1];
   
    Invent_Ary[location] = info; // stores the info after location is found by shifting index
    length++;
}

int main ()
{

  ifstream infile;
  ofstream outfile;

  productInfo temp;
  sortItems store_data;
  int i=0; // to keep track of max item
  int num;
  char name[12];
  double p_item;
  char t_n;
  int input_num; // from the user
  int quantity ;
  double total_cost;
  double total;
  double subtotal;
  char input_char = 'Y';
  int count= 0; // to keep track of customer number
  double tax;
  double total_tax;
  bool found_num = false; // bool to match key

  infile.open("Invent.dat"); // open input file
  outfile.open("Receipts.out"); // output file
  if (!infile)
  { 
      cout << "File opening error. Program terminated.";
      return 1;
  }
  infile >> num >> name >> p_item >> t_n;
 
      while (infile && i< 50)
      {
          temp.setProduct_Num(num);
          temp.setDescription(name);
          temp.setPrice(p_item);
          temp.setTax(t_n);

          cout << num << setw(14)<< '\t' << name << setw(14) << setprecision(2)<< '\t' << p_item << '\t' << t_n << endl;
          store_data.insertItem(temp); // call insetItem function
          i++;
          infile >> num >> name >> p_item >> t_n; // reads data from input file     
      } // end while
      cout << "---------------------------------------------------------------" << endl << endl;

      do
      {
          subtotal = 0;
          total_tax = 0;
          count++;
          cout << "Enter the product number and quantity : press '0' to stop" << endl;
          cin >> input_num ; // gets num from the user
         
          outfile << "Customer - " << count << endl;
          outfile << "=============" << endl;

          while (input_num != 0)
          {
              temp.setProduct_Num (input_num);
              store_data.retrieveItem(temp, found_num) ;
              cin >> quantity; // gets quantity from the user
              if (!(quantity >0 && quantity <= 100))
                cout << "***Quantity not in the specified range.****" << endl;
              else
                  {
               
                  if (found_num == true) // if the number found
                  {
                      total_cost = temp.getPrice() * quantity; // calculate total cost for that number
                     
                      outfile << temp.getDescription() << setw(14) <<'\t' << quantity <<'\t' << "@"
                        << setw(15)<<setprecision(3)<< temp.getPrice() << setw(10) << setprecision(3)<< '\t' << total_cost;
                     
                      if (temp.getTax() == 'T')  // if 'T' calculate tax for those items
                      {
                          outfile << " TX ";
                          tax = total_cost * TAX;
                          total_tax = total_tax + tax;
                      }
                      outfile << endl;
                     
                    subtotal = subtotal + total_cost;
                    total = total_tax + subtotal;   
                  }
                  else
                      outfile << "**item ****" <<input_num << "***** not in the inventory ***" << endl;
                    // if found is false, there is no matching, hence print the above mesg
              }
              cin >> input_num; 
          }   

      outfile << "--------------------------------------------------------------------------" << endl;
      outfile << "                              Subtotal    " << setw(14) << setprecision (4) << subtotal << endl;
      outfile << "                              Tax        " << setw(14) << setprecision (2) << total_tax << endl;
      outfile << "--------------------------------------------------------------------------" << endl;
      outfile << "                              Total      " << setw(14) << setprecision (4) << total << endl<< endl;
      outfile << "--------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx------------------------" << endl;
      cout << "------------------------------------------------------------------------------" << endl<<endl;

      cout << "Do you want to proceed with another customer? (Y/N)" ;
      cin >> input_char;
      if (input_char == 'N')
          cout << "Your receipt is printing .... " << endl;
     
  } while (input_char == 'Y'); // keeps processing until the user enters 'N'
  return 0;   
}

//headerfile productInfo.h

#include <fstream>

const int MAX_NUM = 50;
enum RelationType { LESS, GREATER, EQUAL};
const double TAX = 0.075;

class productInfo
{
public:
    productInfo();
    RelationType comparedTo (productInfo) const;
    int getproduct_num ()  { return product_number;} // accessor function
    void setProduct_Num (int pnum){ product_number = pnum;} // to access private members
    char* getDescription () { return description;} // to access private members
    void setDescription (char* dscr){strcpy (description, dscr);} // accessor function
    double getPrice() { return price;} // accessor function
    void setPrice (float p) { price = p; } // accessor function
    char getTax (){ return t; } // accessor function
    void setTax (char c) { t = c;} // accessor function

private:
    int product_number; // member variable
    char description[12]; // member variable
    double price; // member variable
    char t; // member variable
   
};






// productInfo.cpp


#include "productInfo.h"

// constructor of productIfo
productInfo::productInfo()
{
}

//************************************************************************************
// Definition of the comparedTo method
// compares the input number with the existing number and returns appropriate enum type
// used for inserting and retrieving methods
//***********************************************************************************

RelationType productInfo :: comparedTo (productInfo otherItem) const

{
    if ( product_number < otherItem.product_number )
        return LESS;
    else if (product_number > otherItem.product_number )
        return GREATER;
    else return EQUAL;
}

12345    milk            1.99    T
13246    butter            2.59    N
14236    shell            7.99    N
15421    tissue          6.69    T
15523    juice              3.25    T
12345  surf            9.99      T
16543    notebook        0.99    T
21134    candy            1.99    T
23414    yogurt            2.99    T
24332    frozen            1.99    N



Customer - 1
=============
milk                2    @          1.99            3.98 TX
tissue                2    @          6.69            13.4 TX
**item ****15423***** not in the inventory ***
juice                2    @          3.25            6.5 TX
--------------------------------------------------------------------------
                              Subtotal            23.86
                              Tax                    1.8
--------------------------------------------------------------------------
                              Total                25.65

--------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx------------------------
ASSIGNMENT # 2  DATA STRUCTURE  DEEPTI SAHU
____________________________________________

Input File: Invent.dat

12345    milk            1.99    T
13246    butter            2.59    N
14236    shell            7.99    N
15421    tissue          6.69    T
15523    juice                  3.25    T
12345  surf                9.99      T
16543    notebook        0.99    T
21134    candy            1.99    T
23414    yogurt            2.99    T
24332    frozen            1.99    N

*****************
TESt #1
***********
OUTPUT ON SCREEN
******************

12345                  milk                    2      T
13246                  butter                  2.6    N
14236                  shell                  8      N
15421                  tissue                  6.7    T
15523                  juice                  3.3    T
12345                  surf                    10      T
Error! Duplicate product number.
16543                  notebook                0.99    T
21134                  candy                  2      T
23414                  yogurt                  3      T
24332                  frozen                  2      N
---------------------------------------------------------------

Enter the product number and quantity : press '0' to stop
12345 2
14236 0
***Quantity not in the specified range.****
14236 1
32112 3
0
------------------------------------------------------------------------------

Do you want to proceed with another customer? (Y/N)Y
Enter the product number and quantity : press '0' to stop
13246 2
21134 3
23414 1
0
------------------------------------------------------------------------------

Do you want to proceed with another customer? (Y/N)N
Your receipt is printing ....
Press any key to continue


********************
Receipt.out
******************
Customer - 1
=============
milk                2    @          1.99            3.98 TX
shell                1    @          7.99            7.99
**item ****32112***** not in the inventory ***
--------------------------------------------------------------------------
                              Subtotal            11.97
                              Tax                    0.3
--------------------------------------------------------------------------
                              Total                12.27

--------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx------------------------
Customer - 2
=============
butter                2    @          2.59            5.18
candy                3    @          1.99            5.97 TX
yogurt                1    @          2.99            2.99 TX
--------------------------------------------------------------------------
                              Subtotal            14.14
                              Tax                  0.67
--------------------------------------------------------------------------
                              Total                14.81

--------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx------------------------


************************************************
TESt #2
****************************************************


OUTPUT SCREEN
********************


Enter the product number and quantity : press '0' to stop
12345 2
15421 2
15423 2
15523 2
0
------------------------------------------------------------------------------

Do you want to proceed with another customer? (Y/N)N
Your receipt is printing ....
Press any key to continue

************************
Receipt.out
*********************

Customer - 1
=============
milk                2    @          1.99            3.98 TX
tissue                2    @          6.69            13.4 TX
**item ****15423***** not in the inventory ***
juice                2    @          3.25            6.5 TX
--------------------------------------------------------------------------
                              Subtotal            23.86
                              Tax                    1.8
--------------------------------------------------------------------------
                              Total                25.65

--------------xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx------------------------

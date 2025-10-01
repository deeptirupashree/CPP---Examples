/*****************************************************************************
 This program uses recurssion to print character. Recursion is calling
a function from the same function.
The first recursive C++ function, writeLine that writes a character repeatedly 
to form a line of n characters.
The second recursive C++ function, writeBlock, that uses writeLine to write m 
lines of n characters each.
All input and output is from the main function. 


	Written by:  Deepti Sahu
	
*****************************************************************************/

#include <iostream>
#include <iomanip> // for setw

using namespace std;

void writeLine(char ch, int n);
void writeBlock(char ch, int row, int column);

int main()

{

	int row;
	int column;
	char symbol = '*';

	cout << "Enter the symbol to be entered: ";
  cin >> symbol;

  cout << "Enter the number of columns: ";
  cin >> column;

	cout << "Enter the number of rows: ";
	cin >> row;

	cout << "    Line Printed  " << endl;
	cout << setw(10);
  writeLine ( symbol, column);
	cout << endl;

  cout << endl << "    Block Printed  " << endl;
  writeBlock ( symbol, row, column);

	return 0;

}

void writeLine(char symbol, int column)

{

	if ( column > 0)

		{
		   cout << symbol;
			 writeLine ( symbol, column-1 );
	}
}

void writeBlock(char symbol, int row, int column)

{
cout << setw(10);
	if (row > 0)

		{
		  if (column > 0)

			{
				cout << symbol;
				writeLine (symbol, column-1);
			}
    cout << "\n";
		writeBlock(symbol, row-1, column);
		}
}




  


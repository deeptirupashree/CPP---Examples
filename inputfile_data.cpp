
/***************************************************************************************
Data Structures : This program will get a filename from the input, the inputfile must
be a syntactically correct C++ program. Then it'll print all assignment statements and 
the variables (only) in the RHS and LHS next to it. The output is printed to a file called
"parse.out".

  written By: Deepti Sahu
  

***************************************************************************************/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctype.h>

using namespace std;

char *remove_Doublequote (char *);
void getleftrightstr (char *, ofstream &outfile);
void processleftstr (char *, ofstream &outfile);
void processrightstr (char *, ofstream &outfile);
char* remove_comment (char* );

int main()

{		
  ifstream infile;
  ofstream outfile;
  char filename[80];
  cout << "Enter a file name: " ;
  cin >> filename;

  infile.open(filename);

  outfile.open ("parse.out", ios::out);
  char str[256];
  char tempstr[256];
  char newstr[256];

  if (!infile)

  {  
	  cout << "File opening error. Program terminated.";
      return 1;
  }
  outfile << "Assignment statement" << setw(30) << " LHS " << setw(10) << " RHS " << endl << endl;

  while (infile.getline(str, 256))
  {
	 strcpy(newstr, remove_comment(str)); // newstr has string before '//'
	 strcpy(tempstr, remove_Doublequote(newstr)); // tempstr stores the string outside " "

	 if (strchr(tempstr, '=') != NULL ) // strchr locates the first occurence of '=' in tempstr
	 {
		outfile << newstr; // prints the assignment statement
		getleftrightstr ( tempstr, outfile ); 
		outfile << endl;
	 }
  } 
  
  infile.close();
  
  return 0;
}

/*********************************************************************************
This function will remove comment part of a statement (after '//' in the program.)

precondition:input file/ string 
postcondition: string is free from all comments (written // ..)

*********************************************************************************/

char* remove_comment(char* str)

{
	int i=0;
	int j=0;
	static char assignstr[256]; // even if it leaves the function, it retains its value

	while (str[i] != '\0')
		{
				assignstr[j++] = str[i];

				if (str[i] == ';')// takes char upto ';'
					break;
				i++;
		}
	assignstr[j] = '\0';
	
	return assignstr;
}

/*****************************************************************************************
This function will remove the portion of the statement that is within a doublequote.

precondition: string without comment
postcondition: the file/string is free from the commented part written within doublequotes

******************************************************************************************/

char *remove_Doublequote (char* str)

{
	static char buffer[256];  // even if it leaves the function, it retains its value
	int i, j;
	bool findoublequote = false;
	i=0;
	j=0;
	while (str[i] != '\0')
	{
		if ( str[i]!= '"')
			{
				if (findoublequote == false) 
				{
				buffer[j] = str[i]; // all char outside '"' is copied to buffer from str
				j++;
				}
			}
		else
			findoublequote = (!findoublequote); 
			
			i++;
	}
		buffer[j] = '\0';
		return buffer; // return the string outside the  " "
}

/********************************************************************************
This function gives the left and the right variables.
precondition: strings having equal sign (no quotes or comments)
postcondition: gets left and right variables

*********************************************************************************/

void getleftrightstr (char* str, ofstream &outfile)

{
	char sl[256], sr[256];

	strcpy(sl, strtok(str, "=")); // strings before '=' copied to sl
	strcpy(sr, strtok(NULL, "="));  // strings after '=' copied to sr

	processleftstr(sl, outfile);
	processrightstr(sr, outfile);
}


/*******************************************************************************
This function gets the left variable
precondition: string with equal sign
postcondition: leftvariable printed to outfile

********************************************************************************/

void processleftstr(char *str, ofstream &outfile) 

{	
	char* tempvariable;
	char leftvariable[256];

	tempvariable = strtok(str, " "); // tokenizes space to get rid of the datatype 	
	while ( tempvariable != NULL ) 
	{
		strcpy (leftvariable, tempvariable); // the last string will be copied to "leftvariable",
		                                 // which is the variable when it finally comesout of the loop
		tempvariable = strtok (NULL, " ");
	}
	outfile << setw(30) << leftvariable << setw(10);
}


/*****************************************************************************
This function gets all right variables
precondition: string (assignment statement)
postcondition: right variables printed out with , to the outfile

******************************************************************************/

void processrightstr (char *str, ofstream &outfile)

{
	char variablename [256];

	int i = 0;
	int j = 0;

	bool firstrightvar = true;

	while (str[i] != '\0' )
	{
		if (isalnum ( str[i] ))
		{
			variablename[j] = str[i];
			j++;
		}
	
		else 
		{
		  if ( isspace (str[i]) )
              ;
		  else if ( str[i] == ')' )
			  ;
		  else if ( str[i] == '(' ) 
		  {
			 variablename[0] = '\0';
			 j = 0;
		  }

		 else 
		 {
			 if (isdigit (variablename[0]))
				 ;
			 else
			 {
				variablename[j] = '\0';

				if (strlen(variablename) != 0) {
					if (firstrightvar)
						firstrightvar = false;
					else
						outfile << ", " ;
					outfile << variablename;
				}
			 }
			 variablename[0] = '\0';
			 j = 0;
		 }
		}
	   i++;
	}
}



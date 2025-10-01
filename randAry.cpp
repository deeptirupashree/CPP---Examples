/*  ARRAYS: IN THE GIVEN CONDITION AN ARRAY OF 100 RANDOM NUMBERS IN THE RANGE 1.....999, THIS PROGRAM WILL
A. PRINT THE ARRAY TEN VALUES TO A LINE. MAKE SURE THAT THE VALUES ARE ALLIGNED IN ROWS
B. PRINT THE ODD VALUES, TEN TO A LINE
C. PRINT THE VALUES AT THE ODD NUMBERED INDEX LOCATIONS, TEN TO A LINE
D. RETURN A COUNT OF THE NUMBER OF EVEN VALUES
E. RETURN THE SUM OF ALL VALUES IN THE ARRAY
F. RETURN THE LOCATION OF THE SMALLEST VALUE IN THE ARRAY
G. RETURN THE LOCATION OF THE LARGEST VALUE IN THE ARRAY
H. COPY ALL POSITIVE VALUES TO A NEW ARRAY. THEN USE PROCESS "A" ABOVE TO PRINT THE NEW ARRAY
I. COPY ALL NEGATIVE VALUES TO A NEW ARRAY. THEN USE PROCESS "A" ABOVE TO PRINT THE NEW ARRAY
( IF THE RANDOM NUMBER IS EVENLY DIVIDED BY 3 0R 7, STORE IT AS A NEGATIVE NUMBER )

  WRITTEN BY: DEEPTI SAHU
   */



#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARY_SIZE 100
#define    RAND_LIMIT 999


void getRand ( int list [], int n);
void printLine (int list [] );
int testOdd ( int );
void printOdd ( int list[]);
void printOdd_Index ( int list[] );
int  countEven (int list []);
int calcSum ( int list []);
int getSmallest_Numloc( int list []);
int getLargest_Numloc ( int list []);
int getNeg ( int );
void copyNew_Arraypos ( int list [], int poslist [] );
void copyNew_Arrayneg ( int list [], int neglist [] );


int main (void)


{
 
   
    int list[ARY_SIZE];
    int new_NegArray [ARY_SIZE];
    int new_PosArray [ARY_SIZE];
   

    printf ("\n The 100 values in the array are  : \n\n");

    getRand ( list, ARY_SIZE );   
   
    printLine ( list );

    printOdd ( list );

    printOdd_Index (list);

    printf ("\n\n Total Even Number = %d\n ", countEven (list ));
   
    printf ("\n Sum of all values in the array is = %d\n ", calcSum ( list ));

    printf ("\n Location of the Smallest value in the Array = %d \n", getSmallest_Numloc ( list ));

    printf ("\n Location of the Largest value in the Array = %d \n", getLargest_Numloc ( list ) );

    copyNew_Arraypos (list,  new_PosArray );

    printf("\n\n New Array of All Positive numbers \n\n");

    printLine (new_PosArray);

    copyNew_Arrayneg ( list,  new_NegArray);

    printf("\n\n New Array of All Negative numbers \n\n");

    printLine (new_NegArray);

    printf ("\n\n        **** End ****                  \n");


    return 0;

}

/*===================================================================================================================

***** This fuction will get a random number from 1 to 999 *****


  pre: int list[],
  post: returns random numbers from 1 to 999 and sorts out the positive and -ve numbers by calling the getNeg function

==================================================================================================================== */


void getRand (int list [ ], int n )

{
   
    int i;

    srand ( time (NULL) ); /* shoul be called only once */
   
    for ( i = 0; i < n; i++)

      list [i] = getNeg ( rand () % RAND_LIMIT + 1) ;

    return;
}


/*===================================================================================================================

  **** This function will print all 100 random numbers ten per line ****

  pre: 100 random numbers from 1 to 999, sorted positive and negative
  post: prints all 100 random numbers 10 per line 
 
====================================================================================================================*/


void printLine ( int list [] )

{
    int count;
    int j = 0;
   
    for ( count =0; count < ARY_SIZE; count++ )
    {
        if ( list [count] != 0)
        {
          printf ("%5d", list [count]);

          j++;
        }

        if ( j == 10 )
        {
            printf ("\n");
            j = 0;
        }
    }

return;
}

/*===============================================================================================================

**** This fuction will print all odd numbers in the list ****

      pre: 100 Ramdom numbers printed
      post: prints all odd numbers 10 per line by calling the testOdd function. If the testOdd function
            returns 1, then the number is odd

==================================================================================================================== */


void printOdd ( int list[] )

{
    int count;
    int j = 0;
    int odd;

    printf ("\n **** The ODD numbers are : *****\n\n");

    for ( count =0; count < ARY_SIZE; count++ )
    {
       
        odd = testOdd (list [count]);

            if ( odd == 1 || odd == -1 )
            {
                printf ("%5d", list [count] );

                j++;
            }


            if ( j == 10 )
            {
                printf ("\n");
                j = 0;
            }
    }

    return;

}

/*======================================================================================================================

**** This function returns the remainder after dividing a number by 2 ****

  pre: a random number
  post: returns the remainder after dividing by 2

======================================================================================================================= */


int testOdd ( int num )
{
    int odd;

    odd = num % 2;

    return odd;
}

/*=======================================================================================================================

**** This function prints the values which are at the odd numbered index location, ten per line ****

  pre: 100 random numbers
  post: prints the values which are at the odd numbered index location

======================================================================================================================= */


void printOdd_Index ( int list [])

{
    int count;
    int j = 0;
   
    printf ("\n\n Values in the odd numbered index are:\n\n");

    for ( count =1; count < ARY_SIZE; count += 2)
    {
        printf ("%5d", list [count]);

        j++;

        if ( j == 10 )
        {
            printf ("\n");
            j = 0;
        }

    }

  return;
}


/*===================================================================================================================

**** This function will count the total number of even numbers in the 100 random numbers ****

  pre: 100 random numbers, odd numbers sorted out
  post: counts the total number of even numbers in the array by calling the testOdd function again.
        if the remainder is 0, it is an even number

======================================================================================================================= */


int countEven (int list [])

{

    int even;
    int count;
    int j = 0;


    for ( count =0; count < ARY_SIZE; count++ )

    {   
        even = testOdd (list [count]);

            if ( even == 0)

                j++;
    }


    return j;

}


/*======================================================================================================================

**** This function calculates the sum of all 100 numbers in the array ****   

  pre: 100 positive and negative random numbers
  post: returns the sum of all hundred randon numbers

======================================================================================================================= */


int calcSum ( int list [] )

{
    int count;
    int sum = 0;
   
    for ( count =0; count < ARY_SIZE; count++ )

        sum = sum + list[ count];

    return sum;
}


/*======================================================================================================================

**** This function gets the location of the smallest value in the array ****

  pre: 100 positive and negative random numbers, list [100]
  post: returns the location of the smallest value in the array 

========================================================================================================================*/


int getSmallest_Numloc ( int list [])

{

    int count;
    int smallest;
    int smallest_Index =0;
   
    smallest = list [0];
   
    for ( count =0; count < ARY_SIZE; count++ )

    {
        if ( list[count] < smallest )
        {
          smallest = list [count];
          smallest_Index = count;
        }

    }

    return smallest_Index;
}


/*======================================================================================================================

**** This function returns the location of the largest value in the array ****

  pre: 100 random numbers, list [100]
  post: returns the location of the largest number in the array 

========================================================================================================================*/


int getLargest_Numloc ( int list [])

{

    int count;
    int largest;
    int largest_Index =0;
   
    largest = list [0];
   
    for ( count =0; count < ARY_SIZE; count++ )

    {
        if ( list[count] > largest )
        {
          largest = list [count];
          largest_Index = count;
        }

    }

    return largest_Index;
}

/*======================================================================================================================

**** This function sorts out the negative numbers in the array by evenly dividing the number by 3 or 7.****

  pre:100 Random numbers
  post: sorts out negative numbers by evenly dividing the number by 3 or 7

======================================================================================================================= */


int getNeg ( int num )

{

    {
        if (( num % 7 == 0) || ( num % 3 ==0 ))

            return ((-1) * num);
        else
            return num;
    }
}


/*=====================================================================================================================

***** This function copies all positive values to a new array and prints them 10 per line *****

  pre: Positive and negative random numbers
  post: copies all positive values to  a new array and prints 10 per line

=======================================================================================================================*/


void copyNew_Arraypos ( int list [], int poslist [] )

{

    int count;
   

    for ( count =0; count < ARY_SIZE; count++ )
    {
        if ( list[count] > 0 )
        {

            poslist [count] = list [count];
           
        }

        else

            poslist [count] = 0;
    }


    return;
}


/*=======================================================================================================================

***** This function will copy all negative values to another new array and then prints the values 10 per line****

  pre: positive and negative random numbers
  post: copies the negative values in to a new array and prints 10 values per line

========================================================================================================================*/


void copyNew_Arrayneg ( int list [], int neglist [] )

{
    int count;
   

    for ( count =0; count < ARY_SIZE; count++ )
    {
        if ( list[count] < 0 )
        {

            neglist [count] = list [count] ;
           
        }

        else

            neglist [count] = 0;
           
    }
           
return;

}

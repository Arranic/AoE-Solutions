#include <string.h>
#include <stdio.h>
char *strrev (char *string)
{
  // initialize variables
  char temp; // temp used for swapping
  int i = 0, j = strlen(string) - 1; // i is the left hand side, j is the right hand side
  
  // loop as long as the left hand pointer is to the left of the right hand pointer, or equal to it
  while (i <= j)
  {
    temp = string[i]; // put the left char in temp
    string[i] = string[j]; // put the right char in the left spot
    string[j] = temp; // put the temp char (left char) in the right spot
    i++; // move the left pointer to the next char
    j--; // move the right pointer to the previous char
  }

  return string; // reverse the string in place and return it
}

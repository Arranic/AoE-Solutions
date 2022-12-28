#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

char *number_to_string(int number)
{
  /*
    Initialize the output string. Calloc allocates memory
    and returns a pointer to it. In this case, we used the
    absolute value of the input number to use for the creation
    of the appropriate number of placeholder objects. Then we
    used sizeof(char) to ensure the placeholders were the 
    correct size to hold chars. This was stored in a c-string
    variable.
  */
  char* string = (char*)calloc(abs(number), sizeof(char));
  
  // Sprintf converts the integer to a string
  sprintf(string, "%d", number);

  // Return the converted value
  return string;
}

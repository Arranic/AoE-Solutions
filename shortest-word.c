#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

ssize_t find_short(const char *s)
{
  int count = 0, shortest = 0; // initialize counter and shortest variables
  for(unsigned long i = 0; i <= strlen(s); i++)
  {
    /*
      Iterate through the string. If the character is a space,
      or if the character is a null character ('\0'), then check
      to see if shortest has been populated yet. If so, check to
      see if count is less than shortest. If it is, shortest
      becomes count. Otherwise, if shortest is still == 0,
      this is the first word and we will store the word's count 
      in the shortest variable.
    */
    if (s[i] == ' ' || s[i] == '\0')
    {
      
      if (shortest > 0)
      {
        if (count < shortest)
        {
          // if the current word is shorter than the shortest, replace shortest
          shortest = count;
        }
      }
      else
      {
        // This is the first word since shortest is 0
        shortest = count;
      }
      count = 0; // reset the count since we hit the end of a word
    }
    else
    {
      count += 1;
    }
  }
  return shortest; // return the answer
}

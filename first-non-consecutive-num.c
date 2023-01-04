// For c the function should return false if no non consecutive numbers are found
// It should return true if one is found and the pointer arg first set to the value

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool firstNonConsecutive (const int arr[], const int length, int *first)
{
  bool flag = false;
  
  if (length == 0 || length == 1)
  {
    if (length == 1)
    {
      (*first) = arr[0];
    }
    return flag;
  }
  
  for (int i = 0; i < length; i++)
  {
    if (i == 0)
    {
      if (abs(arr[i+1] - arr[i]) == 1)
      {
        flag = false;
      }
      else
      {
        flag = true;
        (*first) = arr[i+1];
        return flag;
      }
    }
    else
    {
      if (abs(arr[i] - arr[i-1]) == 1)
      {
        flag = false;
      }
      else
      {
        flag = true;
        (*first) = arr[i];
        return flag;
      }
    }
  }
  
  return flag;
}

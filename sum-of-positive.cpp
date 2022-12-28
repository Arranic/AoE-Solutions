#include <vector>

int positive_sum (const std::vector<int> arr){
  if (arr.size() == 0)
    return 0; // meets the instruction to return 0
  
  double sum = 0.0; // initialize sum variable
  for (unsigned int i = 0; i < arr.size(); i++)
  {
    if (arr[i] >= 0)
    {
      /*
        Loop through the array. If an element is
        greater than or equal to 0, add it to the
        sum, otherwise it gets discarded.
      */
      sum += arr[i];
    }
  }
  return sum;
}

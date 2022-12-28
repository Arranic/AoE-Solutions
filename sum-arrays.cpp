#include <vector>

int sum(std::vector<int> nums) {
  double sumd = 0.0; // initialzie return variable
  for (int i = 0; i < nums.size(); i++)
  {
    // loop through each item and add it to the summation
    sumd += nums[i];
  }
  return sumd; // return the summation
}

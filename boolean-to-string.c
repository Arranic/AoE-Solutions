#include <string>

std::string bool_to_word(bool value)
{
  /*
    Shorthand if statement that returns "Yes" if the passed
    in value is true, and "No" if the passed in value is false.
  */
  return (value == true ? "Yes":"No");
}

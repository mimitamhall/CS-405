// NumericOverflows-Solution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>pair<success, value> -- if success is false, value is start, else value is start + (increment * steps)</returns>
/// 
/// Let's use the example where T is int, start is 5, increment is 3, and steps is 4
/// Initial Values: start is 5, increment is 3, steps is 4, T = int, std::numeric_limits<int>::max() = 2147483647
/// 
/// The two if statements within the for loop are overflow checks. 
/// If overflow check fails, std::make_pair() is called to return 2 values: false and the start value.
/// 
/// First iteration:
///   Initial result value: 5
///   Overflow check: if ((3 > 0) && (5 > (2147483647 - 3))) is evaluiated to false
///   Therefore, the overflow check passes & the return statement below did not ge4t executed.
///   Update result: result = 5 + 3 = 8
/// 
/// Second iteration:
///   Initial result value: 8
///   Overflow check: if ((3 > 0) && (8 > (2147483647 - 3))) is evaluiated to false
///   Therefore, the overflow check passes & the return statement below did not ge4t executed.
///   Update result: result = 8 + 3 = 11
/// 
/// Third iteration:
///   Initial result value: 11
///   Overflow check: if ((3 > 0) && (11 > (2147483647 - 3))) is evaluiated to false
///   Therefore, the overflow check passes & the return statement below did not ge4t executed.
///   Update result: result = 11 + 3 = 14  
/// 
/// Fourth iteration:
///   Initial result value: 14
///   Overflow check: if ((3 > 0) && (14 > (2147483647 - 3))) is evaluiated to false
///   Therefore, the overflow check passes & the return statement below did not ge4t executed.
///   Update result: result = 14 + 3 = 17
/// 
/// Final Results
///   After 4 iterations, the final result is 17, and no overflow occurred. Since the overflow 
///   check never triggered the return statement, the function completes and returns true and the
///   incremented final result value.
///    -- return std::make_pair(true, result);
/// 
/// 
template <typename T>
std::pair<bool, T> add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
  T result = start;

  for (unsigned long int i = 0; i < steps; ++i)
  {
    // if the maximum for this type - existing result is less then the amount to be added, its an overflow
    // FACILITATOR NOTE: if the student has something similar to the first check, it is proficient
    // FACILITATOR NOTE: if the student has something similar to the second check in addition to the first, it is exemplary
    if ((increment > 0) && (result > (std::numeric_limits<T>::max() - increment))) // result + increment would overflow
      return std::make_pair(false, start);
    if ((increment < 0) && (result < (std::numeric_limits<T>::min() - increment))) // result + increment would overflow
      return std::make_pair(false, start);
    result += increment;
  }

  return std::make_pair(true, result);
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>pair<success, value> -- if success is false, value is start, else value is start - (increment * steps)</returns>

template <typename T>
std::pair<bool, T> subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
  T result = start;

  for (unsigned long int i = 0; i < steps; ++i)
  {
    // if the minimum for this type + existing result is less then the amount to be subtracted, its an overflow
    // FACILITATOR NOTE: if the student has something similar to the first check, it is proficient
    // FACILITATOR NOTE: if the student has something similar to the second check in addition to the first, it is exemplary
    if ((decrement < 0) && (result > (std::numeric_limits<T>::max() + decrement))) // result - increment would overflow
      return std::make_pair(false, start);
    if ((decrement > 0) && (result < (std::numeric_limits<T>::min() + decrement))) // result - increment would overflow
      return std::make_pair(false, start);

    result -= decrement;
  }

  return std::make_pair(true, result);
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
  // TODO: The add_numbers template function will overflow in the second method call
  //        You need to change the add_numbers method to:
  //        1. Detect when an overflow will happen
  //        2. Prevent it from happening
  //        3. Return the correct value when no overflow happened or
  //        4. Return something to tell test_overflow the addition failed
  //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
  //
  //        You need to change the test_overflow method to:
  //        1. Detect when an add_numbers failed
  //        2. Inform the user the overflow happened
  //        3. A successful result displays the same result as before you changed the method
  //        NOTE: You cannot change anything between START / END DO NOT CHANGE
  //              The test_overflow method must remain a template in the NumericOverflows source file
  //
  //  There are more than one possible solution to this problem. 
  //  The solution must work for all of the data types used to call test_overflow() in main().

  // START DO NOT CHANGE
  //  how many times will we iterate
  const unsigned long int steps = 5;
  // how much will we add each step (result should be: start + (increment * steps))
  const T increment = std::numeric_limits<T>::max() / steps;
  // whats our starting point
  const T start = 0;

  std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
  // END DO NOT CHANGE

  std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
  auto result = add_numbers<T>(start, increment, steps);
  std::cout << "overflow=" << !result.first << " result=" << +result.second << std::endl;

  std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
  result = add_numbers<T>(start, increment, steps + 1);
  std::cout << "overflow=" << !result.first << " result=" << +result.second << std::endl;
}

template <typename T>
void test_underflow()
{
  // TODO: The subtract_numbers template function will underflow in the second method call
  //        You need to change the subtract_numbers method to:
  //        1. Detect when an underflow will happen
  //        2. Prevent it from happening
  //        3. Return the correct value when no underflow happened or
  //        4. Return something to tell test_underflow the subtraction failed
  //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
  //
  //        You need to change the test_underflow method to:
  //        1. Detect when an subtract_numbers failed
  //        2. Inform the user the underflow happened
  //        3. A successful result displays the same result as before you changed the method
  //        NOTE: You cannot change anything between START / END DO NOT CHANGE
  //              The test_underflow method must remain a template in the NumericOverflows source file
  //
  //  There are more than one possible solution to this problem. 
  //  The solution must work for all of the data types used to call test_overflow() in main().

  // START DO NOT CHANGE
  //  how many times will we iterate
  const unsigned long int steps = 5;
  // how much will we subtract each step (result should be: start - (increment * steps))
  const T decrement = std::numeric_limits<T>::max() / steps;
  // whats our starting point
  const T start = std::numeric_limits<T>::max();

  std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
  // END DO NOT CHANGE

  std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
  auto result = subtract_numbers<T>(start, decrement, steps);
  std::cout << "overflow=" << !result.first << " result=" << +result.second << std::endl;

  std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
  result = subtract_numbers<T>(start, decrement, steps + 1);
  std::cout << "overflow=" << !result.first << " result=" << +result.second << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
  std::cout << std::endl << star_line << std::endl;
  std::cout << "*** Running Overflow Tests ***" << std::endl;
  std::cout << star_line << std::endl;

  // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
  // signed integers
  test_overflow<char>();
  test_overflow<wchar_t>();
  test_overflow<short int>();
  test_overflow<int>();
  test_overflow<long>();
  test_overflow<long long>();

  // unsigned integers
  test_overflow<unsigned char>();
  test_overflow<unsigned short int>();
  test_overflow<unsigned int>();
  test_overflow<unsigned long>();
  test_overflow<unsigned long long>();

  // real numbers
  test_overflow<float>();
  test_overflow<double>();
  test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
  std::cout << std::endl << star_line << std::endl;
  std::cout << "*** Running Undeflow Tests ***" << std::endl;
  std::cout << star_line << std::endl;

  // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
  // signed integers
  test_underflow<char>();
  test_underflow<wchar_t>();
  test_underflow<short int>();
  test_underflow<int>();
  test_underflow<long>();
  test_underflow<long long>();

  // unsigned integers
  test_underflow<unsigned char>();
  test_underflow<unsigned short int>();
  test_underflow<unsigned int>();
  test_underflow<unsigned long>();
  test_underflow<unsigned long long>();

  // real numbers
  test_underflow<float>();
  test_underflow<double>();
  test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
  //  create a string of "*" to use in the console
  const std::string star_line = std::string(50, '*');

  std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

  // run the overflow tests
  do_overflow_tests(star_line);

  // run the underflow tests
  do_underflow_tests(star_line);

  std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

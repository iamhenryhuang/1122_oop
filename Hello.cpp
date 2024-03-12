/**
    * File: Hello.cc
    * Purpose: Sample program for the OOP class
    * Author: Tsai-Yen Li (li@cs.nccu.edu.tw) 8/28/96
    *         Ming-Te Chi (mtchi@cs.nccu.edu.tw) 2/20/2024
    *         (You need put your ID here as well.)
    */
  
#include <iostream>
#include <ctime>
#include "Hello.h"
 
// constant string definition
const char *kHelloMessage = "Hello, C++ World.\n";
 
/**
* A function that prints "Hello" greeting message
*/
 
void
PrintHello() {
 
  std::cout << kHelloMessage;
 
}
 
void
PrintTime() {
  // current date/time based on current system
  std::time_t now = std::time(0);
 
  // convert now to string form
  char* dt = std::ctime(&now);
 
  std::cout << "The local date and time is: " << dt << std::endl;
}
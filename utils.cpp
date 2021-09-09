/* Citation and Sources...
Final Project Milestone 5
Module: Utils
Filename: utils.cpp
Version 1.0
Author	George Petrovski
Revision History
-----------------------------------------------------------
Date            Reason
2021/08/02      First Submission
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invlid time, try agian (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   int getInt(const char* prompt)
   {
       int i = 0;
       string line;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       
       while (getline(cin, line))
       {
           int error = 0;
           try
           {
               i = stoi(line);
           }
           catch (...)
           {
               cout << "Bad integer value, try again: ";
               error = 1;
           }
           string compare = to_string(i);
           if (line.length() == compare.length())
           {
               break;
           }
           else if (error == 0)
           {
               cout << "Enter only an integer, try again: ";
           }
       }
       return i;
   }

   int getInt(
       int min,   // minimum acceptable value
       int max,   // maximum acceptable value
       const char* prompt,  // User entry prompt
       const char* errorMessage, // Invalid value error message
       bool showRangeAtError    // display the range if invalud value entered 
   )
   {
       int i = 0;
       string line;
       if (prompt != nullptr)
       {
           cout << prompt;
       }

       while (getline(cin, line))
       {
           int error = 0;
           try
           {
               i = stoi(line);
           }
           catch (...)
           {
               cout << "Bad integer value, try again: ";
               error = 1;
           }
           string compare = to_string(i);
           if (line.length() == compare.length() && i >= min && i <= max)
           {
               break;
           }
           else if (line.length() != compare.length() && error == 0)
           {
               error = 2;
               cout << "Enter only an integer, try again: ";
           }
           else if (error == 0)
           {
               if (errorMessage != nullptr)
               {
                   cout << errorMessage;
                   if (showRangeAtError)
                   {
                       cout << "[" << min << " <= value <= " << max << "]: ";
                   }

               }
           }
       }
       return i;
   }

   char* getcstr(
       const char* prompt,   // User entry prompt
       std::istream& istr,  // the Stream to read from
       char delimiter    // Delimiter to mark the end of data
   )
   {
       string Name;
       if (prompt != nullptr)
       {
           cout << prompt;
       }
       getline(istr, Name, delimiter);
       char* cstr = new char[Name.length() + 1];
       strcpy(cstr,Name.c_str());
       return cstr;
   }
   void strCpy(char* des, const char* src)
   {
       while (*src != '\0')
       {
           *des = *src;
           des++;
           src++;
       }
       *des = '\0';
   }
   int strLen(const char* s)
   {
       int s_length = 0;
       while (*s != '\0')
       {
           s_length++;
           s++;
       }
       return s_length;
   }
}
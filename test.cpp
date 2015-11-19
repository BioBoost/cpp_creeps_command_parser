#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class TMyClass
{
public:
   int DoIt(float a, char b, char c){ cout << "TMyClass::DoIt"<< endl; return a+b+c;};
   int DoMore(float a, char b, char c) const
         { cout << "TMyClass::DoMore" << endl; return a-b+c; };

   /* more of TMyClass */
};



int (TMyClass::*pt2ConstMember)(float, char, char) = NULL;




int main(void) {
  TMyClass test;

  pt2ConstMember = &TMyClass::DoIt; // note: <pt2Member> may also legally point to &DoMore

// Calling Function using Function Pointer

  (test.*pt2ConstMember)(12, 'a', 'b');

  return 0;
}
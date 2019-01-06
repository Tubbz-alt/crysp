#include <cassert>
#include <cstdio>

#include "nil.hpp"
#include "double.hpp"
#include "fixnum.hpp"
#include "float.hpp"
#include "int.hpp"


void show(T x) {
   printf("%016lX = ", x.debug_bits());
   x.print(stdout);
   putchar('\n');
}


int main(void) 
{
   show(t);
   show(nil);

   show(Double(0.0));
   show(Double(0.5));
   show(Double(1.0));
   show(Double(1023.0));
   show(Double(1.0/0.0)); // inf
   show(Double(-0.0/0.0)); // -NaN

   show(Float(0.0f));
   show(Float(0.5f));
   show(Float(1.0f));
   show(Float(1023.0f));
   show(Float(1.0f/0.0f)); // inf
   show(Float(-0.0f/0.0f)); // -NaN

   Fixnum F;
   for (int64_t i = -16; i <= 16; i++) {
       F = i;
       show(F);
       assert(F == Int(i));
   }
   show(most_positive_fixnum);
   show(most_negative_fixnum);
   show(most_positive_int);
   show(most_negative_int);
   return 0;
}

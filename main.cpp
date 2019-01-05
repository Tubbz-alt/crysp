#include <cstdio>

#include "nil.hpp"
#include "double.hpp"
#include "fixnum.hpp"
#include "float.hpp"
#include "int.hpp"


void show(T x) {
   printf("%016lX\n", x.debug_bits());
}

void show(Fixnum I) {
    printf("%ld\n", I.value());
    show(static_cast<T>(I));
}

int main(void) 
{
   T x;
   show(x);
   x = nil;
   show(x);

   Double D = 0.0/0.0;
   printf("%f\n", D.value());
   show(D);

   Fixnum I;
   for (int64_t i = -16; i <= 16; i++) {
       I = i;
       show(I);
   }
   show(most_positive_fixnum);
   show(most_negative_fixnum);
   show(most_positive_int);
   show(most_negative_int);
   return 0;
}

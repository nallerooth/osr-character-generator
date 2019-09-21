 #include <stdio.h>
 #include "lib/minunit.h"

#include "rulesets/basic_fantasy_test.h"

 int tests_run = 0;

 int foo = 7;
 int bar = 4;

 /*static char * test_foo() {*/
     /*mu_assert("error, foo != 7", foo == 7);*/
     /*return 0;*/
 /*}*/

 static char * all_tests() {
     /*mu_run_test(test_foo);*/
     mu_run_test(test_bf_character_attr_mod);
     return 0;
 }

 int main() {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("\nTests run: %d\n", tests_run);

     return result != 0;
}


 /* file: minunit.h */
#ifndef _MINUNIT_H_
#define _MINUNIT_H_

 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;

 #define pass_msg(msg) printf("> %s passed\n",msg);

 #endif // _MINUNIT_H_
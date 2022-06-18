
#ifndef ___boolean___h____
#define ___boolean___h____

/*
* Type: bool
* ----------
* This type has 两个变量, FALSE(0) 和 TRUE(1) 
* 这样做最大的好处是程序的可读性
*/

#ifdef THINK_C
   typedef int bool;
#else
#  ifdef TRUE
#    ifndef bool
#      define bool int
#    endif
#  else
#    ifdef bool
#      define FALSE 0
#      define TRUE 1
#    else
       typedef enum {FALSE, TRUE} bool;
#    endif
#  endif
#endif

#endif // #ifndef ___boolean___h____


/* ensure included only once */ 
#ifndef __EUCLID_H__ 
#define __EUCLID_H__ 
/* global v a ri a b l e s ( declared i n e u c l i d . c ) */ 
extern int x , y ; 
/* compute gcd */
int gcd ( int a , int b ) ; 
/* compute g = gcd ( a , b ) and solve ax+by=g */
int ext_euclid ( int a , int b ) ; 
#endif 

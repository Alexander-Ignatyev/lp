var x1 >=0 ;
var x2 >=0 ;
var x3 >=0 ;
var x4 >=0 ;
var x5 >=0 ;
var x6 >=0 ;
var x7 >=0 ;
var x8 >=0 ;
var x9 >=0 ;
var x10 >=0 ;
var x11 >=0 ;
var x12 >=0 ;
var x13 >=0 ;
var x14 >=0 ;
var x15 >=0 ;
var x16 >=0 ;
var x17 >=0 ;
var x18 >=0 ;
var x19 >=0 ;
var x20 >=0 ;
var x21 >=0 ;
var x22 >=0 ;
var x23 >=0 ;
maximize obj: 0.0  + 0.0 * x1   + 2.0 * x2   + 0.0 * x3   -2.0 * x4   + 0.0 * x5   + 0.0 * x6   + 2.0 * x7   + 0.0 * x8 ;
c1: x9 = 4.0  -1.0 * x1  -1.0 * x2  -2.0 * x3  + 3.0 * x4  + 3.0 * x5  -2.0 * x6  + 2.0 * x7  -3.0 * x8 ;
c2: x10 = 11.0  -2.0 * x1  + 2.0 * x2  + 2.0 * x3  -1.0 * x4  -1.0 * x5  + 3.0 * x6  -3.0 * x7  -1.0 * x8 ;
c3: x11 = 2.0  + 0.0 * x1  -3.0 * x2  + 0.0 * x3  -3.0 * x4  + 3.0 * x5  + 3.0 * x6  + 1.0 * x7  -3.0 * x8 ;
c4: x12 = 10.0  + 2.0 * x1  + 3.0 * x2  + 1.0 * x3  + 2.0 * x4  -3.0 * x5  -1.0 * x6  + 0.0 * x7  -2.0 * x8 ;
c5: x13 = 13.0  + 0.0 * x1  + 1.0 * x2  + 1.0 * x3  + 2.0 * x4  -2.0 * x5  + 3.0 * x6  + 0.0 * x7  -3.0 * x8 ;
c6: x14 = 8.0  + 1.0 * x1  + 2.0 * x2  -2.0 * x3  + 1.0 * x4  -3.0 * x5  + 1.0 * x6  + 1.0 * x7  + 0.0 * x8 ;
c7: x15 = 3.0  + 1.0 * x1  -3.0 * x2  + 0.0 * x3  -2.0 * x4  -3.0 * x5  -1.0 * x6  -1.0 * x7  + 0.0 * x8 ;
c8: x16 = 15.0  + 3.0 * x1  + 1.0 * x2  -2.0 * x3  + 0.0 * x4  + 0.0 * x5  + 2.0 * x6  -2.0 * x7  -2.0 * x8 ;
c9: x17 = 2.0  -3.0 * x1  + 2.0 * x2  + 1.0 * x3  + 1.0 * x4  + 2.0 * x5  + 0.0 * x6  + 1.0 * x7  -2.0 * x8 ;
c10: x18 = 7.0  + 3.0 * x1  -3.0 * x2  -2.0 * x3  -2.0 * x4  + 1.0 * x5  + 0.0 * x6  -2.0 * x7  -2.0 * x8 ;
c11: x19 = 11.0  -3.0 * x1  -1.0 * x2  + 1.0 * x3  + 0.0 * x4  + 3.0 * x5  -1.0 * x6  + 0.0 * x7  -1.0 * x8 ;
c12: x20 = 11.0  -2.0 * x1  + 0.0 * x2  -2.0 * x3  -3.0 * x4  -2.0 * x5  + 2.0 * x6  + 0.0 * x7  -3.0 * x8 ;
c13: x21 = 11.0  + 3.0 * x1  -1.0 * x2  + 2.0 * x3  -2.0 * x4  -3.0 * x5  -2.0 * x6  + 1.0 * x7  -3.0 * x8 ;
c14: x22 = 15.0  -3.0 * x1  + 0.0 * x2  -2.0 * x3  + 0.0 * x4  -1.0 * x5  + 3.0 * x6  + 1.0 * x7  + 1.0 * x8 ;
c15: x23 = 15.0  -2.0 * x1  + 0.0 * x2  -2.0 * x3  + 3.0 * x4  -3.0 * x5  + 3.0 * x6  -2.0 * x7  + 1.0 * x8 ;
solve; 
display 0.0  + 0.0 * x1   + 2.0 * x2   + 0.0 * x3   -2.0 * x4   + 0.0 * x5   + 0.0 * x6   + 2.0 * x7   + 0.0 * x8 ;
 
 end; 

#include "ControleAr.h"

/*C�digos referentes ao arcondicionado Elgin*/

unsigned int OFF[197] = { 6400,7000, 850,1300, 900,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 550,1650, 550,550,
550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1650,
500,1650, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600,
550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,600, 550,550, 550,550, 550,600, 500,600, 550,550, 550,1650, 550,1600, 550,1650,
550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 550,1600,
600,1600, 550,600, 550,1600, 550,550, 550,1650, 550,1600, 550,600, 550,550, 550,600, 550,1600, 550,600, 500,1650, 550,600, 500,600, 500,600, 550,
1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,1650, 550,600, 500,1650, 550,1650, 500,7350, 550 };  // UNKNOWN B99B0EA9
unsigned int ON[197] = { 6350,7000, 850,1350, 850,1300, 800,1400, 650,1550, 600,1550, 600,1600, 550,1600, 600,1600, 550,550, 550,600, 550,
550, 550,600, 500,600, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 600,550,
550,550, 550,600, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,550,
550,600, 500,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,1650,
500,1650, 550,550, 550,1650, 550,1600, 550,1700, 550,550, 550,1650, 500,600, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,550,
550,550, 550,1650, 550,550, 550,1650, 500,600, 550,1600, 550,600, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1600, 550,1650, 550,7350, 500 };  // UNKNOWN AF9C26D


// The codes below are the individual codes for set the reference temperature of the air-conditioner
/*
unsigned int temp18[197] = { 6350,7000, 900,1300, 800,1400, 650,1500, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 550,600, 550,550,550,550, 550,600,
550,550, 550,550, 600,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,600,
550,550, 550,600, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,
600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,550, 600,1600, 550,1650, 550,1600, 550,1600, 600,550,
550,1650, 500,600, 550,1600, 550,1650, 550,1600, 550,600, 500,1650, 550,1650, 500,600, 550,1600, 550,600, 550,550, 550,550, 600,1600, 550,550, 550,600, 550,550, 550,1650,500,
600, 550,1600, 550,600, 550,1600, 550,550, 600,550, 550,1600, 600,550, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 500,7350, 550 };  // UNKNOWN F3DC3BCD
unsigned int temp19[197] = { 6400,6950, 850,1350, 800,1350, 850,1350, 650,1550, 600,1550, 600,1600, 600,1550, 600,1600, 550,550, 550,550, 600,550,
550,550, 550,600, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600,
550,550, 550,600, 550,550, 550,600, 500,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600, 550,600,
550,550, 550,600, 550,550, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,1650,
500,1650, 550,1650, 500,1650, 550,550, 550,600, 550,550, 550,1600, 600,1600, 550,1650, 550,550, 550,1600, 600,1600, 550,1650, 550,1600, 550,550, 600,550, 550,550,
550,1650, 550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,550, 600,1600, 550,550, 550,600, 550,1600, 550,600, 500,
1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,7350, 550 };  // UNKNOWN 35370B80
unsigned int temp20[197] = { 6400,7000, 850,1300, 850,1350, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 600,1600, 550,550, 550,550, 550,600, 550,550,
550,600, 550,550, 550,550, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,
550, 600,550, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,550,
550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,550, 600,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,1650,
500,1650, 550,550, 550,1650, 550,1600, 600,550, 550,1650, 550,1600, 550,600, 550,1600, 550,1650, 550,550, 550,550, 550,1650, 550,550, 550,550, 600,1600, 550,550,
600,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,600,550,550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7350, 500 };  // UNKNOWN 18867080
unsigned int temp21[197] = { 6400,7000, 850,1350, 800,1350, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 600,1600, 550,550, 550,600, 500,600, 550,
550, 550,600, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,550, 550,550,
550,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,550,
550,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1600, 600,1600, 550,1600, 600,
1600, 550,550, 600,550, 550,1600, 550,600, 550,1600, 550,1650, 550,550, 550,1650, 500,1650, 550,1650, 500,600, 550,1650, 500,600, 550,550, 550,1650, 500,600, 550,550,
550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,7350, 550 };  // UNKNOWN C72BCAA5
unsigned int temp22[197] = { 6350,7000, 900,1300, 850,1300, 700,1500, 650,1550, 600,1550, 600,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,600,
550,550, 550,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,550, 600,550, 550,550, 550,600, 500,600, 550,550, 550,
600, 550,550, 550,1600, 600,550, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,550, 550,1650, 550,550, 550,600, 500,600, 550,550, 550,550, 550,600,
550,1600, 550,600, 550,1600, 550,600, 550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,1600, 550,
600, 550,550, 550,1650, 500,1650, 550,550, 550,1650, 550,1600, 550,600, 550,1600, 550,1650, 500,600, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,1650, 550,550,
550,1650, 500,600, 500,1650, 550,600, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550 };  // UNKNOWN B61F4F4D
unsigned int temp23[197] = { 6400,7000, 850,1300, 850,1350, 800,1350, 750,1450, 600,1550, 650,1550, 600,1600, 550,1600, 600,550, 550,550, 550,600, 500,600,
550,550, 550,550, 550,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,
600, 550,550, 550,600, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,1650, 500,1650, 550,1650, 550,1600, 550,600, 500,1650, 550,550, 550,550, 550,600, 550,
550, 550,600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650,
550,550, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,1600, 550,600, 550,550, 550,
550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,1600, 600,550, 550,1650, 550,550, 550,1600, 550,600, 500,1650, 550,1650, 500,7350, 550 };// UNKNOWN 879D9AE1
unsigned int temp24[197] = { 6350,7050, 850,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 550,550, 550,550, 550,600, 500,600, 550,550, 550,600, 550,550,
550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650,
500,1650, 550,1650, 500,1650, 550,1650, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,550, 550,550, 600,550, 550,550, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,
550, 600,550, 550,1650, 550,550, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,1650, 600,1600, 550,600, 550,1600, 550,600, 500,1650, 550,
1650, 500,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,1650, 550,550, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,1600, 550,600,
550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550 };  // UNKNOWN 669B7BE9
unsigned int temp25[197] = { 6350,7000, 850,1350, 850,1300, 900,1300, 800,1350, 700,1500, 650,1550, 600,1600, 550,1600, 550,600, 550,550, 550,550, 550,550, 600,550,
550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,1600, 600,1600, 550,600, 500,600, 500,600, 550,550, 550,600,
550,550, 550,600, 500,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,600,
550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,
1650, 550,1600, 550,550, 600,550, 550,1600, 600,1600, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,1650, 550,600, 500,1650,
550,550, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,1650,
550,1600, 550,7350, 550 };  // UNKNOWN E4D1A145
unsigned int temp26[197] = { 6400,6950, 900,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 500,600, 550,550,
550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600,
550,550, 550,550, 550,600, 550,550, 550,550, 600,550, 550,550, 550,1650, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,550,
550,1650, 550,550, 550,600, 550,550, 550,550, 550,550, 600,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600,
550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 500,600, 550,1600, 550,600,
550,1600, 550,600, 550,1600, 550,600, 500,600, 550,550, 550,1650, 500,600, 550,1600, 600,550,550,1600, 600,550, 550,550, 550,1650, 500,600, 550,1600,
550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550 };  // UNKNOWN DF8364A5
unsigned int temp27[197] = { 6350,7000, 850,1300, 850,1350, 650,1550, 600,1600, 600,1550, 600,1600, 550,1600, 550,1650, 550,550, 550,600, 500,
600, 550,550, 550,550, 600,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550,
550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,1600, 550,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600,
550,600, 500,600, 550,550, 550,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,550, 600,550, 550,550, 550,1650, 500,600, 550,1600, 550,600,
550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,
1650, 550,550, 550,1650, 500,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,550, 550,1650, 550,550,
550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,7350, 550 };  // UNKNOWN 5538180
unsigned int temp28[197] = { 6400,7000, 850,1300, 850,1350, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550,
550,600, 550,550, 550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550, 550,600, 550,
550, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,600, 500,600, 550,550,
550,1650, 500,600, 550,1600, 550,600, 550,550, 550,600, 550,550, 550,1650, 500,600, 550,1600, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 500,600, 550,1600, 550,
1650, 600,550, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,550, 600,550, 550,1600, 600,1600, 550,550, 550,1650, 550,550, 550,600, 500,600, 550,1600, 550,550, 600,
1600, 550,550, 600,1600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,7350, 550 };  // UNKNOWN 163E7144
*/

/*Codes organized in a bi-dimensional array in ascending order
The first on the array is the 18�C and the last is 28�C
*/
unsigned int tempCodes[11][197] = {
{6350,7000, 900,1300, 800,1400, 650,1500, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 550,600, 550,550,550,550, 550,600,
550,550, 550,550, 600,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,600,
550,550, 550,600, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,
600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,550, 600,1600, 550,1650, 550,1600, 550,1600, 600,550,
550,1650, 500,600, 550,1600, 550,1650, 550,1600, 550,600, 500,1650, 550,1650, 500,600, 550,1600, 550,600, 550,550, 550,550, 600,1600, 550,550, 550,600, 550,550, 550,1650,500,
600, 550,1600, 550,600, 550,1600, 550,550, 600,550, 550,1600, 600,550, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 500,7350, 550},

{6400,6950, 850,1350, 800,1350, 850,1350, 650,1550, 600,1550, 600,1600, 600,1550, 600,1600, 550,550, 550,550, 600,550,
550,550, 550,600, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600,
550,550, 550,600, 550,550, 550,600, 500,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600, 550,600,
550,550, 550,600, 550,550, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,1650,
500,1650, 550,1650, 500,1650, 550,550, 550,600, 550,550, 550,1600, 600,1600, 550,1650, 550,550, 550,1600, 600,1600, 550,1650, 550,1600, 550,550, 600,550, 550,550,
550,1650, 550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,550, 600,1600, 550,550, 550,600, 550,1600, 550,600, 500,
1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,7350, 550},

{6400,7000, 850,1300, 850,1350, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 600,1600, 550,550, 550,550, 550,600, 550,550,
550,600, 550,550, 550,550, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,
550, 600,550, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,550,
550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,550, 600,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,1650,
500,1650, 550,550, 550,1650, 550,1600, 600,550, 550,1650, 550,1600, 550,600, 550,1600, 550,1650, 550,550, 550,550, 550,1650, 550,550, 550,550, 600,1600, 550,550,
600,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,600,550,550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7350, 500},

{6400,7000, 850,1350, 800,1350, 650,1550, 600,1550, 600,1600, 600,1600, 550,1600, 600,1600, 550,550, 550,600, 500,600, 550,
550, 550,600, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,550, 550,550,
550,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,550,
550,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1600, 600,1600, 550,1600, 600,
1600, 550,550, 600,550, 550,1600, 550,600, 550,1600, 550,1650, 550,550, 550,1650, 500,1650, 550,1650, 500,600, 550,1650, 500,600, 550,550, 550,1650, 500,600, 550,550,
550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,600, 500,1650, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,7350, 550},

{6350,7000, 900,1300, 850,1300, 700,1500, 650,1550, 600,1550, 600,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,600,
550,550, 550,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,550, 600,550, 550,550, 550,600, 500,600, 550,550, 550,
600, 550,550, 550,1600, 600,550, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,550, 550,1650, 550,550, 550,600, 500,600, 550,550, 550,550, 550,600,
550,1600, 550,600, 550,1600, 550,600, 550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,1600, 550,
600, 550,550, 550,1650, 500,1650, 550,550, 550,1650, 550,1600, 550,600, 550,1600, 550,1650, 500,600, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,1650, 550,550,
550,1650, 500,600, 500,1650, 550,600, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550},

{6400,7000, 850,1300, 850,1350, 800,1350, 750,1450, 600,1550, 650,1550, 600,1600, 550,1600, 600,550, 550,550, 550,600, 500,600,
550,550, 550,550, 550,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,550, 550,600, 500,
600, 550,550, 550,600, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,1650, 500,1650, 550,1650, 550,1600, 550,600, 500,1650, 550,550, 550,550, 550,600, 550,
550, 550,600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650,
550,550, 550,550, 550,600, 500,600, 550,1600, 550,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,1600, 550,600, 550,550, 550,
550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,1600, 600,550, 550,1650, 550,550, 550,1600, 550,600, 500,1650, 550,1650, 500,7350, 550},

{6350,7050, 850,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 550,550, 550,550, 550,600, 500,600, 550,550, 550,600, 550,550,
550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,1650,
500,1650, 550,1650, 500,1650, 550,1650, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,550, 550,550, 600,550, 550,550, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,
550, 600,550, 550,1650, 550,550, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,1650, 600,1600, 550,600, 550,1600, 550,600, 500,1650, 550,
1650, 500,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,1650, 550,550, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,1600, 550,600,
550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550},

{6350,7000, 850,1350, 850,1300, 900,1300, 800,1350, 700,1500, 650,1550, 600,1600, 550,1600, 550,600, 550,550, 550,550, 550,550, 600,550,
550,550, 550,600, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,1600, 600,1600, 550,600, 500,600, 500,600, 550,550, 550,600,
550,550, 550,600, 500,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 500,600, 550,550, 550,600,
550,550, 550,550, 550,600, 550,1600, 550,550, 600,1600, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,
1650, 550,1600, 550,550, 600,550, 550,1600, 600,1600, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,1650, 550,550, 550,550, 550,1650, 550,600, 500,1650,
550,550, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,1650,
550,1600, 550,7350, 550},

{6400,6950, 900,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 500,600, 550,550,
550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 550,600,
550,550, 550,550, 550,600, 550,550, 550,550, 600,550, 550,550, 550,1650, 500,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,1600, 600,1600, 550,550,
550,1650, 550,550, 550,600, 550,550, 550,550, 550,550, 600,550, 550,1650, 550,550, 550,1650, 500,600, 500,600, 550,550, 550,600, 550,1600, 550,600, 550,1600,
550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,1650, 500,600, 550,1600, 550,600,
550,1600, 550,600, 550,1600, 550,600, 500,600, 550,550, 550,1650, 500,600, 550,1600, 600,550,550,1600, 600,550, 550,550, 550,1650, 500,600, 550,1600,
550,600, 550,1600, 550,600, 550,1600, 550,1650, 550,7300, 550},

{6350,7000, 850,1300, 850,1350, 650,1550, 600,1600, 600,1550, 600,1600, 550,1600, 550,1650, 550,550, 550,600, 500,
600, 550,550, 550,550, 600,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550,
550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,1600, 550,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,1600,
550,600, 500,600, 550,550, 550,600, 550,550, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,550, 600,550, 550,550, 550,1650, 500,600, 550,1600, 550,600,
550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,600, 550,550, 550,1650, 500,600, 550,1600, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,
1650, 550,550, 550,1650, 500,600, 550,550, 550,550, 600,1600, 550,550, 550,1650, 550,550, 550,1650, 550,550, 550,550, 550,1650, 550,550,
550,1650, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,7350, 550},

{6400,7000, 850,1300, 850,1350, 650,1500, 650,1550, 600,1600, 550,1600, 600,1600, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550,
550,600, 550,550, 550,600, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,600, 550,550, 550,550, 550,600, 550,550, 550,600, 550,
550, 550,550, 550,1650, 550,550, 550,1650, 500,1650, 550,1650, 500,1650, 550,1650, 500,1650, 550,550, 550,1650, 550,550, 550,600, 550,550, 550,600, 500,600, 550,550,
550,1650, 500,600, 550,1600, 550,600, 550,550, 550,600, 550,550, 550,1650, 500,600, 550,1600, 550,600, 500,1650, 550,1650, 550,1600, 550,1650, 500,600, 550,1600, 550,
1650, 600,550, 550,550, 550,1650, 550,550, 550,1650, 550,1600, 550,550, 600,550, 550,1600, 600,1600, 550,550, 550,1650, 550,550, 550,600, 500,600, 550,1600, 550,550, 600,
1600, 550,550, 600,1600, 550,550, 550,600, 550,1600, 550,600, 550,1600, 550,600, 500,1650, 550,550, 550,1650, 550,1600, 550,7350, 550}

};


/*M�todos*/
void TurnAirConditionerON(IRsend *sender) {
	(*sender).sendRaw(ON, 197, 38);
}
void TurnAirConditionerOFF(IRsend *sender) {
	(*sender).sendRaw(OFF, 197, 38);
}

void SetAirConditionerTemp(int temp, IRsend *sender) {
	(*sender).sendRaw(tempCodes[temp - 18], 197, 38); // The temperature pass by reference is the index of the array minus 18. 18�C is array[0] and 28�C is array[10]  
}

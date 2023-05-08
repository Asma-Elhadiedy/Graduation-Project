//VP of Selecting order
#define order    0x1   
#define suger    0x2
#define cup      0x3
#define extra    0x4

//icons VP for reviewing order in English
#define orderFE       0x5
#define sugerFE       0x6   
#define cupFE         0x7
#define extraFE       0x8
#define priceFE       0x9

//icons VP for reviewing order in Arabic
#define orderFA       0x10
#define sugerFA       0x11   
#define cupFA         0x12
#define extraFA       0x13
#define priceFA       0x14

//VP for touches
#define touch         0x15

//VV of VP=0x15  
#define vendMoney     0x3
#define vendNoMoney   0x4 
#define englishLan    0x5 
#define arabicLan     0x6 

//VV of VP=0x1 (Drink)
#define espresso      0x1  //10 L.E
#define macchiato     0x2  //20 L.E
#define americano     0x3  //15 L.E
#define lungo         0x4  //15 L.E
#define ristretto     0x5  //10 L.E
#define longMacchiato 0x6  //20 L.E
#define nescafe       0x7  //25 L.E
#define flatWhite     0x8  //25 L.E
#define caffeLatte    0x9  //25 L.E
#define piccoloLatte  0x10 //25 L.E
#define mocha         0x11 //25 L.E
#define cappuccino    0x12 //25 L.E
#define longBlack     0x13 //15 L.E
#define hotChocolate  0x14 //20 L.E
#define frenchCoffee  0x15 //15 L.E
#define turkishCoffee 0x16 //10 L.E
#define milkCoffee    0x17 //15 L.E
#define redTea        0x18 //10 L.E
#define karakTea      0x19 //20 L.E
#define milkTea       0x20 //15 L.E

//VV of VP=0x2 (Suger)
#define noSuger      0x0    
#define oneSuger     0x1
#define twoSuger     0x2
#define threeSuger   0x3

//VV of VP=0x3 (Cup Size)
#define small        0x0    
#define large        0x1

//VV of VP=0x4 (Extra)
#define noExtra        0x0    
#define extraEspresso  0x1
#define extraChocolate 0x2
#define extraMilk      0x3

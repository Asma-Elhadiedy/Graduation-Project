#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // rx, tx
#include <E_Pcb_DwinSoft.h>
#include "Screen_Address.h"
#include "checkingCont_Conts.h"   
//--------------------------------------------
int cupS =5000;  //Time from tank to boiler (Small cup)
int cupL =7000;  //Time from tank to boiler (Large cup)
int boile = 50000;       //time to boile
int water_level = 0;
//-----------------------------------------------------------------------------------------------------------------------------------

uint8_t Data;
char drink = 0;
char cup_size = 'l';
char plusExtra = 0;
unsigned long timePassedToOrder = 0;
byte pointDrink = 0;
byte pointSize =0;
byte pointExtra =0;
byte totalPriceE =0;
byte totalPriceA =0;
byte vendingMode =0;
byte language = 0;   //0 for english & 1 for arabic 
byte flag =0;
byte OrderIsDone = 0;

//Coin Acceptor
const int coin = 2;
boolean insert = false;
volatile int pulse = 0;
unsigned long balance;
unsigned long totalInserted;
unsigned long timePassedToPay;

#define cup_sensor_end   30      // to detceted cup    
#define cup_sensor_start 18      // to detceted cup    
#define level_sensorw    19      //level sensor to check water level in tank

#define pump_h           47      //pin for boilar pump to mixer
#define pump_c           45      //pin for tank pump to boiler
#define pump_m           49      //pin for mixer pump to cup
#define boiler_pin       53      // boiler pin
#define fans             51      // Fans pin
#define arm_motor1       22      // cup mechansem (motor driver)
#define arm_motor2       24      // cup mechansem(motor driver)
#define belt_motor1      26      // belt to moving cup(motor driver)
#define belt_motor2      28      // belt to moving cup(motor driver)

void setup()
{ 
  // SENSORS
  pinMode(level_sensorw, INPUT);      // FOR Clean TANK
  pinMode(cup_sensor_end, INPUT);  
  pinMode(cup_sensor_start, INPUT);
  // OUTPUTS
  pinMode(stepperRelay, OUTPUT);        
  pinMode(container1, OUTPUT);        //container1 DC Motor
  pinMode(container2, OUTPUT);        //container2 DC Motor
  pinMode(container3, OUTPUT);        //container3 DC Motor
  pinMode(container4, OUTPUT);        //container4 DC Motor
  pinMode(container5, OUTPUT);        //container5 DC Motor
  pinMode(container6, OUTPUT);        //container6 DC Motor
  pinMode(container7, OUTPUT);        //container7 DC Motor
  pinMode(mixer, OUTPUT);             //mixer
  pinMode(pump_c, OUTPUT);            //pump of tank
  pinMode(pump_h, OUTPUT);            //pump of heater
  pinMode(pump_m, OUTPUT);            //pump of mixer
  pinMode(boiler_pin, OUTPUT);
  pinMode(fans, OUTPUT);
  pinMode(arm_motor1, OUTPUT);
  pinMode(arm_motor2, OUTPUT);
  pinMode(belt_motor1, OUTPUT);
  pinMode(belt_motor2, OUTPUT);
  //All Containers' Motors are Initially LOW
  digitalWrite(container1, HIGH);     
  digitalWrite(container2, HIGH);
  digitalWrite(container3, HIGH);
  digitalWrite(container4, HIGH);
  digitalWrite(container5, HIGH);
  digitalWrite(container6, HIGH);
  digitalWrite(container7, HIGH);
  digitalWrite(mixer, HIGH);
  digitalWrite(pump_c, HIGH);
  digitalWrite(pump_h, HIGH);
  digitalWrite(pump_m , HIGH);
  digitalWrite(boiler_pin, HIGH);
  digitalWrite(fans, HIGH);
  digitalWrite(stepperRelay, HIGH);
  
  digitalWrite(belt_motor1, LOW);
  digitalWrite(belt_motor2, LOW);
  digitalWrite(arm_motor1, LOW);
  digitalWrite(arm_motor2, LOW);
  Serial.begin(9600);
  mySerial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), coinInterrupt, RISING); 
  GO_PAGE(0);
  Serial.println ("start");  
}


void loop()
{
  timePassedToOrder = millis();
  if (millis() - timePassedToOrder > 15000){GO_PAGE(1);}
  
  Data = Read();
  if (Data){
    switch (VP){
      case order:{ //for drinks 
        switch (VV) {
         case espresso:      {drink = 1;  Serial.println("Espresso");       PUT(orderFA,61); break;}
         case macchiato:     {drink = 2;  Serial.println("Macchiato");      PUT(orderFA,62); break;}
         case americano:     {drink = 3;  Serial.println("Americano");      PUT(orderFA,63); break;}
         case lungo:         {drink = 4;  Serial.println("Lungo");          PUT(orderFA,64); break;}
         case ristretto:     {drink = 5;  Serial.println("Ristretto");      PUT(orderFA,65); break;}
         case longMacchiato: {drink = 6;  Serial.println("Long Macchiato"); PUT(orderFA,66); break;}
         case nescafe:       {drink = 7;  Serial.println("Nescafe");        PUT(orderFA,67); break;}
         case flatWhite:     {drink = 8;  Serial.println("Flat White");     PUT(orderFA,68); break;}
         case caffeLatte:    {drink = 9;  Serial.println("Caffe Latte");    PUT(orderFA,69); break;}
         case piccoloLatte:  {drink = 10; Serial.println("Piccolo Latte");  PUT(orderFA,70); break;}
         case mocha:         {drink = 11; Serial.println("Mocha");          PUT(orderFA,71); break;}
         case cappuccino:    {drink = 12; Serial.println("Cappuccino");     PUT(orderFA,72); break;}
         case longBlack:     {drink = 13; Serial.println("Long Black");     PUT(orderFA,73); break;}
         case hotChocolate:  {drink = 14; Serial.println("Hot Chocolate");  PUT(orderFA,74); break;}
         case frenchCoffee:  {drink = 15; Serial.println("French Coffee");  PUT(orderFA,75); break;}
         case turkishCoffee: {drink = 16; Serial.println("Turkish Coffee"); PUT(orderFA,76); break;}
         case milkCoffee:    {drink = 17; Serial.println("Milk Coffee");    PUT(orderFA,77); break;}
         case redTea:        {drink = 18; Serial.println("Red Tea");        PUT(orderFA,78); break;}
         case karakTea:      {drink = 19; Serial.println("Karak Tea");      PUT(orderFA,79); break;}
         case milkTea:       {drink = 20; Serial.println("Milk Tea");       PUT(orderFA,80); break;}
        }
         PUT(orderFE,drink);
         break;
      }
      
      
      case suger:
      {
        switch (VV)
        {
          case noSuger:    {amount1 =0; Serial.print("+ No Suger ");    Serial.println(amount1); PUT(sugerFE,24); PUT(sugerFA,81);  break;}
          case oneSuger:   {amount1 =1; Serial.print("+ 1 tsp Suger "); Serial.println(amount1); PUT(sugerFE,21); PUT(sugerFA,82);  break;}
          case twoSuger:   {amount1 =2; Serial.print("+ 2 tsp Suger "); Serial.println(amount1); PUT(sugerFE,22); PUT(sugerFA,83);  break;}
          case threeSuger: {amount1 =3; Serial.print("+ 3 tsp Suger "); Serial.println(amount1); PUT(sugerFE,23); PUT(sugerFA,84);  break;}
        }
      break;
      }

      case cup:
      {
        switch (VV)
        {
          case small: {cup_size = 's'; Serial.print("Small "); Serial.println(cup_size); PUT(cupFE,26);  PUT(cupFA,85); break;}
          case large: {cup_size = 'l'; Serial.print("Large "); Serial.println(cup_size); PUT(cupFE,25);  PUT(cupFA,86); break;}
        }
      break;
      }
      
      case extra:
      {
        switch (VV)
        {
          case noExtra:       {plusExtra = 0; Serial.print("+ No Extra "); Serial.println(plusExtra);            PUT(extraFE,27); PUT(extraFA,87); break;}
          case extraEspresso: {plusExtra = 1; Serial.print("+ Extra Espresso Shot "); Serial.println(plusExtra); PUT(extraFE,28); PUT(extraFA,88);  break;}
          case extraChocolate:{plusExtra = 2; Serial.print("+ Extra Chocolate "); Serial.println(plusExtra);     PUT(extraFE,29); PUT(extraFA,89);  break;}
          case extraMilk:     {plusExtra = 3; Serial.print("+ Extra Milk "); Serial.println(plusExtra);          PUT(extraFE,30); PUT(extraFA,90);  break;}
        }
      break;
      }
      
      case touch:
      {
        switch (VV)  
        {
          case vendMoney:    {vendingMode = 0; break;}
          case vendNoMoney:  {vendingMode = 1; break;}
          case englishLan:   {language = 0; if ( vendingMode == 0 ){GO_PAGE(7);}  if ( vendingMode == 1 ){GO_PAGE(45);}    break;}
          case arabicLan:    {language = 1; break;}   
        }
      break;
      }

      case 0x16: //Automatic Washing
      {
        switch (VV) 
        {
          case 0x1: {GO_PAGE(272); delay (7000); GO_PAGE(41); break;}
        }
      break;
      }
      
      case 0x17:  //Fault Checking
      {
        switch (VV) 
        {
          case 0x1:   {GO_PAGE(272); delay (7000); GO_PAGE(42); break;}
        }
      break;
      }
    }
    
  calcPrice();
  }

  coinVoid();
  if (totalInserted == (totalPriceE-25)) 
  {
    totalInserted =0; 
    if (language == 0)      {Serial.print("coins done English"); GO_PAGE(17); OrderIsDone = 1;}
    else if (language == 1) {Serial.print("coins done Arabic "); GO_PAGE(29); OrderIsDone = 1;}
   }
     
  if (drink == 1 && OrderIsDone == 1 )    //Order is: Espresso
  {
    OrderIsDone = 0;
    delay (4000);
    GO_PAGE(54);
    Serial.println("process");
    espressoVoid();
    if (language == 0)      {GO_PAGE(18);} 
    else if (language == 1) {GO_PAGE(30);}
    delay (10000);
    language = 0;
    GO_PAGE(1);
  }
}

void pumpC ()
{
  water_level = digitalRead(level_sensorw);
  if (water_level == HIGH)
  {
    digitalWrite( pump_c, LOW);  //NEED TO ADD TIMER
    if (cup_size=='s') {delay (cupS);}
    else               {delay (cupL);}
    digitalWrite(pump_c, HIGH);
  }
  else
  {digitalWrite(pump_c, HIGH);} //Send to screen (no water)
}

void boiler ()
{ 
  digitalWrite(boiler_pin, LOW);
  delay(boile);
  digitalWrite(boiler_pin, HIGH);
}

void pumpH ()
{
  digitalWrite(pump_h, LOW);
  delay (7000);
  digitalWrite(pump_h, HIGH );
}

void pumpM ()
{
  digitalWrite(pump_m, LOW);
  delay (7000);
  digitalWrite(pump_m, HIGH );
}

//-------------------------------------------------------------------------

void espressoVoid ()
{ 
  pumpC();
  boiler();
  in = 1 ; //Suger Container
  cont1();
  in = 2 ; //Espresso Container
  cont2();
  pumpH();
  gotospace();
  digitalWrite(boiler_pin,HIGH); //To Ensure Boiler is OFF
  armMech ();
  beltMechBackward();
  pumpM();
  beltMechForward();
}
  
void calcPrice(){
  if(drink == 1 || drink == 5 || drink == 16 || drink == 18)                              
    {pointDrink = 10;}  
  else if (drink == 3 || drink == 4 || drink == 13 || drink == 15 || drink == 17 || drink == 20) 
    {pointDrink = 15;}
  else if(drink == 2 || drink == 6 || drink == 14 || drink == 19)                  
    {pointDrink = 20;}
  else {pointDrink = 25;}
  
  if (cup_size == 's') {pointSize = 0;} else {pointSize = 5;}
  if (plusExtra == 0) {pointExtra = 0;} else {pointExtra = 5;}
  totalPriceE = (25 + pointDrink + pointSize + pointExtra);
  totalPriceA = (85 + pointDrink + pointSize + pointExtra);
  Serial.println(totalPriceE-25);
  PUT(priceFE,totalPriceE);
  PUT(priceFA,totalPriceA);  
}

//Interrupt for Coin Acceptor
void coinInterrupt() 
{
  pulse++ ;
  insert = true;
}

void armMech ()
{  
  digitalWrite(arm_motor1, LOW);
  digitalWrite(arm_motor2, HIGH);
  delay (2200);
  digitalWrite(arm_motor1, LOW);
  digitalWrite(arm_motor2, LOW);
  delay(200);
  digitalWrite(arm_motor1, HIGH);
  digitalWrite(arm_motor2, LOW);
  delay (2200);
  digitalWrite(arm_motor1, LOW);
  digitalWrite(arm_motor2, LOW);
}

void beltMechForward()
{
  digitalWrite(belt_motor1, LOW);
  digitalWrite(belt_motor2, HIGH);
  delay (6000);
  digitalWrite(belt_motor1, LOW);
  digitalWrite(belt_motor2, LOW);
}

void beltMechBackward()
{
  digitalWrite(belt_motor1, HIGH);
  digitalWrite(belt_motor2, LOW);
  delay (6000);
  digitalWrite(belt_motor1, LOW);
  digitalWrite(belt_motor2, LOW);
}
  
void coinVoid()    
{
  if (insert) 
  {
    timePassedToPay = millis();
    insert = false;
    balance+=10;
    Serial.println("Balance : "+(String)balance);
  }
  if(balance>0 )
  {
   if (millis() - timePassedToPay > 7000)
    {
      totalInserted = (balance/4);
      Serial.print("You've just inserted: ");
      Serial.print(totalInserted);
      Serial.println(" L.E");
      balance=0;
    }
  }
}

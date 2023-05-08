char in =0;      //Containr No.
int x =0;        //Used to move mixer
int wantToGo =0; 
int currentPos = 0;

//Mixer Configuraion
#define mixer   31          // mixer pin 
int mix_time = 25000;       // mixing time

//Stepper Configuraion
#define stepperRelay  33    //Power of relay 
#define dirPin  4           //DIR-
#define stepPin 5           //PUL-
char delayOfsteps = 1500;   //For Stepper Speed

//DC Motors for Containers 
#define container1 23       //container1 motor-relay
#define container2 25       //container2 motor-relay
#define container3 27       //container3 motor-relay
#define container4 29       //container4 motor-relay
#define container5 39       //container5 motor-relay
#define container6 41       //container6 motor-relay
#define container7 43       //container7 motor-relay

char amount1   = 0;         //Determind in each drink void //0 steps needed to reach container 1
#define tsp1   20000        //time in (ms) needed for DC of container 1 to supply (one)tsp   

char amount2   = 0;         //Determind in each drink void //0 steps needed to reach container 2 
#define tsp2   20000        //time in (ms) needed for DC of container 2 to supply (one)tsp  

char amount3   = 0;         //Determind in each drink void //3200 steps needed to reach container 3 
#define tsp3   20000        //time in (ms) needed for DC of container 3 to supply (one)tsp  

char amount4   = 0;         //Determind in each drink void //6000 steps needed to reach container 4 
#define tsp4   20000        //time in (ms) needed for DC of container 4 to supply (one)tsp  

char amount5   = 0;         //Determind in each drink void //6000 steps needed to reach container 5 
#define tsp5   20000        //time in (ms) needed for DC of container 5 to supply (one)tsp  

char amount6   = 0;         //Determind in each drink void //12300steps needed to reach container 6 
#define tsp6   20000        //time in (ms) needed for DC of container 6 to supply (one)tsp  

char amount7   = 0;         //Determind in each drink void //12300steps needed to reach container 7 
#define tsp7   20000        //time in (ms) needed for DC of container 7 to supply (one)tsp

                            //9000 steps needed to between cont 5 & cont 6 

void goToContainer()        //Stepper-Mixer Mechanism
{
  if (currentPos == wantToGo){Serial.print("Mixer is already under container "); Serial.println(in);}
  else if (currentPos < wantToGo)
  {
    digitalWrite(stepperRelay, LOW);
    delay (2000);
    digitalWrite(dirPin, HIGH);
    for (x = 0; x < (wantToGo - currentPos); x++)
    { 
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayOfsteps);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayOfsteps);
    }
    digitalWrite(stepperRelay, HIGH);
    currentPos = wantToGo;
    Serial.print("container ");
    Serial.print(in);
    Serial.println(" is reached");
    Serial.print("Mixer Position is ");
    Serial.println(currentPos);

  }

  else if (currentPos > wantToGo)
  {    
    digitalWrite(stepperRelay, LOW);
    digitalWrite(dirPin, LOW);
    for (x = 0; x < (currentPos - wantToGo); x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayOfsteps);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayOfsteps);
    }
    digitalWrite(stepperRelay, HIGH);
    currentPos = wantToGo;
    Serial.print("container ");
    Serial.print(in);
    Serial.println(" is reached");
    Serial.print("Mixer Position is ");
    Serial.println(currentPos);
  }
}

void checkingCont () {   //To Determine Position of The Mixer 

  if (in == '1' || in == '2')
  {
    wantToGo = 0;
    Serial.print("container to go ");
    Serial.println(in);
    goToContainer();
  }

  else if (in == '3')
  {
    wantToGo = 3200;
    Serial.print("container to go ");
    Serial.println(in);
    goToContainer();
  }

  else if (in == '4' || in == '5')
  {
    wantToGo = 6000;
    Serial.print("container to go ");
    Serial.println(in);
    goToContainer();
  }

  else if (in == '6' || in == '7')
  {
    wantToGo = 12300;
    Serial.print("container to go ");
    Serial.println(in);
    goToContainer();
  }

  else if (in == 'm')             //space between cont5 & cont6
  {
    wantToGo = 9000;
    Serial.print("container to go ");
    Serial.println(in);
    goToContainer();
  }
  else {return;}

}


void cont1()         //to reach container 1 & Turn On DC Motor
{
  checkingCont() ;
  goToContainer();
  if (amount1 == 1)
  {
    digitalWrite(container1, LOW);
    delay(tsp1);
    digitalWrite(container1, HIGH);
  }
  else if (amount1 == 2)
  {
    digitalWrite(container1, LOW);
    delay(2 * tsp1);
    digitalWrite(container1, HIGH);
  }
  else if (amount1 == 3)
  {
    digitalWrite(container1, LOW);
    delay(3 * tsp1);
    digitalWrite(container1, HIGH);
  }
  else {return;}
}


void gotospace()         //to go to the space and mix & Turn On Mixer Motor
{              
  checkingCont() ;
  goToContainer();
  digitalWrite(mixer, LOW);
  delay (mix_time);
  digitalWrite(mixer, HIGH);
}

void cont2()         //to reach container 2 & Turn On DC Motor
{
  checkingCont() ;
  goToContainer();
  if (amount2 == 1)
  {
    digitalWrite(container2, LOW);
    delay(tsp2);
    digitalWrite(container2, HIGH);
  }
  else if (amount2 == 2)
  {
    digitalWrite(container2, LOW);
    delay(2 * tsp2);
    digitalWrite(container2, HIGH);
  }
  else if (amount2 == 3)
  {
    digitalWrite(container2, LOW);
    delay(3 * tsp2);
    digitalWrite(container2, HIGH);
  }
  else {return;}

}

void cont3()         //to reach container 3 & Turn On DC Motor
{
  checkingCont() ;
  goToContainer();
  if (amount3 == 1)
  {
    digitalWrite(container3, LOW);
    delay(tsp3);
    digitalWrite(container3, HIGH);
  }
  else if (amount3 == 2)
  {
    digitalWrite(container3, LOW);
    delay(2 * tsp3);
    digitalWrite(container3, HIGH);
  }
  else if (amount3 == 3)
  {
    digitalWrite(container3, LOW);
    delay(3 * tsp3);
    digitalWrite(container3, HIGH);
  }
  else {return;}

}

void cont4()         //to reach container 4 & Turn On DC Motor
{
  checkingCont() ;
  goToContainer();
  if (amount4 == 1)
  {
    digitalWrite(container4, LOW);
    delay(tsp4);
    digitalWrite(container4, HIGH);
  }
  else if (amount4 == 2)
  {
    digitalWrite(container4, LOW);
    delay(2 * tsp4);
    digitalWrite(container4, HIGH);
  }
  else if (amount4 == 3)
  {
    digitalWrite(container4, LOW);
    delay(3 * tsp4);
    digitalWrite(container4, HIGH);
  }
  else {return;}
}

void cont5()         //to reach container 5
{
  checkingCont() ;
  goToContainer();
  if (amount5 == 1)
  {
    digitalWrite(container5, LOW);
    delay(tsp5);
    digitalWrite(container5, HIGH);
  }
  else if (amount5 == 2)
  {
    digitalWrite(container5, LOW);
    delay(2 * tsp5);
    digitalWrite(container5, HIGH);
  }
  else if (amount5 == 3)
  {
    digitalWrite(container5, LOW);
    delay(3 * tsp5);
    digitalWrite(container5, HIGH);
  }
  else {return;}
}

void cont6()         //to reach container 6
{
  checkingCont() ;
  goToContainer();
  if (amount6 == 1)
  {
    digitalWrite(container6, LOW);
    delay(tsp6);
    digitalWrite(container6, HIGH);
  }
  else if (amount6 == 2)
  {
    digitalWrite(container6, LOW);
    delay(2 * tsp6);
    digitalWrite(container6, HIGH);
  }
  else if (amount6 == 3)
  {
    digitalWrite(container6, LOW);
    delay(3 * tsp6);
    digitalWrite(container6, HIGH);
  }
  else {return;}
}

void cont7()         //to reach container 7
{
  checkingCont() ;
  goToContainer();
  if (amount7 == 1)
  {
    digitalWrite(container7, LOW);
    delay(tsp7);
    digitalWrite(container7, HIGH);
  }
  else if (amount7 == 2)
  {
    digitalWrite(container7, LOW);
    delay(2 * tsp7);
    digitalWrite(container7, HIGH);
  }
  else if (amount7 == 3)
  {
    digitalWrite(container7, LOW);
    delay(3 * tsp7);
    digitalWrite(container7, HIGH);
  }
  else {return;}
}

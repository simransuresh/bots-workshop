/*
 * maze_solver.cpp (shortest path search algo)
 *
 * Created: 6/6/2016
 *  Author: Simran Suresh
 */ 

char reshortn[10];
char directions[30];
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 5V BO - 1300
// 8V BO - 850
// 8V Geared - 650
// 5V geared -DO NOT ATTEMPT

int m1 =0;
int m2 =1;
int m3 =24;
int m4=25;

int l;
int c1;
int c2;
int c3;
int r; 

int i,j,flag;

int tdelay=950, fdelay=400;


//~~~~~~~~~~~~~~~Conditions~~~~~~~~~~~~~~

int eosens()
{ 
readsens();
if(((c1+c2+c3)==1) || ((c1+c2+c3)==2))
return 1;
else 
return 0;
}


void forward()
{
    digitalWrite(m1,HIGH);  //Forward
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);  
    //Serial.println("\tMoving FWD");
    lcd.print("Moving FWD");
} 

void left()
{
    digitalWrite(m1,LOW);  //Left
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    //Serial.println("\tTaking LEFT");
    lcd.print("= left");
}
void smallleft()
{
    digitalWrite(m1,LOW);  //Left
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
    //Serial.println("\tTaking LEFT");
    lcd.print("= small left");
}
void right()
{
    digitalWrite(m1,HIGH);  //Right
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
    //Serial.println("\tTaking RIGHT");
    lcd.print("= right");
}
void smallright()
{
    digitalWrite(m1,HIGH);  //Right
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    //Serial.println("\tTaking RIGHT");
    lcd.print("= right");
}
void halt()
{
    digitalWrite(m1,LOW);  //STOP
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    //Serial.println("\tSTOPPED!!!!!!");   
    lcd.print("= HALT!!!");
}

void readsens()
{
  l=digitalRead(A2);
  c1=digitalRead(A3);
  c2=digitalRead(A4);
  c3=digitalRead(A5);
  r=digitalRead(A6);
   lcd.print(l);
  lcd.print("--"); 
   lcd.print(c1);
   lcd.print("--"); 
   lcd.print(c2);
   lcd.print("--"); 
   lcd.print(c3);
   lcd.print("--"); 
   lcd.print(r);
   delay (300);
}  

void inch()
{
  //Serial.println("Inside inch function");
    lcd.print("inch function");  
    digitalWrite(m1,LOW);  //STOP
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    delay(100); 
   
    digitalWrite(m1,HIGH);  //Forward
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);  
    delay(900);
    
    digitalWrite(m1,LOW);  //STOP
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
    delay(100);
   
    readsens(); 
    delay(100);
}
 
void preinch()
{
  if((l==1) && (c1==1) || (c3==1) && (r==1)) 
  {
    halt();
    delay(1000);
  
    forward();
    delay(160);
  
    halt();
    delay(1000);
  
    readsens();
  }
} 

void setup()
{
  ////Serial.begin(38400);
  ////Serial.println("Initialized");
  lcd.begin(16,2);
  lcd.print ("Welcome");
  delay(500);
    
  lcd.clear();
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  
  pinMode(26,INPUT);  //l
  pinMode(27,INPUT);  //c1
  pinMode(28,INPUT);  //c2
  pinMode(29,INPUT);  //c3
  pinMode(30,INPUT);  //r
  lcd.print ("initialised");
  delay(500);
  lcd.clear();
}

void loop()
{  
  lcd.clear();
readsens();  
lcd.clear();

//Serial.println("");
//Serial.println(" | L | C | C | C | R | ");
//Serial.print(" | ");
//Serial.print(l);
//Serial.print(" | ");
//Serial.print(c1);
//Serial.print(" | ");
//Serial.print(c2);
//Serial.print(" | ");
//Serial.print(c3);
//Serial.print(" | ");
//Serial.print(r);
//Serial.print(" | \t");

//Line follower  
//Condition for FWD
if((l==0) && (c1==0) && (c2==1) && (c3==0) && (r==0))
 {
    //Serial.println("\tForward");
    lcd.print("Forward");
    forward();   
 }
//Conditions for LEFT
else if(((l==0) && (c1==1) && (c2==0) && (c3==0) && (r==0)) || ((l==0) && (c1==1) && (c2==1) && (c3==0) && (r==0)))
 {
    //Serial.println("\tLeft");
    lcd.print("Left");
    smallleft();
 }
//Conditions for LEFT 
else if(((l==0) && (c1==0) && (c2==0) && (c3==1) && (r==0)) || ((l==0) && (c1==0) && (c2==1) && (c3==1) && (r==0)))
 {
    //Serial.println("\tRight");
    lcd.print("Right");
    smallright();
    
 }
//----------------------------------------------------------------------------------------------
else if(((l==1) && (c1==1)) || ((c3==1) && (r==1)))
 {
  // preinch();

//DECIDE BETWEEN ---- Right only and Straight n right!
if(((l==0) && (c1==0) && (c2==1) && (c3==1) && (r==1)) || ((l==0) && (c1==1) && (c2==1) && (c3==1) && (r==1))) 
 {
   //Serial.println("\tRIGHT ONLY / STRAIGHT AND RIGHT???");
   lcd.print("R/StnRT?");
   inch();
   //Serial.print("Choice = ");
    if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
    {
      //Serial.println("Right only");
      lcd.print("= Right");
      right();
      delay(tdelay);
    }
    
    if((l==0) && (r==0) && (eosens()))
    {
      //Serial.println("Straight N Right");
      lcd.print("= Forward");
      directions[i]='S';
      i++;
      forward();
      delay(fdelay);
    }
    
 }
  
//Left and Straight n left  
  
else if(((l==1) && (c1==1) && (c2==1) && (c3==0) && (r==0)) || ((l==1) && (c1==1) && (c2==1) && (c3==1)  && (r==0)))
 {
   //Serial.println("\tLEFT ONLY / STRAIGHT AND LEFT????");
   lcd.print("Lt/StnLt ");
   inch();
   //Serial.print("Choice = ");
   lcd.print("C??");   
    if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
    {
      //Serial.println("Left only");
      //lcd.print("= Left");
      left();
    }
    
    if((l==0) && (r==0) && (eosens()))
    {
      //Serial.println("Straight N left");
      lcd.print("= StnLT");
      directions[i]='L';
      i++;
      left();
    }
    delay(tdelay);
 }
 
//T-int cross end of maze
 
else if((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))
 {
   //Serial.println("\tT INTERSECTION / END OF MAZE / CLOVERLEAF");
   lcd.print("Tint/End/Crs?");
   inch();
   //Serial.print("Choice = ");
   if((l==0) && (r==0) && (eosens()))
    {
      //Serial.println("CLOVERLEAF");
      lcd.print("= crs");
      directions[i]='L';
      i++;
      left();
      delay(tdelay);
    }

    if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
    {
      //Serial.println("T-INT");
      lcd.print("= tint");
      directions[i]='L';
      i++;
      left();
      delay(tdelay);
    }
    
    if((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))
    {
      //Serial.println("THE END");
      lcd.print("= end");
      halt();
      delay(2500);
   directions[i]='E'; 
   //Serial.println("Maze over!! Existing path is:");
   printing(directions);
   delay(10000); //10 second window
   SPAlgo(directions);
      while(1)
      { 
        halt();
      }
    }
  }
 }

//Dead end
else if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
    {
      //Serial.println("OOPS! I reached a DEADEND  - - - TAKING U TURN");
      lcd.print("= Uturn");
      left();
      delay(1800);
      directions[i]='U';
      i++;
    }
} 
 
 
//~~~~~~ENDOFLOOP~~~~~~~~~~~~~~~~
//PRINTING THE VALUES OF ARRAY
void printing(char prtline[])
{
   //Serial.println("");
   lcd.clear();
   for(i=0;prtline[i]!='E';i++)
   {
     //Serial.print(prtline[i]);
     lcd.print(prtline[i]);
   }
}
//~~~~~~SHORTENING PATH ALGO~~~~~~~~~~~
void SPAlgo(char shortn[])
{
 //Serial.println("");
 for(i=1;shortn[(i+1)]!='E';i++)
   {
    if(shortn[i]=='U')
    {
      if((shortn[i-1]=='L') && (shortn[i+1]=='R'))
      {  
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='U';
      }
     
      if((shortn[i-1]=='L') && (shortn[i+1]=='S'))
      {
        shortn[i-1]='x';
        shortn[i]='x';
        shortn[i+1]='R';
      }
     
      if((shortn[i-1]=='R') && (shortn[i+1]=='L'))
     {
       shortn[i-1]='x';
       shortn[i]='x';  
       shortn[i+1]='U';
     }
     
      if((shortn[i-1]=='S') && (shortn[i+1]=='L'))
     {
       shortn[i-1]='x';
       shortn[i]='x';
       shortn[i+1]='R';
     }
      
      if(shortn[i]=='x')
      i++;
      
       if((shortn[i-1]=='S') && (shortn[i+1]=='S'))
     {
       shortn[i-1]='x';
       shortn[i]='x';
       shortn[i+1]='U';
     }
     
     if((shortn[i-1]=='L') && (shortn[i+1]=='L'))
     {
       shortn[i-1]='x';
       shortn[i]='x';
       shortn[i+1]='S';
     }
    }
  }
  j=0;
  for(i=0;shortn[i]!='E';i++)
  {
    if(shortn[i]!='x')
    {
      reshortn[j]=shortn[i];
      j++;
    }
   }
   reshortn[j]='E';
     //Serial.print("now the path is:");
     lcd.print("SPA : ");
   printing(shortn);
   delay(1000);
   for(i=0;reshortn[i]!='E';i++)
   {
     if(reshortn[i]=='U')
     {
       flag=1;
     }
  }
  delay(2000);
  if(flag==1)
  { 
    j=0;
    SPAlgo(reshortn);
    flag=0;
  }
  else
  {
   //Serial.println("Final path is:");
   lcd.clear();
   lcd.print("Final =");
    printing(reshortn);
    finale();
  }
  /*lcd.print("came here3");
  delay(1000);*/
}
void ptg()
{
  if(reshortn[i]=='S')
  {
    forward();
    delay(fdelay);
  }
  if(reshortn[i]=='L')
  {
    left();
    delay(tdelay);
  }
  if(reshortn[i]=='R')
  {
    right();
    delay(tdelay);
  }
  i++;
}
//~~~~~~~~~~~~~~~~Shortest Path (second run)~~~~~~~~~~~~~~~~~
void finale()
{
  //Serial.println("The Path to Glory");
  lcd.clear();
  i=0;
  while(1)
  {
    readsens();
    if((l==0) && (c1==0) && (c2==1) && (c3==0) && (r==0))
       {
         //Serial.println("\tForward");
         forward();
       }
//Conditions for LEFT
    else if(((l==0) && (c1==1) && (c2==0) && (c3==0) && (r==0)) || ((l==0) && (c1==1) && (c2==1) && (c3==0) && (r==0)))
       {
         //Serial.println("\tLeft");
         smallleft();
       }
//Conditions for LEFT 
    else if(((l==0) && (c1==0) && (c2==0) && (c3==1) && (r==0)) || ((l==0) && (c1==0) && (c2==1) && (c3==1) && (r==0)))
       {
         //Serial.println("\tRight");
         smallright();
       }
    
    else if(((l==1) && (c1==1)) || ((c3==1) && (r==1)))
      {
       preinch();         
       if(((l==0) && (c1==0) && (c2==1) && (c3==1) && (r==1)) || ((l==0) && (c1==1) && (c2==1) && (c3==1) && (r==1))) 
       {
         //Serial.println("\tRIGHT ONLY / STRAIGHT AND RIGHT???");
         inch();
         //Serial.print("Choice = ");
            if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
              {
                //Serial.println("Right only");
                right();
                delay(tdelay);
              }
    
            else if((l==0) && (r==0) && (eosens()))
              {
                //Serial.println("Straight N Right");
                ptg();
              }
       }
  
//Left and Straight n left  
  
    else if(((l==1) && (c1==1) && (c2==1) && (c3==0) && (r==0)) || ((l==1) && (c1==1) && (c2==1) && (c3==1)  && (r==0)))
       {
         //Serial.println("\tLEFT ONLY / STRAIGHT AND LEFT????");
         inch();
         //Serial.print("Choice = ");   
            if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
              {
                //Serial.println("Left only");
                //lcd.print("= left");
                left();
                delay(tdelay);
              }
    
            else if((l==0) && (r==0) && (eosens()))
              {
                //Serial.println("Straight N left");
                lcd.print("= stnlt");
                ptg();
            }
        }
 
//T-int cross end of maze
 
    else if((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))
       {
         //Serial.println("\tT INTERSECTION / END OF MAZE / CLOVERLEAF");
         inch();
         //Serial.print("Choice = ");
            if((l==0) && (r==0) && (eosens()))
             {
                //Serial.println("CLOVERLEAF");
                ptg();
             }
            else if((l==0) && (c1==0) && (c2==0) && (c3==0) && (r==0))
              {   
                //Serial.println("T-INT");
                ptg();
               }
    
          if((l==1) && (c1==1) && (c2==1) && (c3==1) && (r==1))
            {
              //Serial.println("THE END");
              while (1)
                {
                  halt();
                }
            }
      }
   }
  } 
}
//~~~~~~~~~~~~~~~~Finish~~~~~~~~~~~~~~~~~

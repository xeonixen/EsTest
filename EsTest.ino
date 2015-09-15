// Autoshift test program.

const int varmePinin = A2;
const int varmePinut = 5;
const int baltePinin = A1;
const int baltePinut = 6;
const int asPinin[] = {A5,A4,A3};
const int asPinout[] = {2,3,4};
const int ledPin[] = {9,10,11,12,13};  // LED: AS1, AS2, AS3, Värme, Bälte
const int brightness = 80;
int i=0,reading[2][5]; 

int serie=1; // Aktivera rs232
          
void setup()
{

// Initera ben

for(i=0;i<3;i++)
{
  pinMode(varmePinut, OUTPUT);
  pinMode(baltePinut, OUTPUT);
  pinMode(asPinout[i],OUTPUT);
  pinMode(ledPin[i],OUTPUT);
}

for(i=0;i<3;i++)
{
  digitalWrite(asPinout[i],1); // 5v ut på alla as utgångar
  digitalWrite(asPinin[i],1); // pull ups på analoga ingångar
}
for(i=0;i<5;i++) digitalWrite(ledPin[i],0); // alla leds avstängda

  digitalWrite(varmePinut,0); // Värme utgång 0v
  digitalWrite(baltePinut,1); // Bälte utgång 5v
  digitalWrite(varmePinin,1); // Värme utan pull up
  digitalWrite(baltePinin,1); // Bälte med pull up
}

void loop()
{
 if(serie) Serial.begin(9600); // Starta rs232



  // Start test
while(true)
{
  for(i=0;i<3;i++) // AS test
  {
    digitalWrite(asPinout[i],0);
    reading[0][i] = analogRead(asPinin[i]);
    digitalWrite(asPinout[i],1);
    reading[1][i] = analogRead(asPinin[i]);
    if((reading[0][i]<30) && (reading[1][i]>800))
      analogWrite(ledPin[i],brightness);
    else
      digitalWrite(ledPin[i],0);

  }
  
   // Värme test
   digitalWrite(varmePinut,0);
   delay(10);
   reading[0][3] = analogRead(varmePinin);
   digitalWrite(varmePinut,1);
   delay(10);
   reading[1][3] = analogRead(varmePinin);
   if(reading[0][3]<30)
     digitalWrite(ledPin[3], brightness);
   else
     digitalWrite(ledPin[3],0);
 
   // Bälte test
   digitalWrite(baltePinut, 0);
   reading[0][4] = analogRead(baltePinin);
   digitalWrite(baltePinut, 1);
   reading[1][4] = analogRead(baltePinin);
   if(reading[0][4]<30)
     digitalWrite(ledPin[4],1);
   else
     digitalWrite(ledPin[4],0);
     

   if(serie) // Skriv ut mätvärden på rs232.
   {
     for(i=0;i<5;i++)
     {
       Serial.print(reading[0][i]);
       Serial.print(", ");
       Serial.print(reading[1][i]);
       if(i<4) Serial.print("; ");
       else Serial.println(".");
     }
     delay(500);
   }
}
 
}
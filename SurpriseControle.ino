//
// ---------------------------
// Programme Surprise Controle
// ---------------------------
//
// Brancher aléatoirement des periph d'acquisition sur les entrées analogiques (un potar sur A1, A5 et un switch sur A4 par exemple),
// brancher un periph audio sur la pin 9 (buzzer, HP+transistor,..),
// brancher des periph de sortie aléatoirement sur les PIN de sorties (des LEDs sur 3,4,5 et un (moteur+diode roue libre) sur 10 par exemple).
// Alimenter la Arduino
//
//*****************************************************************************************************************************************************************

int out[] = {
  1,2,3,4,5,6,7,8,9,10,11,12,13}; //Utilisé pour declaration as Output dans setup()
int pitch = 1; // fréquence "auto gérée"
int pitchInd = 0; // Inducateur si boucle pitch++ ou pitch--
int thisPitch =0; // Frequence envoyée au buzzer
int a,b,c,d,e,f,g,h;

void setup()  { 

  Serial.begin(9600);
  for (int i=0; i < 14; i++){
    pinMode(out[i] , OUTPUT);
  }

  digitalWrite(A0, HIGH); //  Resistance pull up
  digitalWrite(A1, HIGH); //  pour utlisation d'un
  digitalWrite(A2, HIGH); //  BP 
  digitalWrite(A3, HIGH); //
  digitalWrite(A4, HIGH); // 
  digitalWrite(A5, HIGH); //

} 


void loop()  { 

  acq(); //Fonction d'acquisition des entrées 
  analog_write(); // Fonction write sur sorties analog (PWM)
  digital_to_analog_write(); // Fonction write sur sortie digital, emulation PWM
  audio_out();// Fonction relative au pitch et buzzer

  delay(50);  

  //debug_serial(); //  /!\ Enlever les commentaires dans la fonction aussi !
}


int acq(void){
  a = ((map(analogRead(A0), 10, 1023, 5, 10000))+(map(analogRead(A3), 10, 1023, 0, 255)));
  b = map(analogRead(A0), 10, 1023, 0, 255);
  c = map(analogRead(A1), 10, 1023, 0, 255);
  d = map(analogRead(A2), 10, 1023, 0, 255);
  e = map(analogRead(A3), 10, 1023, 0, 255);
  f = map(analogRead(A4), 10, 1023, 0, 255);
  g = map(analogRead(A5), 10, 1023, 0, 255); 
}

int analog_write(void){ // Chaque potards controles un peu chaque sorties equitablements
  analogWrite(3, ((b/6)+(c/6)+(d/6)+(e/6)+(f/6)+(g/6)));
  analogWrite(5, ((b/6)+(c/6)+(d/6)+(e/6)+(f/6)+(g/6)));
  analogWrite(6, ((b/6)+(c/6)+(d/6)+(e/6)+(f/6)+(g/6)));
  analogWrite(10, ((b/6)+(c/6)+(d/6)+(e/6)+(f/6)+(g/6)));
  analogWrite(11, ((b/6)+(c/6)+(d/6)+(e/6)+(f/6)+(g/6)));

}

int digital_to_analog_write(void){
  PORTD = B10010100; 
  PORTB = B00110001;
  delayMicroseconds(a);
  PORTD = 0; 
  PORTB = 0;
  delayMicroseconds(10000 - a);
}

int audio_out(void){
  if(pitchInd == 0){
    pitch = pitch + 20;
    if(pitch >= 1000){
      pitchInd = 1;
    }
  }
  else if(pitchInd == 1){
    pitch = pitch - 20;
    if(pitch <= 15){
      pitchInd = 0;
    }
  }
  thisPitch = (map(analogRead(A0), 0, 1024, 30, 4000))+(map(analogRead(A1), 0, 1024, 30, 4000)+(map(analogRead(A2), 0, 1024, 30, 4000))
    + (map(analogRead(A3), 0, 1024, 30, 4000))+ (map(analogRead(A4), 0, 1024, 30, 4000))+
    (map(analogRead(A5), 0, 1024, 30, 4000))+pitch);
  tone(9, thisPitch, 10); 
}

/*int debug_serial(void){
 Serial.print("A0 = "); Serial.print(analogRead(A0));
 Serial.print(" // A1 = "); Serial.print(analogRead(A1));
 Serial.print(" // A2 = "); Serial.print(analogRead(A2));
 Serial.print(" // A3 = "); Serial.print(analogRead(A3));
 Serial.print(" // A4 = "); Serial.print(analogRead(A4));
 Serial.print(" // A5 = "); Serial.println(analogRead(A5));
 Serial.print("a = "); Serial.print(a);
 Serial.print("  thisPitch = "); Serial.println(thisPitch);
 }*/



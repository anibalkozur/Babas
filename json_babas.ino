//tarjeta de memoria SD------------------------------------------------
#include <SPI.h>
#include <SD.h>
#define SSpin 53
File archivo;
// comunicacion I2C----------------------------------------------------
#include <Wire.h> //comunicacion por i2c

//metodo libreria json para lectura de datos---------------------------
#include <ArduinoJson.h>
//-------------------------------------------------------------
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

//Comunicacion IC2 placa servos----------------------------------------

#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver servosx1 = Adafruit_PWMServoDriver(0x40);

//Ancho de cuclo de trabajo de pulso a 50 hz de cada servo--------------unsigned int
#define ciclomin1 170 //ancho de pulso para 50 hz en 0°
#define ciclomax1 560 //ancho de pulso para 50hz en 180°
#define ciclomin2 200 //ancho de pulso para 50 hz en 0°
#define ciclomax2 535 //ancho de pulso para 50hz en 180°
#define ciclomin3 170 //ancho de pulso para 50 hz en 0°
#define ciclomax3 550 //ancho de pulso para 50hz en 180°
#define ciclomin4 120 //ancho de pulso para 50 hz en 0°
#define ciclomax4 550 //ancho de pulso para 50hz en 180°
#define ciclomin5 120 //ancho de pulso para 50 hz en 0°
#define ciclomax5 550 //ancho de pulso para 50hz en 180°
#define ciclomin6 120 //ancho de pulso para 50 hz en 0°
#define ciclomax6 550 //ancho de pulso para 50hz en 180°

int VALORPOT1;
int VALORPOT2;
int VALORPOT3;
int VALORPOT4;
int VALORPOT5;
int VALORPOT6;
int ciclo1;
int ciclo2;
int ciclo3;
int ciclo4;
int ciclo5;
int ciclo6;
int ANGINI1 = 90;
int ANGINI2 = 90;
int ANGINI3 = 90;
int ANGINI4 = 90;
int ANGINI5 = 90;
int ANGINI6 = 90;
int arrayANGINI1[40];
int arrayANGINI2[40];
int arrayANGINI3[40];
int arrayANGINI4[40];
int arrayANGINI5[40];
int arrayANGINI6[40];
int contarray = 0;
int mimap1;
int mimap2;
int mimap3;
int mimap4;
int mimap5;
int mimap6;
int POT1 = 0;
int POT2 = 1;
int POT3 = 2;
int POT4 = 3;
int POT5 = 6;
int POT6 = 7;
unsigned long previoMillis = 0;
unsigned long valorMillis;
unsigned long unavezMillis = 0;

int PULSADOR_INI = 30;
int PULSADOR_GRAB = 31;
int CONT_PUL_INI = 0;
int CONT_PUL_FIN = 0;
int GRAB = LOW;
int INICIO_FIN = LOW;
int HABILITA_AUTO = 0;
int automatizacion = 0;
char strcomandos;
String comandos;
int i = 1;

String json;

int KEY; 
int PREVIOUS_KEY;
#define SCL_PIN 12
#define SDO_PIN 13

void setup() {

  pinMode(SCL_PIN, OUTPUT);
  pinMode(SDO_PIN, INPUT);  

  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);  
  lcd.clear();

  Serial.begin(9600);
  delay(30);

  Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

//----------------------------------------------------------------
  servosx1.begin();
  servosx1.setOscillatorFrequency(27000000);
  servosx1.setPWMFreq(50);
  delay(30);
  servosx1.setPWM(1,0,365);
  servosx1.setPWM(2,0,367);
  servosx1.setPWM(3,0,367);
  servosx1.setPWM(4,0,335);
  servosx1.setPWM(5,0,335);
  servosx1.setPWM(6,0,335);
  delay(50);
}

void loop(){

caract_especiales(CONT_PUL_INI,contarray);

KEY = Read_Keypad();
delay(2);
 
 
 
 if (KEY == 16 && KEY != PREVIOUS_KEY && CONT_PUL_INI == 0){

 if (!SD.begin(SSpin)){
      Serial.println("fallo de inicializacion!");
      }
      
      else{ 
      Serial.println("inicalización correcta");   
      archivo = SD.open("/");
      printDirectory(archivo,0);
      }
 }
 
//Crea un archivo en memoria SD coord.txt 
//boton de inicio, creación de archivo--------------------------------------
  if (KEY == 1 && KEY != PREVIOUS_KEY && CONT_PUL_INI == 0){
   
    if (!SD.begin(SSpin)){
      Serial.println("fallo de inicializacion!");
      }
      else{ 
      Serial.println("inicalización correcta");

      String filecomplet = "";
      String coord = "coord";
      String txt = ".txt";
      filecomplet = coord + i + txt;
      
      Serial.println(filecomplet);
      archivo = SD.open(filecomplet, FILE_WRITE); //devuelve un valor verdadero o falso, crea archivo en SD
      delay(10);
 
      CONT_PUL_INI = 1; //1 = habilita grabar - inhabilita boton de inicio de creacion de archivo
      CONT_PUL_FIN = 0; //0 = habilita grabar - no permite cerrar memoria ni archivo
      i = i + 1;
      }
  }
//boton de fin y cierre de tarjeta-----------------------------------------
  if (KEY == 2 && KEY != PREVIOUS_KEY && CONT_PUL_FIN == 1 && CONT_PUL_INI == 1){ 
     delay(50);

     serializador(contarray, arrayANGINI1, arrayANGINI2, arrayANGINI3, arrayANGINI4, arrayANGINI5, arrayANGINI6);     
     archivo.print(json);
     Serial.println(json);
     json = "";
     contarray = 0;

     archivo.close(); 
    
     Serial.println("Escritura correcta");
     Serial.println("Ya puede retirar la memoria");
     CONT_PUL_INI = 0;     
  }
//boton de grabado----------------------------------------------------------   
  if(KEY == 4 && KEY != PREVIOUS_KEY && archivo && CONT_PUL_INI == 1){//solo si archivo es verdadero 
    delay(50); 

    Serial.println("Escribiendo en archivo coord.txt");
    CONT_PUL_FIN = 1;
    
    arrayANGINI1[contarray] = ANGINI1;
    arrayANGINI2[contarray] = ANGINI2;
    arrayANGINI3[contarray] = ANGINI3;
    arrayANGINI4[contarray] = ANGINI4;
    arrayANGINI5[contarray] = ANGINI5;
    arrayANGINI6[contarray] = ANGINI6;
    contarray = contarray + 1;
Serial.println(contarray);
    Serial.println("este es el primer paso");
    }
//boton de lectura de tarjeta SD y grabado en variable string------------

  if(KEY == 13 && KEY != PREVIOUS_KEY && CONT_PUL_INI == 0){
    delay(50);
    if (!SD.begin(SSpin)){
      Serial.println("fallo de inicializacion!");
      }
      else{ 
      Serial.println("inicalización correcta");
      archivo = SD.open("coord1.txt", FILE_READ);
      }
    Serial.println("se abrio el archivo para proceso de automatización");
    automatizacion = 1;

//automatizacón------------------------------------------------------------
//---------------------------------------------------------------------------
  
//  if (automatizacion == 1 && HABILITA_AUTO == 1){
    
    Serial.println("cuidado: en proceso de movimiento automatico");
    
    while (archivo.available()){
    strcomandos = archivo.read();
    comandos = comandos + strcomandos;      
    }
    deserealizador(comandos);
    
    Serial.println(comandos);
    comandos = "";
     automatizacion = 0;
     archivo.close();
 }
 
//visualización en el LCD------------------------------------------------
//-----------------------------------------------------------------------  
 //Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

//lee los valores de entrada analogicos de los potes (0-1024)------------
//----------------------------------------------------------------------- 
  VALORPOT1 = analogRead(POT1);          //lee el valor de pote 1 - entrada analogica 0
  VALORPOT2 = analogRead(POT2);          //lee el valor del pote 2 - entrada analogica 1
  VALORPOT3 = analogRead(POT3);          //lee el valor de pote 3 - entrada analogica 2
  VALORPOT4 = analogRead(POT4);          //lee el valor del pote 4 - entrada analogica 3
  VALORPOT5 = analogRead(POT5);          //lee el valor del pote 5 - entrada analogica 6
  VALORPOT6 = analogRead(POT6);          //lee el valor del pote 6 - entrada analogica 7
  
//inicia semilla de tiempo millis-----------------------------------
//------------------------------------------------------------------
  PREVIOUS_KEY = KEY; KEY = 0;
  valorMillis = millis();

//ahora iniciamos los movimientos de los servos---------------------
//------------------------------------------------------------------
//base--------------------------------------------------------------
  if (VALORPOT1 < 500){    
   if (valorMillis - previoMillis >= VALORPOT1){
   previoMillis = valorMillis;
    long miresultado = valorMillis - previoMillis;
    if (ANGINI1 <= 1){
    ANGINI1 = 1;
    }
    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);
    
    int MAPANGINI1 = map(VALORPOT1, 500, 0, 1, 5);   
    ANGINI1 = ANGINI1 - MAPANGINI1;
    ciclo1 = map(ANGINI1,0,180,ciclomin1,ciclomax1);
    servosx1.setPWM(1,0,ciclo1);
   }
  }
  
  if (VALORPOT1 > 630){
    mimap1 = map(VALORPOT1, 630, 1023, 630, 0);    
    if (valorMillis - previoMillis >= mimap1){
    previoMillis = valorMillis;
      if (ANGINI1 > 179){
      ANGINI1 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI1 = map(VALORPOT1, 630, 1023, 1, 5);
    ANGINI1 = ANGINI1 + MAPANGINI1 ;
    ciclo1 = map(ANGINI1,0,180,ciclomin1,ciclomax1);
    servosx1.setPWM(1,0,ciclo1);
  }
  }
//hombro--------------------------------------------------------------
   if (VALORPOT2 < 480){    
    if (valorMillis - previoMillis >= VALORPOT2){
    previoMillis = valorMillis;
    if (ANGINI2 < 1){
    ANGINI2 = 1;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI2 = map(VALORPOT2, 480, 0, 1, 5);
    ANGINI2 = ANGINI2 - MAPANGINI2;
    ciclo2 = map(ANGINI2,0,180,ciclomin2,ciclomax2);
    servosx1.setPWM(2,0,ciclo2);
    }
  }

  if (VALORPOT2 > 610){
    mimap2 = map(VALORPOT2, 610, 1023, 580, 0);    
    if (valorMillis - previoMillis >= mimap2){
    previoMillis = valorMillis;
      if (ANGINI2 > 179){
      ANGINI2 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI2 = map(VALORPOT2, 610, 1023, 1, 5);
    ANGINI2 = ANGINI2 + MAPANGINI2;
    ciclo2 = map(ANGINI2,0,180,ciclomin2,ciclomax2);
    servosx1.setPWM(2,0,ciclo2);  
  }
  }
//Codo--------------------------------------------------------------
if (VALORPOT3 < 480){    
    if (valorMillis - previoMillis >= VALORPOT3){
    previoMillis = valorMillis;
      if (ANGINI3 < 1){
      ANGINI3 = 1;
      }

      Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI3 = map(VALORPOT3, 480, 0, 1, 4);
    ANGINI3 = ANGINI3 - MAPANGINI3;
    ciclo3 = map(ANGINI3,0,180,ciclomin3,ciclomax3);
    servosx1.setPWM(3,0,ciclo3);
    }
  }

  if (VALORPOT3 > 610){
    mimap3 = map(VALORPOT3, 610, 1023, 580, 0);    
    if (valorMillis - previoMillis >= mimap3){
    previoMillis = valorMillis;
      if (ANGINI3 > 179){
      ANGINI3 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI3 = map(VALORPOT3, 610, 1023, 1, 4);
    ANGINI3 = ANGINI3 + MAPANGINI3;
    ciclo3 = map(ANGINI3,0,180,ciclomin3,ciclomax3);
    servosx1.setPWM(3,0,ciclo3);     
  }
  }
//muñeca--------------------------------------------------------------
if (VALORPOT4 < 480){    
    if (valorMillis - previoMillis >= VALORPOT4){
    previoMillis = valorMillis;
      if (ANGINI4 < 1){
      ANGINI4 = 1;
      }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI4 = map(VALORPOT4, 480, 0, 1, 4);
    ANGINI4 = ANGINI4 - MAPANGINI4;
    ciclo4 = map(ANGINI4,0,180,ciclomin4,ciclomax4);
    servosx1.setPWM(4,0,ciclo4);
    }
  }

  if (VALORPOT4 > 630){
    mimap4 = map(VALORPOT4, 630, 1023, 580, 0);    
    if (valorMillis - previoMillis >= mimap4){
    previoMillis = valorMillis;
      if (ANGINI4 > 179){
      ANGINI4 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);

    int MAPANGINI4 = map(VALORPOT4, 480, 1023, 1, 4);
    ANGINI4 = ANGINI4 + MAPANGINI4;
    ciclo4 = map(ANGINI4,0,180,ciclomin4,ciclomax4);
    servosx1.setPWM(4,0,ciclo4);  
       
  }
  }
//Palma------------------------------------------------------------
if (VALORPOT5 < 450){    
    if (valorMillis - previoMillis >= VALORPOT5){
    previoMillis = valorMillis;
      if (ANGINI5 < 1){
      ANGINI5 = 1;
      }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);
      
    int MAPANGINI5 = map(VALORPOT5, 480, 0, 1, 4);
    ANGINI5 = ANGINI5 - MAPANGINI5;
    ciclo5 = map(ANGINI5,0,180,ciclomin5,ciclomax5);
    servosx1.setPWM(5,0,ciclo5);
    }
  }

  if (VALORPOT5 > 680){
    mimap5 = map(VALORPOT5, 680, 1023, 580, 0);    
    if (valorMillis - previoMillis >= mimap5){
    previoMillis = valorMillis;
      if (ANGINI5 > 179){
      ANGINI5 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);
    
    int MAPANGINI5 = map(VALORPOT5, 480, 1023, 1, 4);
    ANGINI5 = ANGINI5 + MAPANGINI5;
    ciclo5 = map(ANGINI5,0,180,ciclomin5,ciclomax5);
    servosx1.setPWM(5,0,ciclo5);  
       
  }
  }
//Dedo--------------------------------------------------------
if (VALORPOT6 < 500){    
    if (valorMillis - previoMillis >= VALORPOT6){
    previoMillis = valorMillis;
      if (ANGINI6 < 1){
      ANGINI6 = 1;
      }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);
      
    int MAPANGINI6 = map(VALORPOT6, 480, 0, 1, 4);
    ANGINI6 = ANGINI6 - MAPANGINI6;
    ciclo6 = map(ANGINI6,0,180,ciclomin6,ciclomax6);
    servosx1.setPWM(6,0,ciclo6);
    }
  }

  if (VALORPOT6 > 630){
    mimap6 = map(VALORPOT6, 630, 1023, 580, 0);    
    if (valorMillis - previoMillis >= mimap6){
    previoMillis = valorMillis;
      if (ANGINI6 > 179){
      ANGINI6 = 179;
    }

    Display_LCD(ANGINI1,ANGINI2,ANGINI3,ANGINI4,ANGINI5,ANGINI6);
    
    int MAPANGINI6 = map(VALORPOT6, 480, 1023, 1, 4);
    ANGINI6 = ANGINI6 + MAPANGINI6;
    ciclo6 = map(ANGINI6,0,180,ciclomin6,ciclomax6);
    servosx1.setPWM(6,0,ciclo6);  
      
  }
  }
}

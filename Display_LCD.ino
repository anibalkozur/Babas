void caract_especiales(int CONT_PUL_INI, int contarray){

  if(CONT_PUL_INI == 1){
   caract_grab();
  }
  
  if(CONT_PUL_INI == 0){
  lcd.setCursor(15,0);
  lcd.print(" ");
  lcd.setCursor(15,1);
  lcd.print(" ");
  }
  
  if(contarray){
  caract_punto(contarray);  
  }
}
//-----------------------------------------------------------
uint8_t fila_puntos[] = {0,16,24,28,30,31};
int puntos_uno;
int puntos_dos;
int puntos_tres;
int puntos_cuatro;
int puntos_cinco;
int puntos_seis;
int puntos_siete;
int puntos_ocho;
//-----------------------------------------------------------
void caract_punto(int contarray){
  
  if(contarray <= 5){
    puntos_uno = contarray;
  }
  if(contarray > 5 && contarray <= 10){
    puntos_dos = contarray - 5;
  }
  if(contarray > 10 && contarray <= 15){
    puntos_tres = contarray - 10;
  }
  if(contarray > 15 && contarray <= 20){
    puntos_cuatro = contarray - 15;
  }
  if(contarray > 20 && contarray <= 25){
    puntos_cinco = contarray - 20;
  }
  if(contarray > 25 && contarray <= 30){
    puntos_seis = contarray - 25;
  }
  if(contarray > 30 && contarray <= 35){
    puntos_siete = contarray - 30;
  }
  if(contarray > 35 && contarray <= 40){
    puntos_ocho = contarray - 35;
  }
  
  uint8_t uno[8] = 
  {fila_puntos[puntos_uno], 
  fila_puntos[puntos_dos], 
  fila_puntos[puntos_tres], 
  fila_puntos[puntos_cuatro], 
  fila_puntos[puntos_cinco], 
  fila_puntos[puntos_seis], 
  fila_puntos[puntos_siete], 
  fila_puntos[puntos_ocho]}; 
  
  lcd.createChar(1,uno);
  lcd.setCursor(15,1);
  lcd.write(byte(1));                                 
}

//--------------------------------------------------
void caract_grab(){

  uint8_t grab[8] = {0x0, 0x4, 0xE, 0x1F, 0x1F, 0xE, 0x4, 0x0};                              

  lcd.createChar(0,grab);
  lcd.setCursor(15,0);
  lcd.write(byte(0));  
}

//----------------------------------------------------------------------------------------
void Display_LCD(int ANGINI1,int ANGINI2,int ANGINI3,int ANGINI4,int ANGINI5,int ANGINI6){
       
  lcd.setCursor(0,0);
  lcd.print("B:");
  lcd.print(ANGINI1);
  
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(ANGINI2);

  lcd.setCursor(5,0);
  lcd.print("C:");
  lcd.print(ANGINI3);
  
  lcd.setCursor(5,1);
  lcd.print("M:");
  lcd.print(ANGINI4);

  lcd.setCursor(10,1);
  lcd.print("P:");
  lcd.print(ANGINI5);

  lcd.setCursor(10,0);
  lcd.print("D:");
  lcd.print(ANGINI6);

  //borrar el último caracter cuando baja de 100 a menos-------------------
//-----------------------------------------------------------------------
  if (ANGINI1 < 100){
  lcd.setCursor(4,0);
  lcd.print(" ");
  }
  if (ANGINI2 < 100){
  lcd.setCursor(4,1);
  lcd.print(" ");
  }
  if (ANGINI3 < 100){
  lcd.setCursor(9,0);
  lcd.print(" ");
  }
  if (ANGINI4 < 100){
  lcd.setCursor(9,1);
  lcd.print(" ");
  }
  if (ANGINI5 < 100){
  lcd.setCursor(14,1);
  lcd.print(" ");
  }
  if (ANGINI6 < 100){
  lcd.setCursor(14,0);
  lcd.print(" ");
  }
}

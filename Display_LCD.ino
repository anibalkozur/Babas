

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

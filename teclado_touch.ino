

/*Key = Read_Keypad();
 if (Key)
   Serial.println(Key);
   delay(200);*/


int Read_Keypad(void)
{
   byte Count;
   //byte Key_State = 0;
   for(Count = 1; Count <= 16; Count++)
   {
      digitalWrite(SCL_PIN, LOW);
      if (!digitalRead(SDO_PIN))
      KEY = Count;
      digitalWrite(SCL_PIN, HIGH);
    
   }
   return KEY;
}

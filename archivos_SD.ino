String nombres_archivos[50];
int z = 0;
String archivos;
void printDirectory(File archivo, int numTabs) {

 /* while (true) {
    File entry =  archivo.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
     // Serial.print('\t');
    }

    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } 
    else {
      // files have sizes, directories do not
      Serial.print("\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}*/
while (true){
   
    File entry =  archivo.openNextFile();
    if (!entry){
    archivos = nombres_archivos[2];
    Serial.println(archivos); 
    delay(50);
 //   return();
    break;  
    }
    
    nombres_archivos[z] = entry.name();
    Serial.println(entry.name());
    z = z + 1;
    }
    

}

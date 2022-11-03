int deserealizador(String comandos){

int ANGINI1 = 90;
int ANGINI2 = 90;
int ANGINI3 = 90;
int ANGINI4 = 90;
int ANGINI5 = 90;
int ANGINI6 = 90;

  StaticJsonDocument<1024> doc;

  DeserializationError error = deserializeJson(doc, comandos);

  if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

for (JsonObject programa_item : doc["programa"].as<JsonArray>()) {

  int programa_item_base = programa_item["base"]; // Ej 114, 114, 114
  int programa_item_hombro = programa_item["hombro"]; // Ej 66, 66, 66
  int programa_item_codo = programa_item["codo"]; // Ej 90, 66, 66
  int programa_item_mu_eca = programa_item["muñeca"]; // Ej 90, 91, 91
  int programa_item_palma = programa_item["palma"]; // Ej 90, 90, 85
  int programa_item_dedo = programa_item["dedo"]; // Ej 90, 90, 99

  
  Serial.println(programa_item_base);
  delay(700);

  ciclo1 = map(programa_item_base,0,180,ciclomin1,ciclomax1);
  servosx1.setPWM(1,0,ciclo1);

  ciclo2 = map(programa_item_hombro,0,180,ciclomin2,ciclomax2);
  servosx1.setPWM(2,0,ciclo2);

  ciclo3 = map(programa_item_codo,0,180,ciclomin3,ciclomax3);
  servosx1.setPWM(3,0,ciclo3);

  ciclo4 = map(programa_item_mu_eca,0,180,ciclomin4,ciclomax4);
  servosx1.setPWM(4,0,ciclo4);

  ciclo5 = map(programa_item_palma,0,180,ciclomin5,ciclomax5);
  servosx1.setPWM(5,0,ciclo5);
  
  ciclo6 = map(programa_item_dedo,0,180,ciclomin6,ciclomax6);
  servosx1.setPWM(6,0,ciclo6);

  
}
}

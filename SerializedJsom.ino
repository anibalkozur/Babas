#include <ArduinoJson.hpp>
#include <ArduinoJson.h>

String serializador(int contarray, int arrayANGINI1[], int arrayANGINI2[], int arrayANGINI3[], int arrayANGINI4[], int arrayANGINI5[], int arrayANGINI6[])  //String json  
{  
    StaticJsonDocument<1024> doc;
    JsonArray programa = doc.createNestedArray("programa"); 
    
    for(int x = 0; x < contarray ; x++){
      
    int base = arrayANGINI1[x];
    int hombro = arrayANGINI2[x];
    int codo = arrayANGINI3[x];
    int muneca = arrayANGINI4[x];
    int palma = arrayANGINI5[x];
    int dedo = arrayANGINI6[x];
   
    JsonObject obj = programa.createNestedObject();
    obj["base"] = base;
    obj["hombro"] = hombro;
    obj["codo"] = codo;
    obj["muñeca"] = muneca;
    obj["palma"] = palma;
    obj["dedo"] = dedo; 
    Serial.println (x);
    }
    serializeJson(doc, json);
    return json;
}

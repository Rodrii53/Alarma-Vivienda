void WifiPinesMemoria()
{
  //read configuration from FS json
  Serial.println("Montando FS...");

  if (SPIFFS.begin()) {
    Serial.println("Sistema Montado FS");
    if (SPIFFS.exists("/config.json")) {
      
      //Si existe archivo, Lee y carga
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        
        // Buffer para preparar el archivo.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(auth, json["auth"]);
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

// CONFIGURACIONES DE WIFI
WiFiManager wifiManager;
      
// Agrega input HTML a formulario ("Mensaje en Serial.Print", "Texto en HTML", "Variable Guarda", "Cant. de bits", "Titulo HTML")
WiFiManagerParameter custom_auth ("Blynk Token Recibido", "Blynk Token", auth, 35,"title= \"Token: \"");
wifiManager.addParameter(&custom_auth);

//Guardar callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

// REINICIA CONFIGURACIONES GUARDADAS DE WIFI MANAGER
  if (digitalRead(InputReset) == LOW || fabrica==0){fabrica=1; SPIFFS.format(); EEPROM.put(mems0, fabrica); /*fauth=1; EEPROM.put(mfauth, fauth); SON DE TOKEN VIEJO*/
      EEPROM.put(mems1,1); EEPROM.put(mems2,1); EEPROM.put(mems3,1); EEPROM.put(mems4,1); EEPROM.put(mems5,1); EEPROM.put(mems6,1); EEPROM.put(mems7,1); EEPROM.put(mems8,1); EEPROM.put(mems9,1); EEPROM.put(mems10,1); EEPROM.put(mems11,1); EEPROM.put(mems12,1); EEPROM.put(mems13,1); EEPROM.put(mems14,1); EEPROM.put(mems15,1); EEPROM.put(mems16,1); EEPROM.put(mems17,1); EEPROM.put(mems18,1); EEPROM.put(mems19,1); EEPROM.put(mems20,1); EEPROM.put(mems21,1); EEPROM.put(mems22,1); EEPROM.put(mems23,1); EEPROM.put(mems24,1);
      EEPROM.put(mca1,1); EEPROM.put(mca2,1); EEPROM.put(mca3,1); EEPROM.put(mca4,1); EEPROM.put(mca5,1); EEPROM.put(mca6,1); EEPROM.put(mca7,1); EEPROM.put(mca8,1); EEPROM.put(mca9,1); EEPROM.put(mca10,1); EEPROM.put(mcd1,1); EEPROM.put(mcd2,1); EEPROM.put(mcd3,1); EEPROM.put(mcd4,1); EEPROM.put(mcd5,1); EEPROM.put(mcd6,1); EEPROM.put(mcd7,1); EEPROM.put(mcd8,1); EEPROM.put(mcd9,1); EEPROM.put(mcd10,1);
      EEPROM.commit(); /*DELAY*/time_now = millis(); while(millis() < time_now+period1000){/*wait approx. [period]ms*/}/*DELAY*/ wifiManager.resetSettings(); wifiManager.startConfigPortal("Alarma", "");
  }
//wifiManager.autoConnect("Alarma", ""); // Nombre y Contraseña de Wifi LAN

  if (!wifiManager.autoConnect("Alarma", "")) {
    Serial.println("Fallo al conectar, Timeout");
    /*DELAY*/time_now = millis(); while(millis() < time_now+period1500){/*wait approx. [period]ms*/}/*DELAY*/
    ESP.restart();
    /*DELAY*/time_now = millis(); while(millis() < time_now+period1500){/*wait approx. [period]ms*/}/*DELAY*/
  }
    
  //Lee actualiza datos
  strcpy(auth, custom_auth.getValue());

  //Guarda parametros FS
  if (shouldSaveConfig) {
    Serial.println("Guardado");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["auth"] = auth;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("fallo al abrir config");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }

// En reemplazo a Blynk.begin(auth, ssid, pass, host, port); // (Si se quiere usar un servidor propio quedaria: Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);)
   Blynk.connectWiFi(ssid, pass);

  // Utilizado para conectar, tiene que estar antes de Blynk.connect()
    timer.setInterval(11000L, CheckConnection); // check
  
    Blynk.config(auth, host, port);
    Blynk.connect();

//PinModes e inicios Digitales
    pinMode(LED_IN, OUTPUT); // Led integrado como Salida // LED_BUILTIN0
    pinMode(Sirena, OUTPUT); // Sirena Conexion
    pinMode(Reles1, OUTPUT); // Salida o Rele N°1
    pinMode(Reles2, OUTPUT); // Salida o Rele N°2
    pinMode(Reles3, OUTPUT); // Salida o Rele N°3
    pinMode(Reles4, OUTPUT); // Salida o Rele N°4
    pinMode(Reles5, OUTPUT); // Salida o Rele N°5
    pinMode(InputReset, INPUT); // Entrada de voltaje, input boton de Reset
    pinMode(ReceptorRF, INPUT); // Entrada de datos RF
    
//LEE Y ACTUALIZA VARIABLES DE LAS MEMORIAS (eeAddress, val)
    EEPROM.get(mems1, mem1); EEPROM.get(mems2, mem2); EEPROM.get(mems3, mem3); EEPROM.get(mems4, mem4); EEPROM.get(mems5, mem5); EEPROM.get(mems6, mem6);
    EEPROM.get(mems7, mem7); EEPROM.get(mems8, mem8); EEPROM.get(mems9, mem9); EEPROM.get(mems10, mem10); EEPROM.get(mems11, mem11); EEPROM.get(mems12, mem12);
    EEPROM.get(mems13, mem13); EEPROM.get(mems14, mem14); EEPROM.get(mems15, mem15); EEPROM.get(mems16, mem16); EEPROM.get(mems17, mem17); EEPROM.get(mems18, mem18);
    EEPROM.get(mems19, mem19); EEPROM.get(mems20, mem20); EEPROM.get(mems21, mem21); EEPROM.get(mems22, mem22); EEPROM.get(mems23, mem23); EEPROM.get(mems24, mem24);
    EEPROM.get(mca1, ca1); EEPROM.get(mca2, ca2); EEPROM.get(mca3, ca3); EEPROM.get(mca4, ca4); EEPROM.get(mca5, ca5); EEPROM.get(mca6, ca6); EEPROM.get(mca7, ca7); EEPROM.get(mca8, ca8); EEPROM.get(mca9, ca9); EEPROM.get(mca10, ca10);
    EEPROM.get(mcd1, cd1); EEPROM.get(mcd2, cd2); EEPROM.get(mcd3, cd3); EEPROM.get(mcd4, cd4); EEPROM.get(mcd5, cd5); EEPROM.get(mcd6, cd6); EEPROM.get(mcd7, cd7); EEPROM.get(mcd8, cd8); EEPROM.get(mcd9, cd9); EEPROM.get(mcd10, cd10);
    EEPROM.commit();
}

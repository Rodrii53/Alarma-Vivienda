/*
  SIMBOLOGIA EN ORDEN:
  Pin 16   =   SIRENA CONEXION (RESISTENCIA PULL-DOWN)
  Pin 5     =   Rele N°1
  Pin 4     =   Rele N°2
  Pin 0    =   Rele N°3 (NO USAR DE ENTRADA)
  Pin 2    =   Led Integrado (Esta invertido) (NO A GND AL ARRANCAR)
  Pin de voltaje (3,3v)
  Pin de tierra o GND (0v)
  Pin 14    =   Rele N°4
  Pin 12    =   Rele N°5
  Pin 13    =   Entrada de voltaje, input boton de Reset
  Pin 15   =   Receptor 403Mhz (NO PULL-UP)
  Pin 3    =   LIBRE (NO USABLE CON UART)
  Pin 1    =   LIBRE (NO USABLE CON UART)
  Pin de tierra o GND (0v)
  Pin de voltaje (3,3v)
  Pin 17    =   Reservado para Microfono (ADC0)
  Pin 6  =   No son usables, estan reservados
*/

//#define BLYNK_DEBUG PARA VER SI ESTA CONECTADO CONSTANTEMENTE https://community.blynk.cc/t/solved-how-to-run-blynk-run-only-when-wifi-connection-is-established/6492/13
#define BLYNK_TIMEOUT_MS  750  // Tiene que estar antes de la libreria BlynkSimpleEsp   
#define BLYNK_HEARTBEAT   17   // Tiene que estar antes de la libreria BlynkSimpleEsp   

//.....................................//DEFINES E INCLUDES//.....................................//
  #include "SPIFFS.h" // Se extrae en Documentos/Arduino/tools https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
  #define BLYNK_PRINT Serial // Comente esto para desactivar impresiones y ahorrar espacio
  #include <BlynkSimpleEsp32.h> // Permite usar las librerias de Blynk
  #include <WiFi.h> // Permite conectarse al Wifi usando las librerias esp32
  #include <WidgetRTC.h> // Permite usar las librerias de Blynk del tiempo
  #include <EEPROM.h> // Habilita usar la Memoria Interna
  #include <RCSwitch.h> // Habilita el Receptor de Frecuencia.
  #include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
  #include <Keypad.h>

//WIFI MANAGER
#include <WebServer.h> //Local DNS Server used for redirecting all requests to the configuration portal (https://github.com/zhouhan0126/WebServer-esp32)
#include <DNSServer.h> //Local WebServer used to serve the configuration portal (https://github.com/zhouhan0126/DNSServer---esp32)
#include <WiFiManager.h>   // WiFi Configuration Magic (https://github.com/zhouhan0126/WIFIMANAGER-ESP32)

BlynkTimer timer;

// Defino los colores y entradas
#define Rojo        "#780000"
#define Amarillo    "#ebeb00"
#define Verde       "#009c00"

#define LED_IN      2
#define Sirena      23 //16
#define Reles1      22 //5
#define Reles2      1 //4
#define Reles3      3 //0
#define Reles4      5 //14
#define Reles5      17 //12
#define InputReset  16 //13
#define ReceptorRF  4 //15


// Define las llamadas de funciones en otras pestañas. Despues de un tiempo si no esta, tira error de compilacion
void WifiPinesMemoria(); void CheckConnection();
void controlRF();
void GPS();
void Rele1(); void Rele2(); void Rele3(); void Rele4(); void Rele5();
void BotonAlarma(); void BotonAlarmaSilen(); void BotonAlarmaSinc();
void BotonPanico();
void ControlNuevo(); void SensorNuevo();
void ComandosTerminal();
void ControlBorrar(); void SensorBorrar();
void SensorZona();
void SirenaDisparada();

//.....................................//DATOS CONEXION BLYNK//.....................................//
  char auth[35] = ""; 
  char ssid[] = ""; // Nombre de la red WIFI
  char pass[] = ""; // Contraseña de la red WIFI
  const char* host = "blynk.en-26.com";
  unsigned int port = 9600;

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void CheckConnection(){    // check every 11s if connected to Blynk server
  if(!Blynk.connected()){
    Serial.println("Conectado al Blynk server"); 
    Blynk.connect();  // try to connect to server with default timeout
  }
  else{
    Serial.println("Conectado al Blynk server");     
  }
}
//.....................................//TECLADO Y TEMPERATURA INTERNA//.....................................//
const byte ROWS = 5; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'P', 'E', 'F'},
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
/*byte rowPins[ROWS] = {7, 4, 8, 5, 9}; 
  byte colPins[COLS] = {3, 6, 2};*/
byte rowPins[ROWS] = {14, 25, 12, 26, 13}; // P 1 4 7
byte colPins[COLS] = {33, 27, 32}; // * 0 #

char contrasena[]="3699"; // En esta linea creamos la constante de cadena llamada contraseña (el numero 2222 puede ser cambiado)
char codigot[4]; // Creamos otra constante, en esta se guardaran los caracteres que presionemos en nuestro teclado matricial 4x4
int cont=0; // Esta es una variable que nos servirá más adelante

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

 #ifdef __cplusplus
  extern "C" {
 #endif
  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

//.....................................//HABILITA LOS LEDS/TERMINALES VIRTUALES//.....................................//
  WidgetLED estado(V0); // Permite verificar el estado de la alarma
  WidgetLED dispositivo(V7); // Permite verificar que el dispositivo se encuentre en linea
  WidgetTerminal terminal(V3); // Habilita la terminal
  WidgetRTC rtc; // Habilita el tiempo
  WidgetLED sensor1(V16); WidgetLED sensor2(V17); WidgetLED sensor3(V18); WidgetLED sensor4(V19); WidgetLED sensor5(V20); WidgetLED sensor6(V21); // Habilita LED sensor zona 1
  WidgetLED sensor7(V22); WidgetLED sensor8(V23); WidgetLED sensor9(V24); WidgetLED sensor10(V25); WidgetLED sensor11(V26); WidgetLED sensor12(V27); // Habilita LED sensor zona 2
  WidgetLED sensor13(V28); WidgetLED sensor14(V29); WidgetLED sensor15(V30); WidgetLED sensor16(V31); WidgetLED sensor17(V32); WidgetLED sensor18(V33); // Habilita LED sensor zona 3
  WidgetLED sensor19(V34); WidgetLED sensor20(V35); WidgetLED sensor21(V36); WidgetLED sensor22(V37); WidgetLED sensor23(V38); WidgetLED sensor24(V39); // Habilita LED sensor zona 4
  
//.....................................//ACLARACIONES DE VARIABLES//.....................................//
  RCSwitch mySwitch = RCSwitch(); // Le da valor a mySwitch
  /*DELAY*/
  unsigned long time_now = 0;
  int period100 = 100;// Para loop
  int period250 = 250; //Para sirena
  int period500 = 500; // Para nuevos dispositivos
  int period800 = 800; //Cosas de RF
  int period1000 = 1000; // Variados
  int period1500 = 1500; // Variados
  
  // Se utiliza para que una accion se realize cuando el valor de una entrada cambie de su valor anterior
  int anteriorrf=0; int actualrf;

  // Variables
  char hora[25];
  int fabrica=0;
  int sensorN=99;
  int controlN=99;
  int parametroInt;
  String parametroStg;
  int ALARMA=0; int SIRENA=0;
  int actived=0; // Para no spamear el control de activar
  int codigo;
  int Sactivo=0;
  int panic=0;
  int defzona=0; int zona1=1; int zona2=1; int zona3=1; int zona4=1;
  int ssd1; int ssd2; int ssd3; int ssd4; int ssd5; int ssd6; int ssd7; int ssd8; int ssd9; int ssd10; int ssd11; int ssd12; int ssd13; int ssd14; int ssd15; int ssd16; int ssd17; int ssd18; int ssd19; int ssd20; int ssd21; int ssd22; int ssd23; int ssd24;

  // Declaradas las memorias y Sensores/Controles (30 para cosas, y 10 el resto)
  /*int fauth=0; int mfauth=1; SON DE TOKEN VIEJO*/ int mems0=0; 
     // Memoria Sensores
  int mems1=60; int mems2=70; int mems3=80; int mems4=90; int mems5=100; int mems6=110; int mems7=120; int mems8=130; int mems9=140; int mems10=150; int mems11=160; int mems12=170; int mems13=180; int mems14=190; int mems15=200; int mems16=210; int mems17=220; int mems18=230; int mems19=240; int mems20=250; int mems21=260; int mems22=270; int mems23=280; int mems24=290;
     // Sensores
  int mem1=1; int mem2=1; int mem3=1; int mem4=1; int mem5=1; int mem6=1; int mem7=1; int mem8=1; int mem9=1; int mem10=1; int mem11=1; int mem12=1; int mem13=1; int mem14=1; int mem15=1; int mem16=1; int mem17=1; int mem18=1; int mem19=1; int mem20=1; int mem21=1; int mem22=1; int mem23=1; int mem24=1;
     // Memorias Controles
  int mca1=300; int mca2=310; int mca3=320; int mca4=330; int mca5=340; int mca6=350; int mca7=360; int mca8=370; int mca9=380; int mca10=390; int mcd1=400; int mcd2=410; int mcd3=420; int mcd4=430; int mcd5=440; int mcd6=450; int mcd7=460; int mcd8=470; int mcd9=480; int mcd10=490;
     // Controles
  int ca1=1; int ca2=1; int ca3=1; int ca4=1; int ca5=1; int ca6=1; int ca7=1; int ca8=1; int ca9=1; int ca10=1; int cd1=1; int cd2=1; int cd3=1; int cd4=1; int cd5=1; int cd6=1; int cd7=1; int cd8=1; int cd9=1; int cd10=1;
  
//.....................................//AL CONECTAR BLYNK REALIZA ESTAS ACCIONES (SINCRONIZA)//.....................................//
  BLYNK_CONNECTED() {
    rtc.begin();
    Blynk.virtualWrite(V1, "Sincronizando Dispositivo");
    //Pestaña Alarma
      Blynk.syncVirtual(V0); //Led del estado de la alarma
      Blynk.syncVirtual(V3); //Terminal
      Blynk.syncVirtual(V4); //GPS Virtual
      Blynk.syncVirtual(V2); //Boton para activar la alarma  Silenciada
      Blynk.syncVirtual(V6); //Boton para verificar el estado del dispositivo
      Blynk.syncVirtual(V7); //Led para verificar el estado del dispositivo
      Blynk.syncVirtual(V8); //Limpiador de terminal
    //Pestaña Salidas
      Blynk.syncVirtual(V11); //Rele o Salida 1
      Blynk.syncVirtual(V12); //Rele o Salida 2
      Blynk.syncVirtual(V13); //Rele o Salida 3
      Blynk.syncVirtual(V14); //Rele o Salida 4
      Blynk.syncVirtual(V15); //Rele o Salida 5
    //Pestaña Sensores
      Blynk.syncVirtual(V16); Blynk.syncVirtual(V17); Blynk.syncVirtual(V18); Blynk.syncVirtual(V19); Blynk.syncVirtual(V20); Blynk.syncVirtual(V21); //LED Sensor en Zona 1
      Blynk.syncVirtual(V22); Blynk.syncVirtual(V23); Blynk.syncVirtual(V24); Blynk.syncVirtual(V25); Blynk.syncVirtual(V26); Blynk.syncVirtual(V27); //LED Sensor en Zona 2
      Blynk.syncVirtual(V28); Blynk.syncVirtual(V29); Blynk.syncVirtual(V30); Blynk.syncVirtual(V31); Blynk.syncVirtual(V32); Blynk.syncVirtual(V33); //LED Sensor en Zona 3
      Blynk.syncVirtual(V34); Blynk.syncVirtual(V35); Blynk.syncVirtual(V36); Blynk.syncVirtual(V37); Blynk.syncVirtual(V38); Blynk.syncVirtual(V39); //LED Sensor en Zona 4
      Blynk.syncVirtual(V40); // Zona 1
      Blynk.syncVirtual(V41); // Zona 2
      Blynk.syncVirtual(V42); // Zona 3
      Blynk.syncVirtual(V43); // Zona 4
    //Dejamos todo en reposo
      Blynk.virtualWrite(V1, "SIRENA EN DESCANSO"); 
      Blynk.virtualWrite(V1, "Dispositivo Sincronizado");
      Blynk.virtualWrite(V44, LOW); // PANICO OFF
      Blynk.virtualWrite(V9, LOW); // Si se apaga cuando estan activos, se prende igual
      Blynk.virtualWrite(V10, LOW); // Si se apaga cuando estan activos, se prende igual
      estado.on(); //Led virtual V0
      sensor1.off(); sensor2.off(); sensor3.off(); sensor4.off(); sensor5.off(); sensor6.off(); sensor7.off(); sensor8.off(); sensor9.off(); sensor10.off(); sensor11.off(); sensor12.off(); sensor13.off(); sensor14.off(); sensor15.off(); sensor16.off(); sensor17.off(); sensor18.off(); sensor19.off(); sensor20.off(); sensor21.off(); sensor22.off(); sensor23.off(); sensor24.off();
      terminal.print(hora); terminal.println("Dispositivo Sincronizado"); terminal.flush();
}
    
void setup()
{
  //Configuracion basica, no tocar
    Serial.begin(115200);
    SPIFFS.begin();
    EEPROM.begin(4096); // Cantidad de memoria permitida de usar
    EEPROM.get(mems0, fabrica); EEPROM.commit(); // Datos de reinicio de fabrica

    WifiPinesMemoria(); // Configuracion del wifi, pines y memorias. Luego de esto ya esta conectado a la red
    mySwitch.enableReceive(digitalPinToInterrupt(ReceptorRF)); // Receiver on inerrupt - Activa RF
}

void loop()
{
 if(Blynk.connected()){ Blynk.run(); /*DELAY*/time_now = millis(); while(millis() < time_now+period100){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(LED_IN, LOW); } else{ /*DELAY*/time_now = millis(); while(millis() < time_now+period1000){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(LED_IN, LOW); } //Importante, Mantiene la conexion wifi y // LED_BUILTIN
  timer.run();
  
  sprintf(hora, "[%02d:%02d:%02d %02d|%02d|%02d] ", hour(), minute(), second(), day(), month(), year()); // Se encarga de mostrar el tiempo en cada linea de la terminal de Blynk
  controlRF();

//TECLADO
char customKey = customKeypad.getKey(); //esta linea indica que el carácter presionado se guardara en la variable customKey
 if (customKey != NO_KEY){ //Con este siclo preguntamos si se presiono una tecla, si se presiono entonce el ciclo continua
  if (customKey=='*'){ panic=1; SIRENA=1; ALARMA=1; SirenaDisparada(); }
 codigot[cont]=customKey; //se guardaran los caracteres presionados en codigot[cont]
 //Serial.print(codigot[cont]); //Se imprime en nuestro monitor serial lo que este guardado en codigot[cont]
 cont=cont+1; //incrementamos la variable cont (esto con el fin de tener los 4 dígitos que requerimos)
 if(cont==4){ //Ahora comienza otro siclo if, en el cual se pregunta si ya hay 4 datos guardados y si es así entonce el siclo continua
 if(codigot[0]==contrasena[0]&&codigot[1]==contrasena[1]&&codigot[2]==contrasena[2]&&codigot[3]==contrasena[3]){
 terminal.print(hora); terminal.println("Se utilizo correctamente el teclado"); terminal.flush(); //si la contraseña es correcta entonces se imprime ""Password correcta")
 if (ALARMA==0){ Blynk.virtualWrite(V5, HIGH); }else { Blynk.virtualWrite(V5, LOW); } Blynk.syncVirtual(V5);
  digitalWrite(Reles5, HIGH); /*DELAY*/time_now = millis(); while(millis() < time_now+period250){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Reles5, LOW);
 }
 if(codigot!=contrasena){ //empieza un nuevo ciclo, esta vez indicamos si el código es diferente que la contraseña siga con el siclo
 terminal.print(hora); terminal.println("La contraseña ingresada por tecladdo es incorrecta"); terminal.flush(); // se imprime que que la Password es incorrecta
 digitalWrite(Reles5, HIGH); /*DELAY*/time_now = millis(); while(millis() < time_now+period1500){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Reles5, LOW);
 }
 cont=0; //resetear a 0 la variable cont
 }}
//FIN TECLADO

//RESTAURA DE FABRICA
if (digitalRead(InputReset) == LOW || fabrica==0) { // FALTA INPUT DE BOTON RESET
      terminal.print(hora);
      terminal.println("Restaurando de Fabrica");
      terminal.print("Recuerde que su TOKEN es: ");
      terminal.println(auth);
      terminal.flush();
      fabrica=0;
      EEPROM.put(mems0, fabrica);
      EEPROM.put(mems1,1); EEPROM.put(mems2,1); EEPROM.put(mems3,1); EEPROM.put(mems4,1); EEPROM.put(mems5,1); EEPROM.put(mems6,1); EEPROM.put(mems7,1); EEPROM.put(mems8,1); EEPROM.put(mems9,1); EEPROM.put(mems10,1); EEPROM.put(mems11,1); EEPROM.put(mems12,1); EEPROM.put(mems13,1); EEPROM.put(mems14,1); EEPROM.put(mems15,1); EEPROM.put(mems16,1); EEPROM.put(mems17,1); EEPROM.put(mems18,1); EEPROM.put(mems19,1); EEPROM.put(mems20,1); EEPROM.put(mems21,1); EEPROM.put(mems22,1); EEPROM.put(mems23,1); EEPROM.put(mems24,1);
      EEPROM.put(mca1,1); EEPROM.put(mca2,1); EEPROM.put(mca3,1); EEPROM.put(mca4,1); EEPROM.put(mca5,1); EEPROM.put(mca6,1); EEPROM.put(mca7,1); EEPROM.put(mca8,1); EEPROM.put(mca9,1); EEPROM.put(mca10,1); EEPROM.put(mcd1,1); EEPROM.put(mcd2,1); EEPROM.put(mcd3,1); EEPROM.put(mcd4,1); EEPROM.put(mcd5,1); EEPROM.put(mcd6,1); EEPROM.put(mcd7,1); EEPROM.put(mcd8,1); EEPROM.put(mcd9,1); EEPROM.put(mcd10,1);
      EEPROM.commit(); /*DELAY*/time_now = millis(); while(millis() < time_now+period1000){/*wait approx. [period]ms*/}/*DELAY*/ ESP.restart();
    }
//FIN RESTAURA DE FABRICA
/*DELAY*/time_now = millis(); while(millis() < time_now+period100){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(LED_IN, HIGH); // LED_BUILTIN
}

//.....................................//ACCIONES DE BLYNK VIRTUAL//.....................................//

// BOTON ACTIVA/DESACTIVA ALARMA
  BLYNK_WRITE(V5){ parametroInt=param.asInt(); BotonAlarma(); }
  BLYNK_WRITE(V45){ parametroInt=param.asInt(); BotonAlarmaSilen(); }
  BLYNK_WRITE(V2){ parametroInt=param.asInt(); BotonAlarmaSinc(); }
  
// BOTON PANICO
  BLYNK_WRITE(V44){ parametroInt=param.asInt(); BotonPanico(); }
  
// BUSCAR CONTROL 5 SEGUNODS Y LO GUARDA
  BLYNK_WRITE(V10){ parametroInt=param.asInt(); ControlNuevo(); }

// BUSCAR SENSOR 10 SEGUNODS Y LO GUARDA
  BLYNK_WRITE(V9){ parametroInt=param.asInt(); SensorNuevo(); }

// COMANDOS NODE MCU POR TERMINAL
  BLYNK_WRITE(V3){ parametroStg=param.asStr(); parametroInt=param.asInt(); ComandosTerminal(); } 

// ACTUADOR GPS
  BLYNK_WRITE(V4){ parametroInt=param.asInt(); GPS(); }

// BLOQUEA Y DESBLOQUEA ZONAS
  BLYNK_WRITE(V40) { if (param.asInt() == HIGH) { zona1=2; } else { zona1=1; } }
  BLYNK_WRITE(V41) { if (param.asInt() == HIGH) { zona2=2; } else { zona2=1; } }
  BLYNK_WRITE(V42) { if (param.asInt() == HIGH) { zona3=2; } else { zona3=1; } }
  BLYNK_WRITE(V43) { if (param.asInt() == HIGH) { zona4=2; } else { zona4=1; } }

// VERIFICADOR DE CONEXION ENTRE DISPOSITIVO Y SERVER BLYNK
  BLYNK_WRITE(V6){ if (param.asInt() == HIGH){ dispositivo.on(); } else{ dispositivo.off(); }}

// LIMPIEZA DE CONSOLA
  BLYNK_WRITE(V8){ if (param.asInt() == HIGH){
    terminal.clear(); terminal.println("Comandos Disponibles: reiniciar - fabrica - hora - eliminar sensor - eliminar control"); terminal.print("Calidad del Wifi: ");
    if (WiFi.RSSI()>-55){ terminal.print("Excelente! -- "); }else if (WiFi.RSSI()>-65){ terminal.print("Muy buena! -- "); }else if (WiFi.RSSI()>-75){ terminal.print("Buena! -- "); }else if (WiFi.RSSI()>-85){ terminal.print("No es la mejor! -- "); }else if (WiFi.RSSI()>-90){ terminal.print("Pesimo, intente acercar su Wifi! -- "); }
    terminal.print(((temprature_sens_read() - 32) * 0.55)); terminal.println(" C"); terminal.flush(); }}
  
// CONTRO DE RELES/SALIDAS
/*Rele1*/BLYNK_WRITE(V11){ parametroInt=param.asInt(); Rele1(); }
/*Rele2*/BLYNK_WRITE(V12){ parametroInt=param.asInt(); Rele2(); }
/*Rele3*/BLYNK_WRITE(V13){ parametroInt=param.asInt(); Rele3(); }
/*Rele4*/BLYNK_WRITE(V14){ parametroInt=param.asInt(); Rele4(); }
/*Rele5*/BLYNK_WRITE(V15){ parametroInt=param.asInt(); Rele5(); }

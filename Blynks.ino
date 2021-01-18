//.....................................//BOTON ACTIVA/DESACTIVA ALARMA//.....................................//
void BotonAlarma(){
switch (parametroInt) {
      case LOW: digitalWrite(Sirena, HIGH); /*DELAY*/time_now = millis(); while(millis() < time_now+period250){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Sirena, LOW); /*DELAY*/time_now = millis(); while(millis() < time_now+period250){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Sirena, HIGH); /*DELAY*/time_now = millis(); while(millis() < time_now+period250){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Sirena, LOW); break;
      case HIGH: digitalWrite(Sirena, HIGH); /*DELAY*/time_now = millis(); while(millis() < time_now+period250){/*wait approx. [period]ms*/}/*DELAY*/ digitalWrite(Sirena, LOW); break; }BotonAlarmaSilen(); }

void BotonAlarmaSilen(){
switch (parametroInt) {
      case LOW: Blynk.notify("Proteccion Desactivada"); terminal.print(hora); terminal.println("Proteccion Desactivada"); terminal.flush(); break;
      case HIGH: Blynk.notify("Proteccion Activada"); terminal.print(hora); terminal.println("Proteccion Activada"); terminal.flush(); break; }BotonAlarmaSinc(); }

void BotonAlarmaSinc(){
switch (parametroInt) {
      case LOW: ALARMA=0; SIRENA=0; Blynk.setProperty(V5, "offBackColor", Rojo); Blynk.virtualWrite(V5, LOW); Blynk.setProperty(V45, "offBackColor", Rojo); Blynk.virtualWrite(V45, LOW); Blynk.virtualWrite(V2, LOW); Blynk.setProperty(V0, "color", Rojo); Blynk.virtualWrite(V1, "Proteccion Desactivada");
      sensor1.off(); sensor2.off(); sensor3.off(); sensor4.off(); sensor5.off(); sensor6.off(); sensor7.off(); sensor8.off(); sensor9.off(); sensor10.off(); break;
      case HIGH: ALARMA=1; Blynk.setProperty(V5, "onBackColor", Verde); Blynk.virtualWrite(V5, HIGH); Blynk.setProperty(V45, "onBackColor", Verde); Blynk.virtualWrite(V45, HIGH); Blynk.virtualWrite(V2, HIGH); Blynk.setProperty(V0, "color", Verde); Blynk.virtualWrite(V1, "Proteccion Activada"); break; } }
//.....................................//FIN BOTON ACTIVA/DESACTIVA ALARMA//.....................................//

//.....................................//BOTON PANICO//.....................................//
void BotonPanico() {
  switch (parametroInt) {
      case LOW: Blynk.virtualWrite(V5, LOW); Blynk.syncVirtual(V5); Sactivo=0; panic=0; ALARMA=0; break;
      case HIGH: panic=1; SIRENA=1; ALARMA=1; SirenaDisparada(); break; } }
//.....................................//FIN BOTON PANICO//.....................................//

//.....................................//BUSCAR CONTROL 5 SEGUNODS Y LO GUARDA//.....................................//
void ControlNuevo(){
  if (parametroInt==HIGH){ int cactivo=0;
    if (cactivo==0){ terminal.println("Tiene 5 segundos para presionar boton de ""Activar"""); terminal.flush();
    
        for (int x=1; x <=10; x++) {  //Se mantiene en accion durante 5 segundos (por los 500ms 10 veces)
          /*DELAY*/time_now = millis(); while(millis() < time_now+period500){/*wait approx. [period]ms*/}/*DELAY*/
    // Inicio de accion
        if (mySwitch.available()) { int rf=mySwitch.getReceivedValue();
        if (rf == 0) { Serial.print("Unknown encoding");}
          else if (rf==ca1||rf==ca2||rf==ca3||rf==ca4||rf==ca5||rf==ca6||rf==ca7||rf==ca8||rf==ca9||rf==ca10||rf==cd1||rf==cd2||rf==cd3||rf==cd4||rf==cd5||rf==cd6||rf==cd7||rf==cd8||rf==cd9||rf==cd10){
              terminal.println("Control/Boton ya registrado, por favor utilize otro."); terminal.flush(); cactivo=1; }
          else if (cactivo==0){ codigo= mySwitch.getReceivedValue(); cactivo=1;
            if (ca1==1){ ca1=codigo; EEPROM.put(mca1, ca1); terminal.println("Control de Activacion 1 agregado!");}
            else if (ca2==1){ ca2=codigo; EEPROM.put(mca2, ca2); terminal.println("Control de Activacion 2 agregado!");}
            else if (ca3==1){ ca3=codigo; EEPROM.put(mca3, ca3); terminal.println("Control de Activacion 3 agregado!");}
            else if (ca4==1){ ca4=codigo; EEPROM.put(mca4, ca4); terminal.println("Control de Activacion 4 agregado!");}
            else if (ca5==1){ ca5=codigo; EEPROM.put(mca5, ca5); terminal.println("Control de Activacion 5 agregado!");}
            else if (ca6==1){ ca6=codigo; EEPROM.put(mca6, ca6); terminal.println("Control de Activacion 6 agregado!");}
            else if (ca7==1){ ca7=codigo; EEPROM.put(mca7, ca7); terminal.println("Control de Activacion 7 agregado!");}
            else if (ca8==1){ ca8=codigo; EEPROM.put(mca8, ca8); terminal.println("Control de Activacion 8 agregado!");}
            else if (ca9==1){ ca9=codigo; EEPROM.put(mca9, ca9); terminal.println("Control de Activacion 9 agregado!");}
            else if (ca10==1){ ca10=codigo; EEPROM.put(mca10, ca10); terminal.println("Control de Activacion 10 agregado!");}
            else { terminal.println("Memoria llena");}
      } // Fin de accion.
      x=10; } } EEPROM.commit(); terminal.flush(); /*DELAY*/time_now = millis(); while(millis() < time_now+period1500){/*wait approx. [period]ms*/}/*DELAY*/ mySwitch.resetAvailable();  // Reiniciamos la clase para otra lectura
    }
    
    if (cactivo==1){ terminal.println("Tiene 5 segundos para presionar boton de ""Desactivar"""); terminal.flush();
    
        for (int x=1; x <=10; x++) {  //Se mantiene en accion durante 10 segundos
          /*DELAY*/time_now = millis(); while(millis() < time_now+period500){/*wait approx. [period]ms*/}/*DELAY*/
    // Inicio de accion
        if (mySwitch.available()) { int rf=mySwitch.getReceivedValue();
        if (rf == 0) { Serial.print("Unknown encoding");}
      else if (rf==ca1||rf==ca2||rf==ca3||rf==ca4||rf==ca5||rf==ca6||rf==ca7||rf==ca8||rf==ca9||rf==ca10||rf==cd1||rf==cd2||rf==cd3||rf==cd4||rf==cd5||rf==cd6||rf==cd7||rf==cd8||rf==cd9||rf==cd10){
        terminal.println("Control/Boton ya registrado, por favor utilize otro"); terminal.flush(); } 
      else if (cactivo==1){ codigo= mySwitch.getReceivedValue();
      if (cd1==1){ cd1=codigo; EEPROM.put(mcd1, cd1); terminal.println("Control de Desactivacion 1 agregado!");} 
      else if (cd2==1){ cd2=codigo; EEPROM.put(mcd2, cd2); terminal.println("Control de Desactivacion 2 agregado!");}
      else if (cd3==1){ cd3=codigo; EEPROM.put(mcd3, cd3); terminal.println("Control de Desactivacion 3 agregado!");}
      else if (cd4==1){ cd4=codigo; EEPROM.put(mcd4, cd4); terminal.println("Control de Desactivacion 4 agregado!");}
      else if (cd5==1){ cd5=codigo; EEPROM.put(mcd5, cd5); terminal.println("Control de Desactivacion 5 agregado!");}
      else if (cd6==1){ cd6=codigo; EEPROM.put(mcd6, cd6); terminal.println("Control de Desactivacion 6 agregado!");}
      else if (cd7==1){ cd7=codigo; EEPROM.put(mcd7, cd7); terminal.println("Control de Desactivacion 7 agregado!");}
      else if (cd8==1){ cd8=codigo; EEPROM.put(mcd8, cd8); terminal.println("Control de Desactivacion 8 agregado!");}
      else if (cd9==1){ cd9=codigo; EEPROM.put(mcd9, cd9); terminal.println("Control de Desactivacion 9 agregado!");}
      else if (cd10==1){ cd10=codigo; EEPROM.put(mcd10, cd10); terminal.println("Control de Desactivacion 10 agregado!");}
      else { terminal.println("Memoria llena");}
      } // Fin de accion.
x=10; }} EEPROM.commit(); terminal.flush(); /*DELAY*/time_now = millis(); while(millis() < time_now+period1500){/*wait approx. [period]ms*/}/*DELAY*/ mySwitch.resetAvailable();  // Reiniciamos la clase para otra lectura
      }  Blynk.virtualWrite(V10, LOW);}}
//.....................................//FIN BUSCAR CONTROL 5 SEGUNODS Y LO GUARDA//.....................................//

//.....................................//BUSCAR SENSOR 10 SEGUNODS Y LO GUARDA//.....................................//
void SensorNuevo(){
    if (parametroInt == HIGH) { // Hace todo esto si esta el boton apretado
    terminal.println("Tiene 10 segundos para mover su sensor"); terminal.flush();
    for (int x=1; x <=10; x++) {  //Se mantiene en accion durante 5 segundos (por los 500ms 10 veces)
    /*DELAY*/time_now = millis(); while(millis() < time_now+period1000){/*wait approx. [period]ms*/}/*DELAY*/
    // Inicio de accion
    if (mySwitch.available()) { int rf=mySwitch.getReceivedValue();
        if (rf == 0) { Serial.print("Unknown encoding");}
        else if (rf==mem1||rf==mem2||rf==mem3||rf==mem4||rf==mem5||rf==mem6||rf==mem7||rf==mem8||rf==mem9||rf==mem10||rf==mem11||rf==mem12||rf==mem13||rf==mem14||rf==mem15||rf==mem16||rf==mem17||rf==mem18||rf==mem19||rf==mem20||rf==mem21||rf==mem22||rf==mem23||rf==mem24){
        terminal.println("Sensor ya registrado, por favor elije otro"); terminal.flush(); }
      else {
      codigo= mySwitch.getReceivedValue(); defzona=1;
      terminal.println("Elija la zona para su nuevo sensor (1-4)"); terminal.flush(); }
    // Fin de accion
x=10; } } Blynk.virtualWrite(V9, LOW); mySwitch.resetAvailable(); }} // Reiniciamos la clase para otra lectura
//.....................................//FIN BUSCAR SENSOR 10 SEGUNODS Y LO GUARDA//.....................................//

//.....................................//COMANDOS NODE MCU POR TERMINAL//.....................................//
void ComandosTerminal(){
    if (String("reiniciar")==parametroStg){ Blynk.virtualWrite(V1, "Reiniciando Dispositivo"); terminal.print(hora); terminal.println("Reiniciando Dispositivo"); terminal.flush(); /*DELAY*/time_now = millis(); while(millis() < time_now+period500){/*wait approx. [period]ms*/}/*DELAY*/ ESP.restart();}
    else if (String("ayuda")==parametroStg){ terminal.println("Comandos Disponibles: reiniciar - fabrica - hora - eliminar sensor - eliminar control"); terminal.println("Mas ayuda disponible en @Rodrii.iglesias"); terminal.println(""); terminal.flush();}
    else if (String("hora")==parametroStg){ terminal.print(hora); terminal.println(""); terminal.flush();}
    else if (String("fabrica")==parametroStg){fabrica=0;}
    else if (String("eliminar sensor")==parametroStg){ sensorN=0; terminal.println("Nombre cual sensor quiere eliminar (1-24)"); terminal.flush();}
    else if (sensorN==0) {SensorBorrar();} else if (defzona==1) {SensorZona(); }
    else if (String("eliminar control")==parametroStg){ controlN=0; terminal.println("Nombre cual control quiere eliminar (1-10)"); terminal.flush();}
    else if (controlN==0) {ControlBorrar();} }
//.....................................//FIN COMANDOS NODE MCU POR TERMINAL//.....................................//

//.....................................//BORRAR SENSORES y CONTROLES//.....................................//
void SensorBorrar(){
 switch (parametroInt) {
  case 1: terminal.println("Sensor 1 eliminado"); mem1=1; EEPROM.put(mems1, mem1); break;
  case 2: terminal.println("Sensor 2 eliminado"); mem2=1; EEPROM.put(mems2, mem2); break;
  case 3: terminal.println("Sensor 3 eliminado"); mem3=1; EEPROM.put(mems3, mem3); break;
  case 4: terminal.println("Sensor 4 eliminado"); mem4=1; EEPROM.put(mems4, mem4); break;
  case 5: terminal.println("Sensor 5 eliminado"); mem5=1; EEPROM.put(mems5, mem5); break;
  case 6: terminal.println("Sensor 6 eliminado"); mem6=1; EEPROM.put(mems6, mem6); break;
  case 7: terminal.println("Sensor 7 eliminado"); mem7=1; EEPROM.put(mems7, mem7); break;
  case 8: terminal.println("Sensor 8 eliminado"); mem8=1; EEPROM.put(mems8, mem8); break;
  case 9: terminal.println("Sensor 9 eliminado"); mem9=1; EEPROM.put(mems9, mem9); break;
  case 10: terminal.println("Sensor 10 eliminado"); mem10=1; EEPROM.put(mems10, mem10); break;
  case 11: terminal.println("Sensor 11 eliminado"); mem11=1; EEPROM.put(mems11, mem11); break;
  case 12: terminal.println("Sensor 12 eliminado"); mem12=1; EEPROM.put(mems12, mem12); break;
  case 13: terminal.println("Sensor 13 eliminado"); mem13=1; EEPROM.put(mems13, mem13); break;
  case 14: terminal.println("Sensor 14 eliminado"); mem14=1; EEPROM.put(mems14, mem14); break;
  case 15: terminal.println("Sensor 15 eliminado"); mem15=1; EEPROM.put(mems15, mem15); break;
  case 16: terminal.println("Sensor 16 eliminado"); mem16=1; EEPROM.put(mems16, mem16); break;
  case 17: terminal.println("Sensor 17 eliminado"); mem17=1; EEPROM.put(mems17, mem17); break;
  case 18: terminal.println("Sensor 18 eliminado"); mem18=1; EEPROM.put(mems18, mem18); break;
  case 19: terminal.println("Sensor 19 eliminado"); mem19=1; EEPROM.put(mems19, mem19); break;
  case 20: terminal.println("Sensor 20 eliminado"); mem20=1; EEPROM.put(mems20, mem20); break;
  case 21: terminal.println("Sensor 21 eliminado"); mem21=1; EEPROM.put(mems21, mem21); break;
  case 22: terminal.println("Sensor 22 eliminado"); mem22=1; EEPROM.put(mems22, mem22); break;
  case 23: terminal.println("Sensor 23 eliminado"); mem23=1; EEPROM.put(mems23, mem23); break;
  case 24: terminal.println("Sensor 24 eliminado"); mem24=1; EEPROM.put(mems24, mem24); break;
  default: terminal.println("Numero erroneo"); break;
} EEPROM.commit(); terminal.flush(); sensorN=99; }
      
void ControlBorrar(){
 switch (parametroInt) {
  case 1: terminal.println("Control 1 eliminado"); ca1=1; cd1=1; EEPROM.put(mca1, ca1); EEPROM.put(mcd1, cd1); break;
  case 2: terminal.println("Control 2 eliminado"); ca2=1; cd2=1; EEPROM.put(mca2, ca2); EEPROM.put(mcd1, cd2); break;
  case 3: terminal.println("Control 3 eliminado"); ca3=1; cd3=1; EEPROM.put(mca3, ca3); EEPROM.put(mcd1, cd3); break;
  case 4: terminal.println("Control 4 eliminado"); ca4=1; cd4=1; EEPROM.put(mca4, ca4); EEPROM.put(mcd1, cd4); break;
  case 5: terminal.println("Control 5 eliminado"); ca5=1; cd5=1; EEPROM.put(mca5, ca5); EEPROM.put(mcd1, cd5); break;
  case 6: terminal.println("Control 6 eliminado"); ca6=1; cd6=1; EEPROM.put(mca6, ca6); EEPROM.put(mcd1, cd6); break;
  case 7: terminal.println("Control 7 eliminado"); ca7=1; cd7=1; EEPROM.put(mca7, ca7); EEPROM.put(mcd1, cd7); break;
  case 8: terminal.println("Control 8 eliminado"); ca8=1; cd8=1; EEPROM.put(mca8, ca8); EEPROM.put(mcd1, cd8); break;
  case 9: terminal.println("Control 9 eliminado"); ca9=1; cd9=1; EEPROM.put(mca9, ca9); EEPROM.put(mcd1, cd9); break;
  case 10: terminal.println("Sensor 10 eliminado"); ca10=1; cd10=1; EEPROM.put(mca10, ca10); EEPROM.put(mems1, cd10); break;
  default: terminal.println("Numero erroneo"); break;
} EEPROM.commit(); terminal.flush(); controlN=99; }
//.....................................//FIN BORRAR SENSORES y CONTROLES//.....................................//

//.....................................//AGREGAR NUEVO SENSOR COMANDO//.....................................//
void SensorZona() {
if (mem1==1 && parametroInt==1){ mem1=codigo; EEPROM.put(mems1, mem1); terminal.println("Sensor 1 agregado en Zona 1");}
else if (mem2==1 && parametroInt==1){ mem2=codigo; EEPROM.put(mems2, mem2); terminal.println("Sensor 2 agregado en Zona 1");}
else if (mem3==1 && parametroInt==1){ mem3=codigo; EEPROM.put(mems3, mem3); terminal.println("Sensor 3 agregado en Zona 1");}
else if (mem4==1 && parametroInt==1){ mem4=codigo; EEPROM.put(mems4, mem4); terminal.println("Sensor 4 agregado en Zona 1");}
else if (mem5==1 && parametroInt==1){ mem5=codigo; EEPROM.put(mems5, mem5); terminal.println("Sensor 5 agregado en Zona 1");}
else if (mem6==1 && parametroInt==1){ mem6=codigo; EEPROM.put(mems6, mem6); terminal.println("Sensor 6 agregado en Zona 1");}
else if (mem7==1 && parametroInt==2){ mem7=codigo; EEPROM.put(mems7, mem7); terminal.println("Sensor 7 agregado en Zona 2");}
else if (mem8==1 && parametroInt==2){ mem8=codigo; EEPROM.put(mems8, mem8); terminal.println("Sensor 8 agregado en Zona 2");}
else if (mem9==1 && parametroInt==2){ mem9=codigo; EEPROM.put(mems9, mem9); terminal.println("Sensor 9 agregado en Zona 2");}
else if (mem10==1 && parametroInt==2){ mem10=codigo; EEPROM.put(mems10, mem10); terminal.println("Sensor 10 agregado en Zona 2");}
else if (mem11==1 && parametroInt==2){ mem11=codigo; EEPROM.put(mems11, mem11); terminal.println("Sensor 11 agregado en Zona 2");}
else if (mem12==1 && parametroInt==2){ mem12=codigo; EEPROM.put(mems12, mem12); terminal.println("Sensor 12 agregado en Zona 2");}
else if (mem13==1 && parametroInt==3){ mem13=codigo; EEPROM.put(mems13, mem13); terminal.println("Sensor 13 agregado en Zona 3");}
else if (mem14==1 && parametroInt==3){ mem14=codigo; EEPROM.put(mems14, mem14); terminal.println("Sensor 14 agregado en Zona 3");}
else if (mem15==1 && parametroInt==3){ mem15=codigo; EEPROM.put(mems15, mem15); terminal.println("Sensor 15 agregado en Zona 3");}
else if (mem16==1 && parametroInt==3){ mem16=codigo; EEPROM.put(mems16, mem16); terminal.println("Sensor 16 agregado en Zona 3");}
else if (mem17==1 && parametroInt==3){ mem17=codigo; EEPROM.put(mems17, mem17); terminal.println("Sensor 17 agregado en Zona 3");}
else if (mem18==1 && parametroInt==3){ mem18=codigo; EEPROM.put(mems18, mem18); terminal.println("Sensor 18 agregado en Zona 3");}
else if (mem19==1 && parametroInt==4){ mem19=codigo; EEPROM.put(mems19, mem19); terminal.println("Sensor 19 agregado en Zona 4");}
else if (mem20==1 && parametroInt==4){ mem20=codigo; EEPROM.put(mems20, mem20); terminal.println("Sensor 20 agregado en Zona 4");}
else if (mem21==1 && parametroInt==4){ mem21=codigo; EEPROM.put(mems21, mem21); terminal.println("Sensor 21 agregado en Zona 4");}
else if (mem22==1 && parametroInt==4){ mem22=codigo; EEPROM.put(mems22, mem22); terminal.println("Sensor 22 agregado en Zona 4");}
else if (mem23==1 && parametroInt==4){ mem23=codigo; EEPROM.put(mems23, mem23); terminal.println("Sensor 23 agregado en Zona 4");}
else if (mem24==1 && parametroInt==4){ mem24=codigo; EEPROM.put(mems24, mem24); terminal.println("Sensor 24 agregado en Zona 4");}
else { terminal.println("Numero erroneo o zona completa, elimine un sensor de la zona elegida");}
      EEPROM.commit(); terminal.flush(); defzona=0; }
//.....................................//FIN AGREGAR NUEVO SENSOR COMANDO//.....................................//

//.....................................//ALERTA GPS//.....................................//
void GPS() {
  if (parametroInt==HIGH && ALARMA==1) {
      Blynk.setProperty(V4, "color", Verde); Blynk.notify("Acuerdate de que tu Alarma esta Activada"); terminal.print(hora); terminal.println("Acuerdate de que tu Alarma esta Activada"); terminal.flush();}
      else{ Blynk.setProperty(V4, "color", Rojo); }  
}
//.....................................//FIN ALERTA GPS//.....................................//

//.....................................//SALIDA DE RELES//.....................................//
void Rele1() {
switch (parametroInt){
      case LOW: Blynk.setProperty(V11, "offBackColor", Rojo); digitalWrite(Reles1, LOW); terminal.print(hora); terminal.println("Salida 1 Desctivada"); terminal.flush(); break;
      case HIGH: Blynk.setProperty(V11, "onBackColor", Verde); digitalWrite(Reles1, HIGH); terminal.print(hora); terminal.println("Salida 1 Activada"); terminal.flush(); break;}
}
void Rele2() {
switch (parametroInt){
      case LOW: Blynk.setProperty(V12, "offBackColor", Rojo); digitalWrite(Reles2, LOW); terminal.print(hora); terminal.println("Salida 2 Desactivada"); terminal.flush(); break;
      case HIGH: Blynk.setProperty(V12, "onBackColor", Verde); digitalWrite(Reles2, HIGH); terminal.print(hora); terminal.println("Salida 2 Activada"); terminal.flush(); break;}
}
void Rele3() {
switch (parametroInt){
      case LOW: Blynk.setProperty(V13, "offBackColor", Rojo); digitalWrite(Reles3, LOW); terminal.print(hora); terminal.println("Salida 3 Desactivada"); terminal.flush(); break;
      case HIGH: Blynk.setProperty(V13, "onBackColor", Verde); digitalWrite(Reles3, HIGH); terminal.print(hora); terminal.println("Salida 3 Activada"); terminal.flush(); break;}
}
void Rele4() {
switch (parametroInt){
      case LOW: Blynk.setProperty(V14, "offBackColor", Rojo); digitalWrite(Reles4, LOW); terminal.print(hora); terminal.println("Salida 4 Desactivada"); terminal.flush(); break;
      case HIGH: Blynk.setProperty(V14, "onBackColor", Verde); digitalWrite(Reles4, HIGH); terminal.print(hora); terminal.println("Salida 4 Activada"); terminal.flush(); break;}
}
void Rele5() {
switch (parametroInt){
      case LOW: Blynk.setProperty(V15, "offBackColor", Rojo); digitalWrite(Reles5, LOW); terminal.print(hora); terminal.println("Salida 5 Desactivada"); terminal.flush(); break;
      case HIGH: Blynk.setProperty(V15, "onBackColor", Verde); digitalWrite(Reles5, HIGH); terminal.print(hora); terminal.println("Salida 5 Activada"); terminal.flush(); break;}
}
//.....................................//FIN SALIDA DE RELES//.....................................//

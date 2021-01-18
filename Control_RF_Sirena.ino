//.....................................//SENSORES Y COMO SE QUEDA PRENDIDA LUZ DE LA QUE DETECTO MOV//.....................................//
 void controlRF() {
  int rf=mySwitch.getReceivedValue();
    if (panic==1 || rf==ca1||rf==ca2||rf==ca3||rf==ca4||rf==ca5||rf==ca6||rf==ca7||rf==ca8||rf==ca9||rf==ca10||rf==cd1||rf==cd2||rf==cd3||rf==cd4||rf==cd5||rf==cd6||rf==cd7||rf==cd8||rf==cd9||rf==cd10||rf==mem1||rf==mem2||rf==mem3||rf==mem4||rf==mem5||rf==mem6||rf==mem7||rf==mem8||rf==mem9||rf==mem10||rf==mem11||rf==mem12||rf==mem13||rf==mem14||rf==mem15||rf==mem16||rf==mem17||rf==mem18||rf==mem19||rf==mem20||rf==mem21||rf==mem22||rf==mem23||rf==mem24) {
      int x=0; actualrf = rf;

    // CONTROL PANICO Y ACTIVA ALARMA
    if (anteriorrf != actualrf) { // Para no Spamear boton panico
    // La accion empieza aca
    if ( rf==ca1||rf==ca2||rf==ca3||rf==ca4||rf==ca5||rf==ca6||rf==ca7||rf==ca8||rf==ca9||rf==ca10){
      if (actived==0){
    Blynk.virtualWrite(V5, HIGH); Blynk.syncVirtual(V5); actived=1; } // ACTIVAR ALARMA, CONTROL ACTIVADO 
        haypanico: x++;
        rf=mySwitch.getReceivedValue(); actualrf = rf;
        if ( rf==ca1||rf==ca2||rf==ca3||rf==ca4||rf==ca5||rf==ca6||rf==ca7||rf==ca8||rf==ca9||rf==ca10){
            for (x; x < 4; x = x + 1) { //Revisa otra vez
              mySwitch.resetAvailable(); /*DELAY*/time_now = millis(); while(millis() < time_now+period800){/*wait approx. [period]ms*/}/*DELAY*/ // Reiniciamos la clase para otra lectura
              goto haypanico; }// La accion termica aca
              panic=1; actived=0; actualrf = rf;}
            }} x=0; actualrf = rf;
            if (anteriorrf != actualrf) { // Para no Spamear boton desactivar
                if ( rf==cd1||rf==cd2||rf==cd3||rf==cd4||rf==cd5||rf==cd6||rf==cd7||rf==cd8||rf==cd9||rf==cd10){ Blynk.virtualWrite(V5, LOW); Blynk.syncVirtual(V5); Blynk.virtualWrite(V44, LOW); Sactivo=0; panic=0; actived=0;} // DESACTIVAR ALARMA, CONTROL DESACTIVADO
            } anteriorrf=actualrf;
    // FIN CONTROL PANICO Y ACTIVA ALARMA
    
       for (int i=1; i<=1 ; i++){
    if (rf == mem1 && zona1==2) { sensor1.on(); ssd1=1; } if (rf == mem2 && zona1==2) { sensor2.on(); ssd2=1; }       if (rf == mem3 && zona1==2) { sensor3.on(); ssd3=1; }   if (rf == mem4 && zona1==2) { sensor4.on(); ssd4=1; }
    if (rf == mem5 && zona1==2) { sensor5.on(); ssd5=1; } if (rf == mem6 && zona1==2) { sensor6.on(); ssd6=1; }       if (rf == mem7 && zona2==2) { sensor7.on(); ssd7=1; }   if (rf == mem8 && zona2==2) { sensor8.on(); ssd8=1; }
    if (rf == mem9 && zona2==2) { sensor9.on(); ssd9=1; } if (rf == mem10 && zona2==2) { sensor10.on(); ssd10=1; }    if (rf == mem11 && zona2==2) { sensor11.on(); ssd11=1; } if (rf == mem12 && zona2==2) { sensor12.on(); ssd12=1; }
    if (rf == mem13 && zona3==2) { sensor13.on(); ssd13=1; } if (rf == mem14 && zona3==2) { sensor14.on(); ssd14=1; } if (rf == mem15 && zona3==2) { sensor15.on(); ssd15=1; } if (rf == mem16 && zona3==2) { sensor16.on(); ssd16=1; }
    if (rf == mem17 && zona3==2) { sensor17.on(); ssd17=1; } if (rf == mem18 && zona4==2) { sensor18.on(); ssd18=1; } if (rf == mem19 && zona4==2) { sensor19.on(); ssd19=1; } if (rf == mem20 && zona4==2) { sensor20.on(); ssd20=1; }
    if (rf == mem21 && zona4==2) { sensor21.on(); ssd21=1; } if (rf == mem22 && zona4==2) { sensor22.on(); ssd22=1; } if (rf == mem23 && zona4==2) { sensor23.on(); ssd23=1; } if (rf == mem24 && zona4==2) { sensor24.on(); ssd24=1; }
    }
    if (ALARMA==1 && Sactivo==0) {
      if (ssd1 == 1) { terminal.println("Sensor 1 Activado!"); terminal.flush(); Sactivo=1; } if (ssd2 == 1) { terminal.println("Sensor 2 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd3 == 1) { terminal.println("Sensor 3 Activado!"); terminal.flush(); Sactivo=1; } if (ssd4 == 1) { terminal.println("Sensor 4 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd5 == 1) { terminal.println("Sensor 5 Activado!"); terminal.flush(); Sactivo=1; } if (ssd6 == 1) { terminal.println("Sensor 6 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd7 == 1) { terminal.println("Sensor 7 Activado!"); terminal.flush(); Sactivo=1; } if (ssd8 == 1) { terminal.println("Sensor 8 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd9 == 1) { terminal.println("Sensor 9 Activado!"); terminal.flush(); Sactivo=1; } if (ssd10 == 1) { terminal.println("Sensor 10 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd11 == 1) { terminal.println("Sensor 11 Activado!"); terminal.flush(); Sactivo=1; } if (ssd12 == 1) { terminal.println("Sensor 12 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd13 == 1) { terminal.println("Sensor 13 Activado!"); terminal.flush(); Sactivo=1; } if (ssd14 == 1) { terminal.println("Sensor 14 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd15 == 1) { terminal.println("Sensor 15 Activado!"); terminal.flush(); Sactivo=1; } if (ssd16 == 1) { terminal.println("Sensor 16 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd17 == 1) { terminal.println("Sensor 17 Activado!"); terminal.flush(); Sactivo=1; } if (ssd18 == 1) { terminal.println("Sensor 18 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd19 == 1) { terminal.println("Sensor 19 Activado!"); terminal.flush(); Sactivo=1; } if (ssd20 == 1) { terminal.println("Sensor 20 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd21 == 1) { terminal.println("Sensor 21 Activado!"); terminal.flush(); Sactivo=1; } if (ssd22 == 1) { terminal.println("Sensor 22 Activado!"); terminal.flush(); Sactivo=1; }
      if (ssd23 == 1) { terminal.println("Sensor 23 Activado!"); terminal.flush(); Sactivo=1; } if (ssd24 == 1) { terminal.println("Sensor 24 Activado!"); terminal.flush(); Sactivo=1; }
      if (Sactivo==1 || panic==1) { SIRENA=1; SirenaDisparada(); }
      
  } if (ALARMA==0) { Sactivo=0;
  sensor1.off(); ssd1=0; sensor2.off(); ssd2=0; sensor3.off(); ssd3=0; sensor4.off(); ssd4=0; sensor5.off(); ssd5=0; sensor6.off(); ssd6=0; //ZONA 1
  sensor7.off(); ssd7=0; sensor8.off(); ssd8=0; sensor9.off(); ssd9=0; sensor10.off(); ssd10=0; sensor11.off(); ssd11=0; sensor12.off(); ssd12=0; //ZONA 2
  sensor13.off(); ssd13=0; sensor14.off(); ssd14=0; sensor15.off(); ssd15=0; sensor16.off(); ssd16=0; sensor17.off(); ssd17=0; sensor18.off(); ssd18=0; //ZONA 3
  sensor19.off(); ssd19=0; sensor20.off(); ssd20=0; sensor21.off(); ssd21=0; sensor22.off(); ssd22=0; sensor23.off(); ssd23=0; sensor24.off(); ssd24=0; //ZONA 4
  }} mySwitch.resetAvailable();  // Reiniciamos la clase para otra lectura
}
//.....................................//FIN SENSORES Y COMO SE QUEDA PRENDIDA LUZ DE LA QUE DETECTO MOV//.....................................//

//.....................................//CONTROL DE LA SIRENA//.....................................//
void SirenaDisparada() {
switch (SIRENA) {
            case 1:
            if (panic==1){panic=0; Blynk.virtualWrite(V5, HIGH); //Blynk.syncVirtual(V5);
            Blynk.virtualWrite(V1, "PANICO ACTIVADO"); Blynk.notify("BOTON DE PANICO ACTIVADO!"); Blynk.setProperty(V0, "color", Amarillo); terminal.print(hora); terminal.println("BOTON DE PANICO ACTIVADO!!"); terminal.flush(); digitalWrite(Sirena, HIGH);
            }else{
              Blynk.notify("SIRENA DISPARADA");
              Blynk.virtualWrite(V1, "SIRENA DISPARADA");
              Blynk.setProperty(V0, "color", Amarillo);
              terminal.print(hora);
              terminal.println("SIRENA DISPARADA");
              terminal.flush();
              digitalWrite(Sirena, HIGH);
            }break;
            case 0:
              Blynk.virtualWrite(V1, "SIRENA EN DESCANSO");
              terminal.print(hora);
              terminal.println("SIRENA EN DESCANSO");
              terminal.flush();
              digitalWrite(Sirena, LOW);
              break;
}}
//.....................................//FIN CONTROL DE LA SIRENA//.....................................//

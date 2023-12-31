//Declaracion de variables globales
float lecturaV; // almacena la lectura del voltaje
float volt; //variable para manipular la lectura con una resolucion
float voltaje; //esta variable construye el valor de voltaje necesario mediante el valor anterior medido más la lectura actual del voltaje
float lecturaA; //lee la entrada de corriente
float amp;//es la variable que multiplica la corriente almacenada por la resolucion
float corriente;//esta variable construye el valor de la corriente necesaria mediante el valor anterior medido más la lectura actual de la corriente
float resol = 0.0049;  // 5.1/1023 resolucion a usar en las mediciones
int Relay = 3; //asignacion de pin al relay
int V = A1;//asignacion de pin al voltaje
int A = A0;//asignacion de pin a la corriente
int i; //contador para tomar las medidas cada minuto

/* Este es un codigo que realiza la lectura de voltaje y corriente usando un par de sensores conectados a los pines analogicos a1 y a0*/
void setup() {
  Serial.begin(9600); //inicia la comunicacion a una vel de 9600 baudios
  pinMode(V,INPUT); //configuracion de pines 
  pinMode(A,INPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW); //set up de pin para modo descarga
}
void loop() {//codigo a ejecutar cada vez que se toman mediciones
  voltaje = 0; //acumulacion de medida
  corriente = 0;
  for (i = 0; i < 1000; i++){
    lecturaV = analogRead(V);
    lecturaA = analogRead(A);
    voltaje = lecturaV + voltaje; //se suman variables relacionadas al voltaje para poder promediar la medicion tomada en ese instante
    corriente = lecturaA + corriente;
    //delay(3); //dar 3 ms al ADC para la siguiente muestra
  }
  voltaje = voltaje / 1000.000; //obtencion de voltaje por el segundo
  volt = voltaje * resol;
  corriente = corriente / 1000.000;
  amp = corriente * resol;
  corriente = (2.50 - amp) / 0.185; //0.185 = resolución del sensor de I
  Serial.print("Voltaje: ");
  Serial.print(",");
  Serial.print(volt,4);
  Serial.print(",");
  Serial.print("Corriente: ");
  Serial.print(",");
  Serial.println(corriente,4);
  delay(60000);
  if (voltaje > 3.9000) //si marca mas de 3.9V se configura a modo descarga con la batería de 1 ohm
  {
    digitalWrite(Relay, LOW);
  }
  if (voltaje < 2.2000) //si marca 2.2V se configura el pin con la batería de 5 ohm para proteger la celda
  {
    digitalWrite(Relay, HIGH);
  }
}

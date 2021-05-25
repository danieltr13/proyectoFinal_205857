//Librerias necesarias
#include <Servo.h>
#include <Bounce2.h>

//Definir variables
const int PIN_SENSOR = A0;
const int PIN_FOTO_RGB = A1;

const unsigned int PIN_SERVO = 11;
// PIN LED
const int PIN_LED_LUZ = 10;

// Pines del Arduino en los que se conectan las patas del LED RGB
const int PIN_LED_RED = 5;
const int PIN_LED_GREEN = 4;
const int PIN_LED_BLUE = 3;

// PIN PIR
const int PIN_PIR = 12;
//PIN BOTON
const unsigned int PIN_BOTON_IZQUIERDA = 7;
const unsigned int PIN_BOTON_DERECHA = 8;
const unsigned int PIN_BOTON = 2;


int estado;

//pausas
const int PAUSA = 500;
const int DURACION = 3000;
const long PERIODO = 3000;

unsigned long lapsoAnterior = 0;
unsigned long lapsoActual = 0;

//comunicación
const unsigned int BAUD_RATE = 9600;

//variables necesarias
const float luzDia = 0.90;
int ledDia = HIGH;

const int LOFF = 1, LON = 2, LAUTO = 3;
int estado_luz = LAUTO;

//estados de cada LED
int estadoLedRed = HIGH;
int estadoLedGreen = LOW;
int estadoLedBlue = LOW;

// estado en el que se puede encontrar el sensor pir
int estadoAntPir = LOW;
int estadoPir = LOW;
// Intervalo en que el rebote se acaba
const long INTER_REBOTE = 250;

// Angulos) en los que se posicionara el servo
//const int angulos[] = {0, 45, 90, 135, 180};
int angulo = 0;
// Crea una instancia de la clase Servo, que implemeta la biblioteca servo.
Servo servo;

bool cambio = false;

Bounce debouncer = Bounce();
Bounce debouncerDer = Bounce();
Bounce debouncerButton = Bounce();

int estadoLed = LOW;


//Ventana automatica/manual
boolean ventanaAutomatica = true;
int anguloVentanaAutomatica = 0;

//Intencidad led
const int IBAJA = 1, IMEDIO = 2, IALTO = 3;
int intencidad = IBAJA;
int intencidadAnterior = IBAJA;

bool estadoIntencidad = true;

const int LED_ON = 1, LED_OFF = 2, LED_AUTO = 3;
int estadoLED = LED_AUTO;
bool aEstadoLed = false;
bool aEstadoLedAnterior = false;

bool estadoRGB_actual = false;

void setup() {
  Serial.begin(BAUD_RATE);
  // Establece el pin de control del servo
  servo.attach(PIN_SERVO);

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  pinMode(PIN_LED_LUZ, OUTPUT);

  pinMode(PIN_BOTON, INPUT);
  pinMode(PIN_BOTON_IZQUIERDA, INPUT);
  pinMode(PIN_BOTON_DERECHA, INPUT);

  debouncer.attach(PIN_BOTON_IZQUIERDA);
  debouncerDer.attach(PIN_BOTON_DERECHA);
  debouncerButton.attach(PIN_BOTON);

  // Establece el intervalo (en ms) de espera para eliminar el
  // ruido
  debouncer.interval(25);
  debouncerDer.interval(25);
  debouncerButton.interval(25);
  digitalWrite(PIN_LED_LUZ, estadoLed);

  pinMode(PIN_PIR, INPUT);
  servo.write(0);
}

void loop() {
  char comando[10];
  //Se actualiza el estado de los debouncer
  debouncer.update();
  debouncerDer.update();
  debouncerButton.update();

  //se verifica si es que fueron presionados
  if (debouncer.fell()) {
    Serial.println("izquierda");
    ventanaAutomatica = false;
    botonIzquierda();
  }
  if (debouncerDer.fell()) {
    Serial.println("derecha");
    ventanaAutomatica = false;
    botonDerecha();
  }
  if (debouncerButton.fell()) {
    cambiarEstadoRGB();
  }

  //Si el estado la luz esta en automatico entonces se evaluará si existe la presencia de una persona
  if (estado_luz == LAUTO) {
    int valorPir = digitalRead(PIN_PIR);
    // Si se detecta movimiento
    if (valorPir == HIGH) {
      // se enciende el LED
      estadoLEDS();
      if (estadoAntPir == LOW) {
        Serial.println("Movimiento");
        estadoRGB_actual = true;
        estadoAntPir = HIGH;
      }
    }
    // Si no se detecto movimiento
    else {
      // Apaga el LED
      estadoRGB_actual = false;
      RGB_color(0, 0, 0);
      // Si habia movimiento anteriormente
      if (estadoAntPir == HIGH) {
        estadoAntPir = LOW;
      }
    }
  }
  //la intencidad se puede controlar de manera automatica o establecer de manera manual
  // Si se encuentra automatica entonces revisa el nivel de luz
  if (estadoIntencidad) {
    int nivelLuzRGB = analogRead(PIN_FOTO_RGB);
    float valorF = nivelLuzRGB * (5.0 / 1023.0);
    cambiarIntencidad(valorF);
  }

  //Se toma el valor de la intencidad
  int nivelLuz = analogRead(PIN_SENSOR);
  float valor = nivelLuz * (5.0 / 1023.0);
  if (valor < .85) {
    aEstadoLed = true;
    anguloVentanaAutomatica = 180;
  } else {
    aEstadoLed = false;
    anguloVentanaAutomatica = 45;
  }

  if (aEstadoLed != aEstadoLedAnterior) {
    aEstadoLedAnterior = aEstadoLed;
    cambiarEstadoLed();
    Serial.println(valor);
  } else {
    long lapsoActual = millis();
    if (lapsoActual - lapsoAnterior >= PERIODO) {
      Serial.println(valor);
      lapsoAnterior = lapsoActual;
    }
  }
  if (ventanaAutomatica) {
    servo.write(anguloVentanaAutomatica);
  }

  if (Serial.available() > 0) {
    int n = Serial.readBytesUntil('\n', comando, 9);
    comando[n] = '\0';
    manejarRecibido(comando);
  }
}

void cambiarEstadoLed() {
  if (aEstadoLed) {
    digitalWrite(PIN_LED_LUZ, HIGH);
    Serial.println("LED_ON");
  } else {
    digitalWrite(PIN_LED_LUZ, LOW);
    Serial.println("LED_OFF");
  }
}

void manejarRecibido(char comando[]) {
  if (!strcmp(comando, "LON")) {
    estado_luz = LON;
    estadoLEDS();
  }
  else if (!strcmp(comando, "LOFF")) {
    estado_luz = LOFF;
    RGB_color(0, 0, 0);
  }
  else if (!strcmp(comando, "LAUTO")) {
    estado_luz = LAUTO;
  }
  else if (!strcmp(comando, "IBAJA")) {
    intencidad = IBAJA;
    estadoIntencidad = false;
  }
  else if (!strcmp(comando, "IMEDIO")) {
    intencidad = IMEDIO;
    estadoIntencidad = false;
  }
  else if (!strcmp(comando, "IALTO")) {
    intencidad = IALTO;
    estadoIntencidad = false;
  }
  else if (!strcmp(comando, "IAUTO")) {
    estadoIntencidad = true;
  }
  else if (!strcmp(comando, "LED_ON")) {
    estadoLED = LED_ON;
    digitalWrite(PIN_LED_LUZ, HIGH);
    Serial.println("LED_ON");
  }
  else if (!strcmp(comando, "LED_OFF")) {
    estadoLED = LED_OFF;
    digitalWrite(PIN_LED_LUZ, LOW );
    Serial.println("LED_OFF");
  }
  else if (!strcmp(comando, "LED_AUTO")) {
    estadoLED = LED_ON;
  }
  else if (!strcmp(comando, "45")) {
    ventanaAutomatica = false;
    servo.write(45);
    Serial.println("45");
  }
  else if (!strcmp(comando, "90")) {
    ventanaAutomatica = false;
    servo.write(90);
    Serial.println("90");
  }
  else if (!strcmp(comando, "135")) {
    ventanaAutomatica = false;
    servo.write(135);
    Serial.println("135");
  }
  else if (!strcmp(comando, "180")) {
    ventanaAutomatica = false;
    servo.write(180);
    Serial.println("180");
  }
  else if (!strcmp(comando, "VAUTO")) {
    ventanaAutomatica = true;
    servo.write(45);
  }
}

void cambiarIntencidad(float valorF) {
  if (valorF < .85) {
    intencidad = IALTO;
  } else if (valorF > .80 && valorF < 3) {
    intencidad = IMEDIO;
  }
  else if (valorF > 3) {
    intencidad = IBAJA;
  }
  if (intencidad != intencidadAnterior) {
    intencidadAnterior = intencidad;
    enviarEstadoIntencidad();
  }
  if (estadoRGB_actual) {
    estadoLEDS();
  }
}

void enviarEstadoIntencidad() {
  if (intencidad == IALTO) {
    Serial.println("IALTO");
  } else if (intencidad == IMEDIO) {
    Serial.println("IMEDIO");
  } else if (intencidad == IBAJA) {
    Serial.println("IBAJA");
  }
}


void cambiarEstadoRGB() {
  if (estado_luz == LAUTO) {
    estado_luz = LON;
    estadoLEDS();
    estadoRGB_actual = true;
  }
  else if (estado_luz == LON) {
    estado_luz = LOFF;
    RGB_color(0, 0, 0);
    estadoRGB_actual = false;
  }
  else if (estado_luz == LOFF) {
    estado_luz = LAUTO;
  }
}

void estadoLEDS() {
  // Prender/apagar el LED
  if (intencidad == IBAJA) {
    RGB_color(255, 0, 0);
  } else if (intencidad == IMEDIO) {
    RGB_color(0, 255, 0);
  } else if (intencidad == IALTO) {
    RGB_color(0, 0, 255);
  }
}

void botonIzquierda() {
  if (angulo > 45) {
    angulo -= 45;
    servo.write(angulo);
  }
}

void botonDerecha() {
  if (angulo < 180) {
    angulo += 45;
  } else {
    angulo = 45;
  }
  servo.write(angulo);
}

void RGB_color(int red, int green, int blue) {
  analogWrite(PIN_LED_RED, red);
  analogWrite(PIN_LED_GREEN, green);
  analogWrite(PIN_LED_BLUE, blue);
}

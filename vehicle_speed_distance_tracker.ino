/*
https://www.arduino.cc/reference/pt/language/variables/constants/constants/

Configuração do raio da roda do veiculo modificado, original em (https://medium.com/@silicioslab/od%C3%B4metro-para-ve%C3%ADculo-com-arduino-2ca0632e1c46)

Odômetro
https://medium.com/@silicioslab/od%C3%B4metro-para-ve%C3%ADculo-com-arduino-2ca0632e1c46/

Aproveitado Fórmula para zerar os valores:

https://create.arduino.cc/projecthub/user334153146/diy-speedometer-using-arduino-and-processing-android-app-86ba0c?ref=tag&ref_id=speedometer&offset=3

Reaproveitado e melhorado devido ao bug de não zerar os valores:
https://create.arduino.cc/projecthub/139683/arduino-lcd-display-as-a-bicycle-speedometer-6a6568?ref=tag&ref_id=speedometer&offset=2

Criado por Samuel Alencar da Costa - 09-12-2020
*/

#include <LiquidCrystal_I2C.h> // Biblioteca para utilizar o display com 4 fios conectados ao módulo I2C (vcc, gnd, rx e tx)
#include <Wire.h> // Biblioteca para permitir a comunicação com dispositivos I2C
#include <EEPROM.h> // Biblioteca para uso da memória EEPROM com dados lidos da porta analógica a configurar para sensor de corrente (em desenvolvimento)
#include <SPI.h> // Biblioteca para aplicações com protocolo SPI

/*
SPI (Serial Peripheral Interface) é um protocolo de dados seriais síncronos utilizado em microcontroladores para comunicação entre o microcontrolador e periféricos.
*/

//parte2

float start, finished;
float transcorrido, time;
float circunferencia = 2.0734; // Circunferência da roda em metros
float velocidade, speedm;     
float rpm, dtime, Distancia;
float raio_da_roda = 0.33; // Raio da roda da bicicleta em metros

volatile byte rotacao; // Variável volátil para interrupção do sensor de rotação

#define pinBotoes A0 // Conectar o display shield na primeira porta analógica do Arduino
#define pinAceler A1 // Conectar o sinal do acelerador (0 a 5V) na segunda porta analógica (A1)
#define pinBotoes2 A2 // Botões de incremento, decremento, select

// Configurações para comunicação serial com módulo Bluetooth e aplicativo

#define pinRX 0
#define pinTX 1

#define pinBrake 6 // Conectar os manetes de freio no GND e pino digital D6

#define relayEst 3 // Pino de saída para acionamento do sinal nos relés para comutação do estado do Estator trifásico
#define relayRot 4 // Pino de saída para os relés para comutação do estado do rotor
#define relayReg 5 // Pino de saída para o relé que comuta o regulador

// Definição dos botões do LCD shield

#define btNENHUM 0
#define btSELECT 1
#define btLEFT   2
#define btUP     3
#define btDOWN   4
#define btRIGHT  5

// Configuração de pinos digitais para botões e sensores
pinMode(7, INPUT);
pinMode(8, INPUT);
pinMode(9, INPUT);
pinMode(10, INPUT);
pinMode(11, INPUT);
pinMode(12, INPUT);
pinMode(13, INPUT);

// Configuração do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço 0x27 para display 16x2

void setup() {
  // Configura a interrupção para calcular a velocidade
  attachInterrupt(digitalPinToInterrupt(2), CalculaVel, RISING); // Interrupção chamada no sensor Hall
  rotacao = rpm = velocidade = 0; // Inicializa as variáveis a zero
  Distancia = 0;

  lcd.init(); // Inicializa o LCD utilizando I2C
  lcd.backlight(); // Liga a luz de fundo do LCD
  Serial.begin(9600); // Inicializa a comunicação serial
  Wire.begin(); // Inicializa a comunicação via I2C
  pinMode(13, OUTPUT); // Configura o LED interno
  digitalWrite(13, LOW); // Desliga o LED interno

  pinMode(relayEst, OUTPUT); // Configura o pino do relé do Estator
  digitalWrite(relayEst, HIGH); // Configura o relé para modo gerador

  pinMode(relayRot, OUTPUT); // Configura o pino do relé do Rotor
  digitalWrite(relayRot, HIGH); // Configura o relé para modo gerador
  
  pinMode(relayReg, OUTPUT); // Configura o pino do relé do regulador
  digitalWrite(relayReg, HIGH); // Configura o relé para modo regulador

  pinMode(pinAceler, INPUT); // Configura o pino do acelerador
  analogWrite(pinAceler, LOW); 

  pinMode(pinBrake, INPUT_PULLUP); // Configura o pino do freio
}

void CalculaVel() {
  rotacao++;
  dtime = millis();
  if(rotacao >= 2) { 
    if((millis() - start) > 100) { // Considera 100ms antes de calcular a velocidade
      transcorrido = millis() - start;
      start = millis();
      velocidade = (3600 * circunferencia) / transcorrido; // Cálculo da velocidade
      Distancia = (float)(2 * 3.14 * 66 * rotacao) / 100000.0; // Cálculo da distância percorrida
      rpm = (1000 / transcorrido) * 60 * 2; // Cálculo da rotação por minuto (RPM)
      start = millis();
      rotacao = 0;
    }
  }
}

void display1() {
  lcd.clear(); // Limpa o display
  lcd.setCursor(0, 0); // Define a posição do cursor
  lcd.print(int(velocidade)); // Exibe a velocidade
  lcd.print(" km/h ");
  lcd.setCursor(0, 1); // Move para a linha abaixo
  lcd.print(int(rpm)); // Exibe o RPM
  lcd.print(" RPM ");
  lcd.setCursor(10, 0); // Move o cursor para a direita
  lcd.print(int(Distancia)); // Exibe a distância
  lcd.print(" Km");
}

void loop() {
  // A leitura do acelerador e freio é feita para alternar entre os modos
  int valAceler = analogRead(pinAceler);
  int valBrake = digitalRead(pinBrake);

  // Verifica se o acelerador e o freio estão sendo acionados ao mesmo tempo
  if ((valBrake == LOW) && (valAceler >= 205)) {
    delay(100);
    digitalWrite(relayEst, HIGH);
    digitalWrite(relayRot, HIGH);
    digitalWrite(relayReg, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LIBERAR O FREIO");
    lcd.setCursor(0, 1);
    lcd.print("OU ACELERADOR");
    delay(250);
  }
  // Se apenas o acelerador estiver acionado
  else if ((valBrake == HIGH) && (valAceler >= 205)) {
    delay(150);
    digitalWrite(relayReg, LOW);
    digitalWrite(relayRot, LOW);
    digitalWrite(relayEst, LOW);
    delay(200);
    display1(); // Chama a função para exibir a velocidade e a distância
    delay(1500);
    lcd.setCursor(0, 1);
    lcd.print("MODO MOTOR ATIVO");
    delay(1500);
  }

  delay(500);
  Serial.println("Distancia");
  delay(500);
  Serial.println("Km");
  delay(500);
  Serial.println("Km/h:");
  delay(500);
}

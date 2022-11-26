
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
// #include <ESPMmMDNS.h>

#define MAX_GAME_LENGTH 100

const byte ledPins[] = {10, 5, 2, 45};
int buttonPins[MAX_GAME_LENGTH];
int buttonPins2[MAX_GAME_LENGTH];
int buttonsclicked = 0;
int buttonsclicked2 = 0;
int player;
int verifiedinit = 1;
int verified;
#define SPEAKER_PIN 9

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

const int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};

/* Global variables - store the game state */
int gameSequence[MAX_GAME_LENGTH] = {0};
int gameIndex = 0;

//Configura o nome da rede sem fio que será criada

const char *ssid = "ESPLuiz";

//Configura a senha de proteção da rede sem fio
// ATENÇÃO «.ªnm:, mínima de 8 cara: ,-!» senha

const char *password = "Luiz1234";

WebServer server(80);

void handleRoot() {  
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";
  html += "<head>";
      html += "<meta charset='UTF-8'>";
      html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
      html += "<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
      html += "<title>Genius Granville</title>";
  html += "</head>";
  html += "<body>";
      html += "<div>";
          html += "<main style='display:flex ; align-items: center; justify-content: center;'>";
              html += "<div style='display: flex; flex-direction: column; align-items: center; margin: 50px;'>";
                  html += "<div style='margin:10px ;'>";
                      html += "<a href=\"/player1\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(101, 58, 255); margin:10px ;'>Jogador 1</button></a>";
                  html += "</div>";
                  html += "<div style='margin:10px ;'>";
                      html += "<a href=\"/player2\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(255, 58, 58); margin:10px ;'>Jogador 2</button></a>";
                  html += "</div>";
              html += "</div>";
          html += "</main>";
      html += "</div>";
  html += "</body>";
  html += "</html>";
  server.send(200, "text/html", html);
}

void verify(){
  if (!checkUserSequence()) {
    gameOver();
  }

  delay(300);

  if (buttonsclicked2 >= gameIndex){
    if (gameIndex > 0) {
      playLevelUpSound();
      delay(300);
      buttonsclicked = 0;
      buttonsclicked2 = 0;
      verified = 1;
      start();
    } 
  }
  
}

void verify2(){
  if (!checkUserSequence2()) {
    gameOver();
  }

  delay(300);

  if (buttonsclicked >= gameIndex){
    if (gameIndex > 0) {
      playLevelUpSound();
      delay(300);
      buttonsclicked = 0;
      buttonsclicked2 = 0;
      verified = 1;
      start();
    } 
  }
}

void player1() {
  player = 1;
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";

  html += "<head>";
      html += "<meta charset='UTF-8'>";
      html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
      html += "<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
      html += "<title>Genius Granville</title>";
  html += "</head>";

  html += "<body>";
      html += "<div>";
          html += "<main style='display:flex ; align-items: center; justify-content: center;'>";
              html += "<div style='display: flex; flex-direction: column; align-items: center; margin: 50px;'> Jogador 1 <div style='margin:10px ;'> <a href=\"/red1\">";
                html += "<button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(255, 58, 58); margin:10px ;'>Vermelho</button></a> ";
                  html += "<a href=\"/blue1\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(77, 77, 255);'>Azul</button></a>";
              html += "</div>";
              html += "<div> <a href=\"/green1\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(81, 255, 81); margin:10px ;'>Verde</button></a>";
                  html += "<a href=\"/yellow1\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(255, 255, 80);'>Amarelo</button></a>";
                html += "</div>";
              html += "</div>";
              html += "<div>";
                  html += "<div><a href=\"/play\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(93, 93, 93); margin:10px ;'>Iniciar</button></a>";
                  html += "</div>";
          html += "</main>";
      html += "</div>";
  html += "</body>";
  html += "</html>";
  server.send(200, "text/html", html);
}

void player2() {
  player = 2;
  String html = "<!DOCTYPE html>";
  html += "<html lang='en'>";

  html += "<head>";
      html += "<meta charset='UTF-8'>";
      html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
      html += "<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
      html += "<title>Genius Granville</title>";
  html += "</head>";

  html += "<body>";
      html += "<div>";
          html += "<main style='display:flex ; align-items: center; justify-content: center;'>";
              html += "<div style='display: flex; flex-direction: column; align-items: center; margin: 50px;'> Jogador 2 <div style='margin:10px ;'> <a href=\"/red2\">";
                html += "<button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(255, 58, 58); margin:10px ;'>Vermelho</button></a> ";
                  html += "<a href=\"/blue2\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(77, 77, 255);'>Azul</button></a>";
              html += "</div>";
              html += "<div> <a href=\"/green2\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(81, 255, 81); margin:10px ;'>Verde</button></a>";
                  html += "<a href=\"/yellow2\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(255, 255, 80);'>Amarelo</button></a>";
                html += "</div>";
              html += "</div>";
              html += "<div>";
                  html += "<div><a href=\"/play\"><button style='border: none;color: rgb(0, 0, 0); padding: 15px 32px; text-align: center;text-decoration: none; display: inline-block; font-size: 16px; background-color: rgb(93, 93, 93); margin:10px ;'>Iniciar</button></a>";
              html += "</div>";
          html += "</main>";
      html += "</div>";
  html += "</body>";
  html += "</html>";
  server.send(200, "text/html", html);
}

void red1() {
  player1();
  buttonPins[buttonsclicked] = 3;
  buttonsclicked++;
  Serial.println(buttonsclicked);
  Serial.println(gameIndex);
  if(buttonsclicked == gameIndex){
    verify();
  }
}
void green1() {
  player1();
  buttonPins[buttonsclicked] = 2;
  buttonsclicked++;
  Serial.println(buttonsclicked);
  Serial.println(gameIndex);
  if(buttonsclicked == gameIndex){
    verify();
  }
}
void blue1() {
  player1();
  buttonPins[buttonsclicked] = 0;
  buttonsclicked++;
  Serial.println(buttonsclicked);
  Serial.println(gameIndex);
  if(buttonsclicked == gameIndex){
    verify();
  }
}
void yellow1() {
  player1();
  buttonPins[buttonsclicked] = 1;
  buttonsclicked++;
  Serial.println(buttonsclicked);
  Serial.println(gameIndex);
  if(buttonsclicked == gameIndex){
    verify();
  }
}
void red2() {
  player2();
  buttonPins2[buttonsclicked2] = 3;
  buttonsclicked2++;
  Serial.println(buttonsclicked2);
  Serial.println(gameIndex);
  if(buttonsclicked2 == gameIndex){
    verify2();
  }
}
void green2() {
  player2();
  buttonPins2[buttonsclicked2] = 2;
  buttonsclicked2++;
  Serial.println(buttonsclicked2);
  Serial.println(gameIndex);
  if(buttonsclicked2 == gameIndex){
    verify2();
  }
}
void blue2() {
  player2();
  buttonPins2[buttonsclicked2] = 0;
  buttonsclicked2++;
  Serial.println(buttonsclicked2);
  Serial.println(gameIndex);
  if(buttonsclicked2 == gameIndex){
    verify2();
  }
}
void yellow2() {
  player2();
  buttonPins2[buttonsclicked2] = 1;
  buttonsclicked2++;
  Serial.println(buttonsclicked2);
  Serial.println(gameIndex);
  if(buttonsclicked2 == gameIndex){
    verify2();
  }
}
/**
   Set up the Arduino board and initialize Serial communication
*/
/**
   Lights the given LED and plays a suitable tone
*/
void lightLedAndPlayTone(byte ledIndex) {
  digitalWrite(ledPins[ledIndex], HIGH);
  tone(SPEAKER_PIN, gameTones[ledIndex]);
  delay(300);
  digitalWrite(ledPins[ledIndex], LOW);
  noTone(SPEAKER_PIN);
}

/**
   Plays the current sequence of notes that the user has to repeat
*/
void playSequence() {
  for (int i = 0; i < gameIndex; i++) {
    byte currentLed = gameSequence[i];
    lightLedAndPlayTone(currentLed);
    delay(50);
  }
}

/**
    Waits until the user pressed one of the buttons,
    and returns the index of that button
*/

/**
  Play the game over sequence, and report the game score
*/
void gameOver() {
  Serial.print("Game over! your score: ");
  Serial.println(gameIndex - 1);
  gameIndex = 0;
  buttonsclicked = 0;
  delay(200);

  // Play a Wah-Wah-Wah-Wah sound
  tone(SPEAKER_PIN, NOTE_DS5);
  delay(300);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(300);
  tone(SPEAKER_PIN, NOTE_CS5);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(SPEAKER_PIN, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(SPEAKER_PIN);
  delay(500);
  handleRoot();
  verifiedinit = 1;
}

/**
   Get the user's input and compare it with the expected sequence.
*/
bool checkUserSequence() {
  for (int i = 0; i < gameIndex; i++) {
    int expectedButton = gameSequence[i];
    int actualButton = buttonPins[i];
    lightLedAndPlayTone(actualButton);
    if (expectedButton != actualButton) {
      return false;
    }
  }

  return true;
}

bool checkUserSequence2() {
  for (int i = 0; i < gameIndex; i++) {
    int expectedButton = gameSequence[i];
    int actualButton = buttonPins2[i];
    lightLedAndPlayTone(actualButton);
    if (expectedButton != actualButton) {
      return false;
    }
  }

  return true;
}

/**
   Plays a hooray sound whenever the user finishes a level
*/
void playLevelUpSound() {
  tone(SPEAKER_PIN, NOTE_E4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G4);
  delay(150);
  tone(SPEAKER_PIN, NOTE_E5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_C5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_D5);
  delay(150);
  tone(SPEAKER_PIN, NOTE_G5);
  delay(150);
  noTone(SPEAKER_PIN);
}

/**
   The main game loop
*/

void start(){
  if(verified == 1 || verifiedinit == 1){
    verifiedinit = 0;
    verified = 0;
    if (player == 1){
      player1();
    }
    else{
      player2();
    }
    delay(300);
    gameSequence[gameIndex] = random(0, 4);
    gameIndex++;
    if (gameIndex >= MAX_GAME_LENGTH) {
      gameIndex = MAX_GAME_LENGTH - 1;
    }
    playSequence();
  }
  else{
    String html = "<!DOCTYPE html>";
    html += "<html lang='en'>";
    html += "<head>";
        html += "<meta charset='UTF-8'>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        html += "<meta http-equiv='X-UA-Compatible' content='ie=edge'>";
        html += "<title>Genius Granville</title>";
    html += "</head>";
    html += "<body>";
        html += "<div>";
            html += "O JOGO JÁ COMEÇOU VOLTE PARA CONTINUAR JOGANDO!";
        html += "</div>";
    html += "</body>";
    html += "</html>";
    server.send(200, "text/html", html);
  }
}

void setup(void) {
  //Configura o baud rate da comunicação serial
  Serial .begin(115200);

  for (byte i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(SPEAKER_PIN, OUTPUT);
  // The following line primes the random number generator.
  // It assumes pin A0 is floating (disconnected):
  randomSeed(analogRead(A0));


  //Você pode remover o parâmetro de senha, caso deseje criar uma rede sem senha
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print ("SSID: ");

  Serial.println (ssid);

  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Servidor Iniciado");

  // if (MDNS.begin("esp32")) {
  //   Serial.println("MDNS responder started");
  // }
  server.on("/", handleRoot);
  server.on("/player1", player1);
  server.on("/player2", player2);
  server.on("/red1", red1);
  server.on("/green1", green1);
  server.on("/blue1", blue1);
  server.on("/yellow1", yellow1);
  server.on("/red2", red2);
  server.on("/green2", green2);
  server.on("/blue2", blue2);
  server.on("/yellow2", yellow2);
  server.on("/play", start);


  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  delay(2);
}
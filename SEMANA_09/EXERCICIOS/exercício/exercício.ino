#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <string.h>

#define I2C_SDA 2
#define I2C_SCL 1

LiquidCrystal_I2C lcd(0x27, 16, 2);
String password;


String registerPass(){
  Serial.println("Informe uma senha a ser cadastrada (De 4 Caracteres): \n");
  while (Serial.available() == 0) {}     //wait for data available
  password = Serial.readString();  //read until timeout
  password.trim();
  while(!(password.length() == 4)){
    Serial.println("Informe uma senha de 4 caracteres: \n");
    while (Serial.available() == 0) {} 
    password = Serial.readString();
    password.trim();
  }
  
  return password;
}

String readPass(){
  Serial.println("Informe sua senha para ser verificada (De 4 Caracteres): \n");
  while (Serial.available() == 0) {}     //wait for data available
  String verify = Serial.readString();  //read until timeout
  verify.trim();
  while(!(verify.length() == 4)){
    Serial.println("Informe uma senha de 4 caracteres a ser verificada: \n");
    while (Serial.available() == 0) {} 
    verify = Serial.readString();
    verify.trim();
  }
  
  return verify;
}

void verify(String pass){
  String verify= readPass();

  while(!(verify == pass)){
    lcd.setCursor(1, 1);
    lcd.print("Senha incorreta");
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
    delay(2000);
    lcd.clear();
    digitalWrite(RGB_BUILTIN, LOW);    // Turn the RGB LED of
    verify= readPass();

  }
  lcd.setCursor(3, 1);
  lcd.print("Verificado");
  neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
  delay(2000);
  lcd.clear();
  digitalWrite(RGB_BUILTIN, LOW);    // Turn the RGB LED of
  
}


void setup() {

  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);
  // put your setup code here, to run once:

  lcd.init();                
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
  verify(registerPass());


}

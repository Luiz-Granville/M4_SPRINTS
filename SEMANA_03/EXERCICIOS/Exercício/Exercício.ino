#include <String>;

#define LDR 5
#define LED_1 48
#define LED_2 35
#define LED_3 39
#define LED_4 41
#define BUZZER 6
#define BUTTON_SAVE 15
#define BUTTON_PRINT 3

int values[4] = {0,0,0,0};
int saves = 0;

void setup() {
  pinMode(LDR, INPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(BUTTON_SAVE, INPUT);
  pinMode(BUTTON_PRINT, INPUT);
  Serial.begin(9600);
  delay(1000);


}

int contwotScale(int val) {
  int old_min = 0;
  int old_max = 4095;
  int new_min = 0;
  int new_max = 15;

  int new_value = (((val - old_min) * (new_max - new_min) ) / (old_max - old_min)) + new_min;

  return new_value;
}

void acenderLEDs(int one, int two, int three, int four) {
  digitalWrite(LED_1, one);
  digitalWrite(LED_2, two);
  digitalWrite(LED_3, three);
  digitalWrite(LED_4, four);
}

void LEDsBUZZER(int contwoted_LDR_val) {
  if(contwoted_LDR_val == 0) {
    acenderLEDs(0,0,0,0);
    tone(BUZZER, 300, 1000);
  }
  if(contwoted_LDR_val == 1) {
    acenderLEDs(1,0,0,0);
    tone(BUZZER, 400, 1000);
  }
  if(contwoted_LDR_val == 2) {
    acenderLEDs(0,1,0,0);
    tone(BUZZER, 500, 1000);
  }
  if(contwoted_LDR_val == 3) {
    acenderLEDs(1,1,0,0);
    tone(BUZZER, 600, 1000);
  }
  if(contwoted_LDR_val == 4) {
    acenderLEDs(0,0,1,0);
    tone(BUZZER, 700, 1000);
  }
  if(contwoted_LDR_val == 5) {
    acenderLEDs(1,0,1,0);
    tone(BUZZER, 800, 1000);
  }
  if(contwoted_LDR_val == 6) {
    acenderLEDs(0,1,1,0);
    tone(BUZZER, 900, 1000);
  }
  if(contwoted_LDR_val == 7) {
    acenderLEDs(1,1,1,0);
    tone(BUZZER, 1000, 1000);
  }
  if(contwoted_LDR_val == 8) {
    acenderLEDs(0,0,0,1);
    tone(BUZZER, 1100, 1000);
  }
  if(contwoted_LDR_val == 9) {
    acenderLEDs(1,0,0,1);
    tone(BUZZER, 1200, 1000);
  }
  if(contwoted_LDR_val == 10) {
    acenderLEDs(0,1,0,1);
    tone(BUZZER, 1300, 1000);
  }
  if(contwoted_LDR_val == 11) {
    acenderLEDs(1,1,0,1);
    tone(BUZZER, 1400, 1000);
  }
  if(contwoted_LDR_val == 12) {
    acenderLEDs(0,0,1,1);
    tone(BUZZER, 1500, 1000);
  }
  if(contwoted_LDR_val == 13) {
    acenderLEDs(1,0,1,1);
    tone(BUZZER, 1600, 1000);
  }
  if(contwoted_LDR_val == 14) {
    acenderLEDs(0,1,1,1);
    tone(BUZZER, 1700, 1000);
  }
  if(contwoted_LDR_val == 15) {
    acenderLEDs(1,1,1,1);
    tone(BUZZER, 1800, 1000);
  }
}

void loop() {

  int LDR_val = analogRead(LDR);
  int contwoted_LDR_val = contwotScale(LDR_val);

  int btnInsereState = digitalRead(BUTTON_SAVE);
  if(btnInsereState) {
    Serial.println("Botão salvar pressionado");

    values[saves] = contwoted_LDR_val;
    LEDsBUZZER(contwoted_LDR_val);

    String um = "O valor ";
    String dois = " foi armazenado com sucesso.";

    Serial.println(um+contwoted_LDR_val+dois);

    saves = saves + 1;

    delay(2000);

    acenderLEDs(0,0,0,0);
  }

  int btnVarreState = digitalRead(BUTTON_PRINT);
  if(btnVarreState) {
    Serial.println("Botão print pressionado");
    acenderLEDs(0,0,0,0);
    delay(1000);

    int size = sizeof(values)/sizeof(values[0]);

    for(int i = 0; i < saves; i++) {
      LEDsBUZZER(values[i]);
      delay(1000);
      values[i] = NULL;
      
    }

    delay(2000);

    acenderLEDs(0,0,0,0);
    
  }

}




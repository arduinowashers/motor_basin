#include <ESP32Servo.h>

Servo myServo;
int servoPin = 5;       // Пин на серво мотора
int buttonPin = 13;       // Пин за бутона
int buttonState = 0;     // Текущото състояние на бутона
int lastButtonState = 0; // Предишно състояние на бутона
int speedState = 1;      // Начална стойност на скоростта

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);  // Привързване на серво мотора към пина
  pinMode(buttonPin, INPUT_PULLUP); // Настройваме бутона с вътрешно подтегляне
}

void loop() {
  buttonState = digitalRead(buttonPin); // Четене на състоянието на бутона

  // Проверка за натискане на бутона (сменяме скоростта при натиск)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50); // Малко забавяне за избягване на шум
    speedState++;  // Увеличаваме стойността на скоростта

    // Променяме скоростта на серво мотора
    if (speedState > 3) { // Когато скоростта надвиши 3, я връщаме към 1
      speedState = 1;
    }

    // Настройваме серво мотора в зависимост от текущата скорост
    if (speedState == 1) {
      myServo.writeMicroseconds(1050);  // Бавен ход
    } else if (speedState == 2) {
      myServo.writeMicroseconds(875);  // Средна скорост
    } else if (speedState == 3) {
      myServo.writeMicroseconds(700);  // Бърз ход
    }

    Serial.print("Speed State: ");
    Serial.println(speedState); // Отпечатваме текущото състояние на скоростта
  }

  lastButtonState = buttonState;  // Записваме състоянието на бутона за следващия цикъл
}

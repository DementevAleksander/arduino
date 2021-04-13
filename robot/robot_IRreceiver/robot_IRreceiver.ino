// Установка расширеной библиотеки управление ИК-приёмником.
// C:\Program Files (x86)\Arduino\Libraries\RobotIRremote - удалить
// https://github.com/z3t0/Arduino-IRremote - скачать и записать в C:\Program Files (x86)\Arduino\Libraries\

#include <IRremote.h>
#include "IRremote.h" // Подключаем локально библиотеку из текущего каталога 
#include "motor.h" // Подключаем все функции управления моторами
// Функция инициализации, выполняется один раз.
// Порт для IR-приемника.
int RECV_PIN = 7;
// Создание IR-приемника.
IRrecv irrecv(RECV_PIN);
// Переменная для хранения кодов кнопок, получаемых от IR-приемника.
decode_results results;
// Хранит время последнего нажатия кнопки.
unsigned long _time;
/////////////
// Опишем коды кнопок макроподстановками:
#define FORWARD 0xFF18E7
#define LEFT 0xFF10EF
#define RIGHT 0xFF5AA5
#define STOP 0xFF38C7
#define BACKWARD 0xFF4AB5
#define FORWARDLEFT 0xFFA25D
#define FORWARD2 0xFF629D
#define FORWARDRIGHT 0xFFE21D
#define LEFT2 0xFF22DD
#define STOP2 0xFF02FD
#define RIGHT2 0xFFC23D
#define BACKWARDLEFT 0xFFE01F
#define BACKWARD2 0xFFA857
#define BACKWARDRIGHT 0xFF906F
#define STOP3 0xFF9867
#define STOP4 0xFF6897
#define STOP5 0xFFB04F
// Инициализация.
void setup()
{
   // Переменные – номера контактов (пинов) Arduino.
   // Для левых и правых моторов машинки.
   setup_motor_system(2, 3, 4, 5);
   _stop(); // Двигатели остановлены.
   // Запуск IR-приемника.
   irrecv.enableIRIn();
   _time = millis();
 }
// Основная программа.
void loop()
{
 if (irrecv.decode(&results))
 {
   _time = millis();
   switch (results.value) {
     // Вперед
     case FORWARD: 
      forward();
     break;
     // Назад
     case BACKWARD:
     backward();
     break;
     // Влево
     case LEFT:
     left();
     break;
     // Вправо
     case RIGHT:
     right();
     break;
     // Вперед
     case FORWARD2:
     forward();
     break;
     // Назад
     case BACKWARD2:
     backward();
     break;
     // Влево
     case LEFT2:
     left();
     break;
     // Вправо
     case RIGHT2:
     right();
     break;
     // Прямо и влево
     case FORWARDLEFT:
     forward_left();
     break;
     // Прямо и вправо
     case FORWARDRIGHT:
     forward_right();
     break;
     // Назад и влево
     case BACKWARDLEFT:
     backward_left();
     break;
     // Назад и вправо
     case BACKWARDRIGHT:
     backward_right();
     break;
     // Стоп
     case STOP:
     _stop();
     break;
     case STOP2:
     _stop();
     break;
     case STOP3:
     _stop();
     break;
     case STOP4:
     _stop();
     break;
     case STOP5:
     _stop();
     break;
   }
   irrecv.resume();
 }
 // Если никакая клавиша не нажата более 3 сек., то остановка.
 if((millis()-_time)>3000) {_stop();}
}
//=====================================================================

 
 

////===============================================
//// Проверка кодов кнопок у ИК-пульта
//#include "IRremote.h" // Подключаем локально библиотеку из текущего каталога 
//// Порт Arduino для приемника.
//int RECV_PIN = 7;
//// Создаем объект IR-приемник.
//IRrecv irrecv(RECV_PIN);
//// Создаем структуру результата приема данных IR-канала.
//decode_results results;
//void setup()
//{
// // Устанавливаем скорость порта связи с ПК.
// Serial.begin(9600);
// // Запуск IR-приемника.
// irrecv.enableIRIn();
//}
//void loop() {
// // Если пришли данные.
// if (irrecv.decode(&results)) {
// // Послать полученные данные на ПК в 16-м представлении.
// Serial.println(results.value, HEX);
// // Готов к приему.
// irrecv.resume();
// }
// delay(100);
//}

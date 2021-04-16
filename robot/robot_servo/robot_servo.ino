// // -------------------------------- Проверка работоспособности дальномера.
// // Подключаем библиотеку, управляющую дальномером.
// #include "sonar.h"
// void setup()
// {
// // Инициализируем дальномер Trig = 13, Echo = 12.
// Sonar_init(13, 12);
// // При инициализации задаем скорость порта для связи с ПК.
// Serial.begin(9600); // start the serial port
// }
// void loop()
// {
// // В цикле loop отправляем значение,
// // полученное с дальномера, в порт через 1,5 с.
// // получаем дистанцию в сантиметрах с лимитом 300 см.
// int prepyatstvie = Sonar(300); 
// Serial.print("Distance="); // оформляем вывод.
// Serial.print(prepyatstvie); // выводим дистанцию.
// Serial.println(" cm."); // оформляем вывод.
// delay(1500); // приостанавливаем программу.
// } 

// // -------------------------------- Проверка работоспособности сервомотора.
// // Подключаем библиотеку управления сервомоторами.
//#include <Servo.h>
// // Создаем сервомотор поворота головы.
//Servo neck;
//void setup()
//{
// // Инициализируем сервомотор, управление 14-м портом.
// neck.attach(14);
//}
//void loop()
//{
// int i;
// // Создаем цикл для равномерного поворота сервомотора.
// for(i=10; i<=170; i=i+10)
// {
// // Поворачиваем вал на угол i.
// neck.write(i);
// // приостанавливаем программу.
// delay(100);
// }
// // Возвращаем голову назад.
// for(i=170; i>=10;i=i-10)
// {
// // Поворачиваем вал на угол i.
// neck.write(i);
// // приостанавливаем программу.
// delay(100);
// }
//} 

// // -------------------------------- Выставляем сервомотор по центру.
// // Подключаем библиотеку управления сервомоторами.
// #include <Servo.h>
// // Создаем сервомотор поворота головы.
// Servo neck;
// void setup()
// {
//  // Инициализируем сервомотор, управление 9-м портом.
//  neck.attach(9);
// }
// void loop()
// {
//  // Поворачиваем вал на угол 90.
//  neck.write(90);
//  // приостанавливаем программу.
//  delay(100);
// } 

// -------------------------------- Программа обхода препятствий роботом.
// Подключаем библиотеку управления сервомоторами.
#include <Servo.h>
// Подключаем библиотеку, управляющую моторами.
#include "motor.h" 
// Подключаем библиотеку, управляющую дальномером.
#include "sonar.h"
// Создаем сервомотор поворота головы.
Servo neck;
// Константы - постоянные значения для уточнения углов.
const int left_ang = 168;
const int front_ang = 98;
const int right_ang = 28;
// Временные константы служат для точного задания времени на поворот,
// разворот, движение вперед
// в миллисекундах.
const int time_90 = 390;
const int time_180 = 750*1.5;

// задержка по времени поворота головы
const int time_head_turn = 700;

//Дистанция до объекта, по которой робот принимает какие-либо действия
const int time_dist_action = 20*2;

void setup()
{
  // Инициализируем дальномер Trig = 13, Echo = 12.
  Sonar_init(13, 12);
  // Инициализируем сервомотор, управление 9-м портом.
  neck.attach(9);
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.

  //Проверка дальномера
  Serial.begin(9600); // start the serial port
}
// Основная программа.
void loop()
{
  //  _stop();

  // Создаем переменные для хранения трех дистанций - слева, впереди, справа.
  int Dist_left, Dist_front, Dist_right;

  // Поворачиваем голову прямо вперед.
  neck.write(front_ang);
  // Ждем, т. к. поворот занимает небольшое время.
  delay(200);
  // Записываем расстояние до препятствия впереди.
  Dist_front = Sonar(400);
  Serial.print("Dist_front=");
  Serial.print(Dist_front);
  Serial.println(" cm.");

  if ((Dist_front < time_dist_action) || (Dist_front == time_dist_action)) //Едем вперёд пока дистанция не будет меньше 20 см. Если меньше 20, то
  {
    _stop();
    // Поворачиваем голову налево.
    neck.write(left_ang);
    // Ждем, т. к. поворот занимает небольшое время.
    delay(time_head_turn);
    // Записываем расстояние до препятствия слева.
    Dist_left = Sonar(400);
    Serial.print("Dist_left=");
    Serial.print(Dist_left);
    Serial.println(" cm.");

    // Поворачиваем голову прямо вперед.
    neck.write(front_ang);
    // Ждем, т. к. поворот занимает небольшое время.
    delay(200);
    // Записываем расстояние до препятствия впереди.
    Dist_front = Sonar(400);
    Serial.print("Dist_front=");
    Serial.print(Dist_front);
    Serial.println(" cm.");

    // Поворачиваем голову направо.
    neck.write(right_ang);
    // Ждем, т. к. поворот занимает небольшое время.
    delay(time_head_turn); 
    // Записываем расстояние до препятствия впереди.
    Dist_right = Sonar(400);
    Serial.print("Dist_right=");
    Serial.print(Dist_right);
    Serial.println(" cm.");

    neck.write(front_ang);

    // Если расстояние до препятствия слева наибольшее

    if ((Dist_left < time_dist_action) && (Dist_front < time_dist_action) && (Dist_right < time_dist_action))
    {
      // right(); // разворачиваемся.
      left();
      delay(time_180);
      Serial.println("Расстояние меньше 40. Разворачиваюсь!");
    }
    else
    {
      if ((Dist_left > Dist_front) && (Dist_left > Dist_right))
      {

        Serial.print("Dist_left=");
        Serial.print(Dist_left);
        Serial.print(" cm.");
        Serial.print("Dist_front=");
        Serial.print(Dist_front);
        Serial.print(" cm.");
        Serial.print("Dist_right=");
        Serial.print(Dist_right);
        Serial.println(" cm.");

        
        Serial.print(time_dist_action);
        Serial.println(">. Поворачиваю на лево!");
        // left(); // поворачиваем налево 0,5 секунд.
        right();
        delay(time_90);

        Serial.print("лево > прямо и лево > право. Расстояние меньше <");
        Serial.print(time_dist_action);
        Serial.println(">. Поворачиваю на лево!");
        Serial.println("<------------------------------------------------------->");

      } else if (Dist_right > Dist_front)
      {
        Serial.print("Dist_left=");
        Serial.print(Dist_left);
        Serial.print(" cm.");
        Serial.print("Dist_front=");
        Serial.print(Dist_front);
        Serial.print(" cm.");
        Serial.print("Dist_right=");
        Serial.print(Dist_right);
        Serial.println(" cm.");


        // right(); // поворачиваем направо 0,5 секунд.
        left();
        delay(time_90);

        Serial.print("право > прямо. Расстояние меньше <");
        Serial.print(time_dist_action);
        Serial.println(">. Поворачиваю на право!");
        Serial.println("<------------------------------------------------------->");
      }
    }
  }
  else
  {
    Serial.print("Dist_left=");
    Serial.print(Dist_left);
    Serial.print(" cm.");
    Serial.print("Dist_front=");
    Serial.print(Dist_front);
    Serial.print(" cm.");
    Serial.print("Dist_right=");
    Serial.print(Dist_right);
    Serial.println(" cm.");


    forward(); // едем вперед 0,5 секунды.

    Serial.println("Еду вперёд до упора!");
    Serial.println("<------------------------------------------------------->");
  }
}

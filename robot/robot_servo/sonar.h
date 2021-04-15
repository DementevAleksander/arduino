// Номера пинов сонара.
int Trig;
int Echo;
//=Режим пинов/портов ===============================
Sonar_init(int Tr, int Ec)
{
  Trig=Tr;
  Echo=Ec;
  // Задаем режимы работы пинов.
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
} 
//= Измерение расстояния ============================
  int Sonar(unsigned long Limit)
{
  int Long_cm;
  // Переводим лимит из сантиметров в относительные величины (микросек.)
  unsigned long Lim=Limit*58;
  // Генерируем импульс
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  // Ждем отражения импульса.
  // Пересчитываем время в расстояние (по скорости звука).
  Long_cm = int(pulseIn(Echo, HIGH, Lim)/58);
  // Если не дождались отражения,
  // присваиваем значение максимально измеряемому.
  if(Long_cm==0) return int(Limit);
  return Long_cm;
}

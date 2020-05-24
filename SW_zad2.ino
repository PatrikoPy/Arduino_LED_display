#define SENSOR_PIN  0
#define BUTTON_PIN_L 12
#define BUTTON_PIN_P 13


const char maxMode = 0x2;
unsigned short buttonStateL = 0;
unsigned short buttonStateP = 0;
int sensorValue = 0;
unsigned char mode = 0x01;
unsigned char led = 0x0;

void ledClear()
{
  for (short p = 2; p < 12; p++)
  {
    digitalWrite(p, LOW);
  }
}
unsigned char IntToGray(unsigned char input)
{
  return input ^ (input >> 1);
}
unsigned char IntToBCD(unsigned char input)
{
  return ((input / 10) << 4) | (input % 10);
}

void ledDisplay(unsigned char input)
{
  for (short i = 7, p = 4; i >= 0; i--, p++)
  {
    if (input >> i & 1)
    {
      digitalWrite(p, HIGH);
    }
    else
    {
      digitalWrite(p, LOW);
    }
  }
}
void setup() {
  for (int i = 4; i < 12; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_PIN_L, INPUT);
  pinMode(BUTTON_PIN_P, INPUT);
}

void loop() {
  buttonStateL = digitalRead(BUTTON_PIN_L);
  buttonStateP = digitalRead(BUTTON_PIN_P);
  if (buttonStateL == HIGH)
  {
    mode == 0x1 ? mode = maxMode : mode = mode >> 1;
    ledClear(); 
    delay(1000);
  }
  else if (buttonStateP == HIGH)
  {
    mode == maxMode ? mode = 0x1 : mode = mode << 1;
    ledClear();
    delay(1000);
  }
  sensorValue = analogRead(SENSOR_PIN);
  sensorValue = map(sensorValue, 0, 1023, 1, 5);
  if (mode & 0x1)
  {
    led > 99 ? led = 0 : led;
    ledDisplay(IntToBCD(led));
  }
  else if (mode & 0x2)
  {
    ledDisplay(IntToGray(led));
  }
  led++;
  delay(100 * sensorValue);
}

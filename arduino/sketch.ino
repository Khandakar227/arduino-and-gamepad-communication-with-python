/*
* This is sketch to demonstrate controlling a servo motor with a Gamepad controller through bluetooth
*/
#include <Servo.h>

Servo servo;
// To store incomming data
String data,
    // To store split data
    items[10];
// Connect Pin 9 to reset pin (RST)
// Thumb buttons A=3, B=2, X=4, Y=1, L1 = 5, L2 = 6, R1 = 7, R2 = 8, start = 9
// Button numbers may vary based on your gamepad controller
int RESET_PIN = 9,
    SERVO_PIN = 7,
    btn = 0,
    // Left  and Right thumb sliders
    left_thumb_x, left_thumb_y, right_thumb_x, right_thumb_y;
void setup()
{
  // put your setup code here, to run once:
  // pulling the Arduino RESET pin HIGH
  digitalWrite(RESET_PIN, HIGH);
  pinMode(RESET_PIN, OUTPUT);
  // Attach a servo
  servo.attach(SERVO_PIN);
  servo.write(0);
  Serial.begin(9600);
  Serial.println("Starting....");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    // Read the data from the Bluetooth module
    data = Serial.readStringUntil('\n');
    Serial.println(data);
    // data is sent as a stream of string separeted by a delimiter (,)
    int count = split(data, ',', items);
    Serial.print("Count: " + count);
    // First value is button numbe 1-9
    btn = items[0].toInt();
    // Reset arduino if necessary
    if (btn == 9)
      digitalWrite(RESET_PIN, LOW);
    // Slider values are from -100 to 99
    left_thumb_x = items[1].toInt(), left_thumb_y = items[3].toInt(), right_thumb_x = items[2].toInt(), right_thumb_y = items[4].toInt();
    // Process the upcoming value according to the Servo's degree of motion
    servo.write(map(left_thumb_x, -100, 99, 0, 180));
    Serial.print("left_thumb_x: "+ map(left_thumb_x, -100, 99, 0, 180));
  }
}
// A helper function to split the data
int split(String data, char delimiter, String *items)
{
  int count = 0;
  int len = data.length();
  char chars[len + 1];
  data.toCharArray(chars, len + 1);
  String item = "";
  for (int i = 0; i < len; i++)
  {
    if (chars[i] == delimiter)
    {
      items[count] = item;
      count++;
      item = "";
    }
    else
    {
      item += chars[i];
    }
  }
  items[count] = item;
  return count + 1;
}

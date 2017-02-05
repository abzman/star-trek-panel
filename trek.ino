#define woosh_pin 2
#define none_pin 3
#define alert_pin 4
#define trigger_pin 5
#define hail_pin 6
#define button_pin 7
#define blink_pin 8
#define woosh_switch_pin 9
#define none_switch_pin 10
#define alert_switch_pin 11
#define power_pin 12
#define led_pin 13
#define trigger_switch_pin A0
void setup() {
  Serial.begin(115200);
  pinMode(hail_pin, INPUT); //floating
  pinMode(button_pin, INPUT_PULLUP); //inverted
  pinMode(blink_pin, INPUT_PULLUP); //inverted
  pinMode(woosh_switch_pin, INPUT_PULLUP); //inverted
  pinMode(none_switch_pin, INPUT_PULLUP); //inverted
  pinMode(alert_switch_pin, INPUT_PULLUP); //inverted
  pinMode(trigger_pin, OUTPUT);
  digitalWrite(trigger_pin, LOW);
  pinMode(power_pin, OUTPUT);
  digitalWrite(power_pin, HIGH);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  pinMode(trigger_switch_pin, INPUT);
  woosh();
  poweron();
}

void loop() {
  /*
  alert();
  trigger();
Serial.println("first");
  delay(1000);
  killaudio();
Serial.println("second");
  delay(10000);
*/  
/*
  killaudio();
trigger();
Serial.println("first");
delay(3000);
//none();
  killaudio();
trigger();
Serial.println("second");
delay(3000);
  */
  //Serial.println(digitalRead(trigger_pin));
if(digitalRead(trigger_switch_pin))
{
  Serial.println("triggered");
  killaudio();
  trigger();
}
  
  if (!digitalRead(button_pin))//passes through button
  {
  killaudio();
    hail();
  }

  if (!digitalRead(blink_pin))//passses through led
  {
    digitalWrite(led_pin, HIGH);
  }
  else {
    digitalWrite(led_pin, LOW);
  }

  if (!digitalRead(woosh_switch_pin))//passes through switch
  {
    woosh();
  }
  else if (!digitalRead(none_switch_pin))
  {
    none();
  }
  else if (!digitalRead(alert_switch_pin))
  {
    alert();
  }
  
}

void none() {
  pinMode(woosh_pin, INPUT);
  pinMode(alert_pin, INPUT);
  pinMode(none_pin, OUTPUT);
  digitalWrite(none_pin, LOW);
}

void woosh() {
  pinMode(alert_pin, INPUT);
  pinMode(none_pin, INPUT);
  pinMode(woosh_pin, OUTPUT);
  digitalWrite(woosh_pin, LOW);
}

void alert() {
  pinMode(woosh_pin, INPUT);
  pinMode(none_pin, INPUT);
  pinMode(alert_pin, OUTPUT);
  digitalWrite(alert_pin, LOW);
}

void trigger() {
  digitalWrite(trigger_pin, HIGH);
  delay(100);
  digitalWrite(trigger_pin, LOW);
}

void hail() {

  pinMode(hail_pin, OUTPUT);
  digitalWrite(hail_pin, LOW);
  delay(10);
  pinMode(hail_pin, INPUT);

}
void poweron()
{
  
  digitalWrite(power_pin, HIGH);
}
void poweroff()
{
  
  digitalWrite(power_pin, LOW);
}

void killaudio()
{
    poweroff();
  delay(100);
  poweron();
  delay(200);
}



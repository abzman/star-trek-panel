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

#include <SerialCommand.h>
#include <Bounce2.h>

SerialCommand sCmd;     // The demo SerialCommand object

// Instantiate a Bounce object :
Bounce debouncer = Bounce();
Bounce debouncer2 = Bounce();

boolean led_pass = 1;

void setup() {
  Serial.begin(9600);
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


  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("WOOSH",    woosh_command);
  sCmd.addCommand("ALERT",   alert_command);
  sCmd.addCommand("HAIL",   hail_command);
  sCmd.addCommand("NONE",   none_command);
  sCmd.addCommand("KILL",   kill_command);
  sCmd.addCommand("ON",   led_on_command);
  sCmd.addCommand("OFF",   led_off_command);
  sCmd.addCommand("PASS",   led_pass_command);
  sCmd.addCommand("SWITCH",   switch_command);
  sCmd.addCommand("BLINK",   blink_command);
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (outputs command list (duh))

  // After setting up the button, setup the Bounce instance :
  debouncer.attach(trigger_switch_pin);
  debouncer.interval(5);

  // After setting up the button, setup the Bounce instance :
  debouncer2.attach(button_pin);
  debouncer2.interval(5); // interval in ms


  none();
  poweron();
  Serial.println("ready");
}

void woosh_command()
{
Serial.println("woosh");
  woosh();
  killaudio();
  trigger();
}

void alert_command()
{
Serial.println("alert");
  alert();
  killaudio();
  trigger();
}

void hail_command()
{
Serial.println("hail");
  killaudio();
  hail();
}

void none_command()
{
Serial.println("none");
  killaudio();
  none();
}

void kill_command()
{
Serial.println("kill");
  killaudio();
  
}

void led_on_command()
{
  led_pass = 0;
  digitalWrite(led_pin, HIGH);

}

void led_off_command()
{
  led_pass = 0;
  digitalWrite(led_pin, LOW);

}

void led_pass_command()
{
  led_pass = 1;
}

void switch_command()
{
  if (!digitalRead(woosh_switch_pin))//passes through switch
  {
    Serial.println("0");
  }
  else if (!digitalRead(none_switch_pin))
  {
    Serial.println("1");
  }
  else if (!digitalRead(alert_switch_pin))
  {
    Serial.println("2");
  }
  else
  {
    Serial.println("-1");
  }
}

void blink_command()
{
Serial.println("blink");
  alert();
  killaudio();
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("");
  Serial.println("Available commands:");
  Serial.println("WOOSH");
  Serial.println("ALERT");
  Serial.println("HAIL");
  Serial.println("NONE");
  Serial.println("KILL (kill current playing audio)");
  Serial.println("ON (LED on)");
  Serial.println("OFF (LED off)");
  Serial.println("PASS (passes through the LED state from the board)");
  Serial.println("BLINK (sets the board to red alert mode, does not trigger sound, LED blinks slowly)");
  Serial.println("SWITCH (returns the state of the front switch)");
  Serial.println("");
}

void loop() {
  sCmd.readSerial();     // We don't do much, just process serial commands

  if (!digitalRead(blink_pin) && led_pass) //passses through led
  {
    digitalWrite(led_pin, HIGH);
  }
  else if (digitalRead(blink_pin) && led_pass){
    digitalWrite(led_pin, LOW);
  }

  // Update the Bounce instance :
  debouncer.update();
  debouncer2.update();

  if ( debouncer2.fell() ) {
    Serial.println("3");
  }
  if ( debouncer.fell() ) {
    Serial.println("4");
  }

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
  /*
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
  */
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



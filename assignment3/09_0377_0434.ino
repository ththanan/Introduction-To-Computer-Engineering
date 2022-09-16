int button[2] = {9, 8};
int button_state[2] = {1, 1};
int lastbuttonstate[2] = {1, 1};
int lastdebouncetime[2] = {1, 1};
int debounce_delay = 50;

int cooldown[2] = {0, 0};
int cooldown_delay = 100;

int num[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
int G = 0xC2;
int L = 0xC7;
int random_num, current_num;


void setup() 
{
  pinMode(button[0], INPUT_PULLUP);
  pinMode(button[1], INPUT_PULLUP);
  DDRD = 0xFF;
  
  randomSeed(analogRead(A0));
  random_num = random(1,10);
  current_num = 1;
  display_num(current_num);
}


void loop()
{
  Debounce(0);
  Debounce(1);
  
  if(!button_state[0])
  {
    if((millis() - cooldown[0]) > cooldown_delay)
    {
      change_num();
    }
    cooldown[0] = millis();
  }
  display_num(current_num);
  
  if(!button_state[1])
  {
    if((millis() - cooldown[1]) > cooldown_delay)
    {
      check_num();
    }
    cooldown[1] = millis();
  }
}


void Debounce(int pin)
{
  int buttonRead = digitalRead(button[pin]);
  if(buttonRead != lastbuttonstate[pin])
  {
    lastdebouncetime[pin] = millis();
  }
  if((millis() - lastdebouncetime[pin]) > debounce_delay)
  {
    if(buttonRead != button_state[pin])
    {
      button_state[pin] = buttonRead;
    }
  }
  lastbuttonstate[pin] = buttonRead;
}  


void display_num(int n)
{
  PORTD = ~num[n];
}


void change_num()
{
  current_num++;
  if(current_num > 9)
  {
    current_num = 1;
  }
  delay(500);
}


void check_num()
{
  if(current_num == random_num)
  {
    display_num(0);
    current_num = 1;
    random_num = random(1, 10);
  }
  else if(current_num > random_num)
  {
    PORTD = G;
  }
  else if(current_num < random_num)
  {
    PORTD = L;
  }
  delay(1000);
}

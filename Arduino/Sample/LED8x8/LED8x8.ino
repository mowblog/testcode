const int col1 = 2; // the number of the col pin 13
const int col2 = 3; // the number of the col pin 3
const int col3 = 4; // the number of the col pin 4
const int col4 = 5; // the number of the col pin 10
const int col5 = 6; // the number of the col pin 6
const int col6 = 7; // the number of the col pin 11
const int col7 = 8; // the number of the col pin 15
const int col8 = 9; 

const int row1 = 13;

int i=0;
void setup()
{
  for(i=2;i<18;i++)
{
pinMode(i, OUTPUT);
}
}

void loop()
{
  for(i=2;i<=9;i++)
  {
  digitalWrite(i,LOW);
  digitalWrite(13,HIGH);
  delay(50);
  }
}

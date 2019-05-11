const int interuptxA = 2;
const int interuptxB = 5;
const int interuptyA = 3;
const int interuptyB = 4;
volatile int x = 0;
volatile int y = 0;

int xAstate, xBstate, yAstate, yBstate;
int x_lastpulse, y_lastpulse, xcord, ycord, i;
int parr[100][2] = {0};
int mapr[7][9] = { -1};


void Count_pulse_x () 
{
  xAstate = digitalRead(interuptxA);
  xBstate = digitalRead(interuptxB);
  if (xBstate == xAstate)
    x--;
  else if (xBstate != xAstate)
    x++;

  //  Serial.print("Postion 1 ");
  //  Serial.println(x);
}

void Count_pulse_y () 
{
  yAstate = digitalRead(interuptyA);
  yBstate = digitalRead(interuptyB);
  if (yBstate == yAstate)
    y--;
  else if (yBstate != yAstate)
    y++;

  //  Serial.print("Postion 2 ");
  //  Serial.println(y);
}



void setup() {
  Serial.begin(115200);
  pinMode(interuptxA, INPUT);
  digitalWrite(interuptxA, HIGH);
  pinMode(interuptxB, INPUT);
  digitalWrite(interuptxB, HIGH);
  pinMode(interuptyA, INPUT);
  digitalWrite(interuptyA, HIGH);
  pinMode(interuptyB, INPUT);
  digitalWrite(interuptyB, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);


  attachInterrupt(digitalPinToInterrupt(interuptxA), Count_pulse_x, RISING);
  attachInterrupt(digitalPinToInterrupt(interuptyA), Count_pulse_y, RISING);
  Serial.println("Setup executed");
}


void loop() 
{
  if (x - x_lastpulse == 500)
  {
    xcord++;
    x_lastpulse = x;
  }
  else if (x_lastpulse - x == 500)
  {
    xcord--;
    x_lastpulse = x;
  }

  if (y - y_lastpulse == 500)
  {
    ycord++;
    y_lastpulse = y;
  }
  else if (y_lastpulse - y == 500)
  {
    ycord--;
    y_lastpulse = y;
  }

  if (i < 200 && ((parr[i - 1][0] != xcord && parr[i - 1][1] == ycord) || (parr[i - 1][0] == xcord && parr[i - 1][1] != ycord) || (parr[i - 1][0] != xcord && parr[i - 1][1] != ycord)))
  {
    parr[i][0] = xcord;
    parr[i][1] = ycord;
    Serial.println();
    Serial.print(xcord);
    Serial.print("   ");
    Serial.print(ycord);
    Serial.print("\t");
    Serial.print(parr[i][0]);
    Serial.print("   ");
    Serial.print(parr[i][1]);
    Serial.print("\t");
    Serial.print(i);
    Serial.print("   ");
    i++;
    Serial.println();
  }


  if (i == 5)
  {
    for (int a = 0; a <5; a++)
    {
      for (int b = 0; b < 2; b++)
      {
        Serial.print("  Coordinated matrix  ");
        Serial.print("\t");
        Serial.print (parr[a][b]);
      }
      Serial.println();
    }
    
    Serial.println();
    Serial.println();
  }

}

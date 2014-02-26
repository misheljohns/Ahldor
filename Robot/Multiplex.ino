

/*---------------- Module Functions -------------------------*/


void InitMux()
{
  //pinmodes for A1 to A4 - OUT
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  
  //A0 - IN without pullup
  pinMode(A0, INPUT);
}

void SelectIn(uint8_t inp)
{
  digitalWrite(MUX_SET0, inp & 0x01);
  digitalWrite(MUX_SET1, inp & 0x02);
  digitalWrite(MUX_SET2, inp & 0x04);
  digitalWrite(MUX_SET3, inp & 0x08);
}

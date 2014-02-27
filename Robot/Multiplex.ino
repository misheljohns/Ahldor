/*
#define MUX_IN A4 C4
#define MUX_SET0 A3 C3
#define MUX_SET1 A2 C2 
#define MUX_SET2 A0 C0
#define MUX_SET3 A1 C1
*/

/*---------------- Module Variables -------------------------*/
/*
byte controlPins[] = {
                  B00000000, //0 
                  B00001000, //1
                  B00000100, //2
                  B00001100,
                  B00000001,
                  B00001001,
                  B00000101,
                  B00001101,
                  B00000010,
                  B00001010,
                  B00000110,
                  B00001110,
                  B00000011,
                  B00001011,
                  B00000111,
                  B00001111 }; //15
*/
/*---------------- Module Functions -------------------------*/


void InitMux()
{
  //pinmodes for A0 to A3 - OUT
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  //A4 - IN without pullup
  pinMode(A4, INPUT);
}

void SelectIn(byte inp)
{
  //PORTC = controlPins[inp];
  PORTC = inp;//faster to change wiring
}

byte ReadIn()
{
  return bitRead(PINC, 4);
}

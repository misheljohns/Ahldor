/****************************************************
 * Mining and shooting
 * Prefix: MINE
 ****************************************************/
 

/*---------------- Includes ---------------------------------*/

#include "MineShoot.h"

/*------------------ Module Level Variables -----------------*/

Servo rotator;
Servo miner;

byte exchangeSelect;
unsigned int ex3,ex5,ex8;

static Timer* timer;
int event_button_push;

// Desired servo position, used for sweeping the servo
int desired_servo_pos;
int current_servo_pos;

//number of pushes
int button_presses;

/*---------------- Module Functions -------------------------*/

void MINE_servo_write(int microseconds) {
  rotator.writeMicroseconds(microseconds);
}

void MINE_turn_servo(int pos) {
  desired_servo_pos = pos; 
  Serial.println("New turning servo position: " + String(pos));
}

void MINE_update_servo() {
  if(desired_servo_pos > current_servo_pos) current_servo_pos += 1;
  if(desired_servo_pos < current_servo_pos) current_servo_pos -= 1;
  MINE_servo_write(current_servo_pos);
}

void MINE_has_coin() {
  
}

void MINE_button_release() {
  Serial.println("Button released!");
  miner.write(BUTTON_OUT);
  
}

void MINE_button_push() {
  miner.write(BUTTON_IN);
  button_presses += 1;
  timer->after(BUTTON_OUT_TIME, MINE_button_release);
  Serial.println("Button pushed!");
}

int MINE_button_presses() {
  return button_presses;
}

void MINE_start_pushing_button() {
  event_button_push = timer->every(BUTTON_PUSH_RATE, MINE_button_push);
}

void MINE_stop_pushing_button() {
  timer->stop(event_button_push);
}

void MINE_selectside(byte a)
{
  if(a)
 {
   ex3 = EXCHANGE_3_ROT_A;
   ex5 = EXCHANGE_5_ROT_A;
   ex8 = EXCHANGE_8_ROT_A;
 }
 else
 {
   ex3 = EXCHANGE_3_ROT_B;
   ex5 = EXCHANGE_5_ROT_B;
   ex8 = EXCHANGE_8_ROT_B;
 }
}


void MINE_stop_shoot() {
  digitalWrite(SHOOTER, LOW);
}

void MINE_shoot() {
  digitalWrite(SHOOTER, HIGH);
  timer->after(SHOOT_TIME, MINE_stop_shoot);
}


void MINE_rotate_to_shoot()
{
  switch(exchangeSelect)
  {
    case EXCHANGE_3:
      MINE_turn_servo(ex3);
      break;
    case EXCHANGE_5:
      MINE_turn_servo(ex5);
      break;
    case EXCHANGE_8:
      MINE_turn_servo(ex8);
      break;
    case 4:
      //all exchanges down
      //victory code here (hopefully)
      break;
  }
  exchangeSelect = exchangeSelect + 1;
}

void MINE_Init(Timer* t) {
  
  timer = t;
  
  pinMode(SHOOTER, OUTPUT);
  
  rotator.attach(ROTATOR);
  current_servo_pos = SERVO_POS_CENTER;
  desired_servo_pos = current_servo_pos;
  
  miner.attach(MINER);
  miner.write(BUTTON_OUT);
  
  exchangeSelect = 1;
  button_presses = 0;
  
  MINE_stop_shoot();
  
  t->every(SERVO_UPDATE_RATE, MINE_update_servo);
  
  Serial.println("MINE module initialized!");
}

void MINE_commands() {
  COMM_check_command(String("PUSH"), MINE_button_push);
  COMM_check_command(String("START_PUSHING"), MINE_start_pushing_button);
  COMM_check_command(String("STOP_PUSHING"), MINE_stop_pushing_button);
  
  COMM_check_command(String("SERVO"), MINE_turn_servo);
  
  COMM_check_command(String("SHOOT"), MINE_shoot);
  COMM_check_command(String("STOP_SHOOT"), MINE_stop_shoot);
}

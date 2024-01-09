/*
 *  Open Loop Velocity Custom 01 
 *  By Blackcat / 2024.01.09
 *  Board: Nucleo-F446RE & SimpleFOCShield 2.0.4
 *  
 *  Code Description: 
 *  1. When System Power On. Initial Motor Config. (Open Loop)
 *  2. In While Loop. Using millis() Check Time Has Arrived 2s. Then Spin The Motor.
 *  3. If Time Has Arrived. Switch motor_states (FORWARD, STOP, BACKWARD)
 *  4. Spin The Motor 2 Rad/s (360 Deg), or Stop The Motor When motor_states == STOP.
 *
 *  Tips:
 *  1. Set motor.voltage_limit To 1.5 When Using PM3505/PM3510
 */

// Open loop motor control example
#include <SimpleFOC.h>


// BLDC motor & driver instance
// BLDCMotor motor = BLDCMotor(pole pair number);
BLDCMotor motor = BLDCMotor(11);
// BLDCDriver3PWM driver = BLDCDriver3PWM(pwmA, pwmB, pwmC, Enable(optional));
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8);

// Stepper motor & driver instance
//StepperMotor motor = StepperMotor(50);
//StepperDriver4PWM driver = StepperDriver4PWM(9, 5, 10, 6,  8);

// time sch
uint32_t prev_millis = 0;
enum { FORWARD = 0, STOP, BACKWARD };
uint8_t motor_states = FORWARD;

//target variable
float target_velocity = 0;

// instantiate the commander
// 2024.1.9 Blackcat: Ignored!
// Commander command = Commander(Serial);
// void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }
// void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }

void setup() {

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  // limit the maximal dc voltage the driver can set
  // as a protection measure for the low-resistance motors
  // this value is fixed on startup
  driver.voltage_limit = 6;
  driver.init();
  // link the motor and the driver
  motor.linkDriver(&driver);

  // limiting motor movements
  // limit the voltage to be set to the motor
  // start very low for high resistance motors
  // current = voltage / resistance, so try to be well under 1Amp

  // 2024.1.9 Blackcat: Set To 1.5 When Using PM3505/PM3510
  motor.voltage_limit = 1.5;   // [V]
 
  // open loop control config
  motor.controller = MotionControlType::velocity_openloop;

  // init motor hardware
  motor.init();

  // add target command T
//   command.add('T', doTarget, "target velocity");
//   command.add('L', doLimit, "voltage limit");

  Serial.begin(115200);
  Serial.println("Motor ready!");
//   Serial.println("Set target velocity [rad/s]");
//   _delay(1000);
}

void loop() {
  // open loop velocity movement
  // using motor.voltage_limit and motor.velocity_limit
  // to turn the motor "backwards", just set a negative target_velocity
  if ((millis() - prev_millis) >= 2000)
  {
    prev_millis = millis();
    motor_states = (motor_states < 3) ? motor_states + 1 : 0;

    Serial.printf("Motor Status: %d\n", motor_states);
  }

  switch (motor_states)
  {
    case FORWARD: 
        motor.move(6.28); break; // 2 rad = 360 deg 
    case BACKWARD:   
        motor.move(-6.28); break; // 2 rad = 360 deg 
    case STOP: 
    default:
        motor.move(0); break; // stop
  }
  // user communication
//   command.run();
}

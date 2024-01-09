```
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
 ```
void motor(int a, int b) {
  // স্পিড লিমিট করা (সেফটি চেক)
  a = constrain(a, -255, 255);
  b = constrain(b, -255, 255);

  // বাম মোটর (Left Motor) কন্ট্রোল
  if (a >= 0) {
    digitalWrite(left_motor_forward, HIGH);
    digitalWrite(left_motor_backward, LOW);
  } else {
    a = -a;
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(left_motor_backward, HIGH);
  }
  analogWrite(left_motor_speed, a); // পিন ১১ (ENA) তে স্পিড যাবে 

  // ডান মোটর (Right Motor) কন্ট্রোল
  if (b >= 0) {
    digitalWrite(right_motor_forward, HIGH);
    digitalWrite(right_motor_backward, LOW);
  } else {
    b = -b;
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(right_motor_backward, HIGH);
  }
  analogWrite(right_motor_speed, b); // পিন ৫ (ENB) তে স্পিড যাবে 
}


// void brake() {
//   motor(-20, -20);
//   delay(brake_time);
//   motor(0, 0);
//   delay(20);
// }
void brake() {
  // হঠাত থামানোর বদলে পাওয়ার কমিয়ে আনা (Soft Decay)
  for (int i = 80; i >= 0; i -= 20) { 
    motor(-i, -i); // হালকা রিভার্স পাওয়ার দিয়ে ধীরে ধীরে থামা
    delay(5); 
  }
  motor(0, 0); // শেষ পর্যায়ে পুরোপুরি থামা
  delay(10); 
}

void turn_90(char s) {
  (s == 'l') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
  delay(turn90_delay);  //this should be adjusted
  (s == 'r') ? motor(-turn_speed, turn_speed) : motor(turn_speed, -turn_speed);
  delay(turn_brake);
  motor(0, 0);
  delay(100);
}


// এই ফাংশনটি দিয়ে আমরা শর্ট প্রেস (১) এবং লং প্রেস (২) আলাদা করছি
byte push(byte button_number) {
  uint32_t b_timer = 0;
  if (!digitalRead(button_number)) {
    delay(50); // Debounce
    while (!digitalRead(button_number)) {
      delay(10);
      b_timer += 10;
      if (b_timer > 700) digitalWrite(led, 1); // লং প্রেস ডিটেক্ট হলে LED জ্বলবে
    }
    digitalWrite(led, 0);
    
    if (b_timer > 700) return 2; // লং প্রেস (Select বা Back)
    if (b_timer > 20)  return 1; // শর্ট প্রেস (Up বা Down)
  }
  return 0;
}
String menu_list(byte a) {
  if (a == 1)       return "Line Follow       ";
  else if (a == 2)  return "Counter           ";
  else if (a == 3)  return "Adjustment        ";
  else if (a == 4)  return "Path Adjust       ";
  else if (a == 5)  return "Calibration       ";
  else if (a == 6)  return "Analog Display    ";
  else if (a == 7)  return "Digital Display   ";
  else if (a == 8)  return "Go Forward        ";
  else if (a == 9)  return "Rotation Test     ";
  else if (a == 10)  return "Path Clear       ";
  else if (a == 11)  return "Memory Clear     ";
}

byte menu() {
  oled.set1X();
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 11;

  while (1) {
    if (temp != ind) {
      temp = ind;
      for (byte i = 0; i < 8 ; i++) {
        (i == ind - base) ? oled.setInvertMode(1) : oled.setInvertMode(0);
        text(String(i + base) + ") " + menu_list(i + base), 0, i);
      }
    }

    byte r1 = push(btn1);
    if (r1 == 1) { // UP
      ind--;
      if (ind < 1) { ind = limit; peak = ind; base = peak - 7; }
      else if (ind < base) { base = ind; peak = base + 7; }
    }
    else if (r1 == 2) { // SELECT
      // --- এই অংশটি সবথেকে সহজ সমাধান ---
      if (ind == 1) line_follow();
      else if (ind == 2) counter_adjust();
      else if (ind == 3) adjustment_panel();
      else if (ind == 4) path_panel();
      else if (ind == 5) calibration_display();
      else if (ind == 6) analog_display();
      else if (ind == 7) digital_display();
      else if (ind == 8) {
          motor(10 * spl, 10 * spr);
          while (push(btn1)==0);
          motor(0,0);  //button up to stop
        } else if (ind == 9) turn_90('l');
        else if (ind == 10) path_clear();
        else if (ind == 11) memory_clear();
      // সাব-মেনু থেকে ফেরার পর মেইন মেনু রিফ্রেশ করার জন্য:
      oled.clear();
      temp = 0; 
      oled.set1X();
    }

    byte r2 = push(btn2);
    if (r2 == 1) { // DOWN
      ind++;
      if (ind > limit) { ind = 1; base = ind; peak = base + 7; }
      else if (ind > peak) { peak = ind; base = peak - 7; }
    }
    else if (r2 == 2) { // BACK
      return 0; // এটি চাপলেই কেবল হোম স্ক্রিনে (VELOXA) যাবে
    }
  }
}

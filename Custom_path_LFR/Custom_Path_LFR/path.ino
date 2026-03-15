String path_list(byte a) {
  if (a == 0)      return "EMPTY               ";
  else if (a == 1) return "LEFT                ";
  else if (a == 2) return "STRAIGHT            ";
  else if (a == 3) return "RIGHT               ";
  else if (a == 4) return "T-LEFT              ";
  else if (a == 5) return "T-RIGHT             ";
  else if (a == 6) return "CROSS LEFT          ";
  else if (a == 7) return "CROSS STRAIGHT      ";
  else if (a == 8) return "CROSS RIGHT         ";
  else if (a == 9) return "90 DETECT           ";
  else if (a == 10) return "U TURN              ";
  else if (a == 11) return "WALL FOLLOW         ";
  else if (a == 12) return "OBSTACLE            ";
  else if (a == 13) return "INVERSE             ";
  else if (a == 14) return "CONTINUE            ";
  else              return "INVALID             ";
}
void path_panel() {
  oled.set1X();
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 25;
  while (1) {
    if (temp != ind) {
      temp = ind;
      for (byte i = 0; i < 8 ; i++) {
        (i == ind - base) ? oled.setInvertMode(1) : oled.setInvertMode(0);
        text(String(i + base) + ") " + path_list(path[i + base - 1]), 0, i);
      }
    }
    byte r1 = push(btn1);
    if (r1 == 1) { // শর্ট প্রেস = UP
      ind--;
      if (ind < 1) { ind = limit; peak = ind; base = peak - 7; }
      else if (ind < base) { base = ind; peak = base + 7; }
    }
    // UP লং প্রেস = SELECT
    else if (r1 == 2) { 
      path_adjust(ind - 1);
      oled.clear();   // ফিরে আসার পর স্ক্রিন পরিষ্কার
      temp = 0;       // মেনু রিফ্রেশ নিশ্চিত করা
      oled.set1X();   // ফন্ট রিসেট
    }

    // DOWN বাটন শর্ট প্রেস এর কাজ
    byte r2 = push(btn2);
    if (r2 == 1) { // শর্ট প্রেস = DOWN
      ind++;
      if (ind > limit) { ind = 1; base = ind; peak = base + 7; }
      else if (ind > peak) { peak = ind; base = peak - 7; }
    }
    // লং প্রেস = BACK/EXIT
    else if (r2 == 2) { 
      eeprom_refresh();
      return;
    }
   
  }
  
}
void path_adjust(int indicator) {
  oled.set2X();
  oled.clear();
  int value = path[indicator];
  int temp = -1, limit = 14;
  while (1) {
    if (temp != value) {
      temp = value;
      text(path_list(value), 5, 3);
    }
     // Up button short press
    byte r1 = push(btn1);
    if (r1 == 1) { 
       value++;
      if (value > limit) value=limit; 
    }
    //UP Button Long press
    else if (r1 == 2) {
      oled.set1X();
      path[indicator] = value;
      EEPROM.write(memory + indicator, value);
      delay(10);
      oled.set1X();
      return;
    }

    // Down বাটন Short Press
    byte r2 = push(btn2);
    if (r2 == 1) {
      value--;
      if (value < 0) value=0 ; 
    }
    //Down Button Long press
    else if (r2 == 2) {
      oled.set1X(); // ব্যাক
      return;
    }
  }
  oled.clear();
}

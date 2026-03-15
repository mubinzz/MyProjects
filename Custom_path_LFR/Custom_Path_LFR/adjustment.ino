String adjustment_list(byte a) {
    if (a == 1) return    "Top Speed     ";
  else if (a == 2) return "Motor Error   ";
  else if (a == 3) return "Turn Speed    ";
  else if (a == 4) return "Turn Brake    "; //turn newar shomoy opposite a thrust// joto beshi turn er biporite toto dhakka
  else if (a == 5) return "Brake Time    "; //joto beshi toto jore backa dhakka
  else if (a == 6) return "Turn 90 Delay ";// joto beshi toto beshi degree ghurbe
  else if (a == 7) return "U Turn Timer  ";//barale r o shamne check korbe
  else if (a == 8) return "Stop Timer    ";//all black hole kotokhon por thamne
  else if (a == 9) return "Node Delay    ";//junction pawar por r o kototuk shamne jabe
  else if (a == 10) return "Obj Dist.    ";
  else if (a == 11) return "Wall Dist.   ";
  else if (a == 12) return "Wall Mid     ";
  else if (a == 13) return "Wall Prop.   ";
  else if (a == 14) return "Inv. Timer   ";
}

void adjustment_panel() {
  oled.clear();
  oled.set1X();
  byte base = 1, peak = 8, temp = 0, ind = 1, limit = 14;
  int value;
  while (1) {
    if (temp != ind) {
      temp = ind;
      for (byte i = 0; i < 8 ; i++) {
  (i == ind - base) ? oled.setInvertMode(1) : oled.setInvertMode(0);
   if (i + base >= 5 && i + base <= 7) value = EEPROM.read(i + base + 19) * 10;
        else value = EEPROM.read(i + base + 19);
        if (i + base == 2) text(String(i + base) + ") " + adjustment_list(i + base) + String(value - 25) + " ", 0, i);
        else text(String(i + base) + ") " + adjustment_list(i + base) + String(value) + "   ", 0, i);
}
    }

    // UP বাটন শর্ট প্রেস
    byte r1 = push(btn1);
    if (r1 == 1) { // শর্ট প্রেস = UP
      ind--;
      if (ind < 1) { ind = limit; peak = ind; base = peak - 7; }
      else if (ind < base) { base = ind; peak = base + 7; }
    }
    // UP লং প্রেস = SELECT
    else if (r1 == 2) { 
      set_adjust(ind);
      oled.set1X();
      temp=0;
      oled.clear();
      }
    // DOWN বাটন শর্ট প্রেস
    byte r2 = push(btn2);
    if (r2 == 1) { // শর্ট প্রেস = DOWN
      ind++;
      if (ind > limit) { ind = 1; base = ind; peak = base + 7; }
      else if (ind > peak) { peak = ind; base = peak - 7; }
    }
    // DOWN লং প্রেস = BACK/EXIT
    else if (r2 == 2) { 
      return; //back
    }
  }
}

void set_adjust(int indicator) {
  oled.clear();
  oled.set2X();
 int value;
  if (indicator >= 5 && indicator <= 7) value = EEPROM.read(indicator + 19) * 10;
  else value = EEPROM.read(indicator + 19);

  int temp = -1, limit = 255;

  if (indicator == 1) limit = 25;
  else if (indicator == 2) limit = 50;
  else if (indicator >= 5 && indicator <= 7) limit = 2500;

  while (1) {
    if (temp != value) {
      temp = value;
      if (indicator == 2) text("SET: " + String(value - 25) + "    ", 5, 3);
      else text("SET: " + String(value) + "    ", 5, 3);
    }

    // Up button short press
    byte r1 = push(btn1);
    if (r1 == 1) { 
      if (value < limit) value++; 
    }
    //UP Button Long press
    else if (r1 == 2) { 
if (indicator >= 5 && indicator <= 7) {
    EEPROM.write(19 + indicator, value / 10); 
    delay(10);
    eeprom_refresh();
    oled.set1X();
    return;
} else {
    EEPROM.write(19 + indicator, value);
    delay(10);
    eeprom_refresh();
    oled.set1X();
    return;
}
      
    }
     
    // Down বাটন Short Press
    byte r2 = push(btn2);
    if (r2 == 1) {
      if (value > 0) value--; 
    }
    //Down Button Long press
    else if (r2 == 2) {
      oled.set1X(); // ব্যাক
      return;
    }
  }
  oled.clear();
}
void counter_adjust() {
  oled.set2X();
  oled.clear();
  counter = EEPROM.read(19);
  byte temp = -1, limit = 25;
  while (1) {
    if (temp != counter) {
      temp = counter;
      text("SET: " + String(counter) + "    ", 5, 3);
    }
    byte r1 = push(btn1);
    if (r1 == 1) { // শর্ট প্রেস = UP
      counter ++;
        if (counter > limit) counter = limit;
      }
    else if (r1 == 2) { // লং প্রেস = SELECT
       EEPROM.write(19, counter);
      delay(10);
      oled.set1X();
      eeprom_refresh();
      return;
    }

    // বাটন ২ এর কাজ
    byte r2 = push(btn2);
    if (r2 == 1) { // শর্ট প্রেস = DOWN
      counter --;
        if (counter < 0) counter = 0;
    }
    else if (r2 == 2) {// লং প্রেস = BACK/EXIT
      counter = EEPROM.read(19);
        return; 
    }
  }
  }
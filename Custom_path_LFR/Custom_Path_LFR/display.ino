void Veloxa() {
  oled.clear();
  oled.set2X();
  oled.setInvertMode(0);
  text("   LFR   ", 4, 1);
  text("  VELOXA  ", 10, 4);
}
void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}
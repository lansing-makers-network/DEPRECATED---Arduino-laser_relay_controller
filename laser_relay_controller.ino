/***
 *  Relay controller firmware for Lansing Makers Network's buildlog laser cutter.
 *  Original Author: Brian Adams
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/


#define RELAY_ON LOW
#define RELAY_OFF HIGH

#define COOLING A0
#define AIR_ASSIST A1
#define LASER A2
#define VENTILATION A3

#define ENABLE 2

#define COOLING_DELAY  300000
#define AIR_ASSIST_DELAY 30000
#define LASER_DELAY 0
#define VENTILATION_DELAY 20000

unsigned long millis_at_off;
bool running = false;

void setup() {
  digitalWrite(COOLING, RELAY_OFF);
  digitalWrite(AIR_ASSIST, RELAY_OFF);
  digitalWrite(LASER, RELAY_OFF);
  digitalWrite(VENTILATION, RELAY_OFF);
  
  pinMode(COOLING, OUTPUT);
  pinMode(AIR_ASSIST, OUTPUT);
  pinMode(LASER, OUTPUT);
  pinMode(VENTILATION, OUTPUT);
  pinMode(ENABLE, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(ENABLE) == LOW) {
    running = true;
    digitalWrite(COOLING, RELAY_ON);
    digitalWrite(AIR_ASSIST, RELAY_ON);  
    digitalWrite(LASER, RELAY_ON);
    digitalWrite(VENTILATION, RELAY_ON);
  } else {
    if (running == true) {
      running = false;
      millis_at_off = millis();
    }
    unsigned long current_millis = millis();
    
    if (current_millis >= (millis_at_off + COOLING_DELAY)) {
      digitalWrite(COOLING, RELAY_OFF);
    } 
    if (current_millis >= (millis_at_off + AIR_ASSIST_DELAY)) {
      digitalWrite(AIR_ASSIST, RELAY_OFF);
    }
    if (current_millis >= (millis_at_off + LASER_DELAY)) {
      digitalWrite(LASER, RELAY_OFF);
    }
    if (current_millis >= (millis_at_off + VENTILATION_DELAY)){
      digitalWrite(VENTILATION, RELAY_OFF);
    }
  }
}

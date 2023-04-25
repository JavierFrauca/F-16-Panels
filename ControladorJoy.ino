/* V1.0.1 SE INCLUYEN 2 SALIDAS ANALOGICAS MAS, SOLO ESTABA PROGRAMADA HASTA LA 4, AHORA ESTAN LAS 6 QUE PERMITE
 *  SE METEN RESITENCIAS PULL-UP EN LAS ENTRADAS ANALOGICAS, USAR POTENCIOMETROS DE 10K , SOLDADURAS LIMPIAS, LA MITAD DE LOS PROBLEMAS VIENEN POR USAR MALAS SOLDADURAS EN LOS POT.
 */
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Arduino.h>
#include <BasicEncoder.h>
#include <TimerOne.h>
#include <Joystick.h>
#include <pcf8574.h>

// INICIALIZAR LOS EXPANSORES I2C
PCF8574 Ext1(0x20);
PCF8574 Ext2(0x21);
PCF8574 Ext3(0x22);
PCF8574 Ext4(0x23);
PCF8574 Ext5(0x24);
PCF8574 Ext6(0x25);
PCF8574 Ext7(0x26);
PCF8574 Ext8(0x27);
//DEFINIR LOS PINES DE LOS ENCODER
BasicEncoder encoder1( 4, 5);
BasicEncoder encoder2( 6, 7);
BasicEncoder encoder3( 8, 9);
BasicEncoder encoder4( 10, 11);
BasicEncoder encoder5( 12, 13);
//VARIABLE PARA DETERMINAR LA DIRECCION EN LA QUE GIRAN LOS ENCODER
long Pos1 = -999;
long Pos2 = -999;
long Pos3 = -999;
long Pos4 = -999;
long Pos5 = -999;
//DEFINICION DE LOS 128 BOTONES CON LOS QUE SE HA DEFINIDIO EL HID
int ButtonState[128] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD ,
                   128, 0,                  // Button Count, Hat Switch Count
                   true, true, true,     // no X and no Y, no Z Axis
                   true, true, true,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering
//FUNCION QUE PROCESA LOS DATOS CAPTURADOS DE LOS ENCODER, SE LLAMARA CADA X MS DESDE EL TIMER1
void timer_service() {
  encoder1.service();
  encoder2.service();
  encoder3.service();
  encoder4.service();
  encoder5.service();
}
void setup() {
  //ACTIVAMOS LAS PULL-UP EN TODOS LAS ENTRADAS DEL ARDUINO Y LOS EXPANSORES
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  pinMode(Ext1, 0, INPUT_PULLUP);
  pinMode(Ext2, 0, INPUT_PULLUP);
  pinMode(Ext3, 0, INPUT_PULLUP);
  pinMode(Ext4, 0, INPUT_PULLUP);
  pinMode(Ext5, 0, INPUT_PULLUP);
  pinMode(Ext6, 0, INPUT_PULLUP);
  pinMode(Ext7, 0, INPUT_PULLUP);
  pinMode(Ext8, 0, INPUT_PULLUP);

  pinMode (A0, INPUT_PULLUP);
  pinMode (A1, INPUT_PULLUP);
  pinMode (A2, INPUT_PULLUP);
  pinMode (A3, INPUT_PULLUP);
  pinMode (A4, INPUT_PULLUP);
  pinMode (A5, INPUT_PULLUP);
  //SE INICIALIZA EL TIMER QUE ATIENDE LOS ENCODER
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timer_service);
  Joystick.begin(false);
}
void loop() {
  int delta1 = encoder1.get_change();
  if (delta1 > Pos1 && ButtonState[0] == 0) {
    ButtonState[0] = 1;
    ButtonState[1] = 0;
  } else if (delta1 < Pos1 && ButtonState[1] == 0) {
    ButtonState[0] = 0;
    ButtonState[1] = 1;
  } else {
    ButtonState[0] = 0;
    ButtonState[1] = 0;
  }
  Pos1 = 0;
  int delta2 = encoder2.get_change();
  if (delta2 > Pos2 &&  ButtonState[2] == 0) {
    ButtonState[2] = 1;
    ButtonState[3] = 0;
  } else if (delta2 < Pos2 && ButtonState[3] == 0) {
    ButtonState[2] = 0;
    ButtonState[3] = 1;
  } else {
    ButtonState[2] = 0;
    ButtonState[3] = 0;
  }
  Pos2 = 0;
  int delta3 = encoder3.get_change();
  if (delta3 > Pos3 && ButtonState[4] == 0) {
    ButtonState[4] = 1;
    ButtonState[5] = 0;
  } else if (delta3 < Pos3 && ButtonState[5] == 0) {
    ButtonState[4] = 0;
    ButtonState[5] = 1;
  } else {
    ButtonState[4] = 0;
    ButtonState[5] = 0;
  }
  Pos3 = 0;
  int delta4 = encoder4.get_change();
  if (delta4 > Pos4 && ButtonState[6] == 0) {
    ButtonState[6] = 1;
    ButtonState[7] = 0;
  } else if (delta4 < Pos4 && ButtonState[7] == 0) {
    ButtonState[6] = 0;
    ButtonState[7] = 1;
  } else {
    ButtonState[6] = 0;
    ButtonState[7] = 0;
  }
  Pos4 = 0;
  int delta5 = encoder5.get_change();
  if (delta5 > Pos5 && ButtonState[9] == 0) {
    ButtonState[9] = 1;
    ButtonState[10] = 0;
  } else if (delta5 < Pos5 && ButtonState[10] == 0) {
    ButtonState[9] = 0;
    ButtonState[10] = 1;
  } else {
    ButtonState[9] = 0;
    ButtonState[10] = 0;
  }
  Pos5 = 0;

  for (int dev = 1; dev < 9; dev++)
  {
    int offset = (dev * 8) + 8;
    for (int index = 0; index < 8; index++)
    {
      switch (dev) {
        case 1:
          ButtonState[index + offset] = !digitalRead(Ext1, index);
          break;
        case 2:
          ButtonState[index + offset] = !digitalRead(Ext2, index);
          break;
        case 3:
          ButtonState[index + offset] = !digitalRead(Ext3, index);
          break;
        case 4:
          ButtonState[index + offset] = !digitalRead(Ext4, index);
          break;
        case 5:
          ButtonState[index + offset] = !digitalRead(Ext5, index);
          break;
        case 6:
          ButtonState[index + offset] = !digitalRead(Ext6, index);
          break;
        case 7:
          ButtonState[index + offset] = !digitalRead(Ext7, index);
          break;
        case 8:
          ButtonState[index + offset] = !digitalRead(Ext8, index);
          break;
      }
    }
  }
  for (int index = 0; index < 128; index++)
  {
    Joystick.setButton(index, ButtonState[index]);
  }
  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));
  Joystick.setZAxis(analogRead(A2));
  Joystick.setRxAxis(analogRead(A3));
  Joystick.setRzAxis(analogRead(A4));
  Joystick.setRyAxis(analogRead(A5));
  Joystick.sendState();
  delay(50);
}

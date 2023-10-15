#include <ModbusMaster.h>  // Load the (modified) library for modbus communication command codes. Kindly install at our website.
#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
//SoftwareSerial softSerial(9, 8);
SoftwareSerial softSerial;

static uint8_t pzemSlaveAddr = 0x01;  // Declare the address of device (meter) in term of 8 bits. You can change to 0x02 etc if you have more than 1 meter.
static uint8_t pzemSlaveAddr1 = 0x55;
static uint16_t NewshuntAddr = 0x0001;

ModbusMaster node;     /* activate modbus master codes*/
float PZEMVoltage = 0; /* Declare value for DC voltage */
float PZEMCurrent = 0; /* Declare value for DC current*/
float PZEMPower = 0;   /* Declare value for DC Power */
float PZEMEnergy = 0;

typedef struct
{
  float voltage;
  float current;
  float power;
  float energy;
} Data_Pzem_t;
Data_Pzem_t AC;
PZEM004Tv30 pzem(Serial2, 16, 17);  // RX TX

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600, SWSERIAL_8N1, 18, 19, false, 95);
  setShunt(0x00);
  node.begin(pzemSlaveAddr, softSerial);
  //node.begin(pzemSlaveAddr1, softSerial);
  changeAddress(0XF8, 0x01);
}
uint64_t preRead, preRead1;
void loop() {
  if (millis() - preRead >= 2000) {
    uint8_t result; /* Declare variable "result" as 8 bits */
    result = node.readInputRegisters(0x0000, 6);

    if (result == node.ku8MBSuccess) /* If there is a response */
    {
      uint32_t tempdouble = 0x00000000;                     /* Declare variable "tempdouble" as 32 bits with initial value is 0 */
      PZEMVoltage = node.getResponseBuffer(0x0000) / 100.0; /* get the 16bit value for the voltage value, divide it by 100 (as per manual) */
                                                            // 0x0000 to 0x0008 are the register address of the measurement value
      PZEMCurrent = node.getResponseBuffer(0x0001) / 100.0; /* get the 16bit value for the current value, divide it by 100 (as per manual) */

      tempdouble = (node.getResponseBuffer(0x0003) << 16) + node.getResponseBuffer(0x0002); /* get the power value. Power value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
      PZEMPower = tempdouble / 10.0;                                                        /* Divide the value by 10 to get actual power value (as per manual) */

      tempdouble = (node.getResponseBuffer(0x0005) << 16) + node.getResponseBuffer(0x0004); /* get the energy value. Energy value is consists of 2 parts (2 digits of 16 bits in front and 2 digits of 16 bits at the back) and combine them to an unsigned 32bit */
      PZEMEnergy = tempdouble;
    }
    Serial.print("PZEMVoltage : ");
    Serial.println(PZEMVoltage);
    Serial.print("PZEMCurrent : ");
    Serial.println(PZEMCurrent);
    Serial.print("PZEMPower : ");
    Serial.println(PZEMPower);
    Serial.print("PZEMEnergy : ");
    Serial.println(PZEMEnergy);
    Serial.println();
    preRead = millis();
  }
  if (millis() - preRead1 >= 2500) {
    AC.voltage = pzem.voltage();
    AC.energy = pzem.energy();
    AC.power = pzem.power();
    AC.current = pzem.current();

    Serial.print("PZEMVoltage : ");
    Serial.println(AC.voltage);

    Serial.print("PZEMCurrent : ");
    Serial.println(AC.current);

    Serial.print("PZEMPower : ");
    Serial.println(AC.power);

    Serial.print("PZEMEnergy : ");
    Serial.println(AC.energy);
    Serial.println();
    preRead1 = millis();
  }
}
void setShunt(uint8_t slaveAddr)  //Change the slave address of a node
{
  static uint8_t SlaveParameter = 0x06;     /* Write command code to PZEM */
  static uint16_t registerAddress = 0x0003; /* change shunt register address command code */

  uint16_t u16CRC = 0xFFFF;                  /* declare CRC check 16 bits*/
  u16CRC = crc16_update(u16CRC, slaveAddr);  // Calculate the crc16 over the 6bytes to be send
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewshuntAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewshuntAddr));

  softSerial.write(slaveAddr); /* these whole process code sequence refer to manual*/
  softSerial.write(SlaveParameter);
  softSerial.write(highByte(registerAddress));
  softSerial.write(lowByte(registerAddress));
  softSerial.write(highByte(NewshuntAddr));
  softSerial.write(lowByte(NewshuntAddr));
  softSerial.write(lowByte(u16CRC));
  softSerial.write(highByte(u16CRC));
  while (softSerial.available()) /* while receiving signal from softSerial3 from meter and converter */
  {
  }
}
void changeAddress(uint8_t OldslaveAddr, uint8_t NewslaveAddr)  //Change the slave address of a node
{
  static uint8_t SlaveParameter = 0x06;         /* Write command code to PZEM */
  static uint16_t registerAddress = 0x0002;     /* Modbus RTU device address command code */
  uint16_t u16CRC = 0xFFFF;                     /* declare CRC check 16 bits*/
  u16CRC = crc16_update(u16CRC, OldslaveAddr);  // Calculate the crc16 over the 6bytes to be send
  u16CRC = crc16_update(u16CRC, SlaveParameter);
  u16CRC = crc16_update(u16CRC, highByte(registerAddress));
  u16CRC = crc16_update(u16CRC, lowByte(registerAddress));
  u16CRC = crc16_update(u16CRC, highByte(NewslaveAddr));
  u16CRC = crc16_update(u16CRC, lowByte(NewslaveAddr));


  softSerial.write(OldslaveAddr); /* these whole process code sequence refer to manual*/
  softSerial.write(SlaveParameter);
  softSerial.write(highByte(registerAddress));
  softSerial.write(lowByte(registerAddress));
  softSerial.write(highByte(NewslaveAddr));
  softSerial.write(lowByte(NewslaveAddr));
  softSerial.write(lowByte(u16CRC));
  softSerial.write(highByte(u16CRC));
  while (softSerial.available()) /* while receiving signal from softSerial3 from meter and converter */
  {
  }
}
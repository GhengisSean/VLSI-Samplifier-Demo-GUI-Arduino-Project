//TO DO: Look at Turbo SPI
//TO DO: Link with GUI


#include <SPI.h>

#define READ 0xFF
#define WRITE 0x00

#define REG_NUM 28

//#define SS 7 // Set slave select pin to 7 for now

char command[12];

uint16_t registers[] = {
  B00000011,
  B00000100,
  B00000101,
  B00000110,
  B00000111,
  B00001000,
  B00001001,
  B00001010,
  B00001011,
  B00001100,
  B00001101,
  B00001110,
  B00001111,
  B00010000,
  B00010001,
  B00010010,
  B00010011,
  B00010100,
  B00010101,
  B00010110,
  B00010111,
  B00011000,
  B00011010,
  B00011011,
  B00011100,
  B00011101,
  B00011110,
  B00011111
};

void SPIWrite(uint16_t reg, uint16_t data) {
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
  SPI.transfer(WRITE);
  SPI.transfer16(reg);
  SPI.transfer16(data);
  SPI.end(); 
}

void SPIWriteAll() {
  for (int i = 0; i < REG_NUM; i++){
    Serial.print("Enter data for register " + registers[i]);  
    int input = Serial.parseInt();
    if (Serial.available()) SPIWrite(registers[i], Serial.read());
  }
}

void Reset() {
  for (int i = 0; i < REG_NUM; i++){
    SPIWrite(registers[i], 0);
  }
}

void SPIRead(uint16_t reg) {
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
  SPI.transfer(READ);
  uint16_t value = SPI.transfer16(reg);
  Serial.print("Value: ");
  Serial.println(value); 
  SPI.end(); 
}

void SPIReadAll() {
  for (int i = 0; i < REG_NUM; i++){
    Serial.print(registers[i] + ": ");
    SPIRead(registers[i]); 
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    command[12] = Serial.read();

    if(command == "WRITE"){
      Serial.print("Register: ");
      uint16_t addr = Serial.read();
      Serial.print("Data: ");
      uint16_t data = Serial.read();
      SPIWrite(addr, data);
    }

    else if (command == "READ"){
      Serial.print("Register: ");
      uint16_t addr = Serial.read();
      SPIRead(addr);
    }

    else if (command == "WRITE ALL"){
      SPIWriteAll();
    }

    else if (command == "READ ALL"){
      SPIReadAll();
    }

    else if (command == "RESET"){
      Reset();
    }

    else{
      Serial.println("To write to a regiser, input WRITE");
      Serial.println("To read from a regiser, input READ");
      Serial.println("To write to all registers, input WRITE ALL");
      Serial.println("To read from all regisers, input READ ALL");
      Serial.println("To reset, input RESET");
    }
    
  }

}

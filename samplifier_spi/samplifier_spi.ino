//TO DO: Look at Turbo SPI
//TO DO: Link with GUI


#include <SPI.h>

#define READ 0xFF
#define WRITE 0x00

#define REG_NUM 28

#define READ_NUM 14 //Number of read registers
#define WRITE_NUM 14 //Number of write registers


#define SS 4 // Set slave select pin to 7 for now

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


//array of read registers
uint16_t read_reg[] = {
  
};


//array of write registers
uint16_t write_reg[] = {
  
};


void Reset() {
  for (int i = 0; i < REG_NUM; i++){
    SPISend(registers[i], 0);
  }
}

//for reading
void SPISend(uint16_t reg) {

  SPI.begin(4);
  //SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0)); <-- for some reason this isn't working
  
  //use these settings for now, SPISettings object not behaving as expected
  SPI.setClockDivider(4, 256);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  uint16_t value = SPI.transfer16(4, reg);
  Serial.print("Value: ");
  Serial.println(value); 
  SPI.end(); 
}

//for writing
void SPISend(uint16_t reg, uint16_t data){
  
  SPI.begin(4);
  //SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0)); <-- for some reason this isn't working
  
  //use these settings for now, SPISettings object not behaving as expected
  SPI.setClockDivider(4, 256);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  SPI.transfer16(4, reg, SPI_CONTINUE);
  SPI.transfer16(4, data);
  Serial.println("Successfully wrote " + String(data) + "in register " + String(reg));
  SPI.end(); 
}

void SPIReadAll() {
  for (int i = 0; i < REG_NUM; i++){
    Serial.print(read_reg[i] + ": ");
    SPISend(read_reg[i]); 
  }
}

void SPIWriteAll() {
  for (int i = 0; i < WRITE_NUM; i++){
    Serial.print("Enter data for register " + write_reg[i]);  
    int input = Serial.parseInt();
    if (Serial.available()) SPISend(write_reg[i], Serial.read());
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  }

void loop() {
  // put your main code here, to run repeatedly:

  while(!Serial.available()) //poll serial monitor
  
   
  if (Serial.readString() == "WRITE"){
    Serial.print("Register: ");
    uint16_t addr = Serial.read();
    Serial.print("Data: ");
    uint16_t data = Serial.read();
    SPISend(addr, data);
  }
  
  else if (Serial.readString() == "READ"){
    Serial.print("Register: ");
    uint16_t addr = Serial.parseInt();
    SPISend(addr);
  }
  
  else if (Serial.readString() == "WRITE ALL"){
    SPIWriteAll();
  }
  
  else if (Serial.readString() == "READ ALL"){
    SPIReadAll();
  }
  
  else if (Serial.readString() == "RESET"){
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

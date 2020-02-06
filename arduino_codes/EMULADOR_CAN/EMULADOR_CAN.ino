#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
  Serial.println("MCP2515 Initialized Successfully!");
  else 
  Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   
}
 //0 a 255 
 //Vetores que simulam os dados do inversor
byte data1[8] = {0x39, 0x09, 0xC0, 0xF0, 0xCF, 0xFF, 0xCC, 0x07}; //8cf00002 || Velocidade km/h [0] || Velocidade RPM [2]
byte data2[8] = {0x10, 0x00, 0x00, 0x00, 0x20, 0xFF, 0xA6, 0xC7}; //8cf10002 || Frente [0+1] || Ré [2+3] || Carga da bateria
byte data3[8] = {0x60, 0x31, 0x02, 0xB3, 0x74, 0xA7, 0x46, 0x17}; //8cf20002 ||
byte data4[8] = {0xF4, 0xB0, 0xC4, 0xB8, 0x74, 0x59, 0xF4, 0xA8}; //8cf30002 ||
byte data5[8] = {0x30, 0x25, 0x10, 0x12, 0x64, 0x25, 0x46, 0x27}; //8cf40002 ||
byte data6[8] = {0x00, 0x00, 0x00, 0x00, 0xD4, 0x1E, 0x1F, 0xCA}; //8cf50002 ||
byte data7[8] = {0xCD, 0xF3, 0x3F, 0xCF, 0xFE, 0x3D, 0x86, 0x12}; //8cf60002 ||
byte data8[8] = {0x10, 0xF1, 0xC3, 0xD3, 0xA4, 0x15, 0x66, 0x80}; //8cf70002 ||
byte data9[8] = {0xA0, 0xC1, 0x88, 0x76, 0xC4, 0xC5, 0xE6, 0x55}; //8cf80002 ||
byte data10[8] = {0x10, 0x10, 0xF1, 0xA3, 0xC4, 0xC5, 0xE6, 0xD7}; //986555f4 ||
byte data11[8] = {0xF0, 0xE1, 0xF2, 0xA1, 0xCC, 0xBB, 0xD4, 0xD8}; //986655f4 ||
byte data12[8] = {0xA9, 0xE4, 0x31, 0x64, 0xC0, 0xC1, 0xE2, 0xD9}; //986955f4 ||
byte data13[8] = {0x11, 0x10, 0x12, 0x07, 0x03, 0x02, 0x04, 0x03}; //986a55f4 ||
byte data14[8] = {0x65, 0xE4, 0xF8, 0x66, 0x24, 0xF5, 0xB6, 0xA7}; //986b55f4 ||
byte data15[8] = {0xA9, 0xE4, 0xE8, 0x46, 0x20, 0x75, 0x46, 0xC7}; //986c55f4 ||
byte data16[8] = {0x19, 0xE4, 0xD8, 0xA6, 0x24, 0xF5, 0xB6, 0xB7}; //986d55f4 ||
byte data17[8] = {0x29, 0xA4, 0xD8, 0x26, 0x49, 0xff, 0x26, 0xA0}; //986e55f4 ||
byte data18[8] = {0x1C, 0xE4, 0xA8, 0x26, 0x24, 0xF5, 0xB6, 0xA7}; //90f00001 ||
byte data19[8] = {0x01, 0xE4, 0xF8, 0x66, 0xA4, 0x15, 0xF6, 0xA7}; //8cf30003 ||
byte data20[8] = {0x10, 0x11, 0x10, 0x09, 0x22, 0xD5, 0xB6, 0xA7}; //8cf40003 ||
//Serial.println();
void loop()
{
for( int i=0; i<20;i++){
  
  if(i == 0) CAN0.sendMsgBuf(0xCF00002, 1, 8, data1); // Envia um vetor de cada vez pro barramento, já com os identificadores do inversor, simulando o inversor
  if(i == 1) CAN0.sendMsgBuf(0xCF10002, 1, 8, data2); // ( Identificador , 1 = Extended Frame ID , tamanho do vetor , Vetor)
  if(i == 2) CAN0.sendMsgBuf(0xCF20002, 1, 8, data3);
  if(i == 3) CAN0.sendMsgBuf(0xCF30002, 1, 8, data4);
  if(i == 4) CAN0.sendMsgBuf(0xCF40002, 1, 8, data5);
  if(i == 5) CAN0.sendMsgBuf(0xCF50002, 1, 8, data6);
  if(i == 6) CAN0.sendMsgBuf(0xCF60002, 1, 8, data7);
  if(i == 7) CAN0.sendMsgBuf(0xCF70002, 1, 8, data8);
  if(i == 8) CAN0.sendMsgBuf(0xCF80002, 1, 8, data9); 
  if(i == 9) CAN0.sendMsgBuf(0x186555F4, 1, 8, data10);
  if(i == 10)CAN0.sendMsgBuf(0x186655F4, 1, 8, data11);
  if(i == 11)CAN0.sendMsgBuf(0x186955F4, 1, 8, data12);
  if(i == 12)CAN0.sendMsgBuf(0x186A55F4, 1, 8, data13);
  if(i == 13)CAN0.sendMsgBuf(0x186B55F4, 1, 8, data14);
  if(i == 14)CAN0.sendMsgBuf(0x186C55F4, 1, 8, data15);
  if(i == 15)CAN0.sendMsgBuf(0x186D55F4, 1, 8, data16);
  if(i == 16)CAN0.sendMsgBuf(0x186E55F4, 1, 8, data17);
  if(i == 17)CAN0.sendMsgBuf(0x10F00001, 1, 8, data18);
  if(i == 18)CAN0.sendMsgBuf(0x0CF30003, 1, 8, data19);
  if(i == 19)CAN0.sendMsgBuf(0x0CF40003, 1, 8, data20);// Só estou conseguindo receber variaveis de 8bits mas o inversor trabalha com 16bits '-'
delay (10);
}
}
// 2048
//29

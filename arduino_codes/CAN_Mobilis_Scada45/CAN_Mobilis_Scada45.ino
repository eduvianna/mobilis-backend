#include <SimpleModbusSlave.h>
#include <mcp_can.h>
#include <SPI.h>
#define CAN0_INT 2

long unsigned int rxId, Identificador, tempo;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128]; 

MCP_CAN CAN0(10);
void sendCan(void);
unsigned int holdingRegs[63], auxiliar[63], vetor[8];

void setup() {
  
 Serial.begin(115200);
 pinMode(CAN0_INT, INPUT);
 modbus_configure(&Serial, 115200, SERIAL_8N1, 1, 2, 63, holdingRegs);
 modbus_update_comms(115200, SERIAL_8N1, 1);
 if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
 Serial.println("MCP2515 Initialized Successfully!");
 else Serial.println("Error Initializing MCP2515...");
 CAN0.setMode(MCP_NORMAL);
 Serial.println("MCP2515 CAN Receive");
// tempo = millis();
 }

void sendData(const String& id, const String& Word, const String& value) {
  String message = String(id)+":"+String(Word)+":"+String(value);
  Serial.println(message);
}

void loop() {
  delay(1000);
if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    Identificador = rxId;
    String ID = String(Identificador,HEX);
    
       for(byte i = 0; i<len; i++){
       vetor[i] = rxBuf[i];
  //     sprintf(msgString, " 0x%.2X", rxBuf[i]);
  //    Serial.println(ID);

if(ID == "8cf00002"){
 auxiliar[0] = vetor[0]; // Velocidade km/h 
 sendData("0xcf00002", "1", String(auxiliar[0]));
 auxiliar[61] = vetor[2]; // Velocidade RPM
 sendData("0xcf00002", "2", String(auxiliar[61]));
 }
if(ID == "8cf10002"){
auxiliar[1] = vetor[0] + vetor[1]; // Frente 
sendData("0xcf10002", "1", String(auxiliar[1])); 
auxiliar[2] = vetor[2] + vetor[3]; // Ré
sendData("0xcf10002", "2", String(auxiliar[2])); 
auxiliar[62] = vetor[4]; //Carga da bateria
sendData("0xcf10002", "3", String(auxiliar[3]));  
}
if(ID == "8cf20002"){
  auxiliar[3] = vetor[3]; // Torque motor
  sendData("0xcf20002", "4", String(auxiliar[3])); 
 }
if(ID == "8cf30002"){ 
  auxiliar[4] = vetor[0] + vetor[1]; // Temperatura Mosfet 1
  sendData("0xcf30002", "1", String(auxiliar[4])); 
  auxiliar[5] = vetor[2] + vetor[3]; // Temperatura Mosfet 2
  sendData("0xcf30002", "2", String(auxiliar[5]));
  auxiliar[6] = vetor[4] + vetor[5]; // Temperatura Ambiente
  sendData("0xcf30002", "3", String(auxiliar[6]));
  auxiliar[7] = vetor[6] + vetor[7]; // Temperatura Motor
  sendData("0xcf30002", "4", String(auxiliar[7]));
}
if( ID == "8cf40002"){
 auxiliar[8] = vetor[0] + vetor[1]; // Corrente Regeneração Motor
 sendData("0xcf40002", "1", String(auxiliar[8]));
 auxiliar[9] = vetor[2] + vetor[3]; // Corrente Motor
 sendData("0xcf40002", "2", String(auxiliar[9]));
 auxiliar[10] = vetor[4] + vetor[5]; // Tensão Motor
 sendData("0xcf40002", "3", String(auxiliar[10]));
 auxiliar[11] = vetor[6] + vetor[7]; // Potencia Motor
 sendData("0xcf40002", "4", String(auxiliar[11]));
}
if( ID == "8cf50002"){
 auxiliar[12] = vetor[0] + vetor[1]; // Alarme Atual 
 sendData("0xcf50002", "1", String(auxiliar[12]));
 auxiliar[13] = vetor[2] + vetor[3]; // Falha Atual
 sendData("0xcf50002", "2", String(auxiliar[13]));
 auxiliar[14] = vetor[4] + vetor[5]; // Última Falha
 sendData("0xcf50002", "3", String(auxiliar[14]));
 auxiliar[15] = vetor[6] + vetor[7]; // Segunda Falha
 sendData("0xcf50002", "4", String(auxiliar[15]));
}
if( ID == "8cf60002"){
 auxiliar[16] = vetor[0] + vetor[1]; // Terceira Falha
 sendData("0xcf60002", "1", String(auxiliar[16]));
 auxiliar[17] = vetor[2] + vetor[3]; // Quarta Falha
 sendData("0xcf60002", "2", String(auxiliar[17]));
 auxiliar[18] = vetor[4] + vetor[5]; // Quinta Falha
 sendData("0xcf60002", "3", String(auxiliar[18]));
 auxiliar[19] = vetor[6] + vetor[7]; // Corrente da Última Falha
 sendData("0xcf60002", "4", String(auxiliar[19]));
}

if( ID == "8cf70002"){
 auxiliar[20] = vetor[0] + vetor[1]; // Tensão Bateria Última Falha
 sendData("0xcf70002", "1", String(auxiliar[20]));
 auxiliar[21] = vetor[2] + vetor[3]; // Rotação Última Falha (rpm)
 sendData("0xcf70002", "2", String(auxiliar[21]));
 auxiliar[22] = vetor[4] + vetor[5]; // Frequencia Última Falha
 sendData("0xcf70002", "3", String(auxiliar[22]));
 auxiliar[23] = vetor[6] + vetor[7]; // Tensão Motor Última Falha
 sendData("0xcf70002", "4", String(auxiliar[23]));
}

if(ID == "8cf80002"){
 auxiliar[24] = vetor[0] + vetor[1]; // Corrente de entrada do Inversor
 sendData("0xcf80002", "1", String(auxiliar[24]));
 auxiliar[25] = vetor[2] + vetor[3]; // Código de alarme CVW300
 sendData("0xcf80002", "2", String(auxiliar[25]));
} 

if(ID == "986555f4"){
 auxiliar[26] = vetor[0] + vetor[1]; // Tensão Total 
 sendData("0x186555f4", "1", String(auxiliar[26]));
 auxiliar[27] = vetor[2] + vetor[3]; // Corrente de Carga Total
 sendData("0x186555f4", "2", String(auxiliar[27]));
 auxiliar[28] = vetor[4] + vetor[5]; // Corrente de Descarga
 sendData("0x186555f4", "3", String(auxiliar[28]));
}

if(ID == "986655f4"){
 auxiliar[29] = vetor[0] + vetor[1]; // Temp Bateria ponto 1
 sendData("0x186655f4", "1", String(auxiliar[29]));
 auxiliar[30] = vetor[2] + vetor[3]; // Temp Bateria ponto 2
 sendData("0x186655f4", "2", String(auxiliar[30]));
 auxiliar[31] = vetor[4] + vetor[5]; // Temp Bateria ponto 3
 sendData("0x186655f4", "3", String(auxiliar[31]));
 auxiliar[32] = vetor[6] + vetor[7]; // Temp Bateria ponto 4
 sendData("0x186655f4", "4", String(auxiliar[32]));
}

if(ID == "986955f4"){
 auxiliar[33] = vetor[0] + vetor[1]; // Maxima temperatura
 sendData("0x186955f4", "1", String(auxiliar[33]));
 auxiliar[34] = vetor[2] + vetor[3]; // Minima temperatura 
 sendData("0x186955f4", "1", String(auxiliar[34]));
}

if(ID == "986a55f4"){
 auxiliar[35] = vetor[0] + vetor[1]; // Tensão mais alta
 sendData("0x186a55f4", "1", String(auxiliar[35])); 
 auxiliar[36] = vetor[2] + vetor[3]; // Tensão mais Baixa
 sendData("0x186a55f4", "2", String(auxiliar[36]));
 auxiliar[37] = vetor[4] + vetor[5]; // ID da celula de maior tensão
 sendData("0x186a55f4", "3", String(auxiliar[37]));
 auxiliar[38] = vetor[6] + vetor[7]; // ID da celula de menor tensão
 sendData("0x186a55f4", "4", String(auxiliar[38]));
}

if(ID == "986b55f4"){
 auxiliar[39] = vetor[0] + vetor[1]; // Temp célula 1
 sendData("0x186b55f4", "1", String(auxiliar[39])); 
 auxiliar[40] = vetor[2] + vetor[3]; // Temp célula 2
 sendData("0x186b55f4", "2", String(auxiliar[40])); 
 auxiliar[41] = vetor[4] + vetor[5]; // Temp célula 3
 sendData("0x186b55f4", "3", String(auxiliar[41])); 
 auxiliar[42] = vetor[6] + vetor[7]; // Temp célula 4
 sendData("0x186b55f4", "4", String(auxiliar[42]));
}

if(ID == "986c55f4"){
 auxiliar[43] = vetor[0] + vetor[1]; // Temp célula 5
 sendData("0x186c55f4", "1", String(auxiliar[43]));
 auxiliar[44] = vetor[2] + vetor[3]; // Temp célula 6
 sendData("0x186c55f4", "2", String(auxiliar[44])); 
 auxiliar[45] = vetor[4] + vetor[5]; // Temp célula 7
 sendData("0x186c55f4", "3", String(auxiliar[45])); 
 auxiliar[46] = vetor[6] + vetor[7]; // Temp célula 8
 sendData("0x186c55f4", "4", String(auxiliar[46])); 
}

if(ID == "986d55f4"){
 auxiliar[47] = vetor[0] + vetor[1]; // Temp célula 9
 sendData("0x186d55f4", "1", String(auxiliar[47]));  
 auxiliar[48] = vetor[2] + vetor[3]; // Temp célula 10
 sendData("0x186d55f4", "2", String(auxiliar[48])); 
 auxiliar[49] = vetor[4] + vetor[5]; // Temp célula 11
 sendData("0x186d55f4", "3", String(auxiliar[49])); 
 auxiliar[50] = vetor[6] + vetor[7]; // Temp célula 12
 sendData("0x186d55f4", "4", String(auxiliar[50])); 
}

if(ID == "986e55f4"){
 auxiliar[51] = vetor[0] + vetor[1]; // Temp célula 13
 sendData("0x186e55f4", "1", String(auxiliar[51]));  
 auxiliar[52] = vetor[2] + vetor[3]; // Temp célula 14
 sendData("0x186e55f4", "2", String(auxiliar[52])); 
 auxiliar[53] = vetor[4] + vetor[5]; // Temp célula 15
 sendData("0x186e55f4", "3", String(auxiliar[53])); 
 auxiliar[54] = vetor[6] + vetor[7]; // Temp célula 16
 sendData("0x186e55f4", "4", String(auxiliar[54])); 
}
if(ID == "90f00001"){
 auxiliar[55] = vetor[0]; // Hodômetro Total
 sendData("0x10f00001", "1", String(auxiliar[55]));
 auxiliar[56] = vetor[3]; // Horímetro Total
 sendData("0x10f00001", "2", String(auxiliar[56]));
}
if(ID == "8cf30003"){
 auxiliar[57] = vetor[0]; // Carro Ligado
 sendData("0x0cf30003", "1", String(auxiliar[57]));
 auxiliar[58] = vetor[1]; // Carro Desligado
 sendData("0x0cf30003", "2", String(auxiliar[58]));
}
if(ID == "8cf40003"){
 auxiliar[59] = vetor[0] + vetor[1]; // Temp Inversor (ok)
 sendData("0x0cf40003", "1", String(auxiliar[59]));
 auxiliar[60] = vetor[2] + vetor[3]; // Temp Bateria Media(ok)
 sendData("0x0cf40003", "2", String(auxiliar[60]));
}

modbus_update();
holdingRegs[0] = auxiliar[0];
holdingRegs[1] = auxiliar[1];
holdingRegs[2] = auxiliar[2];
holdingRegs[3] = auxiliar[3];
holdingRegs[4] = auxiliar[4];
holdingRegs[5] = auxiliar[5];
holdingRegs[6] = auxiliar[6];
holdingRegs[7] = auxiliar[7];
holdingRegs[8] = auxiliar[8];
holdingRegs[9] = auxiliar[9];
holdingRegs[10] = auxiliar[10];
holdingRegs[11] = auxiliar[11];
holdingRegs[12] = auxiliar[12];
holdingRegs[13] = auxiliar[13];
holdingRegs[14] = auxiliar[14];
holdingRegs[15] = auxiliar[15];
holdingRegs[16] = auxiliar[16];
holdingRegs[17] = auxiliar[17];
holdingRegs[18] = auxiliar[18];
holdingRegs[19] = auxiliar[19];
holdingRegs[20] = auxiliar[20];
holdingRegs[21] = auxiliar[21];
holdingRegs[22] = auxiliar[22];
holdingRegs[23] = auxiliar[23];
holdingRegs[24] = auxiliar[24];
holdingRegs[25] = auxiliar[25];
holdingRegs[26] = auxiliar[26];
holdingRegs[27] = auxiliar[27];
holdingRegs[28] = auxiliar[28];
holdingRegs[29] = auxiliar[29];
holdingRegs[30] = auxiliar[30];
holdingRegs[31] = auxiliar[31];
holdingRegs[32] = auxiliar[32];
holdingRegs[33] = auxiliar[33];
holdingRegs[34] = auxiliar[34];
holdingRegs[35] = auxiliar[35];
holdingRegs[36] = auxiliar[36];
holdingRegs[37] = auxiliar[37];
holdingRegs[38] = auxiliar[38];
holdingRegs[39] = auxiliar[39];
holdingRegs[40] = auxiliar[40];
holdingRegs[41] = auxiliar[41];
holdingRegs[42] = auxiliar[42];
holdingRegs[43] = auxiliar[43];
holdingRegs[44] = auxiliar[44];
holdingRegs[45] = auxiliar[45];
holdingRegs[46] = auxiliar[46];
holdingRegs[47] = auxiliar[47];
holdingRegs[48] = auxiliar[48];
holdingRegs[49] = auxiliar[49];
holdingRegs[50] = auxiliar[50];
holdingRegs[51] = auxiliar[51];
holdingRegs[52] = auxiliar[52];
holdingRegs[53] = auxiliar[53];
holdingRegs[54] = auxiliar[54];
holdingRegs[55] = auxiliar[55];
holdingRegs[56] = auxiliar[56];
holdingRegs[57] = auxiliar[57];
holdingRegs[58] = auxiliar[58];
holdingRegs[59] = auxiliar[59];
holdingRegs[60] = auxiliar[60];
holdingRegs[61] = auxiliar[61];
holdingRegs[62] = auxiliar[62];

/*for(int i=0;i<30;i++)
{
Serial.println(holdingRegs[i]);

}
Serial.println("------");*/
}}}

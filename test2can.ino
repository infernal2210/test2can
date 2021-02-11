#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned int temp = 0x0;
unsigned char len = 0;
unsigned char rxBuf[8];
unsigned char stmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // шаблон сообщения

MCP_CAN CAN1(5);                               // Устанавливаем CS для приёма с 1 шины на пин 8
MCP_CAN CAN2(9);                                // Устанавливаем CS для отправки на 2 шину на пин 10

void setup()
{
  Serial.begin(115200);
  CAN1.begin(CAN_500KBPS, MCP_8MHz);            // init can bus : baudrate = 500k / 8MHz
  CAN2.begin(CAN_500KBPS, MCP_8MHz);            // init can bus : baudrate = 500k / 8MHz 
  pinMode(2, INPUT);                            // Пин 2 для INT input
  Serial.println("Started...");
}

void loop()
{

    CAN1.readMsgBuf(&len, rxBuf);             // Чтение данных: len = data length, buf = data byte(s)
    rxId = CAN1.getCanId();                   // Get message ID
    if(rxId == 0x555){
      Serial.print("TEMP: ");
      Serial.println(temp, HEX);
      // Отправляем сообщение сброса значения температуры на экране
      if(temp!=rxBuf[0]){
        stmp[2]=0xFF;
      }}
      CAN2.sendMsgBuf(0x558, 0, 8, stmp);
      // Немного ждём
      delay(10);
      // Отправляем сообщение выставляющее новую температуру
      temp=rxBuf[0];
      stmp[2]=temp;
      CAN2.sendMsgBuf(0x558, 0, 8, stmp);
    
  
}

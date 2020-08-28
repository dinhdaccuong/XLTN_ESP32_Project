
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "config.h"
#include "motor_control.h"
#include "led_control.h"
#include "buzzer_control.h"
#include "lcd_control.h"

buzzer_t buzzer_connected = { 3, 500, 500 };
bool isConnected = false;
BLECharacteristic* pCharacteristic;
void executeCommnand(byte* pData);
void responseCommand(byte* pData);
void turnOnLed();
void turnOffLed();
void motorRight();
void motorLeft();
void motorStop();

class DescriptorCallback_Charact1 : public BLEDescriptorCallbacks
{
    void onRead(BLEDescriptor* pDescriptor)
    {
        Serial.println("Descriptor_OnRead: ");
        //Serial.println((char*)pDescriptor->getValue());
    }
    void onWrite(BLEDescriptor* pDescriptor)
    {
        Serial.println("Descriptor_OnWrite: ");
        //Serial.println((char*)pDescriptor->getValue());
    }
};

class CharacteristicCallback1 : public BLECharacteristicCallbacks
{
    virtual void onRead(BLECharacteristic* pCharacteristic)
    {
        Serial.print("Characteristic_OnRead: ");
        Serial.println((char*)pCharacteristic->getData());
    }

    virtual void onWrite(BLECharacteristic* pCharacteristic)
    {
        Serial.print("Characteristic_OnWrite: ");
        Serial.println((char*)pCharacteristic->getData());
        executeCommnand((byte*)pCharacteristic->getData());
    }

    virtual void onNotify(BLECharacteristic* pCharacteristic)
    {
       // Serial.println("Characteristic_OnNotify");
    }

    virtual void onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code)
    {

    }
};

class ServerCallback : public BLEServerCallbacks
{
    void onConnect(BLEServer* pServer)
    {
        Serial.println("Connected");
        isConnected = true;
    }

    void onDisconnect(BLEServer* pServer)
    {
        Serial.println("Disonnected");
        isConnected = false;
    }
};


void setup() {
    Serial.begin(115200);

    led_init();
    //buzzer_init();
    //buzzer_start(&buzzer_connected);
    lcd_init();
    lcd_set_cursor(4, 1);
    lcd_write_char('c');
    //motor_init();
    //motor_turnLeft(127);
    //BLEDevice::init("BLE_Exchange_Data");

    //BLE2902* pDescriptor = new BLE2902();

    //pDescriptor->setValue("Hello");
    //pDescriptor->setCallbacks(new DescriptorCallback_Charact1());

    //pCharacteristic = new BLECharacteristic(CHARACTERISTIC_UUID,
    //    BLECharacteristic::PROPERTY_READ |
    //    BLECharacteristic::PROPERTY_WRITE |
    //    BLECharacteristic::PROPERTY_NOTIFY);

    //pCharacteristic->setValue("Phan Thu Hang");
    //pCharacteristic->addDescriptor(pDescriptor);
    //pCharacteristic->setCallbacks(new CharacteristicCallback1());

    //BLEServer* pServer = BLEDevice::createServer();
    //pServer->setCallbacks(new ServerCallback());
    //BLEService* pService = pServer->createService(SERVICE_UUID);
    //pService->addCharacteristic(pCharacteristic);
    //pService->start();

    //BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    //pAdvertising->addServiceUUID(SERVICE_UUID);
    //pAdvertising->setScanResponse(true);
    //pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    //pAdvertising->setMinPreferred(0x12);
    //BLEDevice::startAdvertising();
    //Serial.println("Characteristic defined! Now you can read it in your phone!");s
}

uint8_t value = 32;
void loop() {
    //if (isConnected)
    //{
    //    pCharacteristic->setValue((char*)&value);
    //    pCharacteristic->notify();
    //    value++;
    //    if (value > 255) value = 32;
    //}
    //delay(500);
}

void turnOnLed()
{
    Serial.println("Led turned on");
}

void turnOffLed()
{
    Serial.println("Led turned off");
}

void motorRight()
{
    Serial.println("Motor right");
}

void motorLeft()
{
    Serial.println("Motor left");
}

void motorStop()
{
    Serial.println("Motor stop");
}

void responseCommand(byte* pData)
{
    if (pData == NULL)
        return;
    byte data0 = pData[0];

    byte dataToWrite[1];
    switch (data0)
    {
    case COMMAND_TURN_ON_LED:
        dataToWrite[0] = RES_TURNED_ON_LED;
        break;
    case COMMAND_TURN_OFF_LED:
        dataToWrite[0] = RES_TURNED_OFF_LED;      
        break;
    case COMMAND_GO_MOTOR:
        dataToWrite[0] = RES_GO_MOTOR;
        break;
    case COMMAND_LEFT_MOTOR:
        dataToWrite[0] = RES_LEFT_MOTOR;
        break;
    case COMMAND_RIGHT_MOTOR:
        dataToWrite[0] = RES_RIGHT_MOTOR;
        break;
    case COMMAND_STOP_MOTOR:
        dataToWrite[0] = RES_STOP_MOTOR;
    default:
        break;
    }
    pCharacteristic->setValue(dataToWrite, 1);
    pCharacteristic->notify();
}
void executeCommnand(byte* pData)
{
    if (pData == NULL)
        return;
    byte data0 = pData[0];
   
    switch (data0)
    {
        case COMMAND_TURN_ON_LED:
            turnOnLed();
            break;
        case COMMAND_TURN_OFF_LED:
            turnOffLed();
            break;
        case COMMAND_GO_MOTOR:
            motorLeft();
            break;
        case COMMAND_LEFT_MOTOR:
            motorLeft();
            break;
        case COMMAND_RIGHT_MOTOR:
            motorRight();
            break;
        case COMMAND_STOP_MOTOR:
            motorStop();
        default:
            break;
    }
    responseCommand(pData);
}






/*******************************************************************************
**                                INCLUDES
*******************************************************************************/
#include "my_ble.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "buzzer_control.h"
#include "led_control.h"
#include "lcd_control.h"
#include "motor_control.h"
#include "sound.h"
#include "string_define.h"
/*******************************************************************************
**                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
// clang-format off

// clang-format on
/*******************************************************************************
**                      COMMON VARIABLE DEFINITIONS
*******************************************************************************/

/*******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
BLECharacteristic* pCharacteristic;
char arr_delete[] = { 32, 32 ,32, 32, 32, 32, 32, 32, 32, 32, 32, 32 }; // ' '
/*******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
void responseCommand(byte* pData);
void executeCommand(byte* pData);

class DescriptorCallback_Charact1 : public BLEDescriptorCallbacks
{
    void onRead(BLEDescriptor* pDescriptor)
    {
#if BLE_DEBUG
        Serial.print("Descriptor_OnRead: ");
        Serial.println((char*)pDescriptor->getValue());
#endif
    }
    void onWrite(BLEDescriptor* pDescriptor)
    {
#if BLE_DEBUG
        Serial.print("Descriptor_OnWrite: ");
        Serial.println((char*)pDescriptor->getValue());
#endif
    }
};

class CharacteristicCallback1 : public BLECharacteristicCallbacks
{
    virtual void onRead(BLECharacteristic* pCharacteristic)
    {
#if BLE_DEBUG
        Serial.print("Characteristic_OnRead: ");
        Serial.println((char*)pCharacteristic->getData());
        Serial.println((char*)pCharacteristic->getData());
#endif
    }

    virtual void onWrite(BLECharacteristic* pCharacteristic)
    {
#if BLE_DEBUG
        Serial.print("Characteristic_OnWrite: ");
        Serial.println((char*)pCharacteristic->getData());
#endif
        executeCommand((byte*)pCharacteristic->getData());
    }

    virtual void onNotify(BLECharacteristic* pCharacteristic)
    {
#if BLE_DEBUG
        Serial.println("Characteristic_OnNotify");
#endif
    }

    virtual void onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code)
    {

    }
};

class ServerCallback : public BLEServerCallbacks
{
    void onConnect(BLEServer* pServer)
    {
        buzzer_start(&sound_connected);
        lcd_set_cursor(X_LINE_STATUS, Y_LINE_STATUS);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_STATUS, Y_LINE_STATUS);
        lcd_write_string("Connected");
#if BLE_DEBUG
        Serial.println("Connected");
#endif           
    }

    void onDisconnect(BLEServer* pServer)
    {
        buzzer_start(&sound_disconnected);
        lcd_set_cursor(X_LINE_STATUS, Y_LINE_STATUS);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_STATUS, Y_LINE_STATUS);
        lcd_write_string("Disconnected");
#if BLE_DEBUG
        Serial.println("Disonnected");
#endif
    }
};
/*******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
void my_ble_init()
{
	BLEDevice::init("Nhom 22 - IoT");

	BLE2902* pDescriptor = new BLE2902();
    pDescriptor->setCallbacks(new DescriptorCallback_Charact1());
    pDescriptor->setValue("Hello");

    pCharacteristic = new BLECharacteristic(CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic->setValue("Phan Hangggggg");
    pCharacteristic->addDescriptor(pDescriptor);
    pCharacteristic->setCallbacks(new CharacteristicCallback1());

    BLEServer* pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallback());

    BLEService* pService = pServer->createService(SERVICE_UUID);
    pService->addCharacteristic(pCharacteristic);
    pService->start();

    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
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

void executeCommand(byte* pData)
{
    if (pData == NULL)
        return;
    byte data0 = pData[0];

    switch (data0)
    {
    case COMMAND_TURN_ON_LED:
        led_control(COMMAND_TURN_ON_LED);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("On");
        break;
    case COMMAND_TURN_OFF_LED:
        led_control(COMMAND_TURN_OFF_LED);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("Off");
        break;
    case COMMAND_GO_MOTOR:
        motor_control(COMMAND_GO_MOTOR);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("Go");
        break;
    case COMMAND_LEFT_MOTOR:
        motor_control(COMMAND_LEFT_MOTOR);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("Left");
        break;
    case COMMAND_RIGHT_MOTOR:
        motor_control(COMMAND_RIGHT_MOTOR);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("Right");
        break;
    case COMMAND_STOP_MOTOR:
        motor_control(COMMAND_STOP_MOTOR);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string(arr_delete);
        lcd_set_cursor(X_LINE_COMMAND, Y_LINE_COMMAND);
        lcd_write_string("Stop");
    default:
        break;
    }
    responseCommand(pData);
}

/******************************** End of file *********************************/

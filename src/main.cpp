#include <Arduino.h>
#include <M5Unified.h>
#include <stdbool.h>

#include "../lib/SesameController/SesameController.h"
#include "secrets.h"

SesameController sesameController(SESAME_MAC_ADDRESS, SESAME_PUBLIC_KEY,
                                  SESAME_SECRET_KEY, models::sesame_5);

void setup() {
    // M5Unifiedの初期化
    M5.begin();
    // シリアルモニターを初期化
    Serial.begin(115200);
    delay(1000);

    M5.Lcd.println("M5SesameUDPModule");

    // BLEDeviceの初期化
    BLEDevice::init("M5SesameUDPModule");

    Serial.println("Setup complete.");
}

void loop() {
    /*
     * M5.BtnAが押されたら、セサミをアンロックします。
     * M5.BtnBが押されたら、セサミをロックします。
     */

    // M5Unifiedの状態を更新する
    M5.update();

    // 接続・再接続
    if (!sesameController.is_active()) {
        Serial.println("Connecting to Sesame...");
        if (sesameController.connect()) {
            Serial.println("Connected to Sesame.");
            delay(1000);
        } else {
            Serial.println(
                "Failed to connect to Sesame. Retrying in 5 seconds...");
            delay(5000);
        }
    }

    // ボタンの状態をチェックして、対応するアクションを実行する
    if (M5.BtnA.wasPressed()) {
        Serial.println("Locking...");
        sesameController.lock();
    } else if (M5.BtnB.wasPressed()) {
        Serial.println("Unlocking...");
        sesameController.unlock();
    }
}
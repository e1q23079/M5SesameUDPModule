#include <Arduino.h>
#include <M5Unified.h>

#include "../lib/SesameController/SesameController.h"
#include "secrets.h"

SesameController sesameController(SESAME_MAC_ADDRESS, SESAME_PUBLIC_KEY,
                                  SESAME_SECRET_KEY, models::sesame_5);

int colorStatus = WHITE;

void setup() {
    // M5Unifiedの初期化
    M5.begin();
    // シリアルモニターを初期化
    Serial.begin(115200);
    delay(1000);

    // 初期状態を表示
    colorStatus = WHITE;
    M5.Display.fillScreen(colorStatus);

    // BLEDeviceの初期化
    BLEDevice::init("M5SesameUDPModule");

    // 準備完了
    colorStatus = BLUE;
    M5.Display.fillScreen(colorStatus);
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
        colorStatus = BLUE;
        M5.Display.fillScreen(colorStatus);
        Serial.println("Connecting to Sesame...");
        if (sesameController.connect()) {
            colorStatus = CYAN;
            M5.Display.fillScreen(colorStatus);
            Serial.println("Connected to Sesame.");
            delay(1000);
        } else {
            colorStatus = YELLOW;
            M5.Display.fillScreen(colorStatus);
            Serial.println(
                "Failed to connect to Sesame. Retrying in 5 seconds...");
            delay(5000);
        }
    }

    // ボタンの状態をチェックして、対応するアクションを実行する
    if (M5.BtnA.wasPressed()) {
        Serial.println("Locking...");
        M5.Display.fillScreen(RED);
        sesameController.lock();
        delay(1000);
    } else if (M5.BtnB.wasPressed()) {
        Serial.println("Unlocking...");
        M5.Display.fillScreen(GREEN);
        sesameController.unlock();
        delay(1000);
    }

    // 状態を表示
    M5.Display.fillScreen(colorStatus);
}
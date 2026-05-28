#include <Arduino.h>
#include <M5Unified.h>

#include "../lib/SesameController/SesameController.h"
#include "../lib/UdpManager/UdpManager.h"
#include "secrets.h"
#include "setting.h"

UdpManager udpManager(SSID, PASSWORD, IP_ADDRESS, PORT, GATEWAY_IP,
                      SUBNET_MASK);

SesameController sesameController(SESAME_MAC_ADDRESS, SESAME_PUBLIC_KEY,
                                  SESAME_SECRET_KEY, models::sesame_5);

int colorStatus = WHITE;

/*
 * セサミをロックする
 */
void sesameLock() {
    Serial.println("Locking...");
    M5.Display.fillScreen(RED);
    sesameController.lock();
    delay(1000);
}

/**
 * セサミをアンロックする
 */
void sesameUnlock() {
    Serial.println("Unlocking...");
    M5.Display.fillScreen(GREEN);
    sesameController.unlock();
    delay(1000);
}

/*
 * 初期化処理
 */
void setup() {
    // M5Unifiedの初期化
    M5.begin();
    // シリアルモニターを初期化
    Serial.begin(115200);
    delay(1000);

    // 初期状態を表示
    colorStatus = WHITE;
    M5.Display.fillScreen(colorStatus);

    // Wi-Fi接続とUDPの開始（待機状態）
    Serial.println("Wi-Fi connecting and starting UDP...");
    if (!udpManager.begin()) {
        colorStatus = ORANGE;
        M5.Display.fillScreen(colorStatus);
        Serial.println(
            "Failed to connect to Wi-Fi. Check your credentials and network "
            "settings.");
        while (true) {
            // 無限ループで停止
        }
    }
    Serial.println("Wi-Fi connected and UDP started.");

    // BLEDeviceの初期化
    BLEDevice::init("M5SesameUDPModule");

    // 準備完了
    colorStatus = BLUE;
    M5.Display.fillScreen(colorStatus);
    Serial.println("Setup complete.");
}

/*
 * メインループ
 */
void loop() {
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
        sesameLock();
    } else if (M5.BtnB.wasPressed()) {
        sesameUnlock();
    }

    // UDPでコマンドを受信する
    String command = udpManager.read();
    if (command == "lock") {
        sesameLock();
    } else if (command == "unlock") {
        sesameUnlock();
    }

    // 状態を表示
    M5.Display.fillScreen(colorStatus);
}
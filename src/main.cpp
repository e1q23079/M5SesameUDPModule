#include <Arduino.h>
#include <M5Unified.h>

#include "../lib/DisplayController/DisplayController.h"
#include "../lib/SesameController/SesameController.h"
#include "../lib/UdpManager/UdpManager.h"
#include "secret/secrets.h"
#include "setting/setting.h"

DisplayController displayController;

UdpManager udpManager(SSID, PASSWORD, IP_ADDRESS, PORT, GATEWAY_IP,
                      SUBNET_MASK);

SesameController sesameController(SESAME_MAC_ADDRESS, SESAME_PUBLIC_KEY,
                                  SESAME_SECRET_KEY, models::sesame_5);

/*
 * セサミをロックする
 */
void sesameLock() {
    Serial.println("Locking...");
    displayController.showLockStatus(true);
    sesameController.lock();
}

/**
 * セサミをアンロックする
 */
void sesameUnlock() {
    Serial.println("Unlocking...");
    displayController.showLockStatus(false);
    sesameController.unlock();
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
    Serial.println("Initializing...");
    displayController.showStatus(DisplayController::Status::Init);

    // Wi-Fi接続とUDPの開始（待機状態）
    Serial.println("Wi-Fi connecting and starting UDP...");
    displayController.showStatus(DisplayController::Status::WifiConnecting);
    if (!udpManager.begin()) {
        Serial.println(
            "Failed to connect to Wi-Fi. Check your credentials and network "
            "settings.");
        displayController.showStatus(DisplayController::Status::WifiFailed);
        while (true) {
            // 無限ループで停止
        }
    }
    Serial.println("Wi-Fi connected and UDP started.");
    displayController.showStatus(DisplayController::Status::WifiConnected);

    // BLEDeviceの初期化
    BLEDevice::init("M5SesameUDPModule");

    // 準備完了
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
        Serial.println("Connecting to Sesame...");
        displayController.showStatus(
            DisplayController::Status::SesameConnecting);
        if (sesameController.connect()) {
            Serial.println("Connected to Sesame.");
            displayController.showStatus(
                DisplayController::Status::SesameConnected);
            delay(1000);
        } else {
            Serial.println(
                "Failed to connect to Sesame. Retrying in 5 seconds...");
            displayController.showStatus(
                DisplayController::Status::SesameFailed);
            delay(5000);
        }
    }

    // ボタンの状態をチェックして、対応するアクションを実行する
    if (M5.BtnA.wasPressed()) {
        sesameLock();
    } else if (M5.BtnB.wasPressed()) {
        sesameUnlock();
    }

    // UDPでコマンドを受信して、対応するアクションを実行する
    String command = udpManager.read();
    if (command == "lock") {
        sesameLock();
    } else if (command == "unlock") {
        sesameUnlock();
    }
}
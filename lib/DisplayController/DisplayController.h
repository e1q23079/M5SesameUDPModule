#pragma once

#include <Arduino.h>
#include <M5Unified.h>

/*
 * @brief
 * DisplayControllerクラスは、M5Unifiedのディスプレイを制御
 */
class DisplayController {
   public:
    /*
     * @brief ステータスを表す列挙型
     */
    enum class Status {
        Init,
        WifiConnecting,
        WifiConnected,
        WifiFailed,
        SesameConnecting,
        SesameConnected,
        SesameFailed,
    };
    DisplayController();
    /*
     * @brief ステータスに応じた画面表示を行う
     * @param status 表示するステータス
     */
    void showStatus(Status status);
    /*
     * @brief セサミのロック状態を表示する
     * @param isLocked
     * セサミがロックされている場合はtrue、アンロックされている場合はfalse
     */
    void showLockStatus(bool isLocked);

   private:
    Status currentStatus = Status::Init;
    /*
     * @brief ステータスに応じた色を取得する
     * @param status 取得するステータス
     * @return ステータスに対応する色
     */
    uint16_t getStatusColor(Status status);
    /*
     * @brief 現在のステータスを取得する
     * @return 現在のステータス
     */
    Status getCurrentStatus();
};
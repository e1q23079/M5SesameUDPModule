#include <WiFi.h>
#include <WiFiUdp.h>

/*
 * @brief UdpManagerクラス
 * UdpManagerクラスは、WiFi接続とUDP通信を管理するためのクラスです。
 */
class UdpManager {
   public:
    /*
     * @brief コンストラクタ
     * @param ssid WiFiのSSID
     * @param password WiFiのパスワード
     * @param ip_address デバイス本体のIPアドレス
     * @param port 送信先のポート番号
     * @param gateway_ip ゲートウェイのIPアドレス
     * @param subnet_mask サブネットマスク
     */
    UdpManager(const char* ssid, const char* password, const char* ip_address,
               uint16_t port, const char* gateway_ip, const char* subnet_mask);
    /*
     * @brief 初期化処理
     * WiFiへの接続とUDPの開始を行う
     * @return 初期化に成功した場合はtrue、失敗した場合はfalse
     */
    bool begin();
    /*
     * @brief UDPでデータを受信する
     * @return 受信したデータをString型で返す。受信がない場合は空のStringを返す
     */
    String read();

   private:
    const char* ssid;
    const char* password;
    const char* ip_address;
    uint16_t port;
    const char* gateway_ip;
    const char* subnet_mask;
};
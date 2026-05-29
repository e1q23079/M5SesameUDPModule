
# UdpManager

UdpManagerはESP系デバイス（M5系など）でWiFi接続とUDP受信を簡潔に扱うための軽量ラッパークラスです。WiFiの固定IP設定を行い、指定ポートでUDPパケットを受信して文字列として返します。

## 概要

- WiFiの固定IP（`WiFi.config()`）を設定して接続します。
- 指定したポートで`WiFiUDP`を開始し、UDPパケットを受信します。
- 受信データは内部バッファ（256バイト）で読み取り、末尾の不要な空白を`trim()`で削除して`String`で返します。

## コンストラクタ

```cpp
UdpManager(const char* ssid,
      const char* password,
      const char* ip_address,
      uint16_t port,
      const char* gateway_ip,
      const char* subnet_mask);
```

- `ssid` - WiFiのSSID
- `password` - WiFiのパスワード
- `ip_address` - デバイスに割り当てる固定IP（例: "192.168.1.50"）
- `port` - 受信するUDPポート番号
- `gateway_ip` - ゲートウェイのIPアドレス（例: "192.168.1.1"）
- `subnet_mask` - サブネットマスク（例: "255.255.255.0"）

## メソッド

- `bool begin()`
  - WiFiの固定IP設定と接続、UDPの開始を行います。
  - `WiFi.config()`が失敗した場合は`false`を返します。
  - WiFi接続が確立するまでブロッキングで待機します（内部で`delay(500)`ループ）。
  - 成功したら`true`を返します。

- `String read()`
  - 利用可能なUDPパケットがあれば読み取り、内容を`String`で返します。
  - パケットがない、または読み取りに失敗した場合は空の`String`を返します。
  - 内部バッファは256バイトに制限されます。より大きなパケットを扱う必要がある場合は実装を拡張してください。

## 使用例

```cpp
#include "UdpManager.h"

const char* ssid = "your_ssid";
const char* password = "your_password";
const char* ip = "192.168.1.50";
const char* gateway = "192.168.1.1";
const char* subnet = "255.255.255.0";
uint16_t port = 12345;

UdpManager udp(ssid, password, ip, port, gateway, subnet);

void setup() {
 Serial.begin(115200);
 if (!udp.begin()) {
  Serial.println("UDP manager init failed");
  while (1) delay(1000);
 }
 Serial.println("UDP manager ready");
}

void loop() {
 String msg = udp.read();
 if (msg.length() > 0) {
  Serial.printf("recv: %s\n", msg.c_str());
  // メッセージ処理
 }
 delay(10);
}
```

## 注意事項

- `ip_address`/`gateway_ip`/`subnet_mask`はIPv4形式の文字列で渡してください。
- `begin()`はWiFi接続をブロッキングで待つため、起動時間が長くなることがあります。必要に応じてタイムアウト処理を追加してください。
- 受信バッファサイズは現状256バイトです。大きなペイロードを扱う場合は`UdpManager.cpp`のバッファサイズと読み取りロジックを調整してください。
- 本ライブラリは`WiFi.h`および`WiFiUdp.h`に依存します。プラットフォーム（ESP32など）に合わせた環境でビルドしてください。

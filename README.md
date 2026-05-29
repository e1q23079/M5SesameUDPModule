# M5SesameUDPModule

M5Unified を使った M5 系デバイスから、Sesame を BLE 経由でロック / アンロックするためのプロジェクトです。

## 概要

- 物理ボタン `BtnA` でロック、 `BtnB` でアンロック
- UDP コマンド（`lock` / `unlock`）で遠隔操作可能
- Sesame の機種はサンプルで `models::sesame_5` を使用（必要に応じて変更してください）

## 必要なもの

- M5 系デバイス（M5Unified 対応ボード）
- PlatformIO（ビルド・書き込み）
- Sesame の公開鍵／秘密鍵と MAC アドレス
- 同一ネットワーク上の PC（UDP 送信元）

## 接続準備

### Sesame の公開鍵・秘密鍵の取得

Sesame の公開鍵・秘密鍵は以下の QR リーダーで取得します。

<https://sesame-qr-reader.vercel.app/>

MAC アドレスは、BLE スキャンアプリ（nRF Connect）で Sesame を検索して取得します。

- Android：<https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=ja>
- iPhone：<https://apps.apple.com/jp/app/nrf-connect-for-mobile/id1054362403>

#### 取得手順

1. Sesame をスマートフォンの近くに置く
2. アプリで BLE スキャンを開始
3. フィルターで RSSI を -67 dBm に設定（近接するデバイスを特定しやすくするため）
4. Company が `CANDY HOUSE, Inc.` のデバイスを探す
5. 見つかった Sesame の詳細画面から MAC アドレスを確認

### ネットワーク情報の確認

デバイスや PC で使用する サブネット マスク、デフォルト ゲートウェイは、Windows では `ipconfig`、Linux では `ifconfig` / `ip addr` などで確認してください（`IPv4` 欄を参照）。

## 設定

`main.cpp` に Sesame の機種を設定してください。

Sesame の機種は、`models::sesame_3` / `models::sesame_4` / `models::sesame_5` / `models::sesame_5_pro` / `models::sesame_6` / `models::sesame_6_pro` から適切なものに変更してください。

```c++
SesameController sesameController(
    SESAME_MAC_ADDRESS,
    SESAME_PUBLIC_KEY,
    SESAME_SECRET_KEY,
    models::sesame_5);
```

`src\secret\secrets.h` に Sesame の MAC アドレス、公開鍵、シークレットキーを設定してください。

```c++
// src\secret\secrets.h の例
#define SESAME_MAC_ADDRESS "xx:xx:xx:xx:xx:xx"
#define SESAME_PUBLIC_KEY "xxxxxxxxxxxxxxxx"
#define SESAME_SECRET_KEY "xxxxxxxxxxxxxxxx"
```

`src\setting\setting.h` にネットワーク情報を設定してください。

```c++
// src\setting\setting.h の例
#define IP_ADDRESS "192.168.1.50"  // デバイスの固定IP（必要に応じて変更）
#define PORT 12345

#define SSID "your-ssid"
#define PASSWORD "your-password"

#define GATEWAY_IP "192.168.1.1"
#define SUBNET_MASK "255.255.255.0"
```

注: `IP_ADDRESS` を固定IPにする場合、ネットワークの IP 決定方法に注意してください（DHCP と競合しないように設定）。

## ビルドと書き込み

PlatformIO 環境でビルドし、ボードへ書き込みます。

```bash
pio run
pio run --target upload
```

## 使い方

### ボタン操作

ボタン操作はローカルでの手動操作用です。押下すると即座に対応する操作を行い、画面表示とシリアルに状態が出力されます。

- `BtnA` 押下：ロック
- `BtnB` 押下：アンロック

### UDPコマンド操作

ロック／アンロックコマンドは UDP で受信します。送信先 IP / ポートは `src/setting.h` の設定に合わせてください。

#### Linux の例（`nc` を使用）

```bash
nc -u <IPアドレス> <ポート番号>
```

接続後に標準入力へ直接コマンドを入力して Enter で送信します。

```bash
lock
# または
unlock
```

### ディスプレイ表示

M5 の画面を使って状態を色で表示します。

- 白 ： 起動直後
- 紫 ： Wi‑Fi 接続待ち
- 青 ： Wi-Fi接続完了・ Sesame 接続待ち
- オレンジ ： Wi-Fi 接続失敗（ネットワーク接続エラー）
- シアン ： Sesame に接続済み
- 黄 ： 接続失敗（再試行中）
- 赤 ： ロック操作中
- 緑 ： アンロック操作中

### シリアルモニター表示

シリアルモニターでデバイスの起動ログや状態確認ができます。

- **ボーレート**: `115200` に設定してください
- **PlatformIO (VS Code)**: コマンドパレットで `PlatformIO: Monitor` を実行するか、ターミナルで次を使います

    ```bash
    pio device monitor -b 115200
    ```

- **Arduino IDE**: ツール > シリアルモニター を開き、右下のボーレートを `115200` に設定します。

#### ログの例

```bash
Initializing...
Wi-Fi connecting and starting UDP...
Wi-Fi connected and UDP started.
Setup complete.
Connecting to Sesame...
Connected to Sesame.
```

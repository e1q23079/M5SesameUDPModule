# M5SesameUDPModule

M5Unified を使った M5 系デバイスから、Sesame を BLE 経由でロック / アンロックするためのプロジェクトです。

## 概要

- `BtnA` でロック
- `BtnB` でアンロック
- 接続が切れている場合は、`loop()` 内で再接続を試みます
- Sesame のモデルは現在 `sesame_5` を使っています

## 接続準備

Sesame の公開鍵・秘密鍵は、以下の QR リーダーで取得します。

<https://sesame-qr-reader.vercel.app/>

## 設定方法

`src/secrets.h` に、次の定義を用意してください。

```c++
#define SESAME_MAC_ADDRESS "xx:xx:xx:xx:xx:xx"
#define SESAME_PUBLIC_KEY "xxxxxxxxxxxxxxxx"
#define SESAME_SECRET_KEY "xxxxxxxxxxxxxxxx"
```

`main.cpp` では、次のようにコントローラを初期化しています。

```c++
SesameController sesameController(
    SESAME_MAC_ADDRESS,
    SESAME_PUBLIC_KEY,
    SESAME_SECRET_KEY,
    models::sesame_5);
```

Sesame の機種が違う場合は、`models::sesame_3` / `models::sesame_4` / `models::sesame_5` / `models::sesame_5_pro` / `models::sesame_6` / `models::sesame_6_pro` から適切なものに変更してください。

## 動作

起動時に M5Unified と BLE を初期化し、シリアルモニタに `Setup complete.` を出力します。`loop()` では Sesame のセッション状態を確認し、未接続なら接続を試みます。

接続後は、以下の操作ができます。

- `BtnA` 押下: ロック
- `BtnB` 押下: アンロック

## ビルドと書き込み

PlatformIO 環境でビルドし、ボードへ書き込みます。

```bash
pio run
pio run --target upload
```

## 実装メモ

- `SesameController` は `lib/SesameController/` にあります
- Sesame への操作は `SesameController` がまとめて担当します
- ロック / アンロック前にセッションが有効かどうかを確認します

## 表示フィードバック

本プロジェクトは M5 の画面を使って状態を色で表示します。色の意味は以下の通りです。

- 白 (`WHITE`): 初期状態
- 青 (`BLUE`): 初期化完了または接続待ち
- シアン (`CYAN`): Sesame に接続済み
- 黄 (`YELLOW`): 接続失敗（再試行中）
- 赤 (`RED`): ロック操作中（`BtnA` 押下）
- 緑 (`GREEN`): アンロック操作中（`BtnB` 押下）

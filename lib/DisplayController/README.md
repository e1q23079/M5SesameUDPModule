# DisplayController

`DisplayController` は `M5Unified` のディスプレイを簡単に扱うためのヘルパークラスです。
本プロジェクトではデバイスの状態（Wi‑Fi・Sesame 接続など）を色で表示し、ロック／アンロック操作時に短く色を点灯して状態を示します。

## 目的

- 起動・接続状態を視覚的に分かりやすく表示する
- セサミのロック／アンロック操作を色でフィードバックする

## 依存

- `M5Unified` ライブラリ（プロジェクトで既に使用）

## 公開 API

- `DisplayController()`
  - コンストラクタ。インスタンス生成時に初期表示（白）を行います。
- `void showStatus(DisplayController::Status status)`
  - 指定したステータスに応じた色で画面を塗りつぶします。
- `void showLockStatus(bool isLocked)`
  - ロック時は赤 (`true`)、アンロック時は緑 (`false`) を 1 秒間表示し、その後直前のステータス色に戻します。

## `Status` 列挙値と対応色

- `Status::Init` — 白（起動直後）
- `Status::WifiConnecting` — 紫（Wi‑Fi 接続待ち）
- `Status::WifiConnected` — 青（Wi‑Fi 接続済み）
- `Status::WifiFailed` — オレンジ（Wi‑Fi 接続失敗）
- `Status::SesameConnecting` — 青（Sesame 接続待ち）
- `Status::SesameConnected` — シアン（Sesame 接続済み）
- `Status::SesameFailed` — 黄（Sesame 接続失敗／再試行中）

（色名は `DisplayController.cpp` 内の定義に従います）

## 使用例

ヘッダをインクルードしてインスタンスを作成します（グローバルに置くのが簡単です）：

```cpp
#include "DisplayController.h"

DisplayController displayController;

// ステータス表示
displayController.showStatus(DisplayController::Status::WifiConnecting);

// ロック表示（1秒間赤が表示され、元の色に戻る）
displayController.showLockStatus(true);
```

## 補足・注意

- `showLockStatus()` は内部で `delay(1000)` を使用しているため、その間はメインループの他処理が一時停止します。必要に応じて非同期表示に改修してください。

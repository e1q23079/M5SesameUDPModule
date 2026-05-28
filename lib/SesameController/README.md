
# SesameController

`SesameController` は、libsesame3bt を利用して Sesame（スマートロック）を BLE 経由で操作するためのラッパークラスです。

## 概要

- BLE アドレス・公開鍵・秘密鍵・モデルを与えて初期化します。
- セッションの有効性確認、接続、ロック／アンロックの基本操作を提供します。

## ヘッダ位置

実装ファイル:

- [lib/SesameController/SesameController.h](lib/SesameController/SesameController/SesameController.h) (インクルードパスに合わせて参照してください)
- [lib/SesameController/SesameController.cpp](lib/SesameController/SesameController.cpp)

（備考: ワークスペース内では `lib/SesameController/` に置かれています）

## API

- コンストラクタ

 ```c++
 SesameController(const std::string& mac_address,
          const std::string& public_key,
          const std::string& secret_key,
          const libsesame3bt::Sesame::model_t model);
 ```

- `mac_address`: Sesame の MAC アドレス（コロン区切り）
- `public_key`: Sesame の公開鍵（hex 文字列）
- `secret_key`: Sesame の秘密鍵（hex 文字列）
- `model`: `libsesame3bt::Sesame::model_t`（プロジェクトでは `models::sesame_5` 等の定数を用意しています）

- `bool is_active()`

 セッションが有効（接続済み）かどうかを返します。

- `bool connect()`

 Sesame に接続を試みます。成功で `true`、失敗で `false` を返します。

- `bool unlock()` / `bool lock()`

 セッションが有効な場合にそれぞれアンロック／ロックを実行します。セッションが有効でない場合は即座に `false` を返します。

 戻り値は libsesame3bt の呼び出し結果に従います。

## 使用例

`src/main.cpp` にあるように、次のように使います。

```c++
#include "../lib/SesameController/SesameController.h"
#include "secrets.h" // SESAME_MAC_ADDRESS, SESAME_PUBLIC_KEY, SESAME_SECRET_KEY を定義

SesameController sesameController(
  SESAME_MAC_ADDRESS,
  SESAME_PUBLIC_KEY,
  SESAME_SECRET_KEY,
  models::sesame_5);

// ループ内で接続状態を確認し、ボタン操作で lock/unlock を呼ぶ
if (!sesameController.is_active()) {
  sesameController.connect();
}

// 例: ボタン押下で操作
sesameController.unlock();
sesameController.lock();
```

## モデル定義

ヘッダで以下のモデル定数が用意されています:

- `models::sesame_3`
- `models::sesame_4`
- `models::sesame_5`
- `models::sesame_5_pro`
- `models::sesame_6`
- `models::sesame_6_pro`

ターゲットデバイスに合わせてコンストラクタに渡してください。

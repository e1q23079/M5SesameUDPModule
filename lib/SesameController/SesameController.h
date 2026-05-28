#pragma once

#include <SesameClient.h>

#include <string>

#define TAG_NAME "SesameController"

namespace models {
constexpr auto sesame_3 = libsesame3bt::Sesame::model_t::sesame_3;
constexpr auto sesame_4 = libsesame3bt::Sesame::model_t::sesame_4;
constexpr auto sesame_5 = libsesame3bt::Sesame::model_t::sesame_5;
constexpr auto sesame_5_pro = libsesame3bt::Sesame::model_t::sesame_5_pro;
constexpr auto sesame_6 = libsesame3bt::Sesame::model_t::sesame_6;
constexpr auto sesame_6_pro = libsesame3bt::Sesame::model_t::sesame_6_pro;
}  // namespace models

/*
 * @brief
 * SesameControllerクラスは、セサミの基本的な操作を抽象化するためのクラスです。
 */
class SesameController {
   public:
    /*
     * @brief コンストラクタ
     * @param mac_address セサミのMACアドレス（コロン区切りの形式）
     * @param public_key セサミの公開鍵（16進数文字列）
     * @param secret_key セサミの秘密鍵（16進数文字列）
     * @param model セサミのモデルタイプ（Sesame::model_t）
     */
    SesameController(const std::string& mac_address,
                     const std::string& public_key,
                     const std::string& secret_key,
                     const libsesame3bt::Sesame::model_t model);
    /**
     * @brief セサミのセッションがアクティブかどうかを確認する
     * @return セッションがアクティブな場合はtrue、そうでない場合はfalse
     */
    bool is_active();
    /*
     * @brief セサミに接続する
     * @return 接続に成功した場合はtrue、失敗した場合はfalse
     */
    bool connect();
    /**
     * @brief セサミをアンロックする
     * @return アンロックに成功した場合はtrue、失敗した場合はfalse
     */
    bool unlock();
    /**
     * @brief セサミをロックする
     * @return ロックに成功した場合はtrue、失敗した場合はfalse
     */
    bool lock();
};
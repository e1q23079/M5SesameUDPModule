#include "SesameController.h"

using libsesame3bt::Sesame;
using libsesame3bt::SesameClient;

SesameClient sesame;

SesameController::SesameController(const std::string& mac_address,
                                   const std::string& public_key,
                                   const std::string& secret_key,
                                   const Sesame::model_t model) {
    sesame.begin(BLEAddress{mac_address, BLE_ADDR_RANDOM}, model);
    sesame.set_keys(public_key, secret_key);
}

bool SesameController::is_active() { return sesame.is_session_active(); }

bool SesameController::connect() { return sesame.connect(); }

bool SesameController::unlock() {
    if (!is_active()) {
        return false;
    }
    return sesame.unlock(TAG_NAME);
}

bool SesameController::lock() {
    if (!is_active()) {
        return false;
    }
    return sesame.lock(TAG_NAME);
}

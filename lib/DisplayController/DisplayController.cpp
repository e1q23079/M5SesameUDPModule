#include "DisplayController.h"

DisplayController::DisplayController() { showStatus(Status::Init); }

uint16_t DisplayController::getStatusColor(Status status) {
    switch (status) {
        case Status::Init:
            return WHITE;
        case Status::WifiConnecting:
            return VIOLET;
        case Status::WifiConnected:
            return BLUE;
        case Status::WifiFailed:
            return ORANGE;
        case Status::SesameConnecting:
            return BLUE;
        case Status::SesameConnected:
            return CYAN;
        case Status::SesameFailed:
            return YELLOW;
        default:
            return TFT_WHITE;
    }
}

DisplayController::Status DisplayController::getCurrentStatus() {
    return currentStatus;
}

void DisplayController::showStatus(Status status) {
    currentStatus = status;
    uint16_t color = getStatusColor(status);
    M5.Display.fillScreen(color);
}

void DisplayController::showLockStatus(bool isLocked) {
    uint16_t color = isLocked ? RED : GREEN;
    M5.Display.fillScreen(color);
    delay(1000);
    M5.Display.fillScreen(getStatusColor(currentStatus));
}
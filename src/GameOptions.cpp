#include "GameOptions.h"

GameOptions GameOptions::instance;

GameOptions& GameOptions::SetFullScene(bool value) {
    this->fullScene = value;
    // if (this->fullScene) Renderer::Get().SetFullScrene();
    // else {

    // }

    return *this;
}
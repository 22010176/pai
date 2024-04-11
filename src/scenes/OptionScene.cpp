// #include "OptionScene.h"

// OptionScene::OptionScene(Renderer& renderer) : Scene(renderer) {
//     TTF_Font* font = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 35);
//     TTF_Font* nfont = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 45);
//     TTF_Font* tfont = TTF_OpenFont("assets\\fonts\\Source Code Pro\\SourceCodePro-ExtraBold.ttf", 70);

//     SDL_Surface* backT = TTF_RenderText_Blended(font, "<", white);
//     SDL_Surface* optT = TTF_RenderText_Blended(tfont, "OPTIONS", white);
//     SDL_Surface* fullScene = TTF_RenderText_Blended(nfont, "Full-screen", white);

//     Entity& optionBg = *new Entity(renderer, GameOptions::Get().GetWidth(), GameOptions::Get().GetHeight());
//     optionBg
//         .AddTexture({ 0,0,WIDTH,GameOptions::Get().GetHeight() }, darkGrey)
//         .SetPos(0, 0);

//     Entity& optionsText = *new Entity(renderer, optT->w, optT->h);
//     optionsText
//         .AddTexture({ 0,0,optT->w,optT->h }, darkGrey)
//         .AddTexture(optT, { 0,0,optT->w,optT->h })
//         .SetPos(50, 50)
//         .SetAngle(-10);

//     // Entity& backBtn = CreateBtn(renderer, backT, 45, 45, white, darkGrey);
//     Entity& backBtn = *new Entity(renderer, 45, 45);
//     backBtn
//         .AddTexture(backT, { CalcPadding(45,backT->w),CalcPadding(45,backT->h),backT->w,backT->h })
//         .AddTexture(3, white)
//         .SetPos(10, 10);

//     AddSprite("_", optionBg);
//     AddSprite("optText", optionsText);
//     AddSprite("backBtn", backBtn);

//     SDL_FreeSurface(backT);
//     SDL_FreeSurface(optT);
//     SDL_FreeSurface(fullScene);

//     TTF_CloseFont(font);
//     TTF_CloseFont(nfont);
//     TTF_CloseFont(tfont);
// }

// OptionScene::~OptionScene() {

// }

// void OS_LoopFunc() {
//     OptionScene::Get().GetRenderer().Draw(&OptionScene::Get().GetEntity("_"));
//     OptionScene::Get().GetRenderer().Draw(&OptionScene::Get().GetEntity("optText"));
//     OptionScene::Get().GetRenderer().Draw(&OptionScene::Get().GetEntity("backBtn"));
// }
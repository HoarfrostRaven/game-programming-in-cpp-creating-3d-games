//
// Created by 叶子寻 on 08/07/2023.
//

#include "Game.h"

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
{}

bool Game::Initialize() {
    // 初始化 SDL 库
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("不能初始化 SDL: %s", SDL_GetError());
        return false;
    }

    // 创建 SDL 窗体
    mWindow = SDL_CreateWindow(
            "游戏环境的搭建",      // 标题
            100,                 // 窗体左上角的 x 坐标
            100,                 // 窗体左上角的 y 坐标
            1024,                // 窗体宽度
            768,                 // 窗体高度
            0                 // 标志位
    );
    if (!mWindow) {
        SDL_Log("创建窗体失败: %s", SDL_GetError());
        return false;
    }

    // 完成初始化
    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    // 队列中有 event 就一直循环
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }
    // 获取键盘的状态
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // 如果按了 Esc，结束循环
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void Game::UpdateGame() {}

void Game::GenerateOutput() {}
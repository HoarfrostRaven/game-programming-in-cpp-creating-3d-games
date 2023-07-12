//
// Created by 叶子寻 on 08/07/2023.
//

#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
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

    // 创建渲染器
    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!mRenderer) {
        SDL_Log("创建渲染器失败: %s", SDL_GetError());
        return false;
    }

    // 初始化球拍和球的坐标
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f / 2.0f;
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;

    // 完成初始化
    return true;
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
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

void Game::GenerateOutput() {
    // 设置 Tiffany 蓝
    SDL_SetRenderDrawColor(
            mRenderer,
            129, 			// R
            216, 			// G
            209, 			// B
            255 			    // A
    );
    // 清理后缓冲区
    SDL_RenderClear(mRenderer);

    // 设置绘制颜色
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

    // 顶部墙的参数
    SDL_Rect wall {
            0, // 左上 x 坐标
            0, // 左上 y 坐标
            1024, // 宽度
            thickness // 高度
    };
    // 绘制顶部墙
    SDL_RenderFillRect(mRenderer, &wall);

    // 绘制底部墙
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);

    // 绘制右边的墙
    wall = {
            1024 - thickness,
            0,
            thickness,
            1024
    };
    SDL_RenderFillRect(mRenderer, &wall);

    // 绘制球拍
    SDL_Rect paddle {
            static_cast<int>(mPaddlePos.x),
            static_cast<int>(mPaddlePos.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    // 绘制球
    SDL_Rect ball {
            static_cast<int>(mBallPos.x - thickness / 2),
            static_cast<int>(mBallPos.y - thickness / 2),
            thickness,
            thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);


    // 交换前后缓冲区
    SDL_RenderPresent(mRenderer);
}
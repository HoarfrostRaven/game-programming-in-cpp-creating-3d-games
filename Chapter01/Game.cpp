//
// Created by 叶子寻 on 08/07/2023.
//

#include "Game.h"

const int thickness = 15;
const int windowWidth = 1024;
const int windowHeight = 768;
const float paddleH = 100.0f;

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mTicksCount(0)
,mPaddleDir(0)
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
        "Pong",      // 标题
        100,                 // 窗体左上角的 x 坐标
        100,                 // 窗体左上角的 y 坐标
        windowWidth,         // 窗体宽度
        windowHeight,        // 窗体高度
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
    mPaddlePos.y = windowHeight / 2.0f;
    mBallPos.x = windowWidth / 2.0f;
    mBallPos.y = windowHeight / 2.0f;

    // 初始化球的速度
    mBallVel = {-200.0f, 235.0f};

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

    // 通过 W/S 更新球拍位置
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
    }
}

void Game::UpdateGame() {
    // 等到与上一帧间隔 16ms
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    // 增量时间是上一帧到现在的时间差
    // (转换成秒)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    // 更新运行时间(为下一帧)
    mTicksCount = SDL_GetTicks();

    // 固定增量时间最大值
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // 根据方向更新球拍位置
    if (mPaddleDir != 0) {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // 确保球拍不能移出窗口
        if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
            mPaddlePos.y = paddleH / 2.0f + thickness;
        } else if (mPaddlePos.y > (windowHeight - paddleH / 2.0f - thickness)) {
            mPaddlePos.y = windowHeight - paddleH / 2.0f - thickness;
        }
    }

    // 根据速度更新球的位置
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // 球是否和顶部或底部墙相碰
    if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
        mBallVel.y *= -1;
    } else if (mBallPos.y >= (windowHeight - thickness) && mBallVel.y > 0.0f) {
        mBallVel.y *= -1;
    }
    // 球是否和右侧墙壁相碰
    if (mBallPos.x >= (windowWidth - thickness) && mBallVel.x > 0.0f) {
        mBallVel.x *= -1;
    }

    // 获得球和球拍 y 轴距离
    float diff = mPaddlePos.y - mBallPos.y;
    // 取绝对值
    diff = (diff > 0.0f) ? diff : -diff;
    if (
            // y 轴距离足够小
            diff <= paddleH / 2.0f &&
            // 球在球拍的 x 范围内
            mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
            // 球正向左运动
            mBallVel.x < 0.0f
            ) {
        mBallVel.x *= -1.0f;
    }
    // 如果球出了窗口，结束游戏
    else if (mBallPos.x <= 0.0f) {
        mIsRunning = false;
    }
}


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
        windowWidth, // 宽度
        thickness // 高度
    };
    // 绘制顶部墙
    SDL_RenderFillRect(mRenderer, &wall);

    // 绘制底部墙
    wall.y = windowHeight - thickness;
    SDL_RenderFillRect(mRenderer, &wall);

    // 绘制右边的墙
    wall = {
        windowWidth - thickness,
        0,
        thickness,
        windowWidth
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
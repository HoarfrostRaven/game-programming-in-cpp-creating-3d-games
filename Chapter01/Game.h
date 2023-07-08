//
// Created by 叶子寻 on 08/07/2023.
//

#ifndef CHAPTER01_GAME_H
#define CHAPTER01_GAME_H

#include <SDL2/SDL.h>

// Vector2 结构体仅存储 x 和 y 坐标
struct Vector2
{
    float x;
    float y;
};

// Game Class
class Game {
public:
    Game();

    // 初始化
    bool Initialize();

    // 游戏运行
    void RunLoop();

    // 关闭游戏
    void ShutDown();

private:
    // 处理进程
    void ProcessInput();

    // 更新游戏
    void UpdateGame();

    // 生成输出
    void GenerateOutput();

    // 通过 SDL 创建窗体
    SDL_Window* mWindow;

    // 继续运行
    bool mIsRunning;

    // 渲染器
    SDL_Renderer* mRenderer;

    // 球拍位置
    Vector2 mPaddlePos;

    // 球的位置
    Vector2 mBallPos;

    // 记录运行时间
    Uint32 mTicksCount;

    // 球拍方向
    int mPaddleDir;

    // 球的速度
    Vector2 mBallVel;
};

#endif //CHAPTER01_GAME_H

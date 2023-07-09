//
// Created by 叶子寻 on 08/07/2023.
//

#ifndef CHAPTER01_GAME_H
#define CHAPTER01_GAME_H

#include <SDL2/SDL.h>

class Game {
public:
    Game();
    // 初始化
    bool Initialize();
    // 游戏运行
    void RunLoop();
    // 关闭游戏
    void Shutdown();
private:
    // 处理进程
    void ProcessInput();
    // 更新游戏
    void UpdateGame();
    // 生成输出
    void GenerateOutput();
    // 通过 SDL 创建窗体
    SDL_Window* mWindow;
    // 判断是否继续运行
    bool mIsRunning;
};

#endif //CHAPTER01_GAME_H

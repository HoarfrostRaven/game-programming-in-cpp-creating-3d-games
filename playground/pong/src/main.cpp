//
//  main.cpp
//  test
//
//  Created by 叶子寻 on 08/07/2023.
//

#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game game;
    bool success = game.Initialize();

    if (success) {
        game.RunLoop();
    }

    game.ShutDown();
    return 0;
}

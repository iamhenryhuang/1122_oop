#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "../gameprocess.h"

class GameOver: public GameProcessBase {
private:
    
public:
    GameOver();
    ~GameOver();

    ProcessInfo run(InputState action) override;

    void render() override;
};

#endif
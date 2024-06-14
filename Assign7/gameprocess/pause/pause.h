#ifndef PAUSE_H
#define PAUSE_H

#include "../gameprocess.h"

class Pause: public GameProcessBase {
private:
    
public:
    Pause();
    ~Pause();

    ProcessInfo run(InputState action) override;

    void render() override;
};

#endif
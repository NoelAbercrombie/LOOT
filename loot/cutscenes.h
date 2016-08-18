#pragma once
#include <stdint.h>
#include "cutscenetype.h"
#include "gamestate.h"

class System;

class Cutscenes
{
  private:
    System * ab;    
    CutsceneType scene;
    GameState stateNext;
    GameState stateLast;
    bool ready;
    bool complete;
    uint8_t time;

  public:
    Cutscenes(System & ab);

    void start(const CutsceneType scene, const GameState stateNext);
    void play(const CutsceneType scene);
    void end(void);

    void step(void);
    void draw(void);
};

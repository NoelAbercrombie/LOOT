#pragma once
#include <stdint.h>

#include "menupage.h"

class System;

class Menu
{
  private:
    System * ab;
    MenuPage page;
    int8_t select;
    bool menuReady;
    int8_t logoAnim;  //slides menu up
    
  public:
    Menu(System & ab);

    inline void menuGoto(const MenuPage page, const int8_t select);

    void init(void);
    void step(void);
    void draw(void);
};

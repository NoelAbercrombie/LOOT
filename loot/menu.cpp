#include "menu.h"
#include "menupage.h"
#include "constants.h"
#include "graphics.h"
#include "system.h"
#include "button.h"

Menu::Menu(System & ab)
{
  this->ab = &ab;
}

void Menu::init(void)
{
  page = MenuPage::Main;
  select = 0;
  logoAnim = 64;
}

void Menu::step(void)
{
  logoAnim = max(logoAnim - 1, 0);

  if(logoAnim == 0) //if menu is ready
  {
    if(ab->isPushed(Button::A))
    {
      switch(page)
      {
        case MenuPage::Main:
        {
          switch(select)
          {
          case 0: { ab->setState(stateGame); break; }
          case 1: { page = MenuPage::Options; break; }
          case 2: { page = MenuPage::About; select = 2; break; } // This basically equates to if(select == 2) select = 2;
          }
          break;
        }
        case MenuPage::Options:
        {
          page = MenuPage::Main;
          select = 1;
          break;
        }
        case MenuPage::About:
        {
          page = MenuPage::Main;
          break;
        }
      }
    }

    if(ab->isPushed(Button::Up))
    {
      if(select > 0) --select;
    }

    if(ab->isPushed(Button::Down))
    {
      if(select < 2) ++select;
    }
  }
}

void Menu::draw(void)
{
  switch(page)
  {
    case MenuPage::Main:
    {
      //logo
      if (logoAnim > 0)
        ab->drawSpriteCentered(64, 32 - (64 - logoAnim), imgTitle, 1);
      //menu text
      ab->setCursor(16, logoAnim + 8);
      ab->print(F("Play"));
      ab->setCursor(16, logoAnim + 16);
      ab->print(F("Config"));
      ab->setCursor(16, logoAnim + 24);
      ab->print(F("About"));
      //select cursor
      ab->setCursor(8, logoAnim + 8 + (8 * select));
      ab->print(F(">"));
      break;
    }
    // Why leave comments explaining what the numbers are when you can do this:
    case MenuPage::Slots:
    {
    }
    case MenuPage::Options:
    {
      ab->setCursor(0, 0);
      ab->print(F("Nothing to see here!"));
      break;
    }
    case MenuPage::About:
    {
      ab->setCursor(0, 0);
      ab->print(F("Test string!"));
      break;
    }
    // And the best bit, it's exactly equivalent to what you were doing before,
    // no memory penalty, no performance penalty, just compiler magic
  }
}

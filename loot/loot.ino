#include <stdint.h>
#include <Arduboy.h>
#include "system.h"
#include "game.h"
#include "graphics.h"
#include "constants.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "menu.h"

System ab = System();
World world = World();
Menu menu = Menu(ab);
Player player = Player(ab, world);
Render render = Render(ab, world, player);
Game game = Game(ab, render, menu, player, world); //controls everything!

void setup(void)
{
	ab.begin();
	Serial.begin(9600);
	Serial.println(F("Start!"));
	ab.fillScreen(0);
  	ab.drawSpriteCentered(64, 32, imgTitle, 1);
	ab.display();
	while(!ab.isPushed(Button::A))	//keep titlescreen up until a button is pressed
	{
		ab.update();
	}
}

void loop(void)
{
	if(!ab.nextFrame())
		return;

	ab.update();
	ab.clear();
	game.step();
	ab.display();
}

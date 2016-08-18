#include <stdint.h>
#include <Arduboy2.h>
#include "system.h"
#include "game.h"
#include "graphics.h"
#include "render.h"
#include "world.h"
#include "player.h"
#include "menu.h"
#include "battle.h"
#include "cutscenes.h"

System ab = System();
Cutscenes cutscenes = Cutscenes(ab);
World world = World();
Battle battle = Battle(ab);
Player player = Player(ab, world, cutscenes);
Menu menu = Menu(ab, cutscenes);
Render render = Render(ab, world, player);
Game game = Game(ab, render, menu, player, world, cutscenes, battle); //controls everything!

void setup(void)
{
	ab.begin();
	Serial.begin(9600);
	Serial.println(F("Start!"));
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

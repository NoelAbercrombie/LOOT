#include <stdint.h>
#include <Arduboy.h>
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
Player player = Player(ab, world, cutscenes);
Battle battle = Battle(ab);
Menu menu = Menu(ab, cutscenes);
Render render = Render(ab, world, player);
Game game = Game(ab, render, menu, player, world, cutscenes, battle); //controls everything!

int main(void)
{
	init();		

	#ifdef USBCON
    	USBDevice.attach();
	#endif

	ab.begin();
	Serial.begin(9600);
	Serial.println(F("Start!"));

	//put a return; right here for maximum fun
	
	while(1)
	{
		if(ab.nextFrame())
	    {
			ab.update();
			ab.clear();
			game.step();
			ab.display();
	    }
	}
}
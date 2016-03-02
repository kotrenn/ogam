#include "region.h"
#include "regionbuilder.h"

#include "common.h"
#include "resourcemanager.h"
#include "manager.h"
#include "surface.h"

int main(int argc, char **argv)
{
	System *system = System::get_instance();
	Manager *manager = new Manager();

	bool running = true;
	while (running)
	{
		running = system->run();
		
		// update here
		manager->update();

		Surface *screen = system->get_screen();
		screen->fill(0);

		// draw here
		manager->draw(screen);

		system->flip();
	}

	delete manager;
	delete system;

	return 0;
}

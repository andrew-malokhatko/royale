#include "application.hpp"

int main()
{
	Application application = Application();
	
	while (application.isRunning())
	{
		application.update();
		application.draw();
	}
}
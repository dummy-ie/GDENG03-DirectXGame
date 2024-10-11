#include "AppWindow.h"


int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*) AppWindow::get();
	while (runningApp->isRunning())
	{
		runningApp->broadcast();
	}
	return 0;
}
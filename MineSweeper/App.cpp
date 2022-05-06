#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {}

App::~App() {}

bool App::OnInit() 
{
	display = new MainWindow();
	display->Show();
	return true;
}




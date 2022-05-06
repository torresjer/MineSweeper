#pragma once
#include "wx/wx.h"
#include "MainWindow.h"

//This could be considered the launcher of the application.
class App : public wxApp
{
private:
	MainWindow* display = nullptr;
public:
	App();
	~App();
	virtual bool OnInit();

};


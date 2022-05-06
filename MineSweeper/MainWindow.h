//This is the main window of the application
#pragma once
#include "wx/wx.h"

class MainWindow : public wxFrame //ensure that you are inheriting from wxFrame
{
public:
	MainWindow();
	~MainWindow();
public:
	
	int fieldHight = 10;
	int fieldWidth = 10;
	wxButton** btn;
	int* minePosition = nullptr;
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};


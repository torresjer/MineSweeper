#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "MineSweeper", wxPoint(30,30), wxSize(800,600)){
	
	btn = new wxButton * [fieldWidth * fieldHight];
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHight, 0, 0);

	minePosition = new int[fieldWidth * fieldHight];
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);


	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHight; y++) {
			btn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			btn[y * fieldWidth + x]->SetFont(font);
			grid->Add(btn[y * fieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
			minePosition[y * fieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MainWindow::~MainWindow(){
	delete[] btn;
}

void MainWindow::OnButtonClicked(wxCommandEvent &evt) {
	//This will allow to get the coordinates of the button in the field array
	int x = (evt.GetId() - 10000) % fieldWidth;
	int y = (evt.GetId() - 10000) / fieldHight;

	if (firstClick) {

		int mines = 30;
		//Generates Mines across the 10x10 field
		while(mines) {

			int mx = rand() % fieldWidth;
			int my = rand() % fieldHight;

			if (minePosition[my * fieldWidth + mx] == 0 && mx != x && my != y) {

				minePosition[my * fieldWidth + mx] = -1;
				mines--;
			}

			firstClick = false;
		}
		
	}
	//Disable Button, Preventing it from being pressed again
	btn[y * fieldWidth + x]->Enable(false);

	//Check if player hit mine 
	if (minePosition[y * fieldWidth + x] == -1) {

		wxMessageBox("YOU'VE BEEN BLOWN UP SON!!! - GAME OVER");

		//reset game
		firstClick = true;
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHight; y++) {

				minePosition[y * fieldWidth + x] = 0;
				btn[y * fieldWidth + x]->SetLabel("");
				btn[y * fieldWidth + x]->Enable(true);
			}
		}
	}
	else {
		//count Neighboring Mines
		int mine_Count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {

				if (x + i >= 0 && x + i < fieldWidth && y + j < fieldHight) {

					if (minePosition[(y + j) * fieldWidth + (x + i)] == -1)
						mine_Count++;
				}
			}
		}
		//Update button lable to show mine count if > 0
		if (mine_Count >= 0) {

			btn[y * fieldWidth + x]->SetLabel(std::to_string(mine_Count));
		}
	}
}
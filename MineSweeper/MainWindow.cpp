#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "MineSweeper", wxPoint(30,30), wxSize(800,600)){
	
	btn = new wxButton * [fieldWidth * fieldHight];
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHight, 0, 0);

	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHight; y++) {
			btn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			grid->Add(btn[y * fieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
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

	evt.Skip();
}
#include "nwpwin.h"
#include "res.h"

class Button : public Window
{
public:
	std::string ClassName() {
		return "BUTTON";
	}
};

class Edit : public Window
{
public:
	std::string ClassName() {
		return "EDIT";
	}
};

class ListBox : public Window
{
public:
	std::string ClassName() {
		return "LISTBOX";
	}
};

class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	ListBox List;
	Edit EntryBox;
	Button AddButton, RemoveButton;
	List.Create(*this, WS_CHILD | WS_VISIBLE, "List", IDC_LB, 20, 20, 100, 120);
	EntryBox.Create(*this, WS_CHILD | WS_VISIBLE, 0, IDC_EDIT, 140, 20, 80, 20);
	AddButton.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 140, 60, 80, 20);
	RemoveButton.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 140, 100, 80, 20);
	// TODO: disable "Remove" button
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(*this, "Poruka", "About", MB_OK);
			break;
		case IDC_ADD:
			char EntryText[20];
			if (GetDlgItemText(*this, IDC_EDIT, EntryText, sizeof(EntryText))) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)EntryText);
			}
			SetDlgItemText(*this, IDC_EDIT, "");
			// TODO: enable "Remove" button
			break;
		case IDC_REMOVE:
			LRESULT Selection = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
			if (Selection != LB_ERR)
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, Selection, 0);
			// TODO: disable "Remove" button if listbox is empty
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow wnd; 
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}

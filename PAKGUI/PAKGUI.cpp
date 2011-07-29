// PAKGUI.cpp : main project file.

#include "stdafx.h"
#include "FrmMain.h"

using namespace PAKGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew frmMain());

	return 0;
}

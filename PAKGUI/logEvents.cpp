#include "stdafx.h"

using namespace PAKGUI;


System::Void inline frmMain::logToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if ( !logToolStripMenuItem->Checked )
	{
		log->Visible = false;
	}
	else
	{
		log->Visible = true;
	}
}

System::Void inline frmMain::frmLog_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
{
	if ( log->Visible ) {
		logToolStripMenuItem->Checked = true;
		log->DesktopLocation = Point( frmMain::DesktopLocation.X + 100, frmMain::DesktopLocation.Y + 100 );
		logScrollToBottom(); // scroll the log to the bottom. For some reason, this works better outside of the if's below.
	}
	else
	{
		logToolStripMenuItem->Checked = false;
	}
}

System::Void inline frmLog::btnOK_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Visible = false;
}

System::Void inline frmLog::frmLog_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	this->Visible = false;
	e->Cancel = true;
}

System::Void inline frmLog::btnClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	txtLog->Text = "";
}
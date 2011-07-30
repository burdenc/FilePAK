#include "stdafx.h"

using namespace PAKGUI;

System::Void frmMain::logToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if ( !logToolStripMenuItem->Checked )
	{
		frmMain::log->Visible = false;
	}
	else
	{
		frmMain::log->Visible = true;
	}
}

System::Void frmMain::frmLog_VisibleChanged(System::Object^  sender, System::EventArgs^  e)
{
	if ( log->Visible ) {
		logToolStripMenuItem->Checked = true;
	}
	else
	{
		logToolStripMenuItem->Checked = false;
	}
}

System::Void frmLog::btnOK_Click(System::Object^  sender, System::EventArgs^  e)
{
	this->Visible = false;
}

System::Void frmLog::frmLog_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	this->Visible = false;
	e->Cancel = true;
}

System::Void frmLog::btnClear_Click(System::Object^  sender, System::EventArgs^  e)
{
	txtLog->Text = "";
}
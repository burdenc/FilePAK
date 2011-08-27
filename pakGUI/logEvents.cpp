/*
	This file is part of pakGUI.

	pakGUI is a user-friendly graphical user interface for libPAK which allows the
	packing and un-packing of several files into one easily manageable resource file.

	pakGUI, pakEXE, and libPAK
	Copyright © 2011  Drew Burden, Hogg Studios

	pakGUI was developed by Drew Burden in cooperation with Cassidy Burden
	and released by Hogg Studios under the GPLv3 License.

	pakGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	pakGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with pakGUI. If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"

using namespace pakGUI;


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
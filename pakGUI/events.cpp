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
#include "events.h"

#include <sstream>

using namespace pakGUI;


libPAK pak;
map<string, long long> fileSizes;
long long currentEstimatedSize = 0;
int numChecked = 0;
int itemProgressed = 0;
int percentProg = 0;
string prog = IDLE;
int sorting = ASCENDING;


// convert System::String (String ^) to std::string for use with LibPAK
inline void MarshalString ( String ^ s, string& os )
{
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

inline long long getFileBytes( String ^filename )
{
	FileInfo^ file = gcnew FileInfo( filename );
	return file->Length;
}

inline System::Void frmMain::logScrollToBottom()
{
	log->txtLog->Focus();
	log->txtLog->Select( log->txtLog->Text->Length, 0 ); // put the caret at the bottom
	log->txtLog->ScrollToCaret(); // scroll to the caret
}

String ^getFileSize( long long origbytes )
{
	// Convert
	int i; // number of iterations through the loop determine what unit to use
	//double sizeconvert = bytes; // the size of the file in bytes
	if ( origbytes == 0 )
	{
		return gcnew String( "0 KB" ); // there was nothing in the file
	}

	double bytes = (double) origbytes;

	for ( i = 0; bytes > 1024.0; ++i, bytes *= ( 1.0/1024.0 ) ) {} // convert from bytes to a more readable unit

	stringstream size; // this holds the final string to be returned

	// append size unit to the end of the stringstream (GB = max supported unit, KB = min supported unit)
	// we only need decimal places for GB
	if ( i == 1 )
	{
		size << Math::Round( bytes ) << " KB"; // we want to make sure we round because typecasting will truncate and may cause problems later
	}
	else if ( i == 2 )
	{
		size << Math::Round( bytes ) << " MB"; // we want to make sure we round because typecasting will truncate and may cause problems later
	}
	else if ( i >= 3 )
	{
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(1);
		size << bytes << " GB";
	}
	else // if less than 1KB, round up to 1KB
	{
		size.str( string() ); // clear stringstream
		size << "1 KB";
	}

	return gcnew String( size.str().c_str() );
}

inline System::Void frmMain::updateStatus()
{
	lblItemProg->Text = itemProgressed + " / " + numChecked;
	lblPercentProg->Text = gcnew String( prog.c_str() );
	stsStatus->Text = lblPercentProg->Text;
	progressBar->Value = percentProg;
}
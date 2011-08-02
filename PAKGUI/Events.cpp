#include "stdafx.h"
#include "Events.h"

#include <sstream>

using namespace PAKGUI;


filePAK pak;
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

	for ( i = 0; bytes > 1024; ++i, bytes *= ( 1.0/1024.0 ) ) {} // convert from bytes to a more readable unit

	stringstream size; // this holds the final string to be returned

	// append size unit to the end of the stringstream (GB = max supported unit, KB = min supported unit)
	// we only need decimal places for MB and GB
	if ( i == 1 )
	{
		size << (int) bytes << " KB";
	}
	else if ( i == 2 )
	{
		size << (int) bytes;
		size << " MB";
	}
	else if ( i >= 3 )
	{
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(1);
		size << bytes;
		size << " GB";
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
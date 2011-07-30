#include "stdafx.h"
#include "Events.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>

using namespace PAKGUI;


filePAK pak;
map<string, long> fileSizes;
long currentEstimatedSize = 0;

// convert System::String (String ^) to std::string for use with LibPAK
void MarshalString ( String ^ s, string& os )
{
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

long getFileBytes( String ^filename )
{
	string dir;
	MarshalString( filename, dir );
	// Calculate file size in bytes
	long beg, end;
	ifstream file ( dir, ios::in|ios::binary); // open file
	beg = (long)file.tellg(); // beginning of file
	file.seekg (0, ios::end); // seek to end
	end = (long)file.tellg(); // end of file
	file.close(); // close file

	return end - beg;
}

String ^getFileSize( long bytes )
{
	// Convert
	int i; // number of iterations through the loop determine what unit to use
	double sizeconvert = bytes; // the size of the file in bytes
	if ( sizeconvert == 0 )
	{
		return gcnew String( "0 KB" ); // there was nothing in the file
	}
	for ( i = 0; sizeconvert > 1024.0; ++i, sizeconvert /= 1024.0 ) {} // convert from bytes to a more readable unit

	stringstream size; // this holds the final string to be returned
	size << (int) ceil( sizeconvert ); // get rid of decimals (round up)

	// append size unit to the end of the stringstream (GB = max supported unit, KB = min supported unit)
	// we only need decimal places for MB and GB
	if ( i == 1 )
	{
		size << " KB";
	}
	else if ( i == 2 )
	{
		size.str(string()); // clear stringstream
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(1);
		size << sizeconvert;
		size << " MB";
	}
	else if ( i >= 3 )
	{
		size.str(string()); // clear stringstream
		size.setf( ios::fixed, ios::floatfield ); // set decimal
		size.precision(2);
		size << sizeconvert;
		size << " GB";
	}
	else // if less than 1KB, round up to 1KB
	{
		size.str(string()); // clear stringstream
		size << "1 KB";
	}

	return gcnew String( size.str().c_str() );
}
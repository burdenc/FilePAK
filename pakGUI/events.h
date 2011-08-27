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

#pragma once

#include <map>


#define		IDLE		"Idle"
#define		UNPAK		"UnPAK'ing - "
#define		PAK			"PAK'ing - "
#define		DONE		"Done"
#define		CANCEL		"Cancelled"

#define		ASCENDING	1
#define		DESCENDING	-1


extern	libPAK								pak;
extern	map<string, long long>				fileSizes;
extern	long long							currentEstimatedSize;
extern	int									numChecked;
extern	int									itemProgressed;
extern	int									percentProg;
extern	string								prog;
extern	int									sorting;


extern	inline void			MarshalString ( System::String ^ s, string& os );
extern	inline long long	getFileBytes( System::String ^filename );
extern	System::String		^getFileSize( long long bytes );
#pragma once

#include <map>

extern filePAK pak;
extern map<string, long> fileSizes;
extern long currentEstimatedSize;

extern void MarshalString ( System::String ^ s, string& os );
extern long getFileBytes( System::String ^filename );
extern System::String ^getFileSize( long bytes );
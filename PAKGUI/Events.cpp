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

void MarshalString ( System::String ^ s, string& os );
long getFileBytes( System::String ^filename );
System::String ^getFileSize( long bytes );

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


// This event occurs every time an item in the PAK Contents list is checked or unchecked.
System::Void frmMain::lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
{
	/////////////////////////////
	// Item Progress Label
	/////////////////////////////
	IEnumerator^ myEnum1 = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
	int numChecked = 0; // The number of items checked
	while ( myEnum1->MoveNext() )
	{
		++numChecked;
	}

	string tmp;
	MarshalString( lstPakContents->Items[ e->Index ]->Text, tmp );
	long checkedsize = fileSizes[ tmp ];

	// Because of the way the checked items are updated in relation to the event, we have to account for a difference of 1 on two occasions.
	// these if-statements also allow us to perform actions specific to a check or uncheck event
	if ( e->CurrentValue == CheckState::Unchecked ) // If the event was triggered by a check
	{
		++numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) + atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize += checkedsize; // calculate the new size (remember, still in bytes)
	}
	else // If the event was triggered by an uncheck
	{
		--numChecked;
		//lblPakSizeAfterPak->Text = atoi( cursize.c_str() ) - atoi( checkedsize.c_str() ) + " KB"; // Update Estimated size of PAK file after PAK'ing
		currentEstimatedSize -= checkedsize; // calculate the new size (remember, still in bytes)
	}

	// finally, determine the new units
	lblPakSizeAfterPak->Text = getFileSize( currentEstimatedSize );

	if ( numChecked > 0 ) // If there's items selected, enable buttons that depend on having selected items
	{
		btnPak->Enabled = true; // Pak button
		btnUnpak->Enabled = true; // Unpak button
		menuPak->Enabled = true; // menu pak button
		menuUnpak->Enabled = true; // menu unpak button
	}
	else if ( btnPak->Enabled || btnUnpak->Enabled ) // Otherwise, disable them if they are enabled
	{
		btnPak->Enabled = false; // Pak button
		btnUnpak->Enabled = false; // Unpak button
		menuPak->Enabled = false; // menu pak button
		menuUnpak->Enabled = false; // menu unpak button
	}

	lblItemProg->Text = "0 / " + numChecked; // Update the item progress label
}

// This event occurs when the user drags a file into the pak contents area
System::Void frmMain::lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{

	// NOTE: drag/drop'ing folders are not working right now, and they might not ever be

	DataObject^ o = gcnew DataObject( DataFormats::FileDrop, e->Data->GetData(DataFormats::FileDrop) );
	if (!o->ContainsFileDropList() ) // probably shouldn't ever happen
	{
		// this error is worth the user's immediate attention
		MessageBox::Show( "Error adding files:\nNo eligible files could be found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error  );
		log->displayMsg( "Error adding files:" + Environment::NewLine + "\tNo eligible files could be found." ); // still add it to the log anyways
		log->addBreak();
	}

	System::Collections::Specialized::StringCollection ^s = o->GetFileDropList();

	bool errors = false; // if there were errors adding files, this will be true
	// cycle through all the files that were dragged and add them to the list
	for each ( String ^p in s )
	{
		// calc file size
		long bytes = getFileBytes( p );
		if ( bytes <= 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tFile \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			continue;
		}
		string tmp;
		MarshalString( p->Substring( p->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tDuplicate file entry detected: \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\"" );
			}
			else 
			{
				errors = true;
				log->displayMsg( "Error adding file: " + Environment::NewLine + "\tDuplicate file entry detected: \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\"" );
			}
			continue;
		}
		fileSizes[tmp] = bytes;
		String ^size = getFileSize( bytes );

		// add an item with all the columns
		ListViewItem^ item = gcnew ListViewItem( p->Substring( p->LastIndexOf('\\') + 1 ) ); // create the item and give it name column
		item->SubItems->Add( p ); // directory column
		item->SubItems->Add( size ); // file size column
		item->SubItems->Add( "Not in PAK" ); // origin column. since you're manually adding the file, it can't already be in the pak
		item->SubItems->Add( p->Substring( p->LastIndexOf('.') ) ); // extension column
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list
	}

	log->addBreak();

	if ( !log->Visible && errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
		if ( result == System::Windows::Forms::DialogResult::Yes )
		{
			log->Visible = true;
		}
	}

}


// This event occurs when the user clicks the Unpak button
System::Void frmMain::btnUnpak_Click(System::Object^  sender, System::EventArgs^  e) 
{
	folderBrowserDialog->ShowDialog(); // open folder browser
}

// This event occurs when the user clicks the browse button for the pak directory
System::Void frmMain::btnSaveDirBrowse_Click(System::Object^  sender, System::EventArgs^  e)
{
	// if text is present in the save file text box and it appears to be a directory
	if ( txtSaveDir->Text->Length > 0 && ( txtSaveDir->Text->LastIndexOf( '\\' ) != -1 || txtSaveDir->Text->LastIndexOf( '/' ) != -1 ) )
	{
		// make that the initial directory and file for the dialog
		savePakDialog->InitialDirectory = txtSaveDir->Text->Substring( 0, txtSaveDir->Text->LastIndexOf( '\\' ) );

		// account for both types of slashes
		if ( txtSaveDir->Text->Length >= txtSaveDir->Text->LastIndexOf( '\\' ) ) // make sure there is a file present after the last slash
		{
			savePakDialog->FileName = txtSaveDir->Text->Substring( txtSaveDir->Text->LastIndexOf( '\\' )+1 );
		}
		else if ( txtSaveDir->Text->Length >= txtSaveDir->Text->LastIndexOf( '/' ) ) // make sure there is a file present after the last slash
		{
			savePakDialog->FileName = txtSaveDir->Text->Substring( txtSaveDir->Text->LastIndexOf( '/' )+1 );
		}
		else
		{
			savePakDialog->FileName = ""; // the user didn't enter a file after the directory
		}
	}
	else // otherwise, we can't ascertain any sort of directory structure
	{
		// so 
		savePakDialog->InitialDirectory = "";
		savePakDialog->FileName = "";
	}

	savePakDialog->ShowDialog();

	// if the user didn't select a file, then it returns the previously selected file without the full path (hence no slashes)
	// this can be a problem because we always want the full path in the directory text box
	if ( savePakDialog->FileName->IndexOf( '\\' ) != -1 || savePakDialog->FileName->IndexOf( '/' ) != -1 ) // if the user didn't select a file
	{
		txtSaveDir->Text = savePakDialog->FileName; // put that path in the save file text box
	}
}
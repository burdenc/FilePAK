#include "stdafx.h"
#include "FrmMain.h"
#include <fstream>
#include <sstream>
#include <iostream>


using namespace PAKGUI;

filePAK pak;

// convert System::String (String ^) to std::string for use with LibPAK
void MarshalString ( String ^ s, string& os )
{
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

String ^getFileSize( String ^filename )
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

	// Convert
	int i; // number of iterations through the loop determine what unit to use
	double sizeconvert = end - beg; // the size of the file in bytes
	if ( sizeconvert == 0 )
	{
		return gcnew String( "0" ); // there was nothing in the file
	}
	for ( i = 0; sizeconvert > 1024.0; ++i, sizeconvert /= 1024.0 ) {} // convert from bytes to a more readable unit

	stringstream size; // this holds the final string to be returned
	size << (int) sizeconvert; // get rid of decimals

	// append size unit to the end of the stringstream (GB is the largest supported unit)
	if ( i == 1 ) size << " KB";
	else if ( i == 2 ) size << " MB";
	else if ( i >= 3 )
	{
		size.str(string()); // clear stringstream
		size.setf( ios::fixed, ios::floatfield); // set decimal
		size.precision(2);
		size << sizeconvert; // only show decimal if file is in GB
		size << " GB";
	}
	else size << "    B";

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
		//if ( lstPakContents->GetItemChecked( *safe_cast<Int32^>(myEnum1->Current) ) )
		//{
		++numChecked;
		//}
	}

	// Because of the way the checked items are updated in relation to the event, we have to account for a difference of 1 on two occasions.
	if ( e->CurrentValue == CheckState::Unchecked ) // If the event was triggered by a check
	{
		++numChecked;
	}
	else // If the event was triggered by an uncheck
	{
		--numChecked;
	}

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
	/////////////////////////////
}

// This event occurs when the Browse button is hit to add an entire directory to the PAK
System::Void frmMain::btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e)
{
	folderBrowserDialog->ShowDialog(); // This displays the folder selection dialog
	//txtAddDir->Text = folderBrowserDialog->SelectedPath; // This sets the text box to the resulting selection from the user

	//todo:
	//		scan selected directory and add files to the list
}

// This event occurs when the Open menu item is clicked
System::Void frmMain::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{

	if ( progressBar->Enabled ) // if the progress bar is enabled, this signifies that there is currently an operation being performed
	{
		// display a message box asking if the user is sure they want to interrupt the current operation
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You are currently PAK'ing or UnPAK'ing a file. Interrupting the current operation may cause loss or corruption of data! Are you sure you want to open a PAK file?", "Operation in progress", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
		else // perform resets on items in the form that are specific to performing an operation
		{
			progressBar->Value = 0;
			progressBar->Enabled = false;
			lblPercentProg->Text = "Idle";
			stsStatus->Text = "Idle";
			lblItemProg->Text = "0 " + lblItemProg->Text->Substring( lblItemProg->Text->IndexOf('/') );
		}
	}
	if ( lstPakContents->Items->Count ) // if the contents list contains any items, this signifies that there is a PAK file open
	{
		// display a message box asking if the user is sure they want to lose their current pak work
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You currently have a PAK file open. If you open a PAK file, any unsaved changes to the currently open PAK will be lost! Are you sure you want to open a PAK file?", "PAK File already opened", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
	}

	openPakDialog->ShowDialog(); // display file selection dialog
	string dir = ""; // will hold the full path to the pak
	MarshalString( openPakDialog->FileName->ToString(), dir ); // convert the dialog result to a string that we can use
	if ( pak.readPAK( dir ) && pak.getNumPAKEntries() > 0 ) {

		// clear the content list
		for each ( ListViewItem ^item in lstPakContents->Items )
		{
			item->Remove();
		}

		// adjust controls to reflect a new pak open
		lblItemProg->Text = "0 / " + pak.getNumPAKEntries();
		btnUnpak->Enabled = true;
		btnPak->Enabled = true;
		menuPak->Enabled = true;
		menuUnpak->Enabled = true;

		for each ( string name in pak.getAllPAKEntries() )
		{
			// add an item with all the columns
			String ^filename = gcnew String( name.c_str() ); // get the name, and convert it (sigh)

			ListViewItem^ item = gcnew ListViewItem( filename ); // create the item and give it name column
			item->SubItems->Add( openPakDialog->FileName->ToString() ); // directory column
			item->SubItems->Add( "In PAK" ); // origin column. since you're opening the pak, it must be in the pak
			item->SubItems->Add( filename->Substring( filename->LastIndexOf('.') ) ); // extension column
			item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
			lstPakContents->Items->Add( item ); // finally add the item to the list
		}

	}
	else
	{
		MessageBox::Show( "Error reading PAK" );
		return;
	}
}

// This event occurs when the New menu item is clicked
System::Void frmMain::newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	if ( progressBar->Enabled ) // if the progress bar is enabled, this signifies that there is currently an operation being performed
	{
		// display a message box asking if the user is sure they want to interrupt the current operation
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You are currently PAK'ing or UnPAK'ing a file. Interrupting the current operation may cause loss or corruption of data! Are you sure you want to make a new PAK file?", "Operation in progress", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
		else // perform resets on items in the form that are specific to performing an operation
		{
			progressBar->Value = 0;
			progressBar->Enabled = false;
			lblPercentProg->Text = "Idle";
			stsStatus->Text = "Idle";
			lblItemProg->Text = "0 " + lblItemProg->Text->Substring( lblItemProg->Text->IndexOf('/') );
		}
	}
	if ( lstPakContents->Items->Count ) // if the contents list contains any items, this signifies that there is a PAK file open
	{
		// display a message box asking if the user is sure they want to lose their current pak work
		System::Windows::Forms::DialogResult result = MessageBox::Show( "You currently have a PAK file open. If you make a new PAK file, any unsaved changes to the currently open PAK will be lost! Are you sure you want to make a new PAK file?", "PAK File already opened", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
		if ( result != System::Windows::Forms::DialogResult::Yes )
		{
			return;
		}
	}

	// reset all items in the form to their original values
	lblItemProg->Text = "0 / 0";
	btnUnpak->Enabled = false;
	btnPak->Enabled = false;
	menuPak->Enabled = false;
	menuUnpak->Enabled = false;

	// clear the content list
	for each ( ListViewItem ^item in lstPakContents->Items )
	{
		item->Remove();
	}
}

// This event occurs when the user drags a file into the pak contents area
System::Void frmMain::lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
{

	// NOTE: folders are not working right now, and they might not ever be

	DataObject^ o = gcnew DataObject( DataFormats::FileDrop, e->Data->GetData(DataFormats::FileDrop) );
	if (!o->ContainsFileDropList() )
		MessageBox::Show( "Error: No files were dropped." ); // CHANGE THIS LATER

	System::Collections::Specialized::StringCollection ^s = o->GetFileDropList();

	// cycle through all the files that were dragged and add them to the list
	for each ( String ^p in s )
	{
		// calc file size
		String ^size = getFileSize( p );
		if ( size == "0" )
		{
			MessageBox::Show( "Error: File \"" + p->Substring( p->LastIndexOf('\\')+1 ) + "\" contains no data." ); // CHANGE THIS LATER
			continue;
		}

		// add an item with all the columns
		ListViewItem^ item = gcnew ListViewItem( p->Substring( p->LastIndexOf('\\') + 1 ) ); // create the item and give it name column
		item->SubItems->Add( p ); // directory column
		item->SubItems->Add( size ); // file size
		item->SubItems->Add( "Not in PAK" ); // origin column. since you're manually adding the file, it can't already be in the pak
		item->SubItems->Add( p->Substring( p->LastIndexOf('.') ) ); // extension column
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list
	}
}

// This event occurs when the user clicks the Select all button
System::Void frmMain::btnSelectAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = true;
	}
}

// This event occurs when the user clicks the Select none button
System::Void frmMain::btnSelectNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = false;
	}
}

// This event occurs when the user clicks the Unpak button
System::Void frmMain::btnUnpak_Click(System::Object^  sender, System::EventArgs^  e) 
{

	//pak.createPAK("lol.pak", "test/", ".jpg|.bmp")
}
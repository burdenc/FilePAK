#include "stdafx.h"
#include "Events.h"

using namespace PAKGUI;


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
	MarshalString( openPakDialog->FileName, dir ); // convert the dialog result to a string that we can use
	if ( pak.readPAK( dir ) && pak.getNumPAKEntries() > 0 ) {

		// clear the content list
		for each ( ListViewItem ^item in lstPakContents->Items )
		{
			item->Remove();
		}

		fileSizes.clear();
		numChecked = 0;
		currentEstimatedSize = 0;

		// adjust controls to reflect a new pak open
		btnUnpak->Enabled = true;
		btnPak->Enabled = true;
		menuPak->Enabled = true;
		menuUnpak->Enabled = true;

		for each ( string name in pak.getAllPAKEntries() )
		{
			// add an item with all the columns
			String ^filename = gcnew String( name.c_str() ); // get the name, and convert it to a System::String

			// calc file size
			String ^size = getFileSize( pak.getPAKEntry( name )->size );
			long bytes = pak.getPAKEntry( name )->size;
			fileSizes[name] = bytes;

			ListViewItem^ item = gcnew ListViewItem( filename ); // create the item and give it name column
			item->SubItems->Add( openPakDialog->FileName ); // directory column
			item->SubItems->Add( size ); // file size column
			item->SubItems->Add( "In PAK" ); // origin column. since you're opening the pak, it must be in the pak
			if ( filename->LastIndexOf('.') == -1 )
			{
				item->SubItems->Add( "" ); // extension column
			}
			else
			{
				item->SubItems->Add( filename->Substring( filename->LastIndexOf('.') ) ); // extension column
			}
			item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
			lstPakContents->Items->Add( item ); // finally add the item to the list

			lblNumFiles->Text = pak.getNumPAKEntries() + " Files";
			txtSaveDir->Text = openPakDialog->FileName;
			lblOrigDir->Text = openPakDialog->FileName;

		}

		lblPakSize->Text = getFileSize( currentEstimatedSize );
		lblPakSizeAfterPak->Text = lblPakSize->Text;
		btnPak->Text = "RePAK";

	}
	else
	{
		// This error is worth bringing the user's immediate attention to
		MessageBox::Show( "Error reading PAK:\nInvalid or corrupt PAK file.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error );
		log->displayMsg( "Error reading PAK:" + Environment::NewLine + "\tInvalid or corrupt PAK file." ); // but still log it anyways
		log->addBreak();
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
			itemProgressed = 0;
			progressBar->Enabled = false;
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
	percentProg = 0;
	numChecked = 0;
	prog = IDLE;
	btnUnpak->Enabled = false;
	btnPak->Enabled = false;
	menuPak->Enabled = false;
	menuUnpak->Enabled = false;
	txtSaveDir->Text = "";
	lblOrigDir->Text = "None";
	lblPakSize->Text = "0 KB";
	lblPakSizeAfterPak->Text = "0 KB";
	currentEstimatedSize = 0;
	lblNumFiles->Text = "0 Files";
	fileSizes.clear();

	lstPakContents->BeginUpdate();
	// clear the content list
	for each ( ListViewItem ^item in lstPakContents->Items )
	{
		item->Remove();
	}
	lstPakContents->EndUpdate();

	updateStatus();
}
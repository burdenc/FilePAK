#include "stdafx.h"
#include "Events.h"

#include <sstream>
#include <fstream>


using namespace PAKGUI;


// This event occurs when the user clicks the Check all button
System::Void frmMain::btnCheckAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	lstPakContents->BeginUpdate();
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = true;
	}
	lstPakContents->EndUpdate();
}

// This event occurs when the user clicks the Check none button
System::Void frmMain::btnCheckNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	lstPakContents->BeginUpdate();
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Checked = false;
	}
	lstPakContents->EndUpdate();
}

// This event occurs when the user clicks the Select all button
System::Void frmMain::btnSelectAll_Click(System::Object^  sender, System::EventArgs^  e)
{
	lstPakContents->BeginUpdate();
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Selected = true;
	}
	lstPakContents->EndUpdate();
	lstPakContents->Focus(); // This is required because for some reason, the listview will not show the selected items unless the control has focus.
}

// This event occurs when the user clicks the Select none button
System::Void frmMain::btnSelectNone_Click(System::Object^  sender, System::EventArgs^  e)
{
	lstPakContents->BeginUpdate();
	for each ( ListViewItem^ item in lstPakContents->Items )
	{
		item->Selected = false;
	}
	lstPakContents->EndUpdate();
	lstPakContents->Focus(); // This is required because for some reason, the listview will not show the selected items unless the control has focus.
}

System::Void frmMain::btnDeleteSelected_Click(System::Object^  sender, System::EventArgs^  e)
{
	lstPakContents->BeginUpdate();
	for each ( ListViewItem^ item in lstPakContents->SelectedItems )
	{
		item->Checked = false;
		string tmp;
		MarshalString( item->Text, tmp );
		fileSizes[ tmp ] = 0;
		item->Remove();
	}
	lstPakContents->EndUpdate();

	if ( !lstPakContents->Items->Count ) // if no items are left after this, treat it as if almost a new file
	{
		// reset several items in the form to their original values
		btnPak->Text = "PAK";
		percentProg = 0;
		numChecked = 0;
		prog = IDLE;
		btnUnpak->Enabled = false;
		btnPak->Enabled = false;
		menuPak->Enabled = false;
		menuUnpak->Enabled = false;
		lblPakSizeAfterPak->Text = "0 KB";
		currentEstimatedSize = 0;

		updateStatus();

		return;
	}

}

// This event occurs when the user clicks the Unpak button
System::Void frmMain::btnUnpak_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if ( unpakFolderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::Yes
		|| unpakFolderBrowserDialog->SelectedPath->Length <= 0 ) // if the user didn't select any files
	{
		return; // the user didn't make a selection, so don't do anything
	}

	// may implement dialog that deals with replacing files
	// give the user option to say no, no to all, yes, yes to all

	lstPakContents->Enabled = false;
	btnPak->Visible = false;
	btnUnpak->Visible = false;
	menuPak->Visible = false;
	menuUnpak->Visible = false;
	menuPak->Enabled = false;
	menuUnpak->Enabled = false;
	menuCancel->Visible = true;
	menuCancel->Enabled = true;
	btnCancel->Visible = true;
	btnCheckAll->Enabled = false;
	btnCheckNone->Enabled = false;
	menuCheckAll->Enabled = false;
	menuCheckNone->Enabled = false;
	btnAddFiles->Enabled = false;
	btnBrowseDir->Enabled = false;
	btnDeleteSelected->Enabled = false;
	progressBar->Enabled = true;

	percentProg = 0;
	stringstream s;
	s << percentProg;
	prog = UNPAK + s.str() + "%";
	updateStatus();

	IEnumerator^ items = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
	bool errors = false;
	while ( items->MoveNext() )
	{

		itemProgressed++;
		percentProg = (int) ( (double)itemProgressed / (double)numChecked * 100.0 );
		stringstream s;
		s << percentProg;
		prog = UNPAK + s.str() + "%";

		Int32 itemIndex = *safe_cast<Int32^>(items->Current);

		// Make sure the user is trying to UnPAK files that are actually in the PAK
		if ( lstPakContents->Items[ itemIndex ]->SubItems[3]->Text == "Not in PAK" )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + lstPakContents->Items[ itemIndex ]->Text + "\" is not in the PAK file." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error UnPAK'ing files: " + Environment::NewLine + "\tFile \"" + lstPakContents->Items[ itemIndex ]->Text + "\" is not in the PAK file." );
			}
			continue;
		}

		// if the file already exists
		if ( File::Exists( unpakFolderBrowserDialog->SelectedPath + "\\" + lstPakContents->Items[ itemIndex ]->Text ) )
		{
			// we need to get the user's attention and ask them whether the want to overwrite the file before we continue
			System::Windows::Forms::DialogResult result = MessageBox::Show( "This folder already contains a file named '" + lstPakContents->Items[ itemIndex ]->Text + "'\nDo you want to replace it?",  "Confirm File Replace", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				// don't do anything. we'll keep going as if the file didn't already exist and the unpak function will overwrite it
			}
			else if ( result == System::Windows::Forms::DialogResult::No )
			{
				updateStatus();
				continue;
			}
			else // cancel or possibly closed dialog with X
			{
				lstPakContents->Enabled = true;
				btnPak->Visible = true;
				btnUnpak->Visible = true;
				menuPak->Visible = true;
				menuUnpak->Visible = true;
				menuPak->Enabled = true;
				menuUnpak->Enabled = true;
				menuCancel->Visible = false;
				menuCancel->Enabled = false;
				btnCancel->Visible = false;
				btnCheckAll->Enabled = true;
				btnCheckNone->Enabled = true;
				menuCheckAll->Enabled = true;
				menuCheckNone->Enabled = true;
				btnAddFiles->Enabled = true;
				btnBrowseDir->Enabled = true;
				btnDeleteSelected->Enabled = true;
				progressBar->Enabled = false;

				itemProgressed = 0;
				percentProg = 0;
				prog = CANCEL;
				updateStatus();
				return;
			}
		}

		string name, dir;
		MarshalString( unpakFolderBrowserDialog->SelectedPath + "\\" + lstPakContents->Items[ itemIndex ]->Text, dir );
		MarshalString( lstPakContents->Items[ itemIndex ]->Text, name );

		ofstream f; //output

		char *buffer;
		buffer = pak.getPAKEntryData(name);
		int ofsize;
		ofsize = pak.getPAKEntrySize(name);
		if(buffer == NULL || ofsize <= 0)
		{
			errors = true;
			log->displayMsg( "Error reading PAK:" + Environment::NewLine + "\tCould not find '" + gcnew String( name.c_str() ) + "' in PAK." ); // but still log it anyways
		}

		f.open(dir, ofstream::binary); // open in binary

		if (f.is_open())  // make sure it opened
		{
			f.write(buffer, ofsize); // write the buffer to the output file with the size of the original file
		}
		else
		{
			delete [] buffer;
			errors = true;
			log->displayMsg( "Error opening file:" + Environment::NewLine + "\tCould not open '" + gcnew String( dir.c_str() ) + "' for writing." ); // but still log it anyways
		}

		updateStatus();

	}

	lstPakContents->Enabled = true;
	btnPak->Visible = true;
	btnUnpak->Visible = true;
	menuPak->Visible = true;
	menuUnpak->Visible = true;
	menuPak->Enabled = true;
	menuUnpak->Enabled = true;
	menuCancel->Visible = false;
	menuCancel->Enabled = false;
	btnCancel->Visible = false;
	btnCheckAll->Enabled = true;
	btnCheckNone->Enabled = true;
	menuCheckAll->Enabled = true;
	menuCheckNone->Enabled = true;
	btnAddFiles->Enabled = true;
	btnBrowseDir->Enabled = true;
	btnDeleteSelected->Enabled = true;
	progressBar->Enabled = false;

	prog = DONE;
	itemProgressed = 0;
	updateStatus();

	if ( errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		log->addBreak();
		if ( !log->Visible )
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				log->Visible = true;
			}
		}
	}

}

// This event occurs when the user clicks the Pak button
System::Void frmMain::btnPak_Click(System::Object^  sender, System::EventArgs^  e)
{
	// open folder browser
	if ( unpakFolderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::Cancel || unpakFolderBrowserDialog->SelectedPath->Length <= 0 ) // show the dialog
	{
		return;
	}

	// may implement dialog that deals with replacing files
	// give the user option to say no, no to all, yes, yes to all

	lstPakContents->Enabled = false;
	btnPak->Visible = false;
	btnUnpak->Visible = false;
	menuPak->Visible = false;
	menuUnpak->Visible = false;
	menuPak->Enabled = false;
	menuUnpak->Enabled = false;
	menuCancel->Visible = true;
	menuCancel->Enabled = true;
	btnCancel->Visible = true;
	btnCheckAll->Enabled = false;
	btnCheckNone->Enabled = false;
	menuCheckAll->Enabled = false;
	menuCheckNone->Enabled = false;
	btnAddFiles->Enabled = false;
	btnBrowseDir->Enabled = false;
	btnDeleteSelected->Enabled = false;
	progressBar->Enabled = true;

	percentProg = 0;
	stringstream s;
	s << percentProg;
	prog = UNPAK + s.str() + "%";
	updateStatus();

	IEnumerator^ items = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
	bool errors = false;
	while ( items->MoveNext() )
	{

		itemProgressed++;
		percentProg = (int) ( (double)itemProgressed / (double)numChecked * 100.0 );
		stringstream s;
		s << percentProg;
		prog = UNPAK + s.str() + "%";

		Int32 itemIndex = *safe_cast<Int32^>(items->Current);

		// Make sure the user is trying to UnPAK files that are actually in the PAK
		if ( lstPakContents->Items[ itemIndex ]->SubItems[3]->Text == "Not in PAK" )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + lstPakContents->Items[ itemIndex ]->Text + "\" is not in the PAK file." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error UnPAK'ing files: " + Environment::NewLine + "\tFile \"" + lstPakContents->Items[ itemIndex ]->Text + "\" is not in the PAK file." );
			}
			continue;
		}

		// if the file already exists
		if ( File::Exists( unpakFolderBrowserDialog->SelectedPath + "\\" + lstPakContents->Items[ itemIndex ]->Text ) )
		{
			// we need to get the user's attention and ask them whether the want to overwrite the file before we continue
			System::Windows::Forms::DialogResult result = MessageBox::Show( "This folder already contains a file named '" + lstPakContents->Items[ itemIndex ]->Text + "'\nDo you want to replace it?",  "Confirm File Replace", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				// don't do anything. we'll keep going as if the file didn't already exist and the unpak function will overwrite it
			}
			else if ( result == System::Windows::Forms::DialogResult::No )
			{
				updateStatus();
				continue;
			}
			else // cancel or possibly closed dialog with X
			{
				lstPakContents->Enabled = true;
				btnPak->Visible = true;
				btnUnpak->Visible = true;
				menuPak->Visible = true;
				menuUnpak->Visible = true;
				menuPak->Enabled = true;
				menuUnpak->Enabled = true;
				menuCancel->Visible = false;
				menuCancel->Enabled = false;
				btnCancel->Visible = false;
				btnCheckAll->Enabled = true;
				btnCheckNone->Enabled = true;
				menuCheckAll->Enabled = true;
				menuCheckNone->Enabled = true;
				btnAddFiles->Enabled = true;
				btnBrowseDir->Enabled = true;
				btnDeleteSelected->Enabled = true;
				progressBar->Enabled = false;

				itemProgressed = 0;
				percentProg = 0;
				prog = CANCEL;
				updateStatus();
				return;
			}
		}

		string name, dir;
		MarshalString( unpakFolderBrowserDialog->SelectedPath + "\\" + lstPakContents->Items[ itemIndex ]->Text, dir );
		MarshalString( lstPakContents->Items[ itemIndex ]->Text, name );

		//pak.unPAKEntry( name, dir );

		ofstream f; //output

		char *buffer;
		buffer = pak.getPAKEntryData(name);
		int ofsize;
		ofsize = pak.getPAKEntrySize(name);
		if(buffer == NULL || ofsize <= 0)
		{
			//cout << "Critical error: Cannot find file listed in PAK\n";
			//system("pause");
			//return 1;
		}

		f.open(dir, ofstream::binary); // open in binary

		if (f.is_open())  // make sure it opened
		{
			f.write(buffer, ofsize); // write the buffer to the output file with the size of the original file
		}
		else
		{
			// to do: make an crash function to display error messages and such
			delete [] buffer;
			//cout << "Critical error: Output file could not be opened\n";
			//system("pause");
			//return 1;
		}

		updateStatus();

	}

	lstPakContents->Enabled = true;
	btnPak->Visible = true;
	btnUnpak->Visible = true;
	menuPak->Visible = true;
	menuUnpak->Visible = true;
	menuPak->Enabled = true;
	menuUnpak->Enabled = true;
	menuCancel->Visible = false;
	menuCancel->Enabled = false;
	btnCancel->Visible = false;
	btnCheckAll->Enabled = true;
	btnCheckNone->Enabled = true;
	menuCheckAll->Enabled = true;
	menuCheckNone->Enabled = true;
	btnAddFiles->Enabled = true;
	btnBrowseDir->Enabled = true;
	btnDeleteSelected->Enabled = true;
	progressBar->Enabled = false;

	prog = DONE;
	itemProgressed = 0;
	updateStatus();

	if ( errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		log->addBreak();
		if ( !log->Visible )
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				log->Visible = true;
			}
		}
	}
}

// This event occurs when the Browse button is hit to add an entire directory to the PAK
System::Void frmMain::btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e)
{
	if ( addFolderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::Cancel ) // This displays the folder selection dialog
	{
		return; // if the user didn't make a selection, then don't do anything
	}

	if ( addFolderBrowserDialog->SelectedPath->Length <= 0 ) // if the user didn't select any files
	{
		return;
	}

	array<String^> ^files = Directory::GetFiles( addFolderBrowserDialog->SelectedPath );

	bool errors = false;

	lstPakContents->BeginUpdate();
	for each ( String ^file in files )
	{
		// calc file size
		long long bytes = getFileBytes( file );
		string tmp;
		MarshalString( file->Substring( file->LastIndexOf('\\') + 1 ), tmp );
		if ( fileSizes[tmp] != 0 )
		{
			if ( errors )
			{
				log->displayMsg( "\tDuplicate file entry detected: \"" + file->Substring( file->LastIndexOf('\\') + 1 ) + "\"" );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tDuplicate file entry detected: \"" + file->Substring( file->LastIndexOf('\\') + 1 ) + "\"" );
			}
			continue;
		}
		fileSizes[tmp] = bytes;
		String ^size = getFileSize( bytes );
		if ( size == "0 KB" )
		{
			if ( errors )
			{
				log->displayMsg( "\tFile \"" + file->Substring( file->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			else
			{
				errors = true;
				log->displayMsg( "Error adding files: " + Environment::NewLine + "\tFile \"" + file->Substring( file->LastIndexOf('\\')+1 ) + "\" contains no data." );
			}
			continue;
		}

		// add an item with all the columns
		ListViewItem^ item = gcnew ListViewItem( file->Substring( file->LastIndexOf('\\') + 1 ) ); // create the item and give it name column
		item->SubItems->Add( file ); // directory column
		item->SubItems->Add( size ); // file size column
		item->SubItems->Add( "Not in PAK" ); // origin column. since you're manually adding the file, it can't already be in the pak
		if ( file->LastIndexOf('.') == -1 )
		{
			item->SubItems->Add( "" ); // extension column
		}
		else
		{
			item->SubItems->Add( file->Substring( file->LastIndexOf('.') ) ); // extension column
		}
		item->Checked = true; // defaults to checked. since you are manually adding the file, it's assumed that you want to include it in your pak
		lstPakContents->Items->Add( item ); // finally add the item to the list

	}
	lstPakContents->EndUpdate();

	if ( errors ) // if there were errors and the log isn't visible, warn them that there were errors and ask to display the log, otherwise we don't want to bug the user
	{
		log->addBreak();
		if ( !log->Visible )
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show( "There were errors performing the previous action. Would you like to view the error log?",  "Errors", MessageBoxButtons::YesNo, MessageBoxIcon::Error );
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
				log->Visible = true;
			}
		}
	}
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
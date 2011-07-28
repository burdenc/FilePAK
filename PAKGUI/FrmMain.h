#pragma once

namespace PAKGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for frmMain
	/// </summary>
	public ref class frmMain : public System::Windows::Forms::Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;








	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  btnUnpak;
	private: System::Windows::Forms::Button^  btnPak;







	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Button^  btnBrowseDir;
	private: System::Windows::Forms::Button^  btnAddDir;



	private: System::Windows::Forms::TextBox^  txtAddDir;
	private: System::Windows::Forms::CheckedListBox^  lstPakContents;
	private: System::Windows::Forms::ProgressBar^  progressBar;






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lblItemProg;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  lblPercentProg;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  stsLblStatus;

	private: System::Windows::Forms::ToolStripStatusLabel^  stsStatus;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  selectNoneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pAKToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  menuPak;
	private: System::Windows::Forms::ToolStripMenuItem^  menuUnpak;



	private: System::Windows::Forms::Button^  btnSelectNone;

	private: System::Windows::Forms::Button^  btnSelectAll;
	private: System::Windows::Forms::OpenFileDialog^  openPakDialog;


	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::Button^  btnAddFiles;

	private: System::Windows::Forms::Button^  btnDeleteSelected;




	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectNoneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pAKToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuPak = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuUnpak = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btnAddFiles = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSelected = (gcnew System::Windows::Forms::Button());
			this->btnSelectNone = (gcnew System::Windows::Forms::Button());
			this->btnSelectAll = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtAddDir = (gcnew System::Windows::Forms::TextBox());
			this->btnAddDir = (gcnew System::Windows::Forms::Button());
			this->btnBrowseDir = (gcnew System::Windows::Forms::Button());
			this->lstPakContents = (gcnew System::Windows::Forms::CheckedListBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->lblPercentProg = (gcnew System::Windows::Forms::Label());
			this->lblItemProg = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->btnUnpak = (gcnew System::Windows::Forms::Button());
			this->btnPak = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->stsLblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->stsStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openPakDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->menuStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->pAKToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Margin = System::Windows::Forms::Padding(10);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(820, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->toolStripMenuItem1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::openToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(149, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->selectAllToolStripMenuItem, 
				this->selectNoneToolStripMenuItem});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->selectAllToolStripMenuItem->Text = L"Select all";
			// 
			// selectNoneToolStripMenuItem
			// 
			this->selectNoneToolStripMenuItem->Name = L"selectNoneToolStripMenuItem";
			this->selectNoneToolStripMenuItem->Size = System::Drawing::Size(135, 22);
			this->selectNoneToolStripMenuItem->Text = L"Select none";
			// 
			// pAKToolStripMenuItem
			// 
			this->pAKToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->menuPak, 
				this->menuUnpak});
			this->pAKToolStripMenuItem->Name = L"pAKToolStripMenuItem";
			this->pAKToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->pAKToolStripMenuItem->Text = L"PAK";
			// 
			// menuPak
			// 
			this->menuPak->Enabled = false;
			this->menuPak->Name = L"menuPak";
			this->menuPak->Size = System::Drawing::Size(152, 22);
			this->menuPak->Text = L"PAK / RePAK";
			// 
			// menuUnpak
			// 
			this->menuUnpak->Enabled = false;
			this->menuUnpak->Name = L"menuUnpak";
			this->menuUnpak->Size = System::Drawing::Size(152, 22);
			this->menuUnpak->Text = L"UnPAK";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->btnAddFiles);
			this->groupBox2->Controls->Add(this->btnDeleteSelected);
			this->groupBox2->Controls->Add(this->btnSelectNone);
			this->groupBox2->Controls->Add(this->btnSelectAll);
			this->groupBox2->Controls->Add(this->groupBox1);
			this->groupBox2->Controls->Add(this->lstPakContents);
			this->groupBox2->Controls->Add(this->panel3);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(0, 24);
			this->groupBox2->Margin = System::Windows::Forms::Padding(10);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(10);
			this->groupBox2->Size = System::Drawing::Size(820, 529);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"PAK Contents";
			// 
			// btnAddFiles
			// 
			this->btnAddFiles->Location = System::Drawing::Point(207, 99);
			this->btnAddFiles->Name = L"btnAddFiles";
			this->btnAddFiles->Size = System::Drawing::Size(75, 23);
			this->btnAddFiles->TabIndex = 16;
			this->btnAddFiles->Text = L"Add file(s)";
			this->btnAddFiles->UseVisualStyleBackColor = true;
			// 
			// btnDeleteSelected
			// 
			this->btnDeleteSelected->Enabled = false;
			this->btnDeleteSelected->Location = System::Drawing::Point(288, 99);
			this->btnDeleteSelected->Name = L"btnDeleteSelected";
			this->btnDeleteSelected->Size = System::Drawing::Size(89, 23);
			this->btnDeleteSelected->TabIndex = 15;
			this->btnDeleteSelected->Text = L"Delete selected";
			this->btnDeleteSelected->UseVisualStyleBackColor = true;
			// 
			// btnSelectNone
			// 
			this->btnSelectNone->Location = System::Drawing::Point(91, 99);
			this->btnSelectNone->Name = L"btnSelectNone";
			this->btnSelectNone->Size = System::Drawing::Size(75, 23);
			this->btnSelectNone->TabIndex = 14;
			this->btnSelectNone->Text = L"Select none";
			this->btnSelectNone->UseVisualStyleBackColor = true;
			// 
			// btnSelectAll
			// 
			this->btnSelectAll->Location = System::Drawing::Point(10, 99);
			this->btnSelectAll->Name = L"btnSelectAll";
			this->btnSelectAll->Size = System::Drawing::Size(75, 23);
			this->btnSelectAll->TabIndex = 13;
			this->btnSelectAll->Text = L"Select all";
			this->btnSelectAll->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtAddDir);
			this->groupBox1->Controls->Add(this->btnAddDir);
			this->groupBox1->Controls->Add(this->btnBrowseDir);
			this->groupBox1->Location = System::Drawing::Point(10, 26);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(10);
			this->groupBox1->Size = System::Drawing::Size(800, 66);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Add Directory";
			// 
			// txtAddDir
			// 
			this->txtAddDir->Location = System::Drawing::Point(9, 23);
			this->txtAddDir->Name = L"txtAddDir";
			this->txtAddDir->Size = System::Drawing::Size(623, 20);
			this->txtAddDir->TabIndex = 8;
			// 
			// btnAddDir
			// 
			this->btnAddDir->Location = System::Drawing::Point(719, 19);
			this->btnAddDir->Name = L"btnAddDir";
			this->btnAddDir->Size = System::Drawing::Size(75, 27);
			this->btnAddDir->TabIndex = 9;
			this->btnAddDir->Text = L"Add";
			this->btnAddDir->UseVisualStyleBackColor = true;
			// 
			// btnBrowseDir
			// 
			this->btnBrowseDir->Location = System::Drawing::Point(638, 19);
			this->btnBrowseDir->Name = L"btnBrowseDir";
			this->btnBrowseDir->Size = System::Drawing::Size(75, 27);
			this->btnBrowseDir->TabIndex = 10;
			this->btnBrowseDir->Text = L"Browse";
			this->btnBrowseDir->UseVisualStyleBackColor = true;
			this->btnBrowseDir->Click += gcnew System::EventHandler(this, &frmMain::btnBrowseDir_Click);
			// 
			// lstPakContents
			// 
			this->lstPakContents->FormattingEnabled = true;
			this->lstPakContents->HorizontalScrollbar = true;
			this->lstPakContents->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"test 1", L"test2", L"test 4\tlksdf\tdslkfj", 
				L"how do add columns\?"});
			this->lstPakContents->Location = System::Drawing::Point(10, 128);
			this->lstPakContents->MultiColumn = true;
			this->lstPakContents->Name = L"lstPakContents";
			this->lstPakContents->ScrollAlwaysVisible = true;
			this->lstPakContents->Size = System::Drawing::Size(800, 334);
			this->lstPakContents->TabIndex = 11;
			this->lstPakContents->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &frmMain::lstPakContents_ItemCheck);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->lblPercentProg);
			this->panel3->Controls->Add(this->lblItemProg);
			this->panel3->Controls->Add(this->label2);
			this->panel3->Controls->Add(this->label1);
			this->panel3->Controls->Add(this->progressBar);
			this->panel3->Controls->Add(this->btnUnpak);
			this->panel3->Controls->Add(this->btnPak);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel3->Location = System::Drawing::Point(10, 476);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(800, 43);
			this->panel3->TabIndex = 5;
			// 
			// lblPercentProg
			// 
			this->lblPercentProg->AutoSize = true;
			this->lblPercentProg->Location = System::Drawing::Point(66, 3);
			this->lblPercentProg->Name = L"lblPercentProg";
			this->lblPercentProg->Size = System::Drawing::Size(24, 13);
			this->lblPercentProg->TabIndex = 6;
			this->lblPercentProg->Text = L"Idle";
			// 
			// lblItemProg
			// 
			this->lblItemProg->AutoSize = true;
			this->lblItemProg->Location = System::Drawing::Point(66, 20);
			this->lblItemProg->Name = L"lblItemProg";
			this->lblItemProg->Size = System::Drawing::Size(30, 13);
			this->lblItemProg->TabIndex = 5;
			this->lblItemProg->Text = L"0 / 0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Item:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Progress:";
			// 
			// progressBar
			// 
			this->progressBar->Enabled = false;
			this->progressBar->Location = System::Drawing::Point(118, 3);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(446, 37);
			this->progressBar->TabIndex = 2;
			// 
			// btnUnpak
			// 
			this->btnUnpak->Enabled = false;
			this->btnUnpak->Location = System::Drawing::Point(570, 0);
			this->btnUnpak->Name = L"btnUnpak";
			this->btnUnpak->Size = System::Drawing::Size(112, 43);
			this->btnUnpak->TabIndex = 1;
			this->btnUnpak->Text = L"UnPAK";
			this->btnUnpak->UseVisualStyleBackColor = true;
			// 
			// btnPak
			// 
			this->btnPak->Enabled = false;
			this->btnPak->Location = System::Drawing::Point(688, 0);
			this->btnPak->Name = L"btnPak";
			this->btnPak->Size = System::Drawing::Size(112, 43);
			this->btnPak->TabIndex = 0;
			this->btnPak->Text = L"PAK/RePAK";
			this->btnPak->UseVisualStyleBackColor = true;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->stsLblStatus, this->stsStatus});
			this->statusStrip1->Location = System::Drawing::Point(0, 553);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(820, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 9;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// stsLblStatus
			// 
			this->stsLblStatus->Name = L"stsLblStatus";
			this->stsLblStatus->Size = System::Drawing::Size(45, 17);
			this->stsLblStatus->Text = L"Status: ";
			// 
			// stsStatus
			// 
			this->stsStatus->Name = L"stsStatus";
			this->stsStatus->Size = System::Drawing::Size(26, 17);
			this->stsStatus->Text = L"Idle";
			// 
			// openPakDialog
			// 
			this->openPakDialog->DefaultExt = L"pak";
			this->openPakDialog->Filter = L"PAK files|*.pak|All files|*.*";
			this->openPakDialog->ShowHelp = true;
			this->openPakDialog->SupportMultiDottedExtensions = true;
			this->openPakDialog->Title = L"Open PAK file";
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->DefaultExt = L"pak";
			this->saveFileDialog->SupportMultiDottedExtensions = true;
			this->saveFileDialog->Title = L"Save PAK file";
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 575);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->statusStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(836, 613);
			this->MinimumSize = System::Drawing::Size(836, 613);
			this->Name = L"frmMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"pakGUI";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// This event occurs every time an item in the PAK Contents list is checked or unchecked.
	private: System::Void lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e)
			 {
				 /////////////////////////////
				 // Item Progress Label
				 /////////////////////////////
				 IEnumerator^ myEnum1 = lstPakContents->CheckedIndices->GetEnumerator(); // This is an enum for cycling through the checked items
				 int numChecked = 0; // The number of items checked
				 while ( myEnum1->MoveNext() )
				 {
					 if ( lstPakContents->GetItemChecked( *safe_cast<Int32^>(myEnum1->Current) ) )
					 {
						 ++numChecked;
					 }
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
					 btnDeleteSelected->Enabled = true; // "Delete Selected" button
					 menuPak->Enabled = true; // menu pak button
					 menuUnpak->Enabled = true; // menu unpak button
				 }
				 else if ( btnPak->Enabled || btnUnpak->Enabled || btnDeleteSelected->Enabled ) // Otherwise, disable them if they are enabled
				 {
					 btnPak->Enabled = false; // Pak button
					 btnUnpak->Enabled = false; // Unpak button
					 btnDeleteSelected->Enabled = false; // "Delete Selected" button
					 menuPak->Enabled = false; // menu pak button
					 menuUnpak->Enabled = false; // menu unpak button
				 }

				 lblItemProg->Text = "0 / " + numChecked; // Update the item progress label
				 /////////////////////////////
			 }

			 // This event occurs when the Browse button is hit to add an entire directory to the PAK
	private: System::Void btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 folderBrowserDialog->ShowDialog(); // This displays the folder selection dialog
				 txtAddDir->Text = folderBrowserDialog->SelectedPath; // This sets the text box to the resulting selection from the user
			 }

			 // This event occurs when the Open menu item is clicked
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 openPakDialog->ShowDialog();
			 }

			 // This event occurs when the New menu item is clicked
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
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
				 if ( lstPakContents->Items ) // if the contents list contains any items, this signifies that there is a PAK file open
				 {
					 // display a message box asking if the user is sure they want to lose their current pak work
					 System::Windows::Forms::DialogResult result = MessageBox::Show( "You currently have a PAK file open. If you make a new PAK file, any unsaved changes to the currently open PAK will be lost! Are you sure you want to make a new PAK file?", "PAK File already opened", MessageBoxButtons::YesNo, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button2 );
					 if ( result != System::Windows::Forms::DialogResult::Yes )
					 {
						 return;
					 }
				 }

				 // reset all items in the form to their original values
				 txtAddDir->Text = "";
				 lblItemProg->Text = "0 / 0";
				 btnUnpak->Enabled = false;
				 btnPak->Enabled = false;
				 btnDeleteSelected->Enabled = false;
				 menuPak->Enabled = false;
				 menuUnpak->Enabled = false;
				 // todo:
					// clear listbox

			 }
	};
}


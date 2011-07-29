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






	private: System::Windows::Forms::ProgressBar^  progressBar;






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lblItemProg;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  lblPercentProg;

	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  stsLblStatus;

	private: System::Windows::Forms::ToolStripStatusLabel^  stsStatus;


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
	private: System::Windows::Forms::ListView^  lstPakContents;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;

private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label5;


private: System::Windows::Forms::TextBox^  textBox1;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Button^  btnSaveBrowse;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::ColumnHeader^  columnHeader5;







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
			this->lstPakContents = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->btnAddFiles = (gcnew System::Windows::Forms::Button());
			this->btnBrowseDir = (gcnew System::Windows::Forms::Button());
			this->btnDeleteSelected = (gcnew System::Windows::Forms::Button());
			this->btnSelectNone = (gcnew System::Windows::Forms::Button());
			this->btnSelectAll = (gcnew System::Windows::Forms::Button());
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
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btnSaveBrowse = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->menuStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox1->SuspendLayout();
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
			this->newToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::openToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(100, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmMain::exitToolStripMenuItem_Click);
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
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->selectAllToolStripMenuItem->Text = L"Check all";
			// 
			// selectNoneToolStripMenuItem
			// 
			this->selectNoneToolStripMenuItem->Name = L"selectNoneToolStripMenuItem";
			this->selectNoneToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->selectNoneToolStripMenuItem->Text = L"Check none";
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
			this->menuPak->Size = System::Drawing::Size(142, 22);
			this->menuPak->Text = L"PAK / RePAK";
			// 
			// menuUnpak
			// 
			this->menuUnpak->Enabled = false;
			this->menuUnpak->Name = L"menuUnpak";
			this->menuUnpak->Size = System::Drawing::Size(142, 22);
			this->menuUnpak->Text = L"UnPAK";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lstPakContents);
			this->groupBox2->Controls->Add(this->btnAddFiles);
			this->groupBox2->Controls->Add(this->btnBrowseDir);
			this->groupBox2->Controls->Add(this->btnDeleteSelected);
			this->groupBox2->Controls->Add(this->btnSelectNone);
			this->groupBox2->Controls->Add(this->btnSelectAll);
			this->groupBox2->Location = System::Drawing::Point(14, 151);
			this->groupBox2->Margin = System::Windows::Forms::Padding(5);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(10);
			this->groupBox2->Size = System::Drawing::Size(792, 334);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"PAK Contents";
			// 
			// lstPakContents
			// 
			this->lstPakContents->AllowColumnReorder = true;
			this->lstPakContents->AllowDrop = true;
			this->lstPakContents->CheckBoxes = true;
			this->lstPakContents->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->columnHeader1, 
				this->columnHeader2, this->columnHeader5, this->columnHeader4, this->columnHeader3});
			this->lstPakContents->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lstPakContents->FullRowSelect = true;
			this->lstPakContents->Location = System::Drawing::Point(10, 58);
			this->lstPakContents->Name = L"lstPakContents";
			this->lstPakContents->Size = System::Drawing::Size(772, 266);
			this->lstPakContents->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->lstPakContents->TabIndex = 17;
			this->lstPakContents->UseCompatibleStateImageBehavior = false;
			this->lstPakContents->View = System::Windows::Forms::View::Details;
			this->lstPakContents->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &frmMain::lstPakContents_ItemCheck);
			this->lstPakContents->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &frmMain::lstPakContents_DragDrop);
			this->lstPakContents->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &frmMain::lstPakContents_DragOver);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"File name";
			this->columnHeader1->Width = 180;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Directory";
			this->columnHeader2->Width = 264;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Text = L"Size";
			this->columnHeader5->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->columnHeader5->Width = 105;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Currently in PAK\?";
			this->columnHeader4->Width = 111;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"File extension";
			this->columnHeader3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->columnHeader3->Width = 86;
			// 
			// btnAddFiles
			// 
			this->btnAddFiles->Location = System::Drawing::Point(205, 26);
			this->btnAddFiles->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->btnAddFiles->Name = L"btnAddFiles";
			this->btnAddFiles->Size = System::Drawing::Size(75, 23);
			this->btnAddFiles->TabIndex = 16;
			this->btnAddFiles->Text = L"Add file(s)";
			this->btnAddFiles->UseVisualStyleBackColor = true;
			// 
			// btnBrowseDir
			// 
			this->btnBrowseDir->Location = System::Drawing::Point(419, 26);
			this->btnBrowseDir->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->btnBrowseDir->Name = L"btnBrowseDir";
			this->btnBrowseDir->Size = System::Drawing::Size(94, 23);
			this->btnBrowseDir->TabIndex = 10;
			this->btnBrowseDir->Text = L"Add directory";
			this->btnBrowseDir->UseVisualStyleBackColor = true;
			this->btnBrowseDir->Click += gcnew System::EventHandler(this, &frmMain::btnBrowseDir_Click);
			// 
			// btnDeleteSelected
			// 
			this->btnDeleteSelected->Location = System::Drawing::Point(286, 26);
			this->btnDeleteSelected->Name = L"btnDeleteSelected";
			this->btnDeleteSelected->Size = System::Drawing::Size(100, 23);
			this->btnDeleteSelected->TabIndex = 15;
			this->btnDeleteSelected->Text = L"Delete highlighted";
			this->btnDeleteSelected->UseVisualStyleBackColor = true;
			// 
			// btnSelectNone
			// 
			this->btnSelectNone->Location = System::Drawing::Point(97, 26);
			this->btnSelectNone->Name = L"btnSelectNone";
			this->btnSelectNone->Size = System::Drawing::Size(75, 23);
			this->btnSelectNone->TabIndex = 14;
			this->btnSelectNone->Text = L"Check none";
			this->btnSelectNone->UseVisualStyleBackColor = true;
			this->btnSelectNone->Click += gcnew System::EventHandler(this, &frmMain::btnSelectNone_Click);
			// 
			// btnSelectAll
			// 
			this->btnSelectAll->Location = System::Drawing::Point(16, 26);
			this->btnSelectAll->Name = L"btnSelectAll";
			this->btnSelectAll->Size = System::Drawing::Size(75, 23);
			this->btnSelectAll->TabIndex = 13;
			this->btnSelectAll->Text = L"Check all";
			this->btnSelectAll->UseVisualStyleBackColor = true;
			this->btnSelectAll->Click += gcnew System::EventHandler(this, &frmMain::btnSelectAll_Click);
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
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(3, 16);
			this->panel3->Margin = System::Windows::Forms::Padding(10);
			this->panel3->Name = L"panel3";
			this->panel3->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->panel3->Size = System::Drawing::Size(786, 53);
			this->panel3->TabIndex = 5;
			// 
			// lblPercentProg
			// 
			this->lblPercentProg->AutoSize = true;
			this->lblPercentProg->Location = System::Drawing::Point(90, 8);
			this->lblPercentProg->Name = L"lblPercentProg";
			this->lblPercentProg->Size = System::Drawing::Size(24, 13);
			this->lblPercentProg->TabIndex = 6;
			this->lblPercentProg->Text = L"Idle";
			this->lblPercentProg->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// lblItemProg
			// 
			this->lblItemProg->AutoSize = true;
			this->lblItemProg->Location = System::Drawing::Point(86, 25);
			this->lblItemProg->Name = L"lblItemProg";
			this->lblItemProg->Size = System::Drawing::Size(30, 13);
			this->lblItemProg->TabIndex = 5;
			this->lblItemProg->Text = L"0 / 0";
			this->lblItemProg->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 25);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Item:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 8);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(51, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Progress:";
			// 
			// progressBar
			// 
			this->progressBar->Enabled = false;
			this->progressBar->Location = System::Drawing::Point(153, 8);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(385, 37);
			this->progressBar->TabIndex = 2;
			// 
			// btnUnpak
			// 
			this->btnUnpak->Enabled = false;
			this->btnUnpak->Location = System::Drawing::Point(544, 5);
			this->btnUnpak->Name = L"btnUnpak";
			this->btnUnpak->Size = System::Drawing::Size(112, 43);
			this->btnUnpak->TabIndex = 1;
			this->btnUnpak->Text = L"UnPAK";
			this->btnUnpak->UseVisualStyleBackColor = true;
			this->btnUnpak->Click += gcnew System::EventHandler(this, &frmMain::btnUnpak_Click);
			// 
			// btnPak
			// 
			this->btnPak->Enabled = false;
			this->btnPak->Location = System::Drawing::Point(662, 5);
			this->btnPak->Name = L"btnPak";
			this->btnPak->Size = System::Drawing::Size(112, 43);
			this->btnPak->TabIndex = 0;
			this->btnPak->Text = L"PAK/RePAK";
			this->btnPak->UseVisualStyleBackColor = true;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->stsLblStatus, this->stsStatus});
			this->statusStrip1->Location = System::Drawing::Point(0, 577);
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
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox3->Controls->Add(this->label9);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->btnSaveBrowse);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->textBox1);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Location = System::Drawing::Point(14, 30);
			this->groupBox3->Margin = System::Windows::Forms::Padding(5);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(10);
			this->groupBox3->Size = System::Drawing::Size(792, 111);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"PAK Info";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(662, 79);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(37, 13);
			this->label9->TabIndex = 10;
			this->label9->Text = L"0 Files";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(662, 54);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(30, 13);
			this->label8->TabIndex = 9;
			this->label8->Text = L"0 KB";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(662, 29);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(30, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"0 KB";
			// 
			// btnSaveBrowse
			// 
			this->btnSaveBrowse->Location = System::Drawing::Point(375, 48);
			this->btnSaveBrowse->Margin = System::Windows::Forms::Padding(3, 3, 3, 6);
			this->btnSaveBrowse->Name = L"btnSaveBrowse";
			this->btnSaveBrowse->Size = System::Drawing::Size(75, 23);
			this->btnSaveBrowse->TabIndex = 7;
			this->btnSaveBrowse->Text = L"Browse";
			this->btnSaveBrowse->UseVisualStyleBackColor = true;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(520, 79);
			this->label7->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(115, 13);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Number of files in PAK:";
			this->label7->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(492, 54);
			this->label6->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(143, 13);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Estimated Size after PAK\'ing:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(544, 29);
			this->label5->Margin = System::Windows::Forms::Padding(6, 6, 24, 6);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(91, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"PAK Size on disk:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(125, 51);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 3, 10, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(237, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 54);
			this->label3->Margin = System::Windows::Forms::Padding(3, 0, 10, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"PAK Save location:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->panel3);
			this->groupBox1->Location = System::Drawing::Point(14, 495);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(792, 72);
			this->groupBox1->TabIndex = 11;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"PAK";
			// 
			// frmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 599);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->statusStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(836, 637);
			this->MinimumSize = System::Drawing::Size(836, 637);
			this->Name = L"frmMain";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"pakGUI";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// This event occurs every time an item in the PAK Contents list is checked or unchecked.
	private: System::Void lstPakContents_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e);

			 // This event occurs when the Browse button is hit to add an entire directory to the PAK
	private: System::Void btnBrowseDir_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the Open menu item is clicked
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the New menu item is clicked
	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the user drags a file into the pak contents area
	private: System::Void lstPakContents_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
	private: System::Void lstPakContents_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
				 if(e->Data->GetDataPresent(DataFormats::FileDrop))
				 {
					 e->Effect = DragDropEffects::All;
				 }
				 else
				 {
					 e->Effect = DragDropEffects::None;
				 }
			 }

			 // This event occurs when the user clicks the Select all button
	private: System::Void btnSelectAll_Click(System::Object^  sender, System::EventArgs^  e);

			 // This event occurs when the user clicks the Select none button
	private: System::Void btnSelectNone_Click(System::Object^  sender, System::EventArgs^  e);

			 // exit menu item clicked
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 delete this;
			 }

			 // unpak button clicked
	private: System::Void btnUnpak_Click(System::Object^  sender, System::EventArgs^  e);
	};	

}


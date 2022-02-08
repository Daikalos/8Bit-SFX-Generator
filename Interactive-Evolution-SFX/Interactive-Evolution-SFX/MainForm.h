#pragma once

#include "SoundUC.h"
#include <iostream>
#include <tchar.h>

namespace Interactive_Evolution_SFX 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			
			if (!initialize_sounds())
				throw gcnew WarningException("sounds failed to load");
		}

	protected:
		~MainForm()
		{
			delete components;
			delete[] sounds;
		}

	protected:

	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::StatusStrip^ statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;

	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadButton;





	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Panel^ pnlItems;
	private: System::Windows::Forms::ToolStripMenuItem^ otherToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ creditsButton;
	private: System::Windows::Forms::ToolStripMenuItem^ helpButton;
	private: System::Windows::Forms::ToolStrip^ botStripTool;
	private: System::Windows::Forms::ToolStripButton^ showNextButton;


	private: System::Windows::Forms::ToolStripButton^ playButton;
	private: System::Windows::Forms::ToolStripButton^ pauseButton;

	private: System::Windows::Forms::ToolStripButton^ resetButton;

















	private: 
		array<SoundUC^>^ sounds;
		bool initialize_sounds();

		static const size_t row_count = 3;
		static const size_t column_count = 4;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->creditsButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->pnlItems = (gcnew System::Windows::Forms::Panel());
			this->botStripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->pauseButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showNextButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->resetButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->pnlItems->SuspendLayout();
			this->botStripTool->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip
			// 
			this->menuStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->optionsToolStripMenuItem,
					this->otherToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(784, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadButton });
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->optionsToolStripMenuItem->Text = L"File";
			// 
			// loadButton
			// 
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(100, 22);
			this->loadButton->Text = L"Load";
			this->loadButton->Click += gcnew System::EventHandler(this, &MainForm::loadButton_Click);
			// 
			// otherToolStripMenuItem
			// 
			this->otherToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->creditsButton,
					this->helpButton
			});
			this->otherToolStripMenuItem->Name = L"otherToolStripMenuItem";
			this->otherToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->otherToolStripMenuItem->Text = L"Help";
			// 
			// creditsButton
			// 
			this->creditsButton->Name = L"creditsButton";
			this->creditsButton->Size = System::Drawing::Size(127, 22);
			this->creditsButton->Text = L"Credits";
			// 
			// helpButton
			// 
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(127, 22);
			this->helpButton->Text = L"View Help";
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip->Location = System::Drawing::Point(0, 775);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->statusStrip->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->statusStrip->Size = System::Drawing::Size(784, 26);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 2;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->BackColor = System::Drawing::Color::White;
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(75, 21);
			this->toolStripStatusLabel1->Text = L"...Loading";
			// 
			// pnlItems
			// 
			this->pnlItems->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pnlItems->BackColor = System::Drawing::Color::Black;
			this->pnlItems->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pnlItems->Controls->Add(this->botStripTool);
			this->pnlItems->Location = System::Drawing::Point(90, 62);
			this->pnlItems->Margin = System::Windows::Forms::Padding(0);
			this->pnlItems->Name = L"pnlItems";
			this->pnlItems->Size = System::Drawing::Size(604, 590);
			this->pnlItems->TabIndex = 3;
			// 
			// botStripTool
			// 
			this->botStripTool->AutoSize = false;
			this->botStripTool->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->botStripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->botStripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->botStripTool->ImageScalingSize = System::Drawing::Size(36, 36);
			this->botStripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->playButton, this->pauseButton,
					this->showNextButton, this->resetButton
			});
			this->botStripTool->Location = System::Drawing::Point(0, 541);
			this->botStripTool->Name = L"botStripTool";
			this->botStripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->botStripTool->Size = System::Drawing::Size(600, 45);
			this->botStripTool->TabIndex = 0;
			this->botStripTool->Text = L"botStripTool";
			// 
			// playButton
			// 
			this->playButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->playButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playButton.Image")));
			this->playButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->playButton->Margin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(40, 41);
			this->playButton->Text = L"Play";
			this->playButton->ToolTipText = L"Play";
			this->playButton->Click += gcnew System::EventHandler(this, &MainForm::playButton_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->pauseButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pauseButton.Image")));
			this->pauseButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->pauseButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(40, 41);
			this->pauseButton->Text = L"Pause";
			this->pauseButton->ToolTipText = L"Pause";
			this->pauseButton->Click += gcnew System::EventHandler(this, &MainForm::pauseButton_Click);
			// 
			// showNextButton
			// 
			this->showNextButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->showNextButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->showNextButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showNextButton.Image")));
			this->showNextButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->showNextButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->showNextButton->Name = L"showNextButton";
			this->showNextButton->Size = System::Drawing::Size(40, 41);
			this->showNextButton->Text = L"Next";
			this->showNextButton->ToolTipText = L"Next";
			this->showNextButton->Click += gcnew System::EventHandler(this, &MainForm::showNextButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->resetButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->resetButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"resetButton.Image")));
			this->resetButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->resetButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(40, 41);
			this->resetButton->Text = L"Pause";
			this->resetButton->ToolTipText = L"Reset";
			this->resetButton->Click += gcnew System::EventHandler(this, &MainForm::resetButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(784, 801);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->menuStrip);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Arial Black", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->ImeMode = System::Windows::Forms::ImeMode::On;
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(8, 9, 8, 9);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"8-bit SFX Generator";
			this->TopMost = true;
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->pnlItems->ResumeLayout(false);
			this->botStripTool->ResumeLayout(false);
			this->botStripTool->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			SaveFileDialog saveFileDialog;
			saveFileDialog.Filter = "WAV File|*.wav";
			saveFileDialog.Title = "Load a sound file";
			saveFileDialog.ShowDialog();

			if (saveFileDialog.FileName != "")
			{

			}
		}
		private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{

		}
		private: System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{

		}
		private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{

		}
		private: System::Void showNextButton_Click(System::Object^ sender, System::EventArgs^ e) 
		{

		}
};
}

#pragma once

#include "SoundUC.h"
#include <iostream>

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
	private: System::Windows::Forms::Button^ playButton;
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








	private: 
		array<SoundUC^>^ sounds;
		bool initialize_sounds();

		static const size_t row_count = 3;
		static const size_t column_count = 4;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->creditsButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->pnlItems = (gcnew System::Windows::Forms::Panel());
			this->menuStrip->SuspendLayout();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(90, 632);
			this->playButton->Margin = System::Windows::Forms::Padding(0);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(134, 40);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
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
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// loadButton
			// 
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(180, 22);
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
			this->otherToolStripMenuItem->Size = System::Drawing::Size(49, 20);
			this->otherToolStripMenuItem->Text = L"Other";
			// 
			// creditsButton
			// 
			this->creditsButton->Name = L"creditsButton";
			this->creditsButton->Size = System::Drawing::Size(180, 22);
			this->creditsButton->Text = L"Credits";
			// 
			// helpButton
			// 
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(180, 22);
			this->helpButton->Text = L"Help";
			// 
			// statusStrip
			// 
			this->statusStrip->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip->Location = System::Drawing::Point(0, 735);
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
			this->pnlItems->Location = System::Drawing::Point(90, 88);
			this->pnlItems->Margin = System::Windows::Forms::Padding(0);
			this->pnlItems->Name = L"pnlItems";
			this->pnlItems->Size = System::Drawing::Size(604, 544);
			this->pnlItems->TabIndex = 3;
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(784, 761);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->playButton);
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
			this->RightToLeftLayout = true;
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Interactive Evolution SFX";
			this->TopMost = true;
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
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
};
}

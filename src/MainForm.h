//  ---------------------------------------------------------------------------
//  This file is part of the 8-Bit SFX Generator
//	Copyright (C) 2022 Tobias Garpenhall <tobiasgarpenhall@gmail.com>
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program. If not, see <http://www.gnu.org/licenses/>.
//  ---------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <tchar.h>

#include <resid/sid.h>
#include <msclr/marshal_cppstd.h>

#include "utilities.h"
#include "Player.h"
#include "SoundUC.h"
#include "InfoForm.h"
#include "Evolution.h"
#include "Heatmap.h"
#include "Config.h"

namespace IESFX
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;

	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			delete components;
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ loadButton;
	private: System::Windows::Forms::Panel^ pnlItems;
	private: System::Windows::Forms::ToolStripMenuItem^ otherToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpButton;
	private: System::Windows::Forms::ToolStrip^ botStripTool;
	private: System::Windows::Forms::ToolStripButton^ showNextButton;
	private: System::Windows::Forms::ToolStripButton^ playButton;
	private: System::Windows::Forms::ToolStripButton^ pauseButton;
	private: System::Windows::Forms::ToolStripButton^ resetButton;
	private: System::Windows::Forms::TrackBar^ mutationSizeSlider;
	private: System::Windows::Forms::Label^ mutationSizeTextLabel;
	private: System::Windows::Forms::Label^ mutationSizeLabel;
	private: System::Windows::Forms::TrackBar^ volumeSlider;
	private: System::Windows::Forms::ToolStripMenuItem^ saveButton;
	private: System::Windows::Forms::Panel^ volumePanel;
	private: System::Windows::Forms::Panel^ modifiersPanel;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::ToolStripButton^ evolveButton;
	private: System::Windows::Forms::ToolStripButton^ showPrevButton;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ mutationRateLabel;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TrackBar^ mutationRateSlider;
	private: System::Windows::Forms::ToolStripButton^ retryButton;
	private: System::Windows::Forms::Timer^ statusTimer;
	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::ToolStripLabel^ statusLabel;
	private: System::Windows::Forms::ToolStripLabel^ evolutionStatusLabel;
	private: System::ComponentModel::IContainer^ components;
	
#pragma region Windows Form Designer generated code
	private:
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otherToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpButton = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pnlItems = (gcnew System::Windows::Forms::Panel());
			this->botStripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->pauseButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showNextButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->showPrevButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->retryButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->resetButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->evolveButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->mutationSizeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->mutationSizeTextLabel = (gcnew System::Windows::Forms::Label());
			this->mutationSizeLabel = (gcnew System::Windows::Forms::Label());
			this->volumeSlider = (gcnew System::Windows::Forms::TrackBar());
			this->modifiersPanel = (gcnew System::Windows::Forms::Panel());
			this->volumePanel = (gcnew System::Windows::Forms::Panel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->mutationRateLabel = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->mutationRateSlider = (gcnew System::Windows::Forms::TrackBar());
			this->statusTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->evolutionStatusLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->menuStrip->SuspendLayout();
			this->pnlItems->SuspendLayout();
			this->botStripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->BeginInit();
			this->modifiersPanel->SuspendLayout();
			this->volumePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->BeginInit();
			this->toolStrip1->SuspendLayout();
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
			this->menuStrip->Size = System::Drawing::Size(675, 24);
			this->menuStrip->TabIndex = 1;
			this->menuStrip->Text = L"menuStrip";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->saveButton,
					this->loadButton
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->optionsToolStripMenuItem->Text = L"File";
			// 
			// saveButton
			// 
			this->saveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"saveButton.Image")));
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(100, 22);
			this->saveButton->Text = L"Save";
			this->saveButton->Click += gcnew System::EventHandler(this, &MainForm::saveButton_Click);
			// 
			// loadButton
			// 
			this->loadButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"loadButton.Image")));
			this->loadButton->Name = L"loadButton";
			this->loadButton->Size = System::Drawing::Size(100, 22);
			this->loadButton->Text = L"Load";
			this->loadButton->Click += gcnew System::EventHandler(this, &MainForm::loadButton_Click);
			// 
			// otherToolStripMenuItem
			// 
			this->otherToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->helpButton });
			this->otherToolStripMenuItem->Name = L"otherToolStripMenuItem";
			this->otherToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->otherToolStripMenuItem->Text = L"Help";
			// 
			// helpButton
			// 
			this->helpButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"helpButton.Image")));
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(99, 22);
			this->helpButton->Text = L"Help";
			this->helpButton->Click += gcnew System::EventHandler(this, &MainForm::helpButton_Click);
			// 
			// pnlItems
			// 
			this->pnlItems->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->pnlItems->BackColor = System::Drawing::Color::Black;
			this->pnlItems->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pnlItems->Controls->Add(this->botStripTool);
			this->pnlItems->Location = System::Drawing::Point(13, 36);
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
			this->botStripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->playButton, this->pauseButton,
					this->showNextButton, this->showPrevButton, this->retryButton, this->resetButton, this->evolveButton
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
			this->showNextButton->Margin = System::Windows::Forms::Padding(0, 2, 0, 2);
			this->showNextButton->Name = L"showNextButton";
			this->showNextButton->Size = System::Drawing::Size(40, 41);
			this->showNextButton->Text = L"Next";
			this->showNextButton->ToolTipText = L"Show Next Subset";
			this->showNextButton->Click += gcnew System::EventHandler(this, &MainForm::showNextButton_Click);
			// 
			// showPrevButton
			// 
			this->showPrevButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->showPrevButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->showPrevButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPrevButton.Image")));
			this->showPrevButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->showPrevButton->Margin = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->showPrevButton->Name = L"showPrevButton";
			this->showPrevButton->Size = System::Drawing::Size(40, 41);
			this->showPrevButton->Text = L"Prev";
			this->showPrevButton->ToolTipText = L"Show Previous Subset";
			this->showPrevButton->Click += gcnew System::EventHandler(this, &MainForm::showPrevButton_Click);
			// 
			// retryButton
			// 
			this->retryButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->retryButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->retryButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"retryButton.Image")));
			this->retryButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->retryButton->Margin = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->retryButton->Name = L"retryButton";
			this->retryButton->Size = System::Drawing::Size(40, 41);
			this->retryButton->Text = L"Retry";
			this->retryButton->ToolTipText = L"Retry";
			this->retryButton->Click += gcnew System::EventHandler(this, &MainForm::retryButton_Click);
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
			this->resetButton->Text = L"Reset";
			this->resetButton->ToolTipText = L"Reset";
			this->resetButton->Click += gcnew System::EventHandler(this, &MainForm::resetButton_Click);
			// 
			// evolveButton
			// 
			this->evolveButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->evolveButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->evolveButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"evolveButton.Image")));
			this->evolveButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->evolveButton->Margin = System::Windows::Forms::Padding(0, 2, 110, 2);
			this->evolveButton->Name = L"evolveButton";
			this->evolveButton->Size = System::Drawing::Size(40, 41);
			this->evolveButton->Text = L"Evolve";
			this->evolveButton->ToolTipText = L"Evolve";
			this->evolveButton->Click += gcnew System::EventHandler(this, &MainForm::evolveButton_Click);
			// 
			// mutationSizeSlider
			// 
			this->mutationSizeSlider->Location = System::Drawing::Point(-2, 30);
			this->mutationSizeSlider->Maximum = 200;
			this->mutationSizeSlider->Minimum = 1;
			this->mutationSizeSlider->Name = L"mutationSizeSlider";
			this->mutationSizeSlider->Size = System::Drawing::Size(327, 45);
			this->mutationSizeSlider->TabIndex = 4;
			this->mutationSizeSlider->TickFrequency = 2;
			this->mutationSizeSlider->Value = 14;
			this->mutationSizeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationSizeSlider_ValueChanged);
			this->mutationSizeSlider->Enter += gcnew System::EventHandler(this, &MainForm::mutationSizeSlider_Enter);
			// 
			// mutationSizeTextLabel
			// 
			this->mutationSizeTextLabel->AutoSize = true;
			this->mutationSizeTextLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mutationSizeTextLabel->ForeColor = System::Drawing::Color::Aqua;
			this->mutationSizeTextLabel->Location = System::Drawing::Point(1, 1);
			this->mutationSizeTextLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeTextLabel->Name = L"mutationSizeTextLabel";
			this->mutationSizeTextLabel->Size = System::Drawing::Size(128, 25);
			this->mutationSizeTextLabel->TabIndex = 6;
			this->mutationSizeTextLabel->Text = L"Mutation Size";
			// 
			// mutationSizeLabel
			// 
			this->mutationSizeLabel->AutoSize = true;
			this->mutationSizeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationSizeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->mutationSizeLabel->Location = System::Drawing::Point(129, 1);
			this->mutationSizeLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationSizeLabel->Name = L"mutationSizeLabel";
			this->mutationSizeLabel->Size = System::Drawing::Size(67, 25);
			this->mutationSizeLabel->TabIndex = 9;
			this->mutationSizeLabel->Text = L"- 7.0%";
			// 
			// volumeSlider
			// 
			this->volumeSlider->Location = System::Drawing::Point(-1, 39);
			this->volumeSlider->Margin = System::Windows::Forms::Padding(0);
			this->volumeSlider->Maximum = 50;
			this->volumeSlider->Name = L"volumeSlider";
			this->volumeSlider->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->volumeSlider->Size = System::Drawing::Size(45, 508);
			this->volumeSlider->TabIndex = 10;
			this->volumeSlider->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->volumeSlider->Value = 8;
			this->volumeSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::volumeSlider_ValueChanged);
			this->volumeSlider->Enter += gcnew System::EventHandler(this, &MainForm::volumeSlider_Enter);
			// 
			// modifiersPanel
			// 
			this->modifiersPanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->modifiersPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->modifiersPanel->Controls->Add(this->mutationSizeTextLabel);
			this->modifiersPanel->Controls->Add(this->mutationSizeSlider);
			this->modifiersPanel->Controls->Add(this->mutationSizeLabel);
			this->modifiersPanel->Location = System::Drawing::Point(13, 638);
			this->modifiersPanel->Name = L"modifiersPanel";
			this->modifiersPanel->Size = System::Drawing::Size(325, 66);
			this->modifiersPanel->TabIndex = 13;
			// 
			// volumePanel
			// 
			this->volumePanel->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->volumePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->volumePanel->Controls->Add(this->pictureBox2);
			this->volumePanel->Controls->Add(this->pictureBox1);
			this->volumePanel->Controls->Add(this->volumeSlider);
			this->volumePanel->Location = System::Drawing::Point(625, 36);
			this->volumePanel->Name = L"volumePanel";
			this->volumePanel->Size = System::Drawing::Size(43, 590);
			this->volumePanel->TabIndex = 14;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(3, 547);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(35, 35);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 12;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(3, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(35, 35);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->mutationRateLabel);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->mutationRateSlider);
			this->panel1->Location = System::Drawing::Point(345, 638);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(325, 66);
			this->panel1->TabIndex = 14;
			// 
			// mutationRateLabel
			// 
			this->mutationRateLabel->AutoSize = true;
			this->mutationRateLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->mutationRateLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->mutationRateLabel->Location = System::Drawing::Point(132, 1);
			this->mutationRateLabel->Margin = System::Windows::Forms::Padding(0);
			this->mutationRateLabel->Name = L"mutationRateLabel";
			this->mutationRateLabel->Size = System::Drawing::Size(67, 25);
			this->mutationRateLabel->TabIndex = 8;
			this->mutationRateLabel->Text = L"- 9.0%";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Aqua;
			this->label4->Location = System::Drawing::Point(1, 1);
			this->label4->Margin = System::Windows::Forms::Padding(0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(131, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Mutation Rate";
			// 
			// mutationRateSlider
			// 
			this->mutationRateSlider->Location = System::Drawing::Point(-1, 30);
			this->mutationRateSlider->Maximum = 200;
			this->mutationRateSlider->Minimum = 1;
			this->mutationRateSlider->Name = L"mutationRateSlider";
			this->mutationRateSlider->Size = System::Drawing::Size(325, 45);
			this->mutationRateSlider->TabIndex = 5;
			this->mutationRateSlider->TickFrequency = 2;
			this->mutationRateSlider->Value = 18;
			this->mutationRateSlider->ValueChanged += gcnew System::EventHandler(this, &MainForm::mutationRateSlider_ValueChanged);
			this->mutationRateSlider->Enter += gcnew System::EventHandler(this, &MainForm::mutationRateSlider_Enter);
			// 
			// statusTimer
			// 
			this->statusTimer->Enabled = true;
			this->statusTimer->Tick += gcnew System::EventHandler(this, &MainForm::statusTimer_Tick);
			// 
			// toolStrip1
			// 
			this->toolStrip1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->toolStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->statusLabel, this->evolutionStatusLabel });
			this->toolStrip1->Location = System::Drawing::Point(0, 716);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolStrip1->ShowItemToolTips = false;
			this->toolStrip1->Size = System::Drawing::Size(675, 25);
			this->toolStrip1->TabIndex = 15;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// statusLabel
			// 
			this->statusLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(80, 22);
			this->statusLabel->Text = L"Loading...";
			// 
			// evolutionStatusLabel
			// 
			this->evolutionStatusLabel->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->evolutionStatusLabel->Name = L"evolutionStatusLabel";
			this->evolutionStatusLabel->Size = System::Drawing::Size(154, 22);
			this->evolutionStatusLabel->Text = L"Gen: 10 | Quality: 50";
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(675, 741);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->volumePanel);
			this->Controls->Add(this->pnlItems);
			this->Controls->Add(this->menuStrip);
			this->Controls->Add(this->modifiersPanel);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Arial Black", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->ImeMode = System::Windows::Forms::ImeMode::On;
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStrip;
			this->Margin = System::Windows::Forms::Padding(8, 9, 8, 9);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"8-Bit SFX Generator";
			this->Activated += gcnew System::EventHandler(this, &MainForm::MainForm_Activated);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->pnlItems->ResumeLayout(false);
			this->botStripTool->ResumeLayout(false);
			this->botStripTool->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationSizeSlider))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeSlider))->EndInit();
			this->modifiersPanel->ResumeLayout(false);
			this->modifiersPanel->PerformLayout();
			this->volumePanel->ResumeLayout(false);
			this->volumePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mutationRateSlider))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void MainForm_Shown(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_Activated(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
		System::Void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void loadButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void pauseButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void evolveButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void retryButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void showPrevButton_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void showNextButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void mutationSizeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void mutationRateSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e);

		System::Void volumeSlider_ValueChanged(System::Object^ sender, System::EventArgs^ e);

		System::Void helpButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void statusTimer_Tick(System::Object^ sender, System::EventArgs^ e);

		System::Void mutationRateSlider_Enter(System::Object^ sender, System::EventArgs^ e);
		System::Void mutationSizeSlider_Enter(System::Object^ sender, System::EventArgs^ e);
		System::Void volumeSlider_Enter(System::Object^ sender, System::EventArgs^ e);

	public:
		double mutation_size();
		double mutation_rate();
		float volume();

	private:
		void player_next();
		void player_done();
		void player_update(Sound* sounds);

		bool ready();

		void update_status(String^ status);
		void us(String^ status);

		void update_evolution_status(String^ status);
		void ues(String^ status);

		void evolution_loop();

	private:
		bool initialize();

	private:
		delegate void update_status_del(String^ status);
		delegate void update_evolution_status_del(String^ status);

	private:
		int _prev, _step, _old_step;
		Color _color;

		array<SoundUC^>^ _soundUCs;
		InfoForm^ _info;

		Player^ _player;

		Thread^ _evolution_thread;
		Evolution* _evolution;

		volatile bool _run_evolution{false};
		volatile bool _shutdown{false};

		Player::callback_play^ play;
		Player::callback_done^ done;
		Player::callback_update^ update;
};
}

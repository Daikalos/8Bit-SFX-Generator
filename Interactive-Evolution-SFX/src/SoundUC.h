#pragma once

#include "Sound.h"
#include "Player.h"
#include "Evolution.h"

namespace IESFX
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	public ref class SoundUC : public System::Windows::Forms::UserControl
	{
	public:
		SoundUC(Player^ player, Evolution* evolution, size_t id)
		{
			InitializeComponent();

			_player = player;
			_evolution = evolution;
			_id = id;

			_selected = false;
		}

	protected:
		~SoundUC()
		{
			delete components;
		}

	public: System::Windows::Forms::DataVisualization::Charting::Chart^ soundWave;

	private: System::Windows::Forms::ToolStrip^ stripTool;
	private: System::Windows::Forms::ToolStripButton^ exportButton;
	private: System::Windows::Forms::ToolStripButton^ playButton;


	private: System::Windows::Forms::ToolStripLabel^ timeLabel;
	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::ToolStripLabel^ durationLabel;

	private: System::ComponentModel::IContainer^ components;




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SoundUC::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->stripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->playButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->exportButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->timeLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->durationLabel = (gcnew System::Windows::Forms::ToolStripLabel());
			this->soundWave = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->stripTool->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->BeginInit();
			this->SuspendLayout();
			// 
			// stripTool
			// 
			this->stripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->stripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->playButton, this->exportButton,
					this->timeLabel, this->durationLabel
			});
			this->stripTool->Location = System::Drawing::Point(0, 155);
			this->stripTool->Name = L"stripTool";
			this->stripTool->Padding = System::Windows::Forms::Padding(0);
			this->stripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->stripTool->Size = System::Drawing::Size(150, 25);
			this->stripTool->TabIndex = 0;
			this->stripTool->Text = L"stripTool";
			// 
			// playButton
			// 
			this->playButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->playButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playButton.Image")));
			this->playButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(23, 22);
			this->playButton->Text = L"Play";
			this->playButton->ToolTipText = L"Play";
			this->playButton->Click += gcnew System::EventHandler(this, &SoundUC::playButton_Click);
			// 
			// exportButton
			// 
			this->exportButton->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->exportButton->AutoToolTip = false;
			this->exportButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->exportButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->exportButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exportButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->exportButton->Margin = System::Windows::Forms::Padding(0, 1, 2, 2);
			this->exportButton->Name = L"exportButton";
			this->exportButton->Size = System::Drawing::Size(48, 22);
			this->exportButton->Text = L"Export";
			this->exportButton->Click += gcnew System::EventHandler(this, &SoundUC::exportButton_Click);
			// 
			// timeLabel
			// 
			this->timeLabel->AutoSize = false;
			this->timeLabel->BackColor = System::Drawing::SystemColors::Control;
			this->timeLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->timeLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->timeLabel->Margin = System::Windows::Forms::Padding(1, 1, 0, 2);
			this->timeLabel->Name = L"timeLabel";
			this->timeLabel->Size = System::Drawing::Size(27, 22);
			this->timeLabel->Text = L"0.1s";
			// 
			// durationLabel
			// 
			this->durationLabel->BackColor = System::Drawing::SystemColors::Control;
			this->durationLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->durationLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->durationLabel->Name = L"durationLabel";
			this->durationLabel->Size = System::Drawing::Size(35, 15);
			this->durationLabel->Text = L"/ 1.0s";
			// 
			// soundWave
			// 
			this->soundWave->BackSecondaryColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->soundWave->BorderSkin->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->soundWave->BorderSkin->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea4->AlignmentStyle = System::Windows::Forms::DataVisualization::Charting::AreaAlignmentStyles::Position;
			chartArea4->AxisX->InterlacedColor = System::Drawing::Color::Transparent;
			chartArea4->AxisX->IsLabelAutoFit = false;
			chartArea4->AxisX->IsMarginVisible = false;
			chartArea4->AxisX->LabelStyle->Enabled = false;
			chartArea4->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea4->AxisX->LineWidth = 0;
			chartArea4->AxisX->MajorGrid->Enabled = false;
			chartArea4->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea4->AxisX->MajorGrid->LineWidth = 2;
			chartArea4->AxisX->MajorTickMark->Enabled = false;
			chartArea4->AxisX->MinorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea4->AxisY->InterlacedColor = System::Drawing::Color::Transparent;
			chartArea4->AxisY->IsLabelAutoFit = false;
			chartArea4->AxisY->LabelStyle->Enabled = false;
			chartArea4->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea4->AxisY->LineWidth = 0;
			chartArea4->AxisY->MajorTickMark->Enabled = false;
			chartArea4->AxisY->Maximum = 16000;
			chartArea4->AxisY->MaximumAutoSize = 100;
			chartArea4->AxisY->Minimum = -16000;
			chartArea4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			chartArea4->BackImageAlignment = System::Windows::Forms::DataVisualization::Charting::ChartImageAlignmentStyle::Center;
			chartArea4->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			chartArea4->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Solid;
			chartArea4->BorderWidth = 2;
			chartArea4->InnerPlotPosition->Auto = false;
			chartArea4->InnerPlotPosition->Height = 99;
			chartArea4->InnerPlotPosition->Width = 99;
			chartArea4->InnerPlotPosition->X = 1;
			chartArea4->InnerPlotPosition->Y = 1;
			chartArea4->Name = L"ChartArea1";
			chartArea4->Position->Auto = false;
			chartArea4->Position->Height = 96;
			chartArea4->Position->Width = 96;
			chartArea4->Position->X = 2;
			chartArea4->Position->Y = 2;
			this->soundWave->ChartAreas->Add(chartArea4);
			this->soundWave->Dock = System::Windows::Forms::DockStyle::Fill;
			legend4->Enabled = false;
			legend4->Name = L"Legend1";
			this->soundWave->Legends->Add(legend4);
			this->soundWave->Location = System::Drawing::Point(0, 0);
			this->soundWave->Margin = System::Windows::Forms::Padding(0);
			this->soundWave->Name = L"soundWave";
			series4->BackSecondaryColor = System::Drawing::Color::Transparent;
			series4->BorderColor = System::Drawing::Color::Black;
			series4->BorderWidth = 2;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series4->Color = System::Drawing::Color::DodgerBlue;
			series4->Legend = L"Legend1";
			series4->Name = L"Sound";
			this->soundWave->Series->Add(series4);
			this->soundWave->Size = System::Drawing::Size(150, 155);
			this->soundWave->TabIndex = 2;
			this->soundWave->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SoundUC::soundWave_MouseDown);
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Tick += gcnew System::EventHandler(this, &SoundUC::timer_Tick);
			// 
			// SoundUC
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Controls->Add(this->soundWave);
			this->Controls->Add(this->stripTool);
			this->Name = L"SoundUC";
			this->Size = System::Drawing::Size(150, 180);
			this->stripTool->ResumeLayout(false);
			this->stripTool->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		void reset()
		{
			if (_selected)
			{
				_evolution->remove_model(_player[_id]->get());
				stripTool->BackColor = Color::White;

				_selected = false;
			}
		}
		void set_color(Color color)
		{
			if (InvokeRequired)
				Invoke(gcnew set_color_del(this, &SoundUC::sc), color);
			else
				sc(color);
		}
		void add_data(array<short>^ samples)
		{
			if (InvokeRequired)
				Invoke(gcnew add_data_del(this, &SoundUC::ad), samples);
			else
				ad(samples);
		}
		void set_time(float time, float duration)
		{
			if (InvokeRequired)
				Invoke(gcnew set_time_del(this, &SoundUC::st), time, duration);
			else
				st(time, duration);
		}

	private: 
		delegate void set_color_del(Color);
		delegate void add_data_del(array<short>^);
		delegate void set_time_del(float, float);

		void sc(Color color)
		{
			soundWave->BackColor = color;
		}
		void ad(array<short>^ samples)
		{
			soundWave->Series[0]->Points->DataBindY(samples);
		}
		void st(float time, float duration)
		{
			timeLabel->Text = String::Format(System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}", Decimal::Round(System::Decimal(time), 1)) + "s";
			durationLabel->Text = "/ " + String::Format(System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}", Decimal::Round(System::Decimal(duration), 1)) + "s";
		}

		System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!_player->active() || _player->position() != _id)
				_player->play(_id);
		}
		System::Void exportButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SaveFileDialog saveFileDialog;
			saveFileDialog.Filter = "WAV File|*.wav|TXT File|*.txt";
			saveFileDialog.Title = "Export";

			if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if (!_player[_id]->save(msclr::interop::marshal_as<std::string>(saveFileDialog.FileName)))
					MessageBox::Show("Could not export.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		System::Void soundWave_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if (e->Button != System::Windows::Forms::MouseButtons::Left)
				return;

			if (_selected = !_selected)
			{
				_evolution->add_model(_player[_id]->get());
				stripTool->BackColor = Color::CornflowerBlue;
			}
			else
			{
				_evolution->remove_model(_player[_id]->get());
				stripTool->BackColor = Color::White;
			}
		}
		System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			set_time(_player[_id]->time(), _player[_id]->duration());
		}

	private:
		size_t _id;

		Player^ _player;
		Evolution* _evolution;

		bool _selected;
};
}

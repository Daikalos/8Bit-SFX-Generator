#pragma once

namespace Interactive_Evolution_SFX 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class SoundUC : public System::Windows::Forms::UserControl
	{
	public:
		SoundUC(void)
		{
			InitializeComponent();
		}

	protected:
		~SoundUC()
		{
			delete components;
		}
	private: System::Windows::Forms::ToolStrip^ stripTool;
	protected:

	protected:
	private: System::Windows::Forms::ToolStripButton^ toolStripButton1;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::StatusStrip^ stripStatus;

	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ soundWave;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SoundUC::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->stripTool = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->stripStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->soundWave = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->stripTool->SuspendLayout();
			this->stripStatus->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->BeginInit();
			this->SuspendLayout();
			// 
			// stripTool
			// 
			this->stripTool->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stripTool->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->stripTool->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripButton1,
					this->toolStripSeparator1
			});
			this->stripTool->Location = System::Drawing::Point(0, 155);
			this->stripTool->Name = L"stripTool";
			this->stripTool->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->stripTool->Size = System::Drawing::Size(150, 25);
			this->stripTool->TabIndex = 0;
			this->stripTool->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// stripStatus
			// 
			this->stripStatus->Dock = System::Windows::Forms::DockStyle::Top;
			this->stripStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->stripStatus->Location = System::Drawing::Point(0, 0);
			this->stripStatus->Name = L"stripStatus";
			this->stripStatus->Size = System::Drawing::Size(150, 22);
			this->stripStatus->SizingGrip = false;
			this->stripStatus->TabIndex = 1;
			this->stripStatus->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(39, 17);
			this->toolStripStatusLabel1->Text = L"Name";
			// 
			// soundWave
			// 
			chartArea1->AxisX->IsLabelAutoFit = false;
			chartArea1->AxisX->LabelStyle->Enabled = false;
			chartArea1->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea1->AxisX->LineWidth = 0;
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->MajorTickMark->Enabled = false;
			chartArea1->AxisX->MinorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dot;
			chartArea1->AxisY->InterlacedColor = System::Drawing::Color::Silver;
			chartArea1->AxisY->IsInterlaced = true;
			chartArea1->AxisY->IsLabelAutoFit = false;
			chartArea1->AxisY->LabelStyle->Enabled = false;
			chartArea1->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea1->AxisY->LineWidth = 0;
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY->MajorTickMark->Enabled = false;
			chartArea1->AxisY->MaximumAutoSize = 100;
			chartArea1->BackColor = System::Drawing::Color::DimGray;
			chartArea1->Name = L"ChartArea1";
			this->soundWave->ChartAreas->Add(chartArea1);
			this->soundWave->Dock = System::Windows::Forms::DockStyle::Fill;
			this->soundWave->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->soundWave->Legends->Add(legend1);
			this->soundWave->Location = System::Drawing::Point(0, 22);
			this->soundWave->Margin = System::Windows::Forms::Padding(0);
			this->soundWave->Name = L"soundWave";
			series1->BackSecondaryColor = System::Drawing::Color::Transparent;
			series1->BorderColor = System::Drawing::Color::Black;
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Color = System::Drawing::Color::CornflowerBlue;
			series1->Legend = L"Legend1";
			series1->Name = L"Sound";
			this->soundWave->Series->Add(series1);
			this->soundWave->Size = System::Drawing::Size(150, 133);
			this->soundWave->TabIndex = 2;
			// 
			// SoundUC
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->Controls->Add(this->soundWave);
			this->Controls->Add(this->stripStatus);
			this->Controls->Add(this->stripTool);
			this->Name = L"SoundUC";
			this->Size = System::Drawing::Size(150, 180);
			this->stripTool->ResumeLayout(false);
			this->stripTool->PerformLayout();
			this->stripStatus->ResumeLayout(false);
			this->stripStatus->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->soundWave))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	};
}

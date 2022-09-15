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

#include "SoundUC.h"

using namespace IESFX;

System::Void SoundUC::playButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!_player->active() || _player->position() != _id)
		_player->play(_id);
}
System::Void SoundUC::exportButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog saveFileDialog;
	saveFileDialog.Filter = "WAV File|*.wav|TXT File|*.txt";
	saveFileDialog.Title = "Export";

	if (saveFileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (!_player[_id]->save(msclr::interop::marshal_as<std::string>(saveFileDialog.FileName)))
			MessageBox::Show("Could not export.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			MessageBox::Show("Sound effect was succesfully saved at:\n" + saveFileDialog.FileName, "Save", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
System::Void SoundUC::soundWave_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if (e->Button != System::Windows::Forms::MouseButtons::Left)
		return;

	if (_evolution->active())
	{
		MessageBox::Show("System is not ready yet.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (_selected = !_selected)
	{
		_evolution->add_model(_sound->get_gene());
		stripTool->BackColor = Color::LightBlue;
	}
	else
	{
		_evolution->remove_model(_sound->get_gene());
		stripTool->BackColor = Color::White;
	}
}
System::Void SoundUC::timer_Tick(System::Object^ sender, System::EventArgs^ e)
{
	st(_sound->time(), _sound->duration());
}

void SoundUC::reset()
{
	if (_selected)
	{
		_evolution->remove_model(_sound->get_gene());
		stripTool->BackColor = Color::White;

		_selected = false;
	}
}
void SoundUC::set_color(Color color)
{
	try
	{
		if (InvokeRequired)
			Invoke(gcnew set_color_del(this, &SoundUC::sc), color);
		else
			sc(color);
	}
	catch (ObjectDisposedException^ exception)
	{
		// annoying problem with race condition and shutdown
	}
}
void SoundUC::add_data(array<short>^ samples)
{
	if (InvokeRequired)
		Invoke(gcnew add_data_del(this, &SoundUC::ad), samples);
	else
		ad(samples);
}
void SoundUC::set_time(float time, float duration)
{
	if (InvokeRequired)
		Invoke(gcnew set_time_del(this, &SoundUC::st), time, duration);
	else
		st(time, duration);
}

void SoundUC::sc(Color color)
{
	soundWave->BackColor = color;
}
void SoundUC::ad(array<short>^ samples)
{
	soundWave->Series[0]->Points->DataBindY(samples);
}
void SoundUC::st(float time, float duration)
{
	timeLabel->Text = String::Format(System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}", Decimal::Round(System::Decimal(time), 1)) + "s";
	durationLabel->Text = "/ " + String::Format(System::Globalization::CultureInfo::InvariantCulture, "{0:0.0}", Decimal::Round(System::Decimal(duration), 1)) + "s";
}
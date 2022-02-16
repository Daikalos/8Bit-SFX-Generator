#include "MainForm.h"

using namespace IESFX;

bool MainForm::initialize()
{
	size_t size = row_count * column_count;

	_soundUCs = gcnew array<SoundUC^>(size);
	_player = gcnew Player(size);
	_evolution = new Evolution();

	for (size_t i = 0; i < size; ++i)
	{
		SoundUC^ soundUC = gcnew SoundUC(_player, _evolution, i);

		pnlItems->Controls->Add(soundUC);
		soundUC->Location = Point(soundUC->Width * (i % column_count), soundUC->Height * (i / column_count));

		_soundUCs[i] = soundUC;
	}

	return true;
}

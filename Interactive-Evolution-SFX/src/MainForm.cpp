#include "MainForm.h"

using namespace IESFX;

bool MainForm::initialize()
{
	std::vector<Sound>* sounds = new std::vector<Sound>(row_count * column_count);

	for (size_t i = 0; i < sounds->size(); ++i)
	{
		SoundUC^ soundUC = gcnew SoundUC(_player, i);

		pnlItems->Controls->Add(soundUC);
		soundUC->Location = Point(soundUC->Width * (i % column_count), soundUC->Height * (i / column_count));
	}

	_player = new Player(sounds);

	return true;
}

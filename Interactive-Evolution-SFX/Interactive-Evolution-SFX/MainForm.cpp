#include "MainForm.h"

using namespace Interactive_Evolution_SFX;

bool MainForm::initialize_sounds()
{
	sounds = gcnew array<SoundUC^>(4);

	for (int i = 0; i < (sizeof(sounds) / sizeof(SoundUC^)); ++i)
	{
		sounds[i] = gcnew SoundUC();

		pnlItems->Controls->Add(sounds[i]);
	}


	return false;
}

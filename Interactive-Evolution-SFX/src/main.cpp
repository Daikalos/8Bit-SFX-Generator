#include "MainForm.h"

#include <windows.h>

using namespace IESFX;

[STAThread]
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(true);
    Application::Run(gcnew MainForm());

    return 0;
}

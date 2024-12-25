#include <Windows.h>
#include "main.h"
#pragma comment( lib, "user32.lib" )

using namespace System;

[STAThread]

INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, INT ) {
	System::Windows::Forms::Application::Run( gcnew fxted::main() );
	return 1;
}
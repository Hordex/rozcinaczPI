#include "stdafx.h"
#include "Slicer.h"
#include <GL/glew.h>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Slicer();
	return 0;
}
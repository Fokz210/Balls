#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	for(;;) MessageBox(NULL, L"Привет!!", L"Оконная процедура", MB_OK);
	return NULL;
}

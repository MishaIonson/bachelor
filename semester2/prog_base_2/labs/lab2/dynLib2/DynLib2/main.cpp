#include "main.h"

// a sample exported function


void list_Spaces(struct list_s* list)
{
	int i;
	int number = 0;
	for (i = 0; i < list->length; i++)
	{
		if ((int)list->line[i] == 32)
		{
			number++;
		}
	}

	if (number > 5)
	{
		for (i = 0; i < list->length; i++)
		{
			if (list->line[i] == ' ')
			{
				list->line[i] = '_';
			}
		}
	}
}

void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}

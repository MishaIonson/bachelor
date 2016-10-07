#include "main.h"
void list_vowelChecking(struct list_s* list)
{
	int i;
	int vowels = 0;
	int consonant = 0;
	for (i = 0; i < list->length; i++)
	{
		if (((int)list->line[i] >= 97) && ((int)list->line[i] <= 122))
		{
			if (((int)list->line[i] == 97) || ((int)list->line[i] == 97 + 4) || ((int)list->line[i] == 97 + 8) || ((int)list->line[i] == 97 + 14) || ((int)list->line[i] == 97 + 20) )
				vowels++;
			else
				consonant++;
		}

	}
	if (vowels > consonant)
		printf("Vowels won. Long live for the Queen");
	else if (vowels < consonant)
		printf("Consonant won. Long live for the King");
	else
		printf("We need more competitions! It's draw");
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

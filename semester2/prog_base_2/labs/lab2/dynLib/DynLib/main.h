
#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "list.h"

int DLL_EXPORT compare(int a, int b);

void DLL_EXPORT list_vowelChecking(struct list_s* list);

#ifdef __cplusplus
}
#endif

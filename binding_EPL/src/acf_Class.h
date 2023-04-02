#ifndef ACF_E_CLASS_H_
#define ACF_E_CLASS_H_

#include "acf_Types.h"
#include <wtypes.h>

extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];

typedef struct _eclass_vfptr {
  DWORD dwVfTable;
  LPVOID pObject;
  LPVOID pCFuncs;
} ECLASS_VFPTR, *PECLASS_VFPTR;

DLL_EXPORTS(RegisterClass, void)(DWORD **pNewClass,int nType);

namespace eClass {

void Copy(void);

LPVOID __stdcall Alloc(int nSize);
void __stdcall memcpy(void *dest, void *src, int size);

LPVOID SetFunctionHookAddr(LPVOID lpSrcAddr, LPVOID lpHookAddr);

// Module Part
extern DWORD m_pVfTable_Environment;
extern DWORD m_pVfTable_Browser;
extern DWORD m_pVfTable_Profile;

extern DWORD m_pVfTable_NewWindowDelegate;

}  // namespace eClass

// EPL Class Struct
#define IMP_NEWECLASS(LocalName, Object, Vfptr, funcs) \
	ECLASS_VFPTR LocalName##T, *LocalName##TT, **LocalName; \
	LocalName##T.dwVfTable = Vfptr; \
	LocalName##T.pObject = (LPVOID)Object; \
	LocalName##T.pCFuncs = (LPVOID)funcs; \
	LocalName##TT = &LocalName##T; \
	LocalName = &LocalName##TT;

#endif
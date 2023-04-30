
#include "struct_class.h"

namespace eClass {

DWORD m_pVfTable_Environment;
DWORD m_pVfTable_Browser;
DWORD m_pVfTable_Profile;
DWORD m_pVfTable_NewWindowDelegate;
DWORD m_pVfTable_Value;
DWORD m_pVfTable_Binary;
DWORD m_pVfTable_Dictionary;
DWORD m_pVfTable_List;
DWORD m_pVfTable_CookieManager;
DWORD m_pVfTable_Frame;
DWORD m_pVfTable_AuthCallback;
DWORD m_pVfTable_MenuCallback;
DWORD m_pVfTable_MenuParams;
DWORD m_pVfTable_MenuModel;

}  // namespace eClass

DLL_EXPORTS(RegisterClass, void)(DWORD **pNewClass, EClassVTable nType) {
  DWORD dwVfptr = **pNewClass;
  if (dwVfptr != NULL) {
    switch (nType) {
      case EClassVTable::VT_ENVIRONMENT:
        eClass::m_pVfTable_Environment = dwVfptr;
        break;
      case EClassVTable::VT_BROWSER:
        eClass::m_pVfTable_Browser = dwVfptr;
        break;
      case EClassVTable::VT_PROFILE:
        eClass::m_pVfTable_Profile = dwVfptr;
        break;
      case EClassVTable::VT_NEWWINDOWDELEGATE:
        eClass::m_pVfTable_NewWindowDelegate = dwVfptr;
        break;
      case EClassVTable::VT_VALUE:
        eClass::m_pVfTable_Value = dwVfptr;
        break;
      case EClassVTable::VT_BINARY:
        eClass::m_pVfTable_Binary = dwVfptr;
        break;
      case EClassVTable::VT_DICTIONARY:
        eClass::m_pVfTable_Dictionary = dwVfptr;
        break;
      case EClassVTable::VT_LIST:
        eClass::m_pVfTable_List = dwVfptr;
        break;
      case EClassVTable::VT_COOKIEMANAGER:
        eClass::m_pVfTable_CookieManager = dwVfptr;
        break;
      case EClassVTable::VT_FRAME:
        eClass::m_pVfTable_Frame = dwVfptr;
        break;
      case EClassVTable::VT_AUTHCALLBACK:
        eClass::m_pVfTable_AuthCallback = dwVfptr;
        break;
      case EClassVTable::VT_MENUCALLBACK:
        eClass::m_pVfTable_MenuCallback = dwVfptr;
        break;
      case EClassVTable::VT_MENUPARAMS:
        eClass::m_pVfTable_MenuParams = dwVfptr;
        break;
      case EClassVTable::VT_MENUMODEL:
        eClass::m_pVfTable_MenuModel = dwVfptr;
        break;

      default:
        break;
    }
    dwVfptr += sizeof(DWORD);
    DWORD dwSrcAddr = *(DWORD *)dwVfptr;
    dwSrcAddr += 6;
    BYTE *pCoder = (BYTE *)dwSrcAddr;
    if (*pCoder != 0xE9)
      eClass::SetFunctionHookAddr((LPVOID)dwSrcAddr, eClass::Copy);
  }
}

__declspec(naked) void eClass::Copy(void) {
  __asm {
		mov esi, [esp];
		call Alloc;
		mov edi, eax;
		pop ecx;
		xchg ecx, esi;
		push ecx;
		push esi;
		push edi;
		call memcpy;
		push edi;
		lea eax, [esp];
		push esi;
		push eax;
		call[ebx + 8];
		pop eax;
		retn;
  }
}

LPVOID eClass::SetFunctionHookAddr(LPVOID lpSrcAddr, LPVOID lpHookAddr) {
  DWORD dwOldProtect;
  char *lSrcAddr = (char *)lpSrcAddr;
  ULONG nOffset = (*(ULONG *)&lSrcAddr[1]);
  ULONG pAddr = (DWORD)lpSrcAddr + nOffset;
  pAddr += 5;
  LPVOID lpSrcFunction = (LPVOID)pAddr;
  DWORD dwOffset = (DWORD)lpSrcAddr - (DWORD)lpHookAddr;
  dwOffset = ~dwOffset;
  dwOffset -= 4;
  if (VirtualProtectEx((HANDLE)-1, lSrcAddr, 5, PAGE_EXECUTE_READWRITE,
                       &dwOldProtect)) {
    lSrcAddr[0] = 0xE9;
    *(DWORD *)&lSrcAddr[1] = dwOffset;
    VirtualProtectEx((HANDLE)-1, lSrcAddr, 5, dwOldProtect, NULL);
  }
  return lpSrcFunction;
}

LPVOID __stdcall eClass::Alloc(int nSize) {
  return HeapAlloc(GetProcessHeap(), 0, nSize);
}

void __stdcall eClass::memcpy(void *dest, void *src, int size) {
  ::memcpy(dest, src, size);
}
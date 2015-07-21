#include "stdafx.h"
#include "Hooks.h"

#include <map>
using namespace std;





static bool SpyOnImplCalled = false;
static bool CatchRealAddress = false;

struct InfoRegistery
{
    map<unsigned, SpyInfo> SpyInfoMap;
    bool Init;
    InfoRegistery()
    {
        Init = true;
    }
    ~InfoRegistery()
    {
        Init = false;
    }

};

InfoRegistery gRegistery;

/*
template<>
void SpyOn<T> (T method)
{
    unsigned m = *((unsigned *)(&method));

    if (SpyInfoMap.find(m) == SpyInfoMap.end())
    {
        SpyInfoMap[m] = SpyInfo();
    }
}*/

void _stdcall SpyOnImpl(unsigned int address)
{
    SpyOnImplCalled = true;

    if (gRegistery.SpyInfoMap.find(address) == gRegistery.SpyInfoMap.end())
    {
        printf("spying on: 0x%X\n", address);
        gRegistery.SpyInfoMap[address] = SpyInfo();
    }

}

void SpyOnVirtual(unsigned int address, FakeObject* obj)
{
    unsigned vtbl = *(unsigned*)obj;
    typedef void (FakeObject::*FF)();
    FF pr = *((FF *)&address);
    CatchRealAddress = true;
    (obj->*pr)();
    CatchRealAddress = false;


}


void _stdcall HandleHook(unsigned retAddress)
{
    if (!gRegistery.Init) return;

    unsigned callAddress = retAddress - 5;
    map<unsigned, SpyInfo>::iterator it;

    it = gRegistery.SpyInfoMap.find(callAddress);

    if (it != gRegistery.SpyInfoMap.end())
    {
        it->second.calls_count++;
    }
}

void DumpCalls()
{
    if (!gRegistery.Init) return;

    for (auto it : gRegistery.SpyInfoMap)
    {
        printf("address: 0x%X  calls: %d\n", it.first, it.second.calls_count);
    }
}



extern "C" void __declspec(naked) _cdecl _penter(void)
{
    static bool inCall = false;
    _asm
    {
        push eax
        push ecx
        push edx
    }
    if (!inCall && SpyOnImplCalled && gRegistery.Init)
    {
        inCall = true;
        if (CatchRealAddress)
        {
            _asm
            {
                mov ecx, [esp + 0Ch]
                sub ecx, 5
                push ecx
                call SpyOnImpl

            }

        }

        else
        {

            _asm
            {
                push[esp + 0Ch]
                call HandleHook

            }
        }

        inCall = false;
    }

    _asm
    {

        pop edx
        pop ecx
        pop eax
    }
    if (!inCall && CatchRealAddress)
        _asm add esp, 4

        _asm ret

    }

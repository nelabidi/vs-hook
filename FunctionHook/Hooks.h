#pragma once


struct SpyInfo
{
    unsigned calls_count;
    SpyInfo() : calls_count(0) {}
};

struct FakeObject
{
    void Method() {}
};


template<typename T>
void SpyOn(T method)
{
    extern void _stdcall SpyOnImpl(unsigned int address);

    unsigned m = *((unsigned *)(&method));
    SpyOnImpl(m);
}

template<typename C, typename M>
void SpyOnV(C &obj, M method)
{
    extern void SpyOnVirtual(unsigned int address, FakeObject * obj);

    unsigned m = *((unsigned *)(&method));

    SpyOnVirtual(m, (FakeObject*) &obj);

}


void DumpCalls();

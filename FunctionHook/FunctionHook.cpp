// FunctionHook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Hooks.h"

using namespace std;




class A
{
public:
    int M1(int arg)
    {
        cout << "Called A::M1 with this=" << this << " arg: " << arg << endl;
        return 0;
    }
    virtual int M2(int arg)
    {
        cout << "Called A::M2 with this=" << this << " arg: " << arg << endl;
        return 0;
    }

};

class B : public A
{
public:
    virtual int M2(int arg)
    {
        cout << "Called B::M2 with this=" << this << " arg: " << arg << endl;
        return 0;
    }
    virtual int M3(int arg)
    {
        cout << "Called B::M3 with this=" << this << " arg: " << arg << endl;
        return 0;
    }

};


#if 0
template <typename F >
struct Proto
{
    Proto(F p) : ptr(p) {}
    F ptr;
};

//typedef A::M1 m1;

//Proto<A::M1> p1;

//T=int (__thiscall A::* )(int)
struct NullType
{
    void m() {}
};
template<typename C, typename M>
void CallMe(M m, C& pthis)
{
    typedef void ( NullType::*voidf)(void);
    Proto<M> pr(m);
    C* ppthis = &pthis;

    printf("%X , %X , %X\n", m, &m, pr.ptr);
    //cout << &m << " "  << endl;
    //(ppthis->*m)(0);
}
#endif


template <typename M, typename C >
void TT(M m, C *p )
{
    unsigned u =  *(unsigned*)p;
}


int _tmain(int argc, _TCHAR* argv[])
{
    A a;
    B b;
    A *pa = &b;

    SpyOn(&A::M1);
    SpyOn(&A::M2);
    SpyOn(&B::M1);
    //SpyOn(&B::M2);
    //SpyOn(&B::M3);
    //unsigned u = (unsigned *) & ((b.M2));
    //TT(&B::M2, &b);
    SpyOnV(a, &A::M2);
    SpyOnV(b, &B::M2);
    SpyOnV(b, &B::M3);

    a.M1(1);
    a.M2(2);

    b.M1(3);
    b.M2(4);

    pa->M1(5);
    pa->M2(6);

    b.M3(7);


    DumpCalls();

    return 0;
}





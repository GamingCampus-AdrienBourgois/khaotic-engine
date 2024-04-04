#include "pch.h"
#include "Translate.h"
#if __has_include("Translate.g.cpp")
#include "Translate.g.cpp"
#endif

namespace winrt::enginecustom::implementation
{
    int32_t Translate::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Translate::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}

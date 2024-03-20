#include "pch.h"
#include "Color.h"
#if __has_include("Color.g.cpp")
#include "Color.g.cpp"
#endif

namespace winrt::enginecustom::implementation
{
    int32_t Color::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Color::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}

#pragma once

#include "Color.g.h"

namespace winrt::enginecustom::implementation
{
    struct Color : ColorT<Color>
    {
        Color() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::enginecustom::factory_implementation
{
    struct Color : ColorT<Color, implementation::Color>
    {
    };
}

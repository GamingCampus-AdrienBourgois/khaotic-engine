#pragma once

#include "Translate.g.h"

namespace winrt::enginecustom::implementation
{
    struct Translate : TranslateT<Translate>
    {
        Translate() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::enginecustom::factory_implementation
{
    struct Translate : TranslateT<Translate, implementation::Translate>
    {
    };
}

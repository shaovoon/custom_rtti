# C++ Custom RTTI

This tip presents a intrusive custom RTTI class which provides better performance than `dynamic_cast`. This class is found in the [Real-Time 3D Rendering with DirectX and HLSL](http://www.varcholik.org/wpress/directx-book/) by Paul Varcholik. Benchmark shows 10x performance lead over `dynamic_cast`. For those who may not be familiar, `dynamic_cast` is used in C++ to do downcast to derived class. For upcast to base class generally do not need any explicit casting. Runtime Type Information (RTTI) must be enabled in the compiler to use `dynamic_cast`.

```
Benchmark under VC2010 Windows
     DynamicCast: 1266ms
          AsCast:  127ms
```

Below shows the entire `RTTI` class which other class needs to be inherited from. User has to define `RTTI_DECLARATIONS` macro inside their class.

```Cpp
#pragma once

#include <string>

namespace Library
{
    class RTTI
    {
    public:
        virtual const size_t TypeIdInstance() const = 0;
        
        virtual RTTI* QueryInterface(const size_t)
        {
            return nullptr;
        }
        virtual const RTTI* QueryInterface(const size_t) const
        {
            return nullptr;
        }

        virtual bool Is(const size_t id) const
        {
            return false;
        }

        virtual bool Is(const std::string& name) const
        {
            return false;
        }

        template <typename T>
        T* As() 
        {
            if (Is(T::TypeIdClass()))
            {
                return (T*)this;
            }

            return nullptr;
        }
        template <typename T>
        const T* As() const
        {
            if (Is(T::TypeIdClass()))
            {
                return (T*)this;
            }

            return nullptr;
        }
    };

#define RTTI_DECLARATIONS(Type, ParentType)                            \
    public:                                                            \
        static std::string TypeName() { return std::string(#Type); }   \
        virtual const size_t TypeIdInstance() const                    \
        { return Type::TypeIdClass(); }                                \
        static const size_t TypeIdClass()                              \
        { static int d = 0; return (size_t) &d; }                      \
        virtual Library::RTTI* QueryInterface( const size_t id )       \
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return (RTTI*)this; }                                \
            else                                                       \
                { return ParentType::QueryInterface(id); }             \
        }                                                              \
        virtual const Library::RTTI* QueryInterface( const size_t id ) const \
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return (RTTI*)this; }                                \
            else                                                       \
                { return ParentType::QueryInterface(id); }             \
        }                                                              \
        virtual bool Is(const size_t id) const                         \
        {                                                              \
            if (id == TypeIdClass())                                   \
                { return true; }                                       \
            else                                                       \
                { return ParentType::Is(id); }                         \
        }                                                              \
        virtual bool Is(const std::string& name) const                 \
        {                                                              \
            if (name == TypeName())                                    \
                { return true; }                                       \
            else                                                       \
                { return ParentType::Is(name); }                       \
        }                                                              
}
```

The trick to uniquely identify a class is by using address of a local static member which should be unique. Credit:Andrew Fedoniouk aka [c-smile](http://www.codeproject.com/script/Membership/View.aspx?mid=129567).

```Cpp
static const size_t TypeIdClass()
{ static int d = 0; return (size_t) &d; }
```

The usage difference between `dynamic_cast` and `As()` member is shown below

```Cpp
Parallelogram* p = dynamic_cast<Parallelogram*>(vec[i]);

Parallelogram* p = vec[i]->As<Parallelogram>();
```

As the reader may notice `As()` function do C style cast instead of `reinterpret_cast`. The compiler will complain of using `reinterpret_cast` in a `const` member function.

```Cpp
template <typename T>
const T* As() const
{
    if (Is(T::TypeIdClass()))
    {
        return (T*)this;
    }

    return nullptr;
}
```

For those who want to use this class in C++98, just change `nullptr` to `NULL`. __Note:__ this class does not work in multiple inheritance if more than 1 base class derive from it. Source code is hosted at [Github](https://github.com/shaovoon/custom_rtti).

## History

* __2015-12-31__: Initial release
* __2016-01-02__: Replaced `sRunTimeTypeId` with a static local variable, so the class is "header only" and Makefile is fixed.


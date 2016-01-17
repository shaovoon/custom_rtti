# custom_rtti
C++ Custom RTTI Class

* [Article](http://www.codeproject.com/Tips/1068171/Cplusplus-Custom-RTTI)

*Version 0.1*: 10x perf on VC, Clang and GCC (Have to define RTTI_DEFINITIONS in cpp)
```cpp
#pragma once

#include <string>

namespace Library
{
    class RTTI
    {
    public:
        virtual const size_t& TypeIdInstance() const = 0;
        
        virtual RTTI* QueryInterface(const size_t) const
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
        T* As() const
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
        virtual const size_t& TypeIdInstance() const                   \
        { return Type::TypeIdClass(); }                                \
        static  const size_t& TypeIdClass() { return sRunTimeTypeId; } \
        virtual Library::RTTI* QueryInterface( const size_t id ) const \
        {                                                              \
            if (id == sRunTimeTypeId)                                  \
                { return (RTTI*)this; }                                \
            else                                                       \
                { return ParentType::QueryInterface(id); }             \
        }                                                              \
        virtual bool Is(const size_t id) const                         \
        {                                                              \
            if (id == sRunTimeTypeId)                                  \
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
        }                                                              \
   private:                                                            \
        static size_t sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type) \
    size_t Type::sRunTimeTypeId = (size_t)& Type::sRunTimeTypeId;
}
```

*Version 0.2*: 12x perf on VC, and 6x on Clang and GCC (No need to define RTTI_DEFINITIONS in cpp)
```cpp
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


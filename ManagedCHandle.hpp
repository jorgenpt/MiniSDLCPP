/* Copyright (C) 2014 Jørgen P. Tjernø <jorgenpt@gmail.com>
 * MiniSDLCPP is licensed under the zlib license, which can be found in the LICENSE file.
 */

#pragma once

#include <cstddef>

#if __cplusplus <= 199711L
# define JPT_CXX11 0
# define JPT_DELETE
# warning You should be using a C++11 compiler with this file.
#else
# define JPT_CXX11 1
# define JPT_DELETE = delete
#endif

#if defined(_MSC_VER)
# define JPT_ALIGNED(x) __declspec(align(x))
# include <intrin.h>
#else
# define JPT_ALIGNED(x) __attribute__ ((aligned(x)))
#endif

namespace jpt
{
    /* Helper class to wrap a given Type in atomic operations. */
    template<typename Type>
    class AtomicAccess
    {
        public:
            AtomicAccess(Type value)
                : mValue(value)
            {
            }

            Type set(Type newValue);
            Type get();
        private:
            Type JPT_ALIGNED(8) mValue;
    };

    /* Class that wraps some type and calls Cleanup on it when the object
     * expires.
     */
    template<typename Handle, void (*Cleanup)(Handle)>
    class ManagedCHandle
    {
    public:
        ManagedCHandle()
            : mHandle((Handle)0)
            , mCleanup(Cleanup)
        {
        }

        ManagedCHandle(Handle handle)
            : mHandle(handle)
            , mCleanup(Cleanup)
        {
        }

        ~ManagedCHandle()
        {
            reset((Handle)0);
        }

        /* Take over the given handle, cleaning up any current handle first. */
        void reset(Handle handle)
        {
            Handle oldHandle = mHandle.set(handle);
            if (oldHandle)
                mCleanup(oldHandle);
        }

        /* Give up ownership of our handle, so that the caller takes responsibility
         * for cleaning it up.
         */
        Handle detach()
        {
            return mHandle.set((Handle)0);
        }

        /* Access the handle. */
        Handle get() { return mHandle.get(); }
        /* Cast operator that returns the handle. */
        operator Handle() { return get(); }

    #if JPT_CXX11
        /* Move constructor that takes over the handle. */
        ManagedCHandle(ManagedCHandle&& other)
            : mHandle(other.detach())
            , mCleanup(Cleanup)
        {
        }

        /* Move assignment operator that takes over the handle. */
        ManagedCHandle& operator=(ManagedCHandle&& other)
        {
            reset(other.detach());
            return *this;
        }
    #endif

    private:
        AtomicAccess<Handle> mHandle;
        void (*const mCleanup)(Handle);

    private:
        /* Copy constructor is inaccessible and (under C++11) deleted. */
        ManagedCHandle(const ManagedCHandle& other) JPT_DELETE;
        /* Copy assignment operator is inaccessible and (under C++11) deleted. */
        ManagedCHandle& operator=(const ManagedCHandle& other) JPT_DELETE;
    };

    /* The following implementations are slightly modified versions of functions
     * from SDL_atomics.h.
     *
     * Differences:
     *  - Arbitrary types (<= 8 bytes.)
     *  - No Mac specific atomic operations (use compiler builtins.)
     *  - Fewer operations supported.
     */
    template<typename Type>
    bool atomicCAS(Type* ptr, Type oldVal, Type newVal)
    {
        #if defined(_MSC_VER)
            static_assert(sizeof(Type) <= sizeof(__int64), "Atomic access only supports 64bit (or smaller) handles.");
            return (_InterlockedCompareExchange64((__int64*)ptr, (__int64)newVal, (__int64)oldVal) == (__int64)oldVal);
        #else
            return __sync_bool_compare_and_swap(ptr, oldVal, newVal);
        #endif
    }

    template<typename Type>
    Type AtomicAccess<Type>::set(Type newValue)
    {
        #if defined(_MSC_VER)
            static_assert(sizeof(Type) <= sizeof(__int64), "Atomic access only supports 64bit (or smaller) handles.");
            return (Type)_InterlockedExchange64((__int64)&mValue, newValue);
        #else
            return __sync_lock_test_and_set(&mValue, newValue);
        #endif
    }

    template<typename Type>
    Type AtomicAccess<Type>::get()
    {
        Type value;
        do { value = mValue; } while (!atomicCas(&mValue, value, value));
        return value;
    }
}

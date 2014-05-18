/* Copyright (C) 2014 Jørgen P. Tjernø <jorgenpt@gmail.com>
 * Licensed under the MIT license, which can be found in the LICENSE file.
 */

#pragma once

#include <cstddef>

#if __cplusplus <= 199711L
# define JPT_CXX11 0
# define JPT_DELETE
# define JPT_NULL NULL
# warning You should be using a C++11 compiler with this file.
#else
# define JPT_CXX11 1
# define JPT_DELETE = delete
# define JPT_NULL nullptr
#endif

namespace jpt
{
    template<typename Handle, void (*Cleanup)(Handle)>
    class ManagedCHandle
    {
    public:
        ManagedCHandle()
            : mHandle(JPT_NULL)
            , mCleanup(Cleanup)
        {
        }

        ManagedCHandle(Handle handle)
            : mHandle(handle)
            , mCleanup(Cleanup)
        {
        }

    #if JPT_CXX11
        ManagedCHandle(ManagedCHandle&& other)
            : mHandle(other.detach())
            , mCleanup(Cleanup)
        {
        }
    #endif

        ~ManagedCHandle()
        {
            reset(JPT_NULL);
        }

        /* Take over the given handle, cleaning up any current handle first. */
        void reset(Handle handle)
        {
            if (mHandle)
                mCleanup(mHandle);

            mHandle = handle;
        }

        /* Give up ownership of our handle, so that the caller takes responsibility
         * for cleaning it up.
         */
        Handle detach()
        {
            Handle data = mHandle;
            mHandle = JPT_NULL;
            return data;
        }

        /* Access the handle. */
        Handle get() { return mHandle; }
        const Handle get() const { return mHandle; }

        /* Cast operators that return the handle. */
        operator const Handle() const { return get(); }
        operator Handle() { return get(); }

    #if JPT_CXX11
        /* Move constructor that takes over the handle. */
        ManagedCHandle& operator=(ManagedCHandle&& other)
        {
            reset(other.detach());
            return *this;
        }
    #endif

    private:
        Handle mHandle;
        void (*const mCleanup)(Handle);

    private:
        /* Copy constructor is inaccessible and (under C++11) deleted. */
        ManagedCHandle(const ManagedCHandle& other) JPT_DELETE;
        /* Copy assignment operator is inaccessible and (under C++11) deleted. */
        ManagedCHandle& operator=(const ManagedCHandle& other) JPT_DELETE;
    };
}

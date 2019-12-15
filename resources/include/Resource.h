#pragma once

#include <blitzcommon/DataType.h>

namespace blitz
{
    using ResourceID = uint32;

	class Resource
	{
	public:
        virtual ~Resource() = default;
    };
	
	// TODO this should have copy/move constructors/operators
    class ResourcePtr
    {
      public:
        explicit ResourcePtr(ResourceID id, Resource* ptr);

        ResourceID getID() const;
        Resource* getResourcePtr() const;

        void setResourcePtr(Resource* resourcePtr);

        virtual ~ResourcePtr();
        void operator delete(void* p);

      private:
        ResourceID id;
        Resource* resourcePtr;
    };
} // namespace blitz
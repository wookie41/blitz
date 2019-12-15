#include <Resource.h>
#include <cassert>

namespace blitz
{
    ResourcePtr::ResourcePtr(ResourceID id, Resource* ptr) : id(id), resourcePtr(ptr) {}
    
	ResourceID ResourcePtr::getID() const { return id; }

    Resource* ResourcePtr::getResourcePtr() const
	{
        return resourcePtr;
	}

	void ResourcePtr::setResourcePtr(Resource* resourcePtr)
	{
        assert(this->resourcePtr == nullptr);
		this->resourcePtr = resourcePtr;
	}

    ResourcePtr::~ResourcePtr()
    {
    	delete resourcePtr;
    }

    void ResourcePtr::operator delete(void* p)
    {
        auto resource = (ResourcePtr*)(p);
        Resource* tmp = resource->resourcePtr;
        resource->resourcePtr = nullptr;
        delete tmp;
    }
}

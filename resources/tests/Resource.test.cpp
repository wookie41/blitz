#include <RefCountedResourceManager.h>
#include <ResourceLoader.h>
#include <catch2/catch.hpp>
#include <fakeit/fakeit.hpp>


SCENARIO("Shared resource scenario")
{
    using namespace blitz;
    using namespace fakeit;

    class MockedResource : public Resource
    {
    public:
        explicit MockedResource(ResourceID id) : Resource(id) {}
        ~MockedResource() override = default;

        void operator delete(void*) {}
    };

    ResourceID resourceID = 2;
    auto resource = new MockedResource(resourceID);
    Mock<MockedResource> mockedResource(*resource);

    When(Dtor(mockedResource)).Do([]() {});

    ResourcePtr resourcePtr(&mockedResource.get());

    {
        ResourcePtr resourceCopy(resourcePtr);

        {
            ResourcePtr resourceCopy2(nullptr);
            resourceCopy2 = resourcePtr;
        }
    }

    Verify(Dtor(mockedResource)).Exactly(1);
}

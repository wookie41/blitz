#include <resources/RefCountedResourceManager.h>
#include <resources/ResourceLoader.h>
#include <catch2/catch.hpp>
#include <fakeit/fakeit.hpp>

SCENARIO("Basic resource loading scenario")
{
    using namespace blitz;
    using namespace fakeit;


    class MockedResource
    {
    public:
        explicit MockedResource(ResourceID id) {};
        virtual ~MockedResource() = default;
    };


    RefCountedResourceManager<MockedResource>  resourceManager;

    GIVEN("a resource loader")
    {
        ResourceID resourceID = 2;
        Mock<MockedResource> mockedResource;
        Mock<ResourceLoader<MockedResource>> mockedResourceLoader;

        When(Method(mockedResourceLoader, getID)).AlwaysReturn(resourceID);
        When(Method(mockedResourceLoader, load)).Return(&mockedResource.get());

        WHEN("a ask the resource manager to load the resource")
        {
            auto loadedResourceID = resourceManager.loadResource(&mockedResourceLoader.get());
            THEN("it gets loaded") { REQUIRE(loadedResourceID == resourceID); }

            AND_WHEN("i ask to load the resource one more time")
            {
                auto loadedResourceID2 = resourceManager.loadResource(&mockedResourceLoader.get());
                THEN("the resource id is returned, but the loader is not called again")
                {
                    REQUIRE(loadedResourceID2 == resourceID);
                    Verify(Method(mockedResourceLoader, load)).Exactly(1);
                }
            }
        }
    }
}
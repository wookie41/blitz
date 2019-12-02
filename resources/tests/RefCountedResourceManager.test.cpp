#include <RefCountedResourceManager.h>
#include <ResourceLoader.h>
#include <catch.hpp>
#include <fakeit.hpp>

SCENARIO("Basic resource loading scenario")
{
    using namespace blitz;
    using namespace fakeit;

    RefCountedResourceManager resourceManager;

    GIVEN("a resource loader")
    {
        ResourceID resourceID = 2;
        Mock<Resource> mockedResource;
        Mock<ResourceLoader> mockedResourceLoader;

        When(Method(mockedResourceLoader,getID)).Return(resourceID);
        When(Method(mockedResourceLoader,load)).Return(&mockedResource.get());

        WHEN("a ask the resource manager to load the resource")
        {
            auto loadedResourceID = resourceManager.loadResource(&mockedResourceLoader.get());
            THEN("it gets loaded") { REQUIRE(loadedResourceID == resourceID); }
        }
    }
}

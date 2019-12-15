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
        Mock<ResourcePtr> mockedResource;
        Mock<ResourceLoader> mockedResourceLoader;

        When(Method(mockedResourceLoader, getID)).Return(resourceID);
        When(Method(mockedResourceLoader, load)).Return(&mockedResource.get());

        WHEN("a ask the resource manager to load the resource")
        {
            auto loadedResourceID = resourceManager.loadResource(&mockedResourceLoader.get());
            THEN("it gets loaded") { REQUIRE(loadedResourceID == resourceID); }
        }
    }
}

SCENARIO("ResourcePtr gets freed after it's released by all of it's clients")
{
    using namespace blitz;
    using namespace fakeit;

    RefCountedResourceManager resourceManager;
    ResourceID loadedResourceID;
    ResourcePtr resourcePtr;

    GIVEN("a resource loader")
    {
        ResourceID resourceID = 2;
        Mock<ResourcePtr> mockedResource;
        Mock<ResourceLoader> mockedResourceLoader;

        When(Method(mockedResourceLoader, getID)).Return(resourceID);
        When(Method(mockedResourceLoader, load)).Return(&mockedResource.get());

        WHEN("a ask the resource manager to load the resource")
        {
            loadedResourceID = resourceManager.loadResource(&mockedResourceLoader.get());
            THEN("it gets loaded") { REQUIRE(loadedResourceID == resourceID); }
            AND_WHEN("i ask for the resource")
            {
                resourcePtr = resourceManager.getResource(loadedResourceID);
                THEN("i get the resource") { REQUIRE(resourcePtr->getID() == loadedResourceID); }
                AND_WHEN("the last client releases the resource")
                {
                    std::weak_ptr<ResourcePtr> weakPtr(resourcePtr);
                    resourcePtr.reset();
                    THEN("the resource gets freed") { REQUIRE(weakPtr.expired()); };
                }
            }

        }
    }
}

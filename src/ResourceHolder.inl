#include <assert.h>

template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder() {}

template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder() {
    if (mInstance != nullptr) {
        delete mInstance;
    }
}

template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>* ResourceHolder<Resource, Identifier>::mInstance = nullptr;

template<typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>* ResourceHolder<Resource, Identifier>::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new ResourceHolder();
    }
    return mInstance;
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    // Create and load resource
    Ptr resource(new Resource());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder<Resource, Identifier>::load - Failed to load " + filename);
    }
    // If loading successful, insert resource to map
    insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *(found->second);
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = mResourceMap.find(id);
    return *(found->second);
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, Ptr resource) {
    // Insert and check success
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}
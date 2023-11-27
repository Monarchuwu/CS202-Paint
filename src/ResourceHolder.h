#pragma once
#include <map>
#include <memory>
#include <string>
#include <cassert>
#include <stdexcept>

template<typename Resource, typename Identifier>
class ResourceHolder {
    typedef std::unique_ptr<Resource> Ptr;

private:
    ResourceHolder();
    ~ResourceHolder();

public:
    static ResourceHolder<Resource, Identifier>* getInstance();

    // Make sure that the resource is not already loaded before
    // If it is already loaded, it will throw an exception
    void load(Identifier id, const std::string& filename);
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insertResource(Identifier id, Ptr resource);

private:
    static ResourceHolder<Resource, Identifier>* mInstance;
    std::map<Identifier, Ptr> mResourceMap;
};

#include "ResourceHolder.inl"
template<typename Resource,typename identifier>
 void ResourceHolder<Resource, identifier>::load(identifier id, const std::string &filename){

    std::unique_ptr<Resource> resource(new Resource());

    if(!resource->loadFromFile(filename)){
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
 }

template <typename Resource, typename identifier>
template <typename Parameter>
 void ResourceHolder<Resource, identifier>::load(identifier id,
      const std::string& filename, const Parameter& secondParam)
      {
         std::unique_ptr<Resource> resource(new Resource());
         if (!resource->loadFromFile(filename, secondParam)){
            throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
         }

         auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
         assert(inserted.second);
     
   }

 template <typename Resource, typename identifier>
  Resource& ResourceHolder<Resource, identifier>::get(identifier id){

    auto found = mResourceMap.find(id);

    assert(found != mResourceMap.end());

    return *found->second;

 }

 template <typename Resource, typename identifier>
  const Resource& ResourceHolder<Resource, identifier>::get(identifier id) const{

    auto found = mResourceMap.find(id);

    assert(found != mResourceMap.end());

    return *found->second;

 }
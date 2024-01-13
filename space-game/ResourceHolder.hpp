template <typename Resource , typename identifier >
class ResourceHolder
{
    public : 
        void load(identifier id, const std::string &filename);
        template <typename Parameter>
        void load(identifier id, const std::string& filename,const Parameter& secondParam);

        Resource& get(identifier id);
        const Resource& get(identifier id) const;

    private :
        std::map<identifier , std::unique_ptr<Resource>> mResourceMap;    

};

#include "ResourceHolder.inl"
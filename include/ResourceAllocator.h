#ifndef ResourceAllocator_h
#define ResourceAllocator_h

#include <map>
#include <memory>
#include <string>

template <class T>
class ResourceAllocator {

public:

    bool Has(int id){ return (Get(id) != nullptr); }

    int Add(const std::string& filePath){

        // Check if the resource was loaded previously.
        auto it = resources.find(filePath);
        if(it != resources.end()){ return it->second.first; }

        // Check if the path is a valid resource.
        std::shared_ptr<T> resource = std::make_shared<T>();
        if(!resource->loadFromFile(filePath)) { return 1; }

        // Add the resource to the resources' container.
        resources.insert(std::make_pair(filePath, std::make_pair(currentID, resource)));

        return currentID++;

    }

    void Remove(int id){

        for (auto it = resources.begin(); it != resources.end(); it++) {
            if(it->second.first == id) { resources.erase(id); }
        }
    }

    std::shared_ptr<T> Get(int id){

        for (auto it = resources.begin(); it != resources.end(); it++) {
            if(it->second.first == id) { return it->second.second; }
        }

        return nullptr;
    }

private:

    int currentID;
    std::map<std::string, std::pair<int, std::shared_ptr<T>>> resources;

};


#endif // ResourceAllocator_h

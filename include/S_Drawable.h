#ifndef S_Drawable_h
#define S_Drawable_h

#include "C_Drawable.h"
#include "Object.h"

class S_Drawable {

public:

    void Add(std::vector<std::shared_ptr<Object>>& object);

    void ProcessRemovals();

    void Draw(Window& window);

private:

    void Add(std::shared_ptr<Object> object);
    void Sort();
    static bool LayerSort(const std::shared_ptr<C_Drawable>& a, const std::shared_ptr<C_Drawable>& b);

    std::map<DrawLayer, std::vector<std::shared_ptr<C_Drawable>>> drawables;

};


#endif // S_Drawable_h

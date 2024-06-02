#ifndef C_Drawable_h
#define C_Drawable_h

#include <SFML/Graphics.hpp>

#include "Window.h"

class C_Drawable {

public:

    C_Drawable();
    virtual ~C_Drawable();

    virtual void Draw(Window& window) = 0;

    void SetOrder(int order);
    int GetSortOrder() const;

private:

    int sortOrder;

};


#endif // C_Drawable_h

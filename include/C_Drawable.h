#ifndef C_Drawable_h
#define C_Drawable_h

#include <SFML/Graphics.hpp>

#include "Window.h"

enum class DrawLayer{
    Default,
    Background,
    Foreground,
    Entities
};

class C_Drawable {

public:

    C_Drawable();
    virtual ~C_Drawable() = default;

    virtual void Draw(Window& window) = 0;
    virtual bool ContinueToDraw() const = 0;

    void SetOrder(size_t order);
    [[nodiscard]] size_t GetSortOrder() const;

    void SetDrawLayer(DrawLayer drawLayer);
    [[nodiscard]] DrawLayer GetDrawLayer() const;

private:

    size_t sortOrder;
    DrawLayer layer;

};


#endif // C_Drawable_h

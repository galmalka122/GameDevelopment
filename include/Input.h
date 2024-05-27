#ifndef Input_h
#define Input_h

#include <SFML/Graphics.hpp>
#include "Bitmask.h"

class Input {

public:

    enum class Key{

        None = 0,
        Left,
        Right,
        Up,
        Down,
        Esc

    };

    Input() = default;

    void Update();

    // Returns true if the key is pressed.
    bool IsKeyPressed(Key keycode);

    // Returns true if the key was just pressed.
    bool IsKeyDown(Key keycode);

    // Returns true if the key was just released.
    bool IsKeyUp(Key keycode);

private:

    Bitmask thisFrameKeys;
    Bitmask lastFrameKeys;

};


#endif //Input_h

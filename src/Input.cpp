#include "Input.h"

void Input::Update() {

    lastFrameKeys.SetMask(thisFrameKeys);

    thisFrameKeys.SetBit((int)Key::Left,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)));

    thisFrameKeys.SetBit((int)Key::Right,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)));

    thisFrameKeys.SetBit((int)Key::Up,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)));

    thisFrameKeys.SetBit((int)Key::Down,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) ||
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)));

    thisFrameKeys.SetBit((int)Key::Esc,
                         sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape));

}


bool Input::IsKeyPressed(Input::Key keycode) {

    return thisFrameKeys.GetBit((int)keycode);

}

bool Input::IsKeyDown(Input::Key keycode) {

    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return thisFrame && !lastFrame;

}

bool Input::IsKeyUp(Input::Key keycode) {

    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);

    return !thisFrame && lastFrame;

}

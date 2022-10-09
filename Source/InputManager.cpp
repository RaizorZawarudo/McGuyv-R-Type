
#include "InputManager.hpp"


RL::InputManager::InputManager(std::string name)
{
    this->_name = name;
}

RL::InputManager::~InputManager()
{
}


// -4 = UP ; -3 = LEFT ; -2 = DOWN ; -1 = RIGHT
void RL::InputManager::recordInputs()
{
    char pressedKey = GetCharPressed();
    if (pressedKey != 0)
        this->_inputQueue.emplace_back(pressedKey);

    if (IsKeyDown(KEY_W))
        this->_inputQueue.emplace_back('w');
    if (IsKeyDown(KEY_S))
        this->_inputQueue.emplace_back('s');
    if (IsKeyDown(KEY_A))
        this->_inputQueue.emplace_back('a');
    if (IsKeyDown(KEY_D))
        this->_inputQueue.emplace_back('d');
    if (IsKeyDown(KEY_SPACE))
        this->_inputQueue.emplace_back(32);
        if (IsKeyDown(KEY_ENTER))
        this->_inputQueue.emplace_back("ascii code of enter");
    //std::this_thread::sleep_for(std::chrono::milliseconds(100)); // This should change
}


void RL::InputManager::popInputs()
{
    if (!this->_inputQueue.empty())
        this->_inputQueue.clear();
}

bool RL::InputManager::playerHasPressedKeyAsChar(int key)
{
    for (int i = 0; i < this->_inputQueue.size(); i++) {
            if (this->_inputQueue[i]== key)
                return true;
    }
    return false;        
}

std::vector<int> RL::InputManager::getInputs()
{
    return this->_inputQueue;
}


Vector2 RL::InputManager::getMousePosition()
{
    Vector2 mousePosition = GetMousePosition();
    return mousePosition;
}

bool RL::InputManager::isMouseLeftClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    // Need click position
}

bool RL::InputManager::isMouseRightClicked()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    // Need click position
}
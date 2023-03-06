/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

InputSystem::~InputSystem()
{
}

void InputSystem::update(std::vector<EntityID> &allEntities)
{
     //clear all the inputs from the 
    _inputManager->recordInputs();
    // for (int i = 0; i < _inputManager->getInputs().size(); i++)
    //         std::cout << _inputManager->getInputs()[i] << std::endl;
    // send data to server functions
    //networking GETINPUTS OF OTHER PLAYERS
    _keysPressed = _inputManager->getInputs(); // add the recording of other players inputs to the vector of vector of keypressed ( change type from int to struct containing an id + the vector of ints)
    for (EntityID _ent:  EntityViewer<Input, Owner>(*_em.get()) ) {
        if (_em->Get<Owner>(_ent)->id == _clientID && _em->Get<EntityModelType>(_ent)->modelType == RL::ModelType::SPACESHIP)
            _em->Get<Input>(_ent)->_inputQueue = _keysPressed;
    }

}

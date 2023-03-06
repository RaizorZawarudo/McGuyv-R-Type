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
    // send data to server functions
    //networking GETINPUTS OF OTHER PLAYERS
    _keysPressed = _inputManager->getInputs(); // add the recording of other players inputs to the vector of vector of keypressed ( change type from int to struct containing an id + the vector of ints)
    for (EntityID _ent:  EntityViewer<Input, Owner>(*_em.get()) ) {
        if (_em->Get<Owner>(_ent)->id == 0 && _em->Get<EntityModelType>(_ent)->modelType == RL::ModelType::SPACESHIP)
            _em->Get<Input>(_ent)->_inputQueue = _keysPressed;
    }

    //instead of the above for loop, we serialise our input with our ID and send it to serve
    //INSERT SERIALISATION
    //INSERT UDP

}
/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DrawingSystem
*/

#include "ISystem.hpp"
#include "DrawingSystem.hpp"


DrawingSystem::DrawingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::CameraManager> cameraManager, std::shared_ptr<RL::Window> window)
: _renderer(renderer) ,_assetManager(assetManager), _cameraManager(cameraManager), _window(window)
{
    _em = em;
}

DrawingSystem::~DrawingSystem()
{
}

void DrawingSystem::update(std::vector<EntityID> &allEntities)
{
    EntityID clientplayerID;
    _renderer->beginDrawing();
        _renderer->clearBackground();

        _renderer->drawBackground(_assetManager, _assetManager->getCurrentMapBeingPlayed());

        _renderer->begin3DMode(_cameraManager->getCamera());

            _renderer->drawMap( _assetManager->getMaps().at(_assetManager->getCurrentMapBeingPlayed()), _cameraManager->getCamera(), _assetManager);

            for (EntityID _ent:  EntityViewer<Position, EntityModelType>(*_em.get()) ) {
                Position *objectPos = _em->Get<Position>(_ent);
                ModelName *objectModelName = _em->Get<ModelName>(_ent);
                EntityModelType *modelType = _em->Get<EntityModelType>(_ent);
                ModelScale *modelScale = _em->Get<ModelScale>(_ent);
                Owner *owner = _em->Get<Owner>(_ent);
                PitchYawRoll *pitchYawRoll = _em->Get<PitchYawRoll>(_ent);
                int maxFrame;

                //find the player of this client and store his id for UI display later (score etc etc)
                if (modelType->modelType == RL::ModelType::SPACESHIP && owner->id == _assetManager->getCurrentClientID()) {
                    clientplayerID = _ent;
                }
                //update the animation of the model before printing it if its a explosion
                if (modelType->modelType == RL::ModelType::EXPLOSION) {
                    AnimationData* animData = _em->Get<AnimationData>(_ent);
                    maxFrame = _assetManager->getSpecificDrawableWithType(objectModelName->modelname, modelType->modelType)->updateModelsAnimation(animData->currentFrame, animData->currentAnim);
                    animData->currentFrame <= maxFrame? animData->currentFrame++ : _em->Get<IsAlive>(_ent)->alive = false;
                    std::cout << animData->currentFrame << " is the current frame of explosion and maxFrame is = " << maxFrame << std::endl;
                }
                //draw shield depending on shield health
                if (_em->Get<Shield>(_ent) && _em->Get<Shield>(_ent)->shieldActive && _em->Get<Shield>(_ent)->shield > 0) {
                    if (_em->Get<Shield>(_ent)->shield >= 80) _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType("shieldblue80", RL::ModelType::EFFECT)->getModel(),objectPos->pos, 1.0f, owner->ownerType, pitchYawRoll); //change scale to obj Dimensions->lengthZ /2 , and change the shield models to be back to 1 square size in blender !
                    if (_em->Get<Shield>(_ent)->shield >= 50 && _em->Get<Shield>(_ent)->shield < 80 ) _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType("shieldblue50", RL::ModelType::EFFECT)->getModel(),objectPos->pos, 1.0f, owner->ownerType, pitchYawRoll); //change scale to obj Dimensions->lengthZ /2 , and change the shield models to be back to 1 square size in blender !
                    if (_em->Get<Shield>(_ent)->shield >= 25 && _em->Get<Shield>(_ent)->shield < 50) _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType("shieldblue25", RL::ModelType::EFFECT)->getModel(),objectPos->pos, 1.0f, owner->ownerType, pitchYawRoll); //change scale to obj Dimensions->lengthZ /2 , and change the shield models to be back to 1 square size in blender !
                    if (_em->Get<Shield>(_ent)->shield > 0 && _em->Get<Shield>(_ent)->shield < 25) _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType("shieldblue00", RL::ModelType::EFFECT)->getModel(),objectPos->pos, 1.0f, owner->ownerType, pitchYawRoll); //change scale to obj Dimensions->lengthZ /2 , and change the shield models to be back to 1 square size in blender !  
                    }
                
                _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType(objectModelName->modelname, modelType->modelType)->getModel(), objectPos->pos, modelScale->modelScale, owner->ownerType, pitchYawRoll);
            }            
        _renderer->end3DMode();
        //now we draw the HUD
        _renderer->draw_2D_model(_assetManager->getSpecificIcon("playerPannel")->getTexture(),_window->getDimensions().x/100 * PANNELLEFTX ,_window->getDimensions().y/100 * PANNELSY);
        _renderer->draw_2D_model(_assetManager->getSpecificIcon("playerPannel")->getTexture(),_window->getDimensions().x/100 * PANNELRIGHTX ,_window->getDimensions().y/100 * PANNELSY);

        //now we draw the data relative to the player on top of the hud
        playerUIDrawing(clientplayerID);
        
        DrawFPS(10, 10);
    _renderer->endDrawing();
}

void DrawingSystem::explosionDrawing()
{
    
}
void DrawingSystem::shieldDrawing()
{
    
}

void DrawingSystem::playerUIDrawing(EntityID clientplayerID)
{
    std::string avatarstatusName = _em->Get<UIAvatarNames>(clientplayerID)->avatarName;
    //these three ifs handle the player avatar
    if (_em->Get<Hp>(clientplayerID)->hp >= 65) {
        avatarstatusName.append("65");
        _renderer->draw_2D_model(_assetManager->getSpecificIcon(avatarstatusName)->getTexture(), _window->getDimensions().x * PLAYERICONX /100  , _window->getDimensions().y * PLAYERICONY /100);
    }
    if (_em->Get<Hp>(clientplayerID)->hp >= 30 && _em->Get<Hp>(clientplayerID)->hp < 65) {
        avatarstatusName.append("30");
        _renderer->draw_2D_model(_assetManager->getSpecificIcon(avatarstatusName)->getTexture(), _window->getDimensions().x * PLAYERICONX /100  , _window->getDimensions().y * PLAYERICONY /100);
    }
    if (_em->Get<Hp>(clientplayerID)->hp >= 0 && _em->Get<Hp>(clientplayerID)->hp < 30) {
        avatarstatusName.append("00");
        _renderer->draw_2D_model(_assetManager->getSpecificIcon(avatarstatusName)->getTexture(), _window->getDimensions().x * PLAYERICONX /100  , _window->getDimensions().y * PLAYERICONY /100);
    }

    //handle weaponslots
    handleWeaponslots(clientplayerID);
    
    //handle ammo of each weapon
    handleWeaponAmmo(clientplayerID);
    
    

    // if (_em->Get<Weaponset>(clientplayerID)->weapons.at(1) != nullptr)

    //handle score
    _renderer->draw_text(std::to_string(_em->Get<Score>(clientplayerID)->score), RAYWHITE, _window->getDimensions().x/100 * SCOREX ,_window->getDimensions().y/100 * SCOREY, _assetManager->getAllFonts().at(0), 25);
}

void DrawingSystem::handleWeaponslots(EntityID clientplayerID)
{
    if (_em->Get<Weaponset>(clientplayerID)->currentWeapon == 0)
        _renderer->draw_text("1", GREEN, _window->getDimensions().x/100 * WEAPON1INDX ,_window->getDimensions().y/100 * WEAPON1INDY, _assetManager->getAllFonts().at(0), 22);
    else
        _renderer->draw_text("1", RAYWHITE, _window->getDimensions().x/100 * WEAPON1INDX ,_window->getDimensions().y/100 * WEAPON1INDY, _assetManager->getAllFonts().at(0), 22);
    if (_em->Get<Weaponset>(clientplayerID)->currentWeapon == 1) 
        _renderer->draw_text("2", GREEN, _window->getDimensions().x/100 * WEAPON2INDX ,_window->getDimensions().y/100 * WEAPON2INDY, _assetManager->getAllFonts().at(0), 22);
    else
        _renderer->draw_text("2", RAYWHITE, _window->getDimensions().x/100 * WEAPON2INDX ,_window->getDimensions().y/100 * WEAPON2INDY, _assetManager->getAllFonts().at(0), 22);
    if(_em->Get<Weaponset>(clientplayerID)->currentWeapon == 2)
        _renderer->draw_text("3", GREEN, _window->getDimensions().x/100 * WEAPON3INDX ,_window->getDimensions().y/100 * WEAPON3INDY, _assetManager->getAllFonts().at(0), 22);
    else
        _renderer->draw_text("3", RAYWHITE, _window->getDimensions().x/100 * WEAPON3INDX ,_window->getDimensions().y/100 * WEAPON3INDY, _assetManager->getAllFonts().at(0), 22);
}

void DrawingSystem::handleWeaponAmmo(EntityID clientplayerID)
{
    //first weapon always full ammo cannot be dropped
    if (_em->Get<Weaponset>(clientplayerID)->currentWeapon == 0) {
        _renderer->draw_text("--", GREEN, _window->getDimensions().x * WEAP1AMMOX /100,
        _window->getDimensions().y/100 * WEAP1AMMOY, _assetManager->getAllFonts().at(0), 16);
    }
    else {
        _renderer->draw_text("--", RAYWHITE, _window->getDimensions().x * WEAP1AMMOX /100 ,
        _window->getDimensions().y/100 * WEAP1AMMOY, _assetManager->getAllFonts().at(0), 16);
    }

    if (_em->Get<Weaponset>(clientplayerID)->weapons.size() >= 2) {
        if (_em->Get<Weaponset>(clientplayerID)->currentWeapon == 1)
            _renderer->draw_text(std::to_string(_em->Get<Weaponset>(clientplayerID)->weapons.at(1).curAmmo), GREEN, _window->getDimensions().x * WEAP2AMMOX /100,
            _window->getDimensions().y/100 * WEAP1AMMOY, _assetManager->getAllFonts().at(0), 16);
        else
            _renderer->draw_text(std::to_string(_em->Get<Weaponset>(clientplayerID)->weapons.at(1).curAmmo), RAYWHITE, _window->getDimensions().x * WEAP2AMMOX /100,
            _window->getDimensions().y/100 * WEAP2AMMOY, _assetManager->getAllFonts().at(0), 16);

    }

    if (_em->Get<Weaponset>(clientplayerID)->weapons.size() == 3) {
        if (_em->Get<Weaponset>(clientplayerID)->currentWeapon == 2)
            _renderer->draw_text(std::to_string(_em->Get<Weaponset>(clientplayerID)->weapons.at(2).curAmmo), GREEN, _window->getDimensions().x * WEAP3AMMOX /100,
            _window->getDimensions().y/100 * WEAP3AMMOY, _assetManager->getAllFonts().at(0), 16);
        else
            _renderer->draw_text(std::to_string(_em->Get<Weaponset>(clientplayerID)->weapons.at(2).curAmmo), RAYWHITE, _window->getDimensions().x * WEAP3AMMOX /100,
            _window->getDimensions().y/100 * WEAP3AMMOY, _assetManager->getAllFonts().at(0), 16);

    }    

}
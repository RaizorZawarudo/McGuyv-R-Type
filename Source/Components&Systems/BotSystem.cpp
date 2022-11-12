/*
** EPITECH PROJECT, 2022
** McGuyverType
** File description:
** AISystem
*/

#include "BotSystem.hpp"
#include "MovementSystem.hpp"

BotSystem::BotSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<AssetManager> assetManager): _assetManager(assetManager)
{
    _em = em;
    _assetManager = assetManager;
}

BotSystem::~BotSystem()
{
}

void BotSystem::update(std::vector<EntityID> &allEntities)
{
    for (EntityID ent : EntityViewer<AI>(*_em.get())) {
        if (_em->Get<AI>(ent)->style == "simple")
            doAI_simple(ent);
    }
}

void BotSystem::doAI_simple(EntityID ennemy)
{
    //dodge bullets and update movement keys input
    dodge_bullets(ennemy);

    //decide if its time to shoot
    fire_weapon_ennemy(ennemy);
   

    //check for obstacles and update movement keys (maybe not for level 1)

}

void BotSystem::dodge_bullets(EntityID ennemy)
{
    //if im moving i just move i dont check for bullets
    if (_em->Get<AI>(ennemy)->isMoving) {
            applyAIInputDodgeProjectile(ennemy);
            return;
    }
    //scan in a tube in front and back of mob if there is a bullet coming
    for (EntityID ent : EntityViewer<Position>(*_em.get())) {
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::PROJECTILE) continue;
        
        //else i check for bullets in range
        //check if bullet is in my X : EDIT = CHECK IF model dimensions, not just model pos, or else the ennemy dodges only when ur SUPER PRECISE AIM and its not in this game
        if (_em->Get<Position>(ent)->pos.x + _em->Get<ModelDimensions>(ent)->widthX / 2 < (_em->Get<Position>(ennemy)->pos.x - _em->Get<ModelDimensions>(ennemy)->widthX / 2) ||
            _em->Get<Position>(ent)->pos.x - _em->Get<ModelDimensions>(ent)->widthX / 2 > (_em->Get<Position>(ennemy)->pos.x + _em->Get<ModelDimensions>(ennemy)->widthX / 2)) return;
        //check if bullet is in my Y
        if (_em->Get<Position>(ent)->pos.y + _em->Get<ModelDimensions>(ent)->heightY / 2 < (_em->Get<Position>(ennemy)->pos.y - _em->Get<ModelDimensions>(ennemy)->heightY / 2) ||
            _em->Get<Position>(ent)->pos.y - _em->Get<ModelDimensions>(ent)->heightY / 2 > (_em->Get<Position>(ennemy)->pos.y + _em->Get<ModelDimensions>(ennemy)->heightY / 2)) return;
        
        //check if bullet is in my Z range
        if (_em->Get<Position>(ent)->pos.z < (_em->Get<Position>(ennemy)->pos.x - _em->Get<AI>(ennemy)->moveDetectRange) ||
            _em->Get<Position>(ent)->pos.z > (_em->Get<Position>(ennemy)->pos.x + _em->Get<AI>(ennemy)->moveDetectRange)) return;

        if (GetTime() -  _em->Get<AI>(ennemy)->lastTimeMoved > _em->Get<AI>(ennemy)->moveCooldown) {
            _em->Get<AI>(ennemy)->lastTimeMoved = GetTime();
            _em->Get<AI>(ennemy)->isMoving = true;

            //find a target to move to with Algorithm you create DAN DAN DAN
            _em->Get<AI>(ennemy)->moveTargetPos = findSafeSpotfromProjectile(ennemy);

            // _em->Get<AI>(ennemy)->moveTargetPos = {-4, 5, 0}; // z set to zero because mobs dont go forward in simple mode

            applyAIInputDodgeProjectile(ennemy);
        }
    }
}

Vector3 BotSystem::findSafeSpotfromProjectile(EntityID ennemy)
{
    Vector3 newTargetPos;
    int newSeedx = _assetManager->getLootRand() + _em->Get<Position>(ennemy)->pos.x;
    int newSeedy = _assetManager->getLootRand() + _em->Get<Position>(ennemy)->pos.y;

    std::cout << newSeedx << std::endl;
    std::cout << newSeedy << std::endl;
    //find a random x using the random from asset manager
    int x = newSeedx % SIMPLEMOVERANGE;
    int y = newSeedy % SIMPLEMOVERANGE;

    std::cout << x << std::endl;
    std::cout << y << std::endl;
    if (_assetManager->getLootRand() % 2 == 1)
        x = -x;
    if (_assetManager->getLootRand() % 2 == 1)
        y = -y;
    
    //add the new x and x to the targetpos

    newTargetPos.x = _em->Get<Position>(ennemy)->pos.x + x;
    newTargetPos.y = _em->Get<Position>(ennemy)->pos.y + y;
    newTargetPos.z = 0;

    std::cout << newTargetPos.x << std::endl;
    std::cout << newTargetPos.y << std::endl;

    if (newTargetPos.x > MAXLEFT)
        newTargetPos.x = MAXLEFT;
    if (newTargetPos.x < MAXRIGHT)
        newTargetPos.x = MAXRIGHT;
    if (newTargetPos.y > MAXUP)
        newTargetPos.y = MAXUP;
    if (newTargetPos.y < MAXDOWN)
        newTargetPos.y = MAXDOWN;
    
    std::cout << newTargetPos.x << std::endl;
    std::cout << newTargetPos.y << std::endl;

    return newTargetPos;
}

bool BotSystem::is_in_range(EntityID ennemy)
{
    if ((_em->Get<Position>(ennemy)->pos.x <= _em->Get<AI>(ennemy)->moveTargetPos.x + 0.2f &&
        _em->Get<Position>(ennemy)->pos.x >= _em->Get<AI>(ennemy)->moveTargetPos.x - 0.2f) &&
        (_em->Get<Position>(ennemy)->pos.y <= _em->Get<AI>(ennemy)->moveTargetPos.y + 0.2f &&
        _em->Get<Position>(ennemy)->pos.y >= _em->Get<AI>(ennemy)->moveTargetPos.y - 0.2f)) {
            return true;
    }
    else 
        return false;
}

void BotSystem::applyAIInputDodgeProjectile(EntityID ennemy)
{
    //here check if we reached target in order to set isMoving to false and Target to 0,0,0
    if (is_in_range(ennemy)) {
        _em->Get<AI>(ennemy)->isMoving = false;
        _em->Get<AI>(ennemy)->moveTargetPos = {0, 0, 0};
        return;
    }
    if (_em->Get<Position>(ennemy)->pos.x < _em->Get<AI>(ennemy)->moveTargetPos.x - MOVEBUFFER) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(LEFT);
        std::cout << " going right " << std::endl;
    }
    
    if (_em->Get<Position>(ennemy)->pos.x > _em->Get<AI>(ennemy)->moveTargetPos.x + MOVEBUFFER) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(RIGHT);
        std::cout << " going left " << std::endl;
    }
    if (_em->Get<Position>(ennemy)->pos.y < _em->Get<AI>(ennemy)->moveTargetPos.y - MOVEBUFFER) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(UP);
        std::cout << " going up " << std::endl;
    }
    if (_em->Get<Position>(ennemy)->pos.y > _em->Get<AI>(ennemy)->moveTargetPos.y + MOVEBUFFER) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(DOWN);
        std::cout << " going down " << std::endl;
    }
}

void BotSystem::fire_weapon_ennemy(EntityID ennemy)
{
    //this line here adds shoot command in the inputs of the ennemy
    //_em->Get<Input>(ennemy)->_inputQueue.emplace_back(SHOOT);
}
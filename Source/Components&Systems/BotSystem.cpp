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
    dodge_obstacles(ennemy);

    // find_player_target(ennemy);

    //target player === get in same X Y as player in order to fire
    //decide if its time to shoot : => 50 means more than 50 % chance to shoot
    int shootchance = _assetManager->getLootRand() * abs(_em->Get<Position>(ennemy)->pos.x * _em->Get<Position>(ennemy)->pos.y);
    if (shootchance % 100 >= 50)
        fire_weapon_ennemy(ennemy);

}

void BotSystem::dodge_bullets(EntityID ennemy)
{
    //if im moving i just move i dont check for bullets
    if (_em->Get<AI>(ennemy)->isMoving) {
            applyAIKeystrokes(ennemy);
            return;
    }
    //scan in a tube in front and back of mob if there is a bullet coming
    for (EntityID ent : EntityViewer<Position>(*_em.get())) {
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::PROJECTILE) continue;
        if (_em->Get<Owner>(ent)->id == ennemy) continue;
        
        float ennemyLeft = _em->Get<Position>(ennemy)->pos.x + _em->Get<ModelDimensions>(ennemy)->widthX / 2;
        float ennemyRight = _em->Get<Position>(ennemy)->pos.x - _em->Get<ModelDimensions>(ennemy)->widthX / 2;
        float ennemyTop = _em->Get<Position>(ennemy)->pos.y + _em->Get<ModelDimensions>(ennemy)->heightY / 2;
        float ennemyBottom = _em->Get<Position>(ennemy)->pos.y - _em->Get<ModelDimensions>(ennemy)->heightY / 2;
        float ennemyRangeFront = _em->Get<Position>(ennemy)->pos.x - _em->Get<AI>(ennemy)->moveDetectRange;
        float ennemyRangeBack = _em->Get<Position>(ennemy)->pos.x + _em->Get<AI>(ennemy)->moveDetectRange;

        float bulletLeft = _em->Get<Position>(ent)->pos.x + _em->Get<ModelDimensions>(ent)->widthX / 2;
        float bulletRight = _em->Get<Position>(ent)->pos.x - _em->Get<ModelDimensions>(ent)->widthX / 2;
        float bulletTop = _em->Get<Position>(ent)->pos.y + _em->Get<ModelDimensions>(ent)->heightY / 2;
        float bulletBottom = _em->Get<Position>(ent)->pos.y - _em->Get<ModelDimensions>(ent)->heightY / 2;

        
        //else i check for bullets in range
        //check if bullet is in my X : EDIT = CHECK IF model dimensions, not just model pos, or else the ennemy dodges only when ur SUPER PRECISE AIM and its not in this game
        if (bulletRight > ennemyLeft || bulletLeft < ennemyRight) continue;
        //check if bullet is in my Y
        if (bulletTop < ennemyBottom || bulletBottom > ennemyTop) continue;
        
        //check if bullet is in my Z range
        if (_em->Get<Position>(ent)->pos.z < (_em->Get<Position>(ennemy)->pos.z - _em->Get<AI>(ennemy)->moveDetectRange) ||
            _em->Get<Position>(ent)->pos.z > (_em->Get<Position>(ennemy)->pos.z + _em->Get<AI>(ennemy)->moveDetectRange) ) continue;
        

        if (GetTime() -  _em->Get<AI>(ennemy)->lastTimeMoved > _em->Get<AI>(ennemy)->moveCooldown) {
            _em->Get<AI>(ennemy)->lastTimeMoved = GetTime();
            _em->Get<AI>(ennemy)->isMoving = true;

            _em->Get<AI>(ennemy)->moveTargetPos = findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.x, _em->Get<Position>(ennemy)->pos.y);

            applyAIKeystrokes(ennemy);
        }
    }
}

void BotSystem::dodge_obstacles(EntityID ennemy)
{
    //if im moving i just move i dont check for obstacles
    if (_em->Get<AI>(ennemy)->isMoving) {
            applyAIKeystrokes(ennemy);
            return;
    }
    //scan in a tube in front and back of mob if there is a obstacle coming
    for (EntityID ent : EntityViewer<Position>(*_em.get())) {
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::OBSTACLE) continue;

        float ennemyLeft = _em->Get<Position>(ennemy)->pos.x + _em->Get<ModelDimensions>(ennemy)->widthX / 2;
        float ennemyRight = _em->Get<Position>(ennemy)->pos.x - _em->Get<ModelDimensions>(ennemy)->widthX / 2;
        float ennemyTop = _em->Get<Position>(ennemy)->pos.y + _em->Get<ModelDimensions>(ennemy)->heightY / 2;
        float ennemyBottom = _em->Get<Position>(ennemy)->pos.y - _em->Get<ModelDimensions>(ennemy)->heightY / 2;
        float ennemyRangeFront = _em->Get<Position>(ennemy)->pos.x - _em->Get<AI>(ennemy)->moveDetectRange;
        float ennemyRangeBack = _em->Get<Position>(ennemy)->pos.x + _em->Get<AI>(ennemy)->moveDetectRange;

        float obstacleLeft = _em->Get<Position>(ent)->pos.x + _em->Get<ModelDimensions>(ent)->widthX / 2;
        float obstacleRight = _em->Get<Position>(ent)->pos.x - _em->Get<ModelDimensions>(ent)->widthX / 2;
        float obstacleTop = _em->Get<Position>(ent)->pos.y + _em->Get<ModelDimensions>(ent)->heightY / 2;
        float obstacleBottom = _em->Get<Position>(ent)->pos.y - _em->Get<ModelDimensions>(ent)->heightY / 2;

        //check if obstacle is in my Z range
        if (_em->Get<Position>(ent)->pos.z < (_em->Get<Position>(ennemy)->pos.z - _em->Get<AI>(ennemy)->moveDetectRange - 5) ||
            _em->Get<Position>(ent)->pos.z > (_em->Get<Position>(ennemy)->pos.z + _em->Get<AI>(ennemy)->moveDetectRange + 5) ) continue;
        //else i check for obstacles in range
        //check if obstacle is in my X : EDIT = CHECK IF model dimensions, not just model pos, or else the ennemy dodges only when ur SUPER PRECISE AIM and its not in this game
        if (obstacleRight > ennemyLeft || obstacleLeft < ennemyRight) continue;
        //check if obstacle is in my Y
        if (obstacleTop < ennemyBottom || obstacleBottom > ennemyTop) continue;        

        if (GetTime() -  _em->Get<AI>(ennemy)->lastTimeMoved > _em->Get<AI>(ennemy)->moveCooldown) {
            _em->Get<AI>(ennemy)->lastTimeMoved = GetTime();
            _em->Get<AI>(ennemy)->isMoving = true;

            //find a target to move to with Algorithm you create DAN DAN DAN
            _em->Get<AI>(ennemy)->moveTargetPos = findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.x, _em->Get<Position>(ennemy)->pos.y);
            applyAIKeystrokes(ennemy);

        }
    }
}

void BotSystem::find_player_target(EntityID ennemy)
{
    //if im moving i just move i dont check for obstacles
    if (_em->Get<AI>(ennemy)->isMoving) {
            applyAIKeystrokes(ennemy);
            return;
    }
    int mcgyuverfixai = 0;
    // if same target == find another target

    // if no other target available, do nothing

    //in all entities present, check for players and target one STEP 1
    for (EntityID ent : EntityViewer<Position>(*_em.get())) {
        
        //if your are not a spaceship we continue
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::SPACESHIP) continue;
        //if you are not in my range to target you contniue
        if (_em->Get<Position>(ent)->pos.z < (_em->Get<Position>(ennemy)->pos.z - _em->Get<AI>(ennemy)->targetPlayerDetectRange)) continue;

        mcgyuverfixai = 0;

        //my move target becoms this player I find
        _em->Get<AI>(ennemy)->moveTargetPos.x = _em->Get<Position>(ent)->pos.x;
        _em->Get<AI>(ennemy)->moveTargetPos.y = _em->Get<Position>(ent)->pos.y;
        _em->Get<AI>(ennemy)->moveTargetPos.z = 0;
        // 

        //in all entities that are ennemies with AI, check if their move target == to the one we
        //just chose, if so find another target, if not proceed to apply keystrokes
        for (EntityID ent2 : EntityViewer<Position>(*_em.get())) {
            //we only want to get to ennemies or obstacles here to check their target pos or their pos
            if ((_em->Get<EntityModelType>(ent2)->modelType != RL::ModelType::ENNEMY && 
                _em->Get<EntityModelType>(ent2)->modelType != RL::ModelType::OBSTACLE) ||
                ent2 == ennemy)
                continue;
            //check for their current pos 
            if (check_for_vicinity(_em->Get<AI>(ennemy)->moveTargetPos.x, _em->Get<Position>(ent2)->pos.x) &&
                check_for_vicinity(_em->Get<AI>(ennemy)->moveTargetPos.y, _em->Get<Position>(ent2)->pos.y)) { //&&
                // _em->Get<Position>(ennemy)->pos.z == _em->Get<Position>(ent2)->pos.z) {
                    // _em->Get<AI>(ennemy)->moveTargetPos = findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.y, _em->Get<Position>(ennemy)->pos.x);
                    std::cout << "match" << std::endl;
                    mcgyuverfixai = 1;
            }
            //if ur not a ennemy aka ur an obstacle u dont have ai and target so you continue to next in loop
            if (_em->Get<EntityModelType>(ent2)->modelType != RL::ModelType::ENNEMY)
                continue;

            //check for their target goals
            if (check_for_vicinity(_em->Get<AI>(ennemy)->moveTargetPos.x, _em->Get<AI>(ent2)->moveTargetPos.x) &&
                check_for_vicinity(_em->Get<AI>(ennemy)->moveTargetPos.y, _em->Get<AI>(ent2)->moveTargetPos.y)) { // &&
                // _em->Get<Position>(ennemy)->pos.z == _em->Get<Position>(ent)->pos.z) {
                    // _em->Get<AI>(ennemy)->moveTargetPos = findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.y, _em->Get<Position>(ennemy)->pos.x);
                    std::cout << "match2" << std::endl;
                    mcgyuverfixai = 1;
            }
            if (mcgyuverfixai == 1) {
                _em->Get<AI>(ennemy)->moveTargetPos = _em->Get<Position>(ent)->pos;
                break;        
            }
        }
        if (mcgyuverfixai == 0) break; 
    }
    if (mcgyuverfixai == 1)
        return;

    if (GetTime() -  _em->Get<AI>(ennemy)->lastTimeMoved > _em->Get<AI>(ennemy)->moveCooldown) {
            _em->Get<AI>(ennemy)->lastTimeMoved = GetTime();
            _em->Get<AI>(ennemy)->isMoving = true;
            applyAIKeystrokes(ennemy);
        } 
}

bool BotSystem::check_for_vicinity(float x, float y)
{
    if (x >= (y - RANGEBUFFER) && x <= (y + RANGEBUFFER))
        return true;
    return false;
}

void BotSystem::fire_weapon_ennemy(EntityID ennemy)
{
    //this line here adds shoot command in the inputs of the ennemy
    if (GetTime() - _em->Get<AI>(ennemy)->lastTimeShot > _em->Get<AI>(ennemy)->shootCooldown) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(SHOOT);
        _em->Get<AI>(ennemy)->lastTimeShot = GetTime();
    }
}

Vector3 BotSystem::findSafeSpotfromProjectile(EntityID ennemy, float ennemyPosX , float ennemyPosY)
{
    Vector3 newTargetPos;
    int newSeedx = _assetManager->getLootRand() * ennemyPosX;
    int newSeedy = _assetManager->getLootRand() * ennemyPosY;

    //find a random x using the random from asset manager
    int x = newSeedx * _em->Get<Hp>(ennemy)->hp % SIMPLEMOVERANGE;
    int y = newSeedy + _em->Get<Hp>(ennemy)->hp % SIMPLEMOVERANGE;

    if (_assetManager->getLootRand() % 2 == 1)
        x = -x;
    if (_assetManager->getLootRand() % 2 == 1)
        y = -y;
    
    //add the new x and x to the targetpos

    newTargetPos.x = _em->Get<Position>(ennemy)->pos.x + x;
    newTargetPos.y = _em->Get<Position>(ennemy)->pos.y + y;
    newTargetPos.z = 0;

    if (newTargetPos.x > MAXLEFT)
        newTargetPos.x = MAXLEFT;
    if (newTargetPos.x < MAXRIGHT)
        newTargetPos.x = MAXRIGHT;
    if (newTargetPos.y > MAXUP)
        newTargetPos.y = MAXUP;
    if (newTargetPos.y < MAXDOWN)
        newTargetPos.y = MAXDOWN;

    //check if there is not already a monster there 
    for (EntityID ent : EntityViewer<Position>(*_em.get())) {
        //we only want to not got to ennemies or obstacles
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::ENNEMY && 
            _em->Get<EntityModelType>(ent)->modelType != RL::ModelType::OBSTACLE)
            continue;
        //check for their current pos 
        if (newTargetPos.x == _em->Get<Position>(ent)->pos.x &&
            newTargetPos.y == _em->Get<Position>(ent)->pos.y &&
            _em->Get<Position>(ennemy)->pos.z == _em->Get<Position>(ent)->pos.z) {
                return findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.y, _em->Get<Position>(ennemy)->pos.x);
        }
        //if ur not a ennemy aka ur an obstacle u dont have ai and target so you continue to next in loop
        if (_em->Get<EntityModelType>(ent)->modelType != RL::ModelType::ENNEMY)
            continue;

        //check for their target goals
        if (newTargetPos.x == _em->Get<AI>(ent)->moveTargetPos.x &&
            newTargetPos.y == _em->Get<AI>(ent)->moveTargetPos.y &&
            _em->Get<Position>(ennemy)->pos.z == _em->Get<Position>(ent)->pos.z) {
                return findSafeSpotfromProjectile(ennemy, _em->Get<Position>(ennemy)->pos.y, _em->Get<Position>(ennemy)->pos.x);
        }
    }

    return newTargetPos;
}

bool BotSystem::is_in_range_of_target(EntityID ennemy)
{
    if ((_em->Get<Position>(ennemy)->pos.x <= _em->Get<AI>(ennemy)->moveTargetPos.x + 0.3f &&
        _em->Get<Position>(ennemy)->pos.x >= _em->Get<AI>(ennemy)->moveTargetPos.x - 0.3f) &&
        (_em->Get<Position>(ennemy)->pos.y <= _em->Get<AI>(ennemy)->moveTargetPos.y + 0.3f &&
        _em->Get<Position>(ennemy)->pos.y >= _em->Get<AI>(ennemy)->moveTargetPos.y - 0.3f)) {
            return true;
    }
    else 
        return false;
}

void BotSystem::applyAIKeystrokes(EntityID ennemy)
{
    //here check if we reached target in order to set isMoving to false and Target to 0,0,0
    if (is_in_range_of_target(ennemy)) {
        _em->Get<AI>(ennemy)->isMoving = false;
        _em->Get<AI>(ennemy)->moveTargetPos = {0, 0, 0};
        return;
    }
    if (_em->Get<Position>(ennemy)->pos.x < _em->Get<AI>(ennemy)->moveTargetPos.x - MOVEBUFFER && _em->Get<Input>(ennemy)->_inputQueue.size() < 3 ) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(LEFT);
        // std::cout << " going right " << std::endl;
    }
    
    if (_em->Get<Position>(ennemy)->pos.x > _em->Get<AI>(ennemy)->moveTargetPos.x + MOVEBUFFER && _em->Get<Input>(ennemy)->_inputQueue.size() < 3) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(RIGHT);
        // std::cout << " going left " << std::endl;
    }
    if (_em->Get<Position>(ennemy)->pos.y < _em->Get<AI>(ennemy)->moveTargetPos.y - MOVEBUFFER && _em->Get<Input>(ennemy)->_inputQueue.size() < 3) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(UP);
        // std::cout << " going up " << std::endl;
    }
    if (_em->Get<Position>(ennemy)->pos.y > _em->Get<AI>(ennemy)->moveTargetPos.y + MOVEBUFFER && _em->Get<Input>(ennemy)->_inputQueue.size() < 3) {
        _em->Get<Input>(ennemy)->_inputQueue.emplace_back(DOWN);
        // std::cout << " going down " << std::endl;
    }
}
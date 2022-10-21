/*
** EPITECH PROJECT, 2022
** R-TYPE 3D
** File description:
** DrawingSystem
*/

#include "ISystem.hpp"
#include "DrawingSystem.hpp"


DrawingSystem::DrawingSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<RL::Renderer> renderer, std::shared_ptr<AssetManager> assetManager, std::shared_ptr<RL::CameraManager> cameraManager)
: _renderer(renderer) ,_assetManager(assetManager), _cameraManager(cameraManager)
{
    _em = em;
}

DrawingSystem::~DrawingSystem()
{
}

void DrawingSystem::update(std::vector<EntityID> &allEntities)
{
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
                _renderer->draw_3D_model(_assetManager->getSpecificDrawableWithType(objectModelName->modelname, modelType->modelType)->getModel(), objectPos->pos, modelScale->modelScale, owner->ownerType, pitchYawRoll);
            }
            
        _renderer->end3DMode();



        DrawFPS(10, 10);
    _renderer->endDrawing();
}



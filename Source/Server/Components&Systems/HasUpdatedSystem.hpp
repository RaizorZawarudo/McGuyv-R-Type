/*
** EPITECH PROJECT, 2023
** RType
** File description:
** updatedNotifSystem
*/

#include "ISystem.hpp"
#include "../Networking/UDPServer.hpp"
#include "../Networking/protocol/Serializator.hpp"
#include "../AssetManager.hpp"

class HasUpdatedSystem : public ISystem {
public:
  HasUpdatedSystem(std::shared_ptr<EntityManager> em, std::shared_ptr<UDPServer> udpServer, std::shared_ptr<AssetManager> assetManager);
  ~HasUpdatedSystem() {};

  void update(std::vector<EntityID> &allEntities) override;
  void sendCreatedEntity(EntityID id);
  int getIndexModel(RL::ModelType type, EntityID id);
  // void createEntity(EntityID id) {};

private:
  std::shared_ptr<EntityManager> _em;
  std::shared_ptr<UDPServer> _udpServer;
  Serializator _serializator;
  std::shared_ptr<AssetManager> _assetManager;
  bool _sentFightingBoss = false;
};

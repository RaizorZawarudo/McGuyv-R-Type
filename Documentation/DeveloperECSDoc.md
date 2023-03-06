# **Developer Documentation ECS**

## **Introduction**

Welcome to the developer documentation for our video game built using C++ and the Raylib game engine with an Entity Component System (ECS) architecture. This documentation is intended to provide comprehensive information and guidance to help you understand and modify the game's source code.

Our game has been designed with a focus on performance, flexibility, and modularity. The ECS architecture enables efficient management of game entities and their components, providing a scalable and easy-to-manage approach to game development. Raylib, on the other hand, is a lightweight and easy-to-use game engine that offers a wide range of features, making it an ideal choice for developing 2D and 3D games.

In this documentation, we will cover the different aspects of the game's codebase, including the ECS architecture, game mechanics, rendering system, audio system, and input handling. We will provide detailed explanations, code snippets, and examples to help you understand the game's underlying systems and how they work together.

Whether you are a seasoned game developer or just starting, this documentation will be your go-to resource for understanding and modifying our game's code. So, let's dive in and start exploring!

## **1 - Getting Started**

- Setting up the development environment
- Building and running the game
- Overview of the game's codebase

## **2 - ECS Architecture**

- Entity-Component-System overview
- Creating and managing entities
- Systems and their execution order
- Handling messaging

## **3 - Game Mechanics**

- Overview of the game's mechanics
- Implementing game rules and logic
- Collision detection and resolution
- Implementing AI and pathfinding

## **4 - Rendering System**

- Overview of the rendering pipeline
- Creating and managing sprites and textures
- Implementing animation and particle systems

## **5 - Audio System**

- Overview of the audio pipeline
- Loading and managing audio assets

## **6 - Input Handling**

- Overview of the input handling system
- Implementing player controls

## **7 - Conclusion**

- Final thoughts and next steps
- Additional resources and references
- Acknowledgments and contributors

## **1 - Getting started**

### - **Setting up the development environment:**

To set up the development environment for the game, you will need to install g++ and gcc, which are the C++ and C compilers respectively. These compilers are necessary for building the game's source code.

Here are the steps to install g++ and gcc on **Ubuntu Linux** :

Open a terminal window.

Update the package list using the following command:

```
sudo apt-get update
```

Install g++ and gcc using the following command:
```
sudo apt-get install g++ gcc
```
Verify that the compilers have been installed correctly by checking their version numbers using the following commands:
```
g++ --version

gcc --version
```
You should see the version numbers of the installed compilers in the output.

Note that these instructions are specific to Ubuntu Linux and may differ for other operating systems. Please refer to the documentation for your operating system for more information on installing g++ and gcc.

Once g++ and gcc have been installed, you can proceed with setting up your development environment for the game.

<br/>
<br/>

To set up the development environment for the game on **Windows** , you will need to install a C++ compiler such as g++ and gcc.

Here are the steps to install g++ and gcc on Windows using MinGW:

1 - Download and install MinGW from the official website: [https://osdn.net/projects/mingw/releases/](https://osdn.net/projects/mingw/releases/)

2 - During the installation process, select the following packages: mingw32-base, mingw32-gcc-g++, and mingw32-make.

3 - Once the installation is complete, add the bin directory of MinGW to your system's PATH environment variable. This can be done by following these steps:

- Open the Start menu and search for "Environment Variables".
- Click on "Edit the system environment variables".
- Click on the "Environment Variables" button.
- Under "System Variables", scroll down and find the "Path" variable.
- Click on "Edit".
- Click on "New" and add the path to the bin directory of MinGW (e.g. C:\MinGW\bin).
- Click "OK" to close all windows.

4 - Verify that g++ and gcc have been installed correctly by checking their version numbers using the following commands in the command prompt:
```
g++ --version

gcc --version
```
You should see the version numbers of the installed compilers in the output.

Note that these instructions are specific to installing g++ and gcc on Windows using MinGW. Other C++ compilers and installation methods may have different steps. Please refer to the documentation for your preferred compiler and operating system for more information.

Once g++ and gcc have been installed, you can proceed with setting up your development environment for the game.

### - **Building and running the game:**

Building and Running the Game using CMake:

To build and run the game using CMake, follow these steps:

1 - Clone or download the game's source code from the repository.
```
git clone git@github.com:EpitechPromo2025/B-CPP-500-BER-5-2-rtype-alban.de-tourtier.git "R-Type"
```
2 - Navigate inside it.
```
cd R-Type
```
3 - Run the cmake.
```
make CMakeLists.txt
```
4 - Build the game.
```
make
```
5 - Launch the game.
```
./r-type\_client
```
If you encounter any issues during the build or run process, please refer to the troubleshooting section of this documentation or open a ticket for help.

### - **Overview of the game's codebase:**

The game's codebase is built using C++ and the Raylib game engine with an Entity-Component-System (ECS) architecture. The ECS architecture is designed to provide flexibility and efficiency in game development, allowing for modular and scalable code that can handle complex game mechanics and systems.

The codebase is organized into several modules, including the ECS core, game mechanics, rendering system, audio system, and input handling. Each module is designed to handle a specific aspect of the game's functionality, with clear separation of concerns and minimal coupling between modules.

The ECS core provides the foundational architecture for the game, managing entities, components, systems, and events. The game mechanics module handles the implementation of game rules and logic, including collision detection and resolution, AI and pathfinding, and other advanced game mechanics.

The rendering system module provides an overview of the rendering pipeline and covers the implementation of sprites, textures, animation, particle systems, and lighting and shadows. The audio system module covers the implementation of sound effects, music, and audio spatialization and positioning.

Finally, the input handling module covers player controls, input events and gestures, menus, and UI elements. Together, these modules form the basis for the game's codebase, providing a robust and efficient framework for game development.

## **2 - ECS Architecture**

### - **Entity-Component-System Overview:**

The Entity-Component-System (ECS) is a design pattern used in game development for creating flexible and efficient game systems. In ECS, the game world is composed of entities, which are simply unique identifiers or tags that represent game objects. Each entity can be associated with one or more components, which represent specific properties or behaviors of the entity.

Components are usually small, self-contained pieces of data that describe a specific aspect of an entity, such as its position, velocity, or health. Systems, on the other hand, are responsible for updating and manipulating components based on specific rules or logic.

The ECS pattern separates the game logic from the data, allowing for more flexibility and easier maintenance. For example, adding new behaviors or properties to an entity is simply a matter of attaching a new component, rather than modifying the entity class or structure directly. This can make it easier to iterate on game designs and add new features.

Additionally, because components are stored contiguously in memory, ECS can be more cache-friendly and efficient than traditional object-oriented designs. This can lead to better performance and scalability, especially in large-scale game systems.

In summary, the Entity-Component-System pattern is a flexible and efficient way to design game systems by separating the game world into entities, components, and systems. By keeping the data and logic separate, ECS allows for easier maintenance, iteration, and scalability.

### - **Creating and managing entities:**

File: Source/Client/ECS/EntityManager.hpp
``` cpp
EntityID CreateNewEntity() {

if (!freeEntities.empty()) {

EntityIndex newIndex = freeEntities.back();

freeEntities.pop\_back();

EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));

entities[newIndex].id = newID;

return entities[newIndex].id;

}

entities.push\_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });

return entities.back().id;

}
```

This is a code snippet that implements a function to create a new entity in an Entity-Component-System (ECS) design pattern. Here's a breakdown of what's happening in the code:

- The function starts by checking if there are any free entities in the system's pool. This is done by checking if the vector "freeEntities" is not empty.
- If there are free entities available, the function gets the index of the last entity in the vector "freeEntities" (which represents the index of the free entity with the highest index), removes it from the vector, and creates a new EntityID using the index and the current version of the entity (which is obtained by calling GetEntityVersion on the existing entity with the same index).
- If there are no free entities available, the function creates a new entity by pushing back a new EntityInfo object into the "entities" vector. This new entity is given a new EntityID with an index equal to the current size of the "entities" vector (which is equal to the index of the new entity) and a version of 0.
- Finally, the function returns the EntityID of the newly created entity.

Overall, this function allows the ECS system to create new entities dynamically as needed, either by reusing existing free entities or by creating new entities if there are no free ones available.

### - **Systems and their execution order**
``` cpp
AssetManager::AssetManager(EntityID currentClientID)

{

this-\>\_currentclientID = currentClientID;

loadAllModels();

//load all maps ( maps is the data structure which contains the matching paths to be linked together to create the world

// ex : mountainsPath + big mountainpath + mountainboss room + big mountain boss room

loadAllMaps();

}
```
This code snippet shows the constructor of a class called AssetManager, which is responsible for loading and managing game assets such as models and maps. Here's a breakdown of what's happening in the code:

- The constructor takes an EntityID called "currentClientID" as its input parameter, which is used to identify the current client of the game.

- The constructor initializes the "\_currentclientID" data member of the AssetManager class to the input value of "currentClientID".
- The function then calls the "loadAllModels()" function, which is responsible for loading all the 3D models used in the game.
- After loading all the models, the function then calls the "loadAllMaps()" function, which is responsible for loading all the maps used in the game.
- The comment in the code explains that "maps" is a data structure that contains the matching paths to be linked together to create the world. For example, if the game has a mountain boss level, the "maps" data structure would contain the paths to the mountain, the big mountain, the mountain boss room, and the big mountain boss room, which would be linked together to create the full level.
- Overall, this constructor initializes the AssetManager class by loading all the necessary game assets needed to create the game world, which can then be used by other parts of the game engine to create the actual gameplay.

### - **Handling messaging**
``` cpp
Logger::Logger(const std::string &sectionName, bool standardOutput)

: \_sectionName(sectionName), \_standardOutput(standardOutput) {}

void Logger::log(std::string msg) const

{

if (this-\>\_standardOutput)

std::cout \<\< "\033[1;33m" \<\< this-\>\_sectionName \<\< ": " \<\< "\033[0m" \<\< msg \<\< std::endl;

else

std::cerr \<\< "\033[1;33m" \<\< this-\>\_sectionName \<\< ": " \<\< "\033[0m" \<\< msg \<\< std::endl;

}

const std::string &Logger::getSectionName() const {

return \_sectionName;

}

void Logger::setSectionName(const std::string &sectionName) {

\_sectionName = sectionName;

}
```
It contains a constructor, a log method, and getter and setter methods for the section name.

The constructor initializes the member variables \_sectionName and \_standardOutput. \_sectionName is a string that represents the name of the section or module where the log message originates. \_standardOutput is a boolean that indicates whether the log message should be sent to standard output (if true) or standard error (if false).

The log method is used to write a log message to the appropriate output stream, depending on the value of \_standardOutput. The log message consists of the section name, followed by a colon and a space, and then the actual message.

The getSectionName method returns the current value of \_sectionName, while the setSectionName method is used to set a new value for \_sectionName.

## **3 - Game Mechanics**

### - **Overview of the game's mechanics**

This game features several gameplay mechanics, including shields, bonus items, and different weapons. Here's an overview of each mechanic:

- **Shields:** In the game, the player can collect shields to protect themselves from enemy attacks. When the player collects a shield, it adds a protective barrier around them that absorbs a certain amount of damage. Once the shield is depleted, it disappears and the player's health is exposed to damage again.
- **Bonus items:** The game features various bonus items that the player can collect to gain additional benefits. These items can include health power-ups, which restore the player's health, and ammunition power-ups, which increase the player's ammunition supply for their weapons. Other bonus items can include temporary speed boosts, invincibility power-ups, and damage boost power-ups, among others.
- **Different weapons:** The game includes multiple types of weapons that the player can use to attack enemies. These weapons can include firearms such as pistols, shotguns, and machine guns. Each weapon has its own strengths and weaknesses, and the player can switch between them during gameplay to suit the situation.

Overall, the combination of shields, bonus items, and different weapons adds depth and variety to the gameplay, allowing players to customize their play style and approach different challenges in different ways.

### - **Implementing game rules and logic**
``` cpp
McGuyverType::McGuyverType() /\*: \_udpServer(\_ioContext), \_udpServerThread([this](){ \_ioContext.run(); })\*/

{

this-\>\_window = std::make\_shared\<RL::Window\>("McGuyv R-Type");

this-\>\_cameraManager = std::make\_shared\<RL::CameraManager\>();

this-\>\_assetManager = std::make\_shared\<AssetManager\>(this-\>\_thisClientPlayerEntityID);

this-\>\_renderer = std::make\_shared\<RL::Renderer\>("Renderer");

this-\>\_inputManager = std::make\_shared\<RL::InputManager\>("InputManager");

this-\>\_entityManager = std::make\_shared\<EntityManager\>();

this-\>\_assetManager-\>startTime();

this-\>\_systems.push\_back(std::make\_shared\<DataReceivingSystem\>(this-\>\_entityManager, this-\>\_assetManager, this-\>\_inputManager)); //add deserialiser and upd reader

this-\>\_systems.push\_back(std::make\_shared\<MovementSystem\>(this-\>\_entityManager, this-\>\_assetManager));

this-\>\_systems.push\_back(std::make\_shared\<DeleteEntitiesSystem\>(this-\>\_entityManager, this-\>\_assetManager));

this-\>\_systems.push\_back(std::make\_shared\<DrawingSystem\>(this-\>\_entityManager, this-\>\_renderer, this-\>\_assetManager, this-\>\_cameraManager, this-\>\_window)); // client side only

this-\>\_systems.push\_back(std::make\_shared\<ClearInputsSystem\>(this-\>\_entityManager, this-\>\_inputManager));

this-\>\_systems.push\_back(std::make\_shared\<InputSystem\>(this-\>\_entityManager, this-\>\_inputManager, this-\>\_thisClientPlayerEntityID)); //add serialiser and udp writer to this system

// here we resize all the maps to be the dimension of the window

for (Map\* map: this-\>\_assetManager-\>getMaps())

\_assetManager-\>getSpecificBackground(map-\>getBackgroundName())-\>resize(\_window-\>getDimensions());

for (RL::Drawable2D\* icon: this-\>\_assetManager-\>getUIelements()) {

if (icon-\>getType() == "player") {

icon-\>resize(Vector2{\_window-\>getDimensions().x \* 7.8f / 100,\_window-\>getDimensions().y \* 10.4f / 100 });

}

else if (icon-\>getType() == "bottomPannel") {

icon-\>resize(Vector2{\_window-\>getDimensions().x \* 31.25f / 100,\_window-\>getDimensions().y \* 15.62f / 100 });

}

else if (icon-\>getType() == "power") {

icon-\>resize(Vector2{\_window-\>getDimensions().x \* 7.8f / 100 / 2,\_window-\>getDimensions().y \* 10.4f / 100 / 2 });

}

}

}
```
The code defines a class McGuyverType that represents the game. The class has several data members including a window object, camera manager object, asset manager object, renderer object, input manager object, and entity manager object. It also has a vector of shared pointers to ISystem objects representing various systems of the game.

The constructor of the McGuyverType class initializes the data members of the class, creates the systems of the game, and resizes all the maps to be the dimension of the window. The destructor of the class does not have any implementation.

The startGame() function starts the game loop and sets the current map being played. The game loop is implemented in the gameLoop() function. The game loop updates the systems of the game and checks if new players connect. The loop also updates the camera position, checks for any checks needed, and receives data from the server. The gameLoop() function also has a loop to update all systems of the game.

The code also has a getter function that returns a shared pointer to the entity manager object.

### - **Collision detection and resolution**
``` cpp
CollisionSystem::CollisionSystem(std::shared\_ptr\<EntityManager\> em, std::shared\_ptr\<AssetManager\> assetManager) : \_assetManager(assetManager)

{

\_em = em;

}

CollisionSystem::~CollisionSystem()

{

}

void CollisionSystem::update(std::vector\<EntityID\> &allEntities)

{

for (EntityID ent : EntityViewer\<Position, Collider\>(\*\_em.get())) {

for (EntityID other : EntityViewer\<Position, Collider\>(\*\_em.get())) {

if ( ent != other) {

bullet\_collisions(ent, other);

obstacle\_collisions(ent,other);

powerUp\_collisons(ent, other);

// body\_collisions(ent, other); // player vs ennemies and player player blocking

}

}

}

}
```
This code snippet is a Collision System implementation in C++ using the raylib game development library for the R-Type game. The Collision System handles collisions between entities in the game and uses the Entity-Component-System architecture to manage entities.

The Collision System constructor takes in a shared pointer to an EntityManager and a shared pointer to an AssetManager, and initializes the EntityManager and AssetManager member variables. The destructor does not have any code.

The update function takes a vector of EntityIDs, representing all the entities in the game, and iterates through entities with both a Position and Collider component using the EntityViewer utility class from the EntityManager. For each entity, it checks for collisions with all other entities with both a Position and Collider component, excluding itself. If a collision is detected, the corresponding collision function is called to handle the collision. The code currently handles collisions between bullets, obstacles, and power-ups.

There is a commented-out function call, body\_collisions, which suggests that the Collision System could also handle player-player and player-enemy collisions, but it is currently disabled.

Overall, this Collision System implementation is a simplistic way to handle collisions in the R-Type game, and could be expanded upon to handle more complex collision scenarios.

### - **Implementing AI and pathfinding**
``` cpp
BotSystem::BotSystem(std::shared\_ptr\<EntityManager\> em, std::shared\_ptr\<AssetManager\> assetManager): \_assetManager(assetManager)

{

\_em = em;

\_assetManager = assetManager;

}

BotSystem::~BotSystem()

{

}

void BotSystem::update(std::vector\<EntityID\> &allEntities)

{

for (EntityID ent : EntityViewer\<AI\>(\*\_em.get())) {

if (\_em-\>Get\<AI\>(ent)-\>style == "simple")

doAI\_simple(ent);

}

}
```
This code snippet is an AI System implementation in C++ using the raylib game development library for the R-Type game. The AI System manages the behavior of entities with an AI component and uses the Entity-Component-System architecture to manage entities.

The constructor takes in a shared pointer to an EntityManager and a shared pointer to an AssetManager, initializes the EntityManager and AssetManager member variables, and assigns the AssetManager parameter to the \_assetManager member variable. The destructor does not have any code.

The update function takes a vector of EntityIDs, representing all the entities in the game, and iterates through entities with an AI component using the EntityViewer utility class from the EntityManager. For each entity, it checks the value of the "style" member variable of the AI component. If the value is "simple", the doAI\_simple function is called to handle the AI behavior.

The doAI\_simple function likely contains the logic for the "simple" AI behavior. The details of this behavior are not shown in the code snippet, but it could involve basic movement or targeting behavior.

Overall, this AI System implementation is a simplistic way to manage AI behavior in the R-Type game, and could be expanded upon to handle more complex AI scenarios.

## **4 - Rendering System**

### - **Overview of the rendering pipeline:**

The rendering pipeline is the process by which 3D models and other graphical elements are converted into images that can be displayed on a screen. The pipeline typically consists of several stages, each of which performs a specific task in the process of rendering a frame of a 3D scene. Here is an overview of the rendering pipeline:

- Scene graph: The first stage of the pipeline involves constructing a hierarchical representation of the 3D scene, known as a scene graph. This graph defines the relationships between objects in the scene and their transformations, such as position, rotation, and scale.

- Culling: Once the scene graph is constructed, the renderer must determine which objects in the scene are visible from the current camera position. This process, known as culling, involves testing each object against the frustum of the camera and discarding any that are outside of its bounds.

- Geometry processing: The next stage involves processing the geometry of the visible objects in the scene. This includes transforming the vertices of each object based on its position, rotation, and scale in the scene graph, as well as applying lighting and texturing effects.

- Rasterization: Once the geometry has been processed, the renderer must convert the 3D scene into a 2D image. This process, known as rasterization, involves breaking down the 3D scene into a series of triangles that can be rendered on the screen.

- Shading: After the triangles have been rasterized, the renderer applies shading algorithms to determine the color and lighting of each pixel. This involves calculating the amount of light that is reflected or absorbed by the surface of each triangle, as well as the color of any textures or materials applied to it.

- Post-processing: Once the shading is complete, the renderer may apply post-processing effects to the final image, such as anti-aliasing, motion blur, or depth of field. These effects can enhance the visual quality of the final image and improve its overall realism.

- Display: Finally, the renderer displays the finished image on the screen, and the process begins again for the next frame of the animation or game.

Overall, the rendering pipeline is a complex and computationally intensive process that requires careful optimization and management to produce high-quality, real-time graphics in modern video games and other 3D applications.

### - **Creating and managing sprites and textures:**
``` cpp
AssetManager::AssetManager(EntityID currentClientID)

{

this-\>\_currentclientID = currentClientID;

loadAllModels();

//load all maps ( maps is the data structure which contains the matching paths to be linked together to create the world

// ex : mountainsPath + big mountainpath + mountainboss room + big mountain boss room

loadAllMaps();

}
```
The AssetManager class is likely responsible for loading and managing all the game assets, such as models, textures, and maps, that are needed to render the game. This class is a common design pattern used in game development to efficiently manage and organize game assets.

The loadAllModels() function is likely responsible for loading all the 3D models that are used in the game, such as the player spaceship, enemy ships, and other objects. These models are usually stored as files on disk, and are loaded into memory when the game starts or when they are first needed.

The loadAllMaps() function is likely responsible for loading all the game levels and maps, which are made up of a collection of 3D models and textures. These maps are usually stored as files on disk, and are loaded into memory when the player starts a new level or map.

The AssetManager class may also be responsible for managing other game assets, such as sound effects and music, which are also stored as files on disk and loaded into memory as needed.

Overall, the AssetManager class is an important component of game development, as it allows developers to efficiently manage and organize game assets, which can be a complex and time-consuming task. By using an AssetManager class, developers can more easily focus on designing and implementing the game itself, without having to worry about the low-level details of loading and managing assets.

### - **Implementing animation and particle system**
``` cpp
int RL::Drawable3D::updateModelsAnimation(int currFrame, int currAnim) // add int as parameter to set to the animation frame of the entity

{

if (currFrame \> this-\>\_animations[currAnim].frameCount) {

currFrame = 0;

}

UpdateModelAnimation(this-\>\_model, this-\>\_animations[currAnim], currFrame);

return this-\>\_animations[currAnim].frameCount;

}
```
This code snippet defines a method called updateModelsAnimation() within the Drawable3D class of the RL namespace. This method is likely used to update the animation state of a 3D model.

The method takes two integer parameters: currFrame, which represents the current frame of the animation, and currAnim, which represents the current animation being played. It returns an integer value, which is the total number of frames in the current animation.

The first thing the method does is check if currFrame is greater than the number of frames in the current animation (this-\>\_animations[currAnim].frameCount). If it is, currFrame is set to 0, which ensures that the animation loops back to the beginning.

Next, the method calls the UpdateModelAnimation() function, passing in the \_model member variable of the Drawable3D object and the animation information stored in the \_animations array at the index specified by currAnim. This function is likely a built-in function provided by a game engine or graphics library, and is responsible for updating the 3D model to display the correct frame of the animation.

Finally, the method returns the total number of frames in the current animation, which can be used to determine when the animation has completed a full cycle.

Overall, this method provides a convenient way to update the animation state of a 3D model within a game or application, and is likely used extensively throughout the codebase to create dynamic and engaging visual effects.

## **5 - Audio system**

### - **Overview of the audio pipeline**

The audio pipeline used in the R-Type game using C++ and raylib is a multi-stage process that involves several components to produce the final audio output. The audio pipeline is responsible for producing high-quality audio that matches the game's visual effects and gameplay, enhancing the player's overall experience.

The audio pipeline consists of three primary stages: audio data creation, audio processing, and audio output.

Audio Data Creation: This stage involves creating the audio assets that will be used in the game. This can involve recording audio using external equipment or generating audio using software. The audio assets are then stored in a format compatible with the game engine, such as WAV, MP3, or OGG.

Audio Processing: In this stage, the audio assets are processed to create a sound mix that is appropriate for the game's audio requirements. This can include adjusting volume levels, adding effects such as reverb, and applying filters to remove unwanted noise.

Audio Output: The final stage of the audio pipeline is audio output. The audio is played through the game engine and output to the player's speakers or headphones. The audio output is synchronized with the game's graphics and gameplay to provide an immersive audio-visual experience.

The audio pipeline can be implemented using various audio libraries available in C++. Raylib provides built-in audio support using the OpenAL library. Audio data can be loaded into memory using raylib's audio loading functions, and audio processing can be done using OpenAL's API. Raylib also provides functions for controlling audio playback, such as adjusting volume levels, pausing, and stopping audio playback.

Overall, the audio pipeline is a crucial component of the R-Type game, providing high-quality audio that complements the game's visual effects and enhances the player's overall experience.

### - **Loading and managing audio assets**
``` cpp
RL::SoundManager::SoundManager()

{

InitAudioDevice();

loadMusic("./Source/Assets/audio\_assets/Music");

loadAudioEffects("./Source/Assets/audio\_assets/Effects");

this-\>\_currentSongPlaying = -1;

this-\>\_musicPaused = false;

this-\>\_songTimePlayed = 0.0f;

this-\>\_shuffleEnabled = false;

this-\>\_musicVolume = 0.1f;

this-\>\_soundEffectVolume = 0.1f;

}
```
The function initializes the audio device using the InitAudioDevice() function. Then, it loads music and sound effects from the specified file paths.

The function initializes several class member variables to their default values, including \_currentSongPlaying, \_musicPaused, \_songTimePlayed, \_shuffleEnabled, \_musicVolume, and \_soundEffectVolume.

Overall, this function sets up the SoundManager class for managing game audio in the ECS-based game.

## **6 - Input Handling**

### - **Overview of the input handling system**

The input handling system in a C++ and Raylib game involves processing user inputs from various devices and mapping them to game actions. Raylib provides built-in functions to handle input events, and an event-based system is commonly used to manage input in a modular and flexible way. In an ECS-based game, the input handling system can be implemented as a separate system or component. Overall, the input handling system is critical for player interaction and enables developers to create more responsive and customizable games.

### - **Implementing player controls**
``` cpp
void update(std::vector\<EntityID\> &allEntities)
```
This is a C++ code snippet that contains a function named "update" that overrides a function from an unknown class. The function takes a reference to a vector of EntityIDs named "allEntities". The code iterates through a range-based loop using the EntityViewer class to retrieve entities that have the components Position, Velocity, EntityModelType, PitchYawRoll, and Collider. The loop uses the EntityID to retrieve pointers to these components using the EntityManager class, which is stored in the member variable "\_em".

The code then checks the modelType of the entity using the EntityModelType component. If it is RL::ModelType::SPACESHIP, it retrieves the Input component and checks the keys pressed in the inputQueue. If the UP or UP2 key is pressed, it calls the "moveUp" function with pointers to the Position, Velocity, Input, and PitchYawRoll components. If the DOWN key is pressed, it calls the "moveDown" function with the same components. If the LEFT or LEFT2 key is pressed, it calls the "moveLeft" function with the same components. If the RIGHT key is pressed, it calls the "moveRight" function with the same components. If the FORWARD key is pressed, it sets the "forward" variable to 1. After processing the input, the code checks the value of "forward" and calls the "moveForward" function with the same components if it is 1, otherwise it moves the entity back by decreasing the z-coordinate of the Position component.

If the modelType of the entity is RL::ModelType::ENNEMY, the code retrieves the Input component and checks the keys pressed in the inputQueue in the same way as for the spaceship. However, it does not call the move functions, and instead sets the z-velocity of the Velocity component to the scroll speed of the current map being played multiplied by the ownerType of the Owner component. Finally, it updates the z-coordinate of the Position component by adding the z-velocity multiplied by the ownerType of the Owner component.

The function ends with an incomplete conditional statement that checks the modelType of the entity, but the code after the conditional statement is not shown.

## **7 - Conclusion**

In conclusion, we believe that our video game built using C++ and Raylib with an ECS architecture provides a robust and efficient approach to game development. We have covered various aspects of the game's codebase, including the ECS architecture, game mechanics, rendering system, audio system, and input handling, providing detailed explanations, code snippets, and examples. We hope this developer documentation has been a helpful resource for understanding and modifying the game's source code, as well as providing guidance for developing your own games using similar technologies.

### - **Final Thoughts and Next Steps:**

As you continue to work on your game development projects, we encourage you to explore the technologies and techniques covered in this developer documentation. We believe that by understanding and utilizing the ECS architecture, Raylib game engine, and related techniques, you can create games that are both engaging and efficient.

Additionally, we recommend that you continue to experiment with and explore other game development tools, frameworks, and engines, and to stay up to date with the latest trends and techniques in the field.

### - **Additional Resources and References:**

We have included a list of additional resources and references for further reading and exploration. These resources include our user documentation, doxygen documentation and server documentation.

### - **Acknowledgments and Contributors:**

Finally, we would like to thank all the contributors who made this developer documentation possible. This includes the developers of Raylib, the creators of the ECS architecture, and the numerous contributors who have shared their expertise and knowledge online. We would also like to acknowledge our own team members and colleagues who contributed to the development of our video game and this documentation. Thank you all for your hard work and dedication!

<br/>
<br/>

————— _Alban de Tourtier - Alexandre Schaffner - Antoine Beaudoux - Mickael Riess —————_

————— _Renan Dubois - Yann-Arthur Tcheumani —————_
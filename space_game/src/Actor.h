#pragma once

#include <vector>
#include "ActorState.h"
#include "Libs/Math.h"
#include "Component.h"
#include "Game.h"
#include <algorithm>
class Actor
{
public:
    Actor(class Game* game);
    virtual ~Actor();

    //called from Game, not overridable
    void Update(float deltaTime);
    //update all components, not overridable
    void UpdateComponents(float deltaTime);
    //actor-specific update
    virtual void UpdateActor(float deltaTime);

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

    ActorState GetState(){
        return state;
    }
    void SetState(ActorState s) { state = s; }

    Vector2 GetPosition() const { return position; }
    void SetPosition(Vector2 pos) { position = pos; }

    float GetScale() const { return scale; }
    void SetScale(float s) { scale = s; }

    void SetRotation(float r) { rotation = r; }
    float GetRotation() const { return rotation; }

    class Game* GetGame() { return mGame; }

private:
    ActorState state;
    Vector2 position;
    float scale;
    float rotation;
    std::vector<class Component*> components;
    class Game* mGame;
};
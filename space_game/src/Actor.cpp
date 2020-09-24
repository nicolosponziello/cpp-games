#include "Actor.h"

Actor::Actor(Game* game)
{
    mGame = game;
    state = ActorState::Active;
    scale = 1.0f;
    rotation = 0.0f;
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    while(!components.empty())
    {
        delete components.back();
    }
}

void Actor::Update(float deltaTime)
{
    if(state == ActorState::Active)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for(auto component : components)
    {
        component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
    
}

void Actor::AddComponent(Component* component)
{
    //insert in order 
    int order = component->GetUpdateOrder();
    auto pos = components.begin();
    while(pos != components.end())
    {
        if(order < (*pos)->GetUpdateOrder())
        {
            break;
        }
        pos++;
    }
    components.insert(pos, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto pos = std::find(components.begin(), components.end(), component);
    if(pos != components.end())
    {
        components.erase(pos);
    }
}
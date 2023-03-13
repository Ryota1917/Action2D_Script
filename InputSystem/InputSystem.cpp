#include "InputSystem.h"

bool InputSystem::Initialize()
{
    mState.Keyboard.Initialze();
    return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepareUpdate()
{
    mState.Keyboard.PrepareUpdate();
}

void InputSystem::Update()
{
}

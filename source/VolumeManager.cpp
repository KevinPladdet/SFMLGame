#include "VolumeManager.h"
#include <iostream>

VolumeManager::VolumeManager(Engine& engine)
    : engine(engine)
{
    arrowWhooshSFX.setBuffer(buffer);
}
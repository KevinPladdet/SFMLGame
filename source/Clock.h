#pragma once

class Engine;
class Clock
{
public:
    Clock(Engine& engine);
    void WaitForSeconds();
        
private:
    Engine& engine;
};
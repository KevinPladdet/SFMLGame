#include "Clock.h"
#include <iostream>
#include <chrono>
#include <thread>

Clock::Clock(Engine& engine)
	: engine(engine)
{
	// Empty for now because I don't need to put anything here
}

void Clock::WaitForSeconds()
{
	std::thread timer([]()
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "3 seconds passed" << "\n";
		// Anything put here will run after the 3 seconds passed
	});
	std::cout << "Thread begun" << "\n";
	// Anything put here will happen during the waiting
	timer.join();
}
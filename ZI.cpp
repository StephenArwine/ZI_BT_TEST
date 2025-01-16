#include "ZI.hpp"
#include "log.hpp"
#include "btlib.h"
#include <signal.h>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <atomic>


std::atomic<bool> interrupt_received(false);
LogLevel logLevel = Verbose;

static void signalHandler(int signum)
{
    switch (signum)
    {
    case SIGINT:
        std::cout << "SIGINT recieved, shutting down" << std::endl;
        interrupt_received = true;
        break;
    case SIGTERM:
        std::cout << "SIGTERM recieved, shutting down" << std::endl;
        interrupt_received = true;
        break;
    default:
        std::cout << "Unhandled signal (" << signum << ") received, shutting down" << std::endl;
        interrupt_received = true;
        break;
    }
}

int generateRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

float generateRandomNumber(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int main()
{
    LogStatus("Bluetooth test for ZonedIn");

    // Setup our signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    std::vector<std::jthread> ZIThreads;
    ZI *zi = new ZI();

    ZIThreads.emplace_back(&ZI::run, zi);
    ZIThreads.emplace_back(&ZI::bluetooth, zi);

    while (!interrupt_received)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete zi;
    return 0;
}

void ZI::run()
{
    LogStatus("Starting ZI thread");
    LogInfo("New pitch will be sent every 10 seconds");

    //  ctrl + c to exit
    while (!interrupt_received)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (bt.connected)
        {
            int strikeZone = generateRandomNumber(0, 9);
            float ballPercentX = generateRandomNumber(-25.0f, 125.0f);
            float ballPercentY = generateRandomNumber(-25.0f, 125.0f);
            int iVelocity = generateRandomNumber(10, 99);

            LogInfo("Sending new pitch");
            bt.sendNewPitch(strikeZone, ballPercentX, ballPercentY, iVelocity);
        }
    }
}

void ZI::bluetooth()
{
    LogStatus("Starting Bluetooth thread");

    bt.run();
}
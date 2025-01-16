#include "bluetooth.hpp"
#include "btlib.h"
#include "log.hpp"
#include <string>
#include <iostream>
#include <cstring>

unsigned char pitchData[] = "";
extern bool interrupt_received;

Bluetooth::Bluetooth()
{
    char filename[] = "devices.txt";

    if (init_blue(filename) == 0)
        return;
}

void Bluetooth::run()
{

    //write_ctic(localnode(), 3, pitchData, 0);
    notify_ctic(localnode(), 3, NOTIFY_ENABLE, btNotifyCallback);
    le_server(btCallback, this, 0);
    close_all();
}

int Bluetooth::sendNewPitch(int zone, float ballX, float ballY, int speed)
{
    int ret = 0;
    int cticn;

    unsigned char *thisPitchData = new unsigned char[64];

    ret = sprintf((char *)thisPitchData, "%d,%.2f,%.2f,%d", zone, ballX, ballY, speed);

    LogInfo(("Pitch Data: " + std::string((char *)thisPitchData)).c_str());
    write_ctic(localnode(), 3, thisPitchData, strlen((char *)thisPitchData));
    return ret;
}

int Bluetooth::btCallback(int node, int operation, int ctic_index, void *userData)
{
    Bluetooth *bt = static_cast<Bluetooth *>(userData);

    if (operation == LE_CONNECT)
    {
        printf("Connected\n");
        bt->connected = true;
    }
    else if (operation == LE_READ)
    {
    }
    else if (operation == LE_DISCONNECT)
    {
        printf("Disconnected\n");
        bt->connected = false;
        interrupt_received = true;
        return (SERVER_EXIT);
    }
    return (SERVER_CONTINUE);
}

int btNotifyCallback(int lenode, int cticn, unsigned char *buf, int nread)
{
    std::cerr << "New pitch notify \n";
    return (0);
}
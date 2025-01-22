#pragma once

// #include "ballPath.hpp"
// #include "target.hpp"

class Bluetooth
{

public:
   Bluetooth();
   void run();
   bool connected;
   static int btCallback(int node, int operation, int ctic_index, void *userData);
   int sendNewPitch(int zone, float ballX, float ballY, int speed);

private:
};
int btNotifyCallback(int lenode, int cticn, unsigned char *buf, int nread);
int sendNewPitch(int zone, float ballX, float ballY, int speed);

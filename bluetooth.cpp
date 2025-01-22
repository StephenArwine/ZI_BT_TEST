#include "bluetooth.hpp"
#include "btlib.h"
#include "log.hpp"
#include "wifiConfig.hpp"
#include "string.h"
#include <string>
#include <iostream>

int pitchint = 1;
unsigned char pitchData[] = "1";

std::string getIP()
{
	FILE *pipe = popen("hostname -I", "r");
	if (!pipe)
	{
		LogError("Error opening pipe");
	}

	char buffer[128];
	std::string ipAddress;
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
	{
		ipAddress += buffer;
	}
	pclose(pipe);
	ipAddress.erase(ipAddress.find_last_not_of(" \n\r\t") + 1);

	return ipAddress;
}

Bluetooth::Bluetooth()
{
}

void Bluetooth::run()
{
	unsigned char mydata[] = "Hello world";
	char filename[] = "devices.txt";
	connected = false;

	if (init_blue(filename) == 0)
		return;

	write_ctic(localnode(), 1, mydata, strlen(reinterpret_cast<const char *>(mydata)));

	write_ctic(localnode(), 3, pitchData, 0);
	notify_ctic(localnode(), 3, NOTIFY_ENABLE, btNotifyCallback);

	std::string ip = getIP();
	std::cout << "Current IP: " << ip << " " << ip.size() << std::endl;

	write_ctic(localnode(), 2, reinterpret_cast<unsigned char *>(ip.data()), 0);

	le_server(btCallback, this, 0);
	close_all();
}

int Bluetooth::sendNewPitch(int zone, float ballX, float ballY, int speed)
{
	int ret = 0;
	int cticn;

	unsigned char *thisPitchData = new unsigned char[64];

	// Format the float values with 2 decimal precision
	ret = sprintf((char *)thisPitchData, "%d,%.2f,%.2f,%d", zone, ballX, ballY, speed);
	std::cerr << thisPitchData << " " << sizeof(thisPitchData) << "\n";
	write_ctic(localnode(), 3, thisPitchData, 16);
	return ret;
}

void parseWifiNetworkData(const std::string &wifiData, std::string &ssid, std::string &password, std::string &confirm)
{
	std::string data = wifiData;
	std::string delimiter = ",";
	size_t pos = 0;

	pos = data.find(delimiter);
	ssid = data.substr(0, pos);
	data.erase(0, pos + delimiter.length());

	pos = data.find(delimiter);
	password = data.substr(0, pos);
	data.erase(0, pos + delimiter.length());

	confirm = data;
}

void handleWriteOperation(int ctic_index)
{
	if (ctic_index == 4)
	{
		unsigned char *data = new unsigned char[64];
		read_ctic(localnode(), 4, data, 64);

		// Parse the data
		std::string wifiData(reinterpret_cast<char *>(data));
		std::string ssid, password, confirm;
		parseWifiNetworkData(wifiData, ssid, password, confirm);

		std::string filePath = "/etc/NetworkManager/system-connections/" + ssid + ".nmconnection";
		WifiConfig thisWifi(ssid, password, filePath);

		if (confirm == "confirm")
		{
			LogInfo("Writing wifi config");
			LogInfo(("SSID: " + ssid).c_str());
			LogInfo(("Password: " + password).c_str());
			LogInfo(("Filepath: " + filePath).c_str());
			if (thisWifi.writeConfig())
			{
				LogInfo("Wifi config written, restarting network manager");
				system("sudo systemctl restart NetworkManager");
			}
			else
			{
				LogError("Wifi config write failed");
			}
		}

		delete[] data;
	}
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
		printf("Read\n");
		std::cerr << ctic_index << "\n";
		if (ctic_index == 2)
		{
			std::string ip = getIP();
			std::cout << "Current IP: " << ip << " " << ip.size() << std::endl;

			write_ctic(localnode(), 2, reinterpret_cast<unsigned char *>(ip.data()), 0);
		}
	}
	else if (operation == LE_WRITE)
	{
		handleWriteOperation(ctic_index);
	}
	else if (operation == LE_DISCONNECT)
	{
		printf("Disconnected\n");
		return (SERVER_EXIT);
	}
	return (SERVER_CONTINUE);
}

int btNotifyCallback(int lenode, int cticn, unsigned char *buf, int nread)
{
	std::cerr << "Notify \n";
	return (0);
}
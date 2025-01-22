#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

class WifiConfig
{
public:
    WifiConfig(const std::string &ssid, const std::string &password, const std::string &filePath);
    ~WifiConfig();
    void setOwner(const std::string &owner);
    void setGroup(const std::string &group);
    void setMode(mode_t mode);
    bool writeConfig();

private:
    std::string ssid;
    std::string password;
    std::string filePath;
    bool writeConfigToFile(const std::string &filePath, const std::string &ssid, const std::string &password);
    bool changeFilePermissions(const std::string &filePath, mode_t mode);
    bool changeFileOwnership(const std::string &filePath, const std::string &owner, const std::string &group);
};

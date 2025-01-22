
#include "wifiConfig.hpp"
#include "log.hpp"

WifiConfig::WifiConfig(const std::string &ssid, const std::string &password, const std::string &filePath)
{
    this->ssid = ssid;
    this->password = password;
    this->filePath = filePath;
}

WifiConfig::~WifiConfig()
{
}

bool WifiConfig::writeConfig()
{
    if (!writeConfigToFile(filePath, ssid, password))
    {
        LogError("Failed to write config file");
        return false;
    }
    if (!changeFilePermissions(filePath, S_IRUSR | S_IWUSR))
    {
        return false;
    }
    if (!changeFileOwnership(filePath, "root", "root"))
    {
        return false;
    }

    return true;
}

bool WifiConfig::writeConfigToFile(const std::string &filePath, const std::string &ssid, const std::string &password)
{
    std::ofstream configFile(filePath);

    if (configFile.is_open())
    {
        configFile << "[connection]\n";
        configFile << "id=" << ssid << "\n";
        configFile << "type=wifi\n";
        configFile << "interface-name=wlan0\n";
        configFile << "autoconnect=true\n\n";

        configFile << "[wifi]\n";
        configFile << "mode=infrastructure\n";
        configFile << "ssid=" << ssid << "\n\n";

        configFile << "[wifi-security]\n";
        configFile << "auth-alg=open\n";
        configFile << "key-mgmt=wpa-psk\n";
        configFile << "psk=" << password << "\n\n";

        configFile << "[ipv4]\n";
        configFile << "method=auto\n\n";

        configFile << "[ipv6]\n";
        configFile << "method=auto\n";

        configFile.close();
        return true;
    }
    else
    {
        LogError(("Unable to open file: " + filePath).c_str());
        return false;
    }
}

bool WifiConfig::changeFilePermissions(const std::string &filePath, mode_t mode)
{
    if (chmod(filePath.c_str(), mode) == 0)
    {
        return true;
        LogInfo("File permissions changed");
    }
    else
    {
        LogError(("Unable to change permissions for file: " + filePath).c_str());
        return false;
    }
}

bool WifiConfig::changeFileOwnership(const std::string &filePath, const std::string &owner, const std::string &group)
{
    struct passwd *pwd = getpwnam(owner.c_str());
    struct group *grp = getgrnam(group.c_str());

    if (pwd == nullptr || grp == nullptr)
    {
        LogError(("Unable to find user or group: " + owner + ":" + group).c_str());
        return false;
    }

    if (chown(filePath.c_str(), pwd->pw_uid, grp->gr_gid) == 0)
    {
        return true;
        LogInfo("File ownership changed to root");
    }
    else
    {
        LogError(("Unable to change ownership for file: " + filePath).c_str());
        return false;
    }
}
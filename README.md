Building and installing
-----------------------

    if you dont have Cmake and make install with
    sudo apt-get -y install make
    sudo apt-get -y install cmake


    git clone https://github.com/StephenArwine/ZI_BT_TEST
    cd ZI_BT_TEST
    mkdir build
    cd build
    cmake ..
    make

 Run
-----------------------

    The "ADDRESS" in devices.txt must have your devices MAC Adress entered, otherwise it will advertise as node 1000 without our custom services.
    eg. ADDRESS=2C:CF:67:4B:9B:A5 for the Raspberry PI used.

    from the ZI_BT_TEST folder.

    sudo build/ZI_BT_TEST     **must be ran from the directory that has Devices.txt in it.**

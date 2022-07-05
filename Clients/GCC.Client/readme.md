### base 
https://electrosome.com/cross-compile-openwrt-c-program/

### compiling 
source openwrt_profile/openwrt_xiaomi_compile.config
mips-openwrt-linux-g++ -o ldnode.mips src/app.cpp


### Router Xiaomi 
OpenWrt - 21
CPU - MediaTek MT7620

### Raspberry 
sudo apt-get install libssl-dev
g++ -Wall -v src/app.cpp -o ldnode -lssl -lcrypto

####Autostart

sudo nano /lib/systemd/system/ldnode.service

[Unit]
Description=My LdService Service
After=multi-user.target

[Service]
Type=idle
ExecStart=/home/pi/ldnode

[Install]
WantedBy=multi-user.target


sudo chmod 644 /lib/systemd/system/ldnode.service
sudo systemctl daemon-reload
sudo systemctl enable ldnode.service
###MacOS
(not working)
brew install openssl
export LDFLAGS="-L/opt/local/lib"
export CPPFLAGS="-I/opt/local/include/openssl"
g++ -Wall -v src/app.cpp -o ldnode -lssl -lcrypto

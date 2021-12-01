. openwrt_profile/openwrt_21.02.config &&
mipsel-openwrt-linux-g++ -Wall -I $STAGING_DIR/target-*/usr/include -L $STAGING_DIR/target-*/usr/lib -o ldnode.mips src/app.cpp -lssl -lcrypto

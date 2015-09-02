
WRT=/home/vova/tools/openwrt_mips_toolchain/bin
set PATH=$WRT:$PATH

$WRT/mips-openwrt-linux-g++ -std=c++11 wget.c main_wget.c -o my_wget

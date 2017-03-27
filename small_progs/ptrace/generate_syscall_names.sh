
perl -n -e '/define\s+__NR_([a-zA-Z_]+)\s+([0-9]+)/ && print "syscallNames[$2] = \"$1\";\n"' \
/usr/include/x86_64-linux-gnu/asm/unistd_64.h > ./syscall_names.cpp


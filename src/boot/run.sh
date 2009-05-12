# Run the BOCHS simulator

make clean
make
if [ "$?" != "0" ]; then
	exit 1
fi

/usr/local/bin/bochs -q -f ../../env/bochsrc_pc_with_nic.cfg


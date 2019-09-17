qemu-system-${1} -drive file=os.bin,media=disk,if=ide -m 512M

# qemu-img convert -pO vmdk os.bin hard_disk.vmdk
# vmware-vdiskmanager hard_disk.vmdk -x 10G
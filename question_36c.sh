# Compare mknod and mkfifo commands using strace (-c prints the system call summary)
rm -f fifo_mknod fifo_mkfifo
strace -c -o mknod_trace.txt mknod fifo_mknod p
strace -c -o mkfifo_trace.txt mkfifo fifo_mkfifo
echo "mknod summary:"
cat mknod_trace.txt
echo "mkfifo summary:"
cat mkfifo_trace.txt
rm -f fifo_mknod fifo_mkfifo mknod_trace.txt mkfifo_trace.txt

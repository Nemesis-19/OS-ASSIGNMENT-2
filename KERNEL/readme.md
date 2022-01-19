Initially we make a copy of existing kernel in a new directory and then go to that directory to make a custom kernel with a new system call. We name the intial kernel using the "stock" keyword. In the first step, we have to make entry of a new system call in "arch/x86/entry/syscalls/syscall_64.tbl" because this table used to identify system calls from unique system call number. We make it under 448th secion, and name it according to naming convention in the question. Secondly, we will define our system call in "kernel/sys.c" file as this file contains  definations of systemcalls and will automatically be compiled with the new kernel. 

Under this syscall we will add our own wrtten code defining the functionality asked in the question. Under this code, we use SYSCALL_DEFINATION3 predenomination, and aa parameters we take to arrays, input and put array, 2 integers, defining the number of rows and columns, and finally the length. Then we use __copy_from_user() and __copy_to_user() system calls to copy data from user space to kernel space and then again from kernel space to user space then returning the copied array. 

For the testing file we use the logic of making an array and using malloc to assign it space (double pointer array as we are creating 2d arrays, at first malloc the rows, then malloc the collumns through for loop), and then provide it values using the num variable and provide it with sum random operation in the nested for loop at the time of assigning it to respected elements in the array, then finally run the system call (syscall()) to check our system calls credebility and is it correct or not. Then finally we will print the output of both the arrays and see if the copy function is successfull or not, which it most probably would be.

Then finally we compile kernel, using the commands provided in the gc. 

make   # for compiling the kernel
sudo make modules_install # for compiling and installing the modules
sudo cp  arch/x86_64/boot/bzImage /boot/vmlinuz-linux-5.14.21
sudo cp System.map System.map-5.14.21
sudo mkinitcpio -k 5.14.21 -g /boot/initramfs-linux-5.14.21.img
sudo grub-mkconfig -o /boot/grub/grub.cfg

sudo reboot

Then on next reboot, we will have modified kernel and we can run our system call in c program by using syscall() function and can pass the appropriate system call number which we had assigned in the system call table, in our case that is 448. And finally test our output using the main.c file used for testing.

Then for finding diff between the stock and the modfied kernel, we will use diff command and will extract a patch from custom kernel.
The commands that we use for this are :

sudo diff -rupN  path-to-stock-kernel/ path-to-modified-kernel/ > original.patch # for making patch
sudo diff path-to-stock-kernel_file/ path-to-modified-kernel_file/ # for making a text file that conatins difference
sudo diff /home/satyam/build/linux-5.14.21/arch/x86/entry/syscalls/syscall_64.tbl /home/satyam/build/linux-5.14.21-stock/arch/x86/entry/syscalls/syscall_64.tbl > table_diff.txt
sudo diff /home/satyam/build/linux-5.14.21/kernel/sys.c /home/satyam/build/linux-5.14.21-stock/kernel/sys.c > sys_C_file_diff.txt

and finally after we obtain our patch we are done.
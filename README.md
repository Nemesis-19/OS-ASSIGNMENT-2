# OS-ASSIGNMENT-2
IPC: Used Exec family system calls to use generate 2 processes which  uses SIGTERM handler to send-receive random numbers. Kernel: made  system call which 
copies one 2D floating point matrix to another.

There are 3 code files in IPC, SR, ST & main. main uses exec call to intiate SR and ST programs. SR generates a randum number and sends it to main using the 
SIGTERM handler. ST generates a random number and uses __rdtsc functionality to generate current time and sends it to main. main has to recieve from both SR 
& ST and print the data.

There is only 1 code file in KERNEL, which is the testing file, used to proove that the system call made is working perfectly. Inside the system call, simple 
functionality of __copy_from_user and __copy_to_user is used to copy data from virtual space to user space. The kernel patch is provided as evidence.

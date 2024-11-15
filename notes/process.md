# Process
- Instance of a running program
- Has:
    - An owner
    - Parent process
        - Parent - child relationship for processes
    - State
    - Capabilites / privileges
    - Resources dedicated to it
        - Files opened, memory allocated to it
    - Contains one or more thread that can execute instructions
    - Own address space

    ## Process State
    - Running: Currently executing instructions
    - Runnable: Ready to run when resources are available
    - Sleeping: Waiting for something
    - Stopped: In the process of exiting
    - Zombie: Has exited but its parent process has not accepted
        - Remains in zombie state until parent process removes
    - Timesharing: Interrupt at a certain time ending Process 1 -> Exception Hanlding (Deals with timer going off) -> Allows Process 2 to execute
        - Repeats

## Concurrency vs Parallelism
- Concurrency: Switching between P1 and P2
    - Gives the appearance of both runing at the same time
- Parallelism: Running in parallel
    - If you have more cores in a processor

## Controlling Processes
- Process is created using its parent process
- Each process has a unique process id (PID)
- getpid(): Returns pid
- getppid(): Returns your parents pid

## How a Process is Created
- fork() system call is only way to create a process
    - Creates a new address space for child
    - Copies parents address space to child
    - Point kernel resources to the parents resources (i.e. open files)
    - Places child on 'Ready to Run' queue
- fork(): returns twice
    1. returns childs pid
    2. returns 0 to child

## Waiting for a child process to complete
- wait: waits for any child to complete
- waitpid: waits for a specific child to complete
- Only applies to direct child
- **  Both system calls can provide information on how the process terminated
- Normal termination of process
    - `return 0`
    -  Ctrl + c (in terminal)

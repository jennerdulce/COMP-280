# Zombies

- Process that has terminated but Parent has not Acknowledged its termination.
- While not acknowledged, will continue using resources
- Need to use the `wait()` system call
- Signal Handler can help do this

![Signal Handler](img/Screenshot%202024-11-20%20at%207.12.54%20PM.png)
![Establish Signal Handler](img/Screenshot%202024-11-20%20at%207.13.56%20PM.png)
![How to Examine](img/Screenshot%202024-11-20%20at%207.15.12%20PM.png)
- errno: global veriable
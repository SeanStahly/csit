rsync -azP $HOME/* u1:~/
mpirun -np 1 -f machinefile ./genv3.out 

rsync -azP $HOME/* u1:~/
mpirun -np 16 -f machinefile ./genv3.out 

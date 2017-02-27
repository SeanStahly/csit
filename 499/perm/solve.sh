rsync -azP $HOME/* u1:~/
mpirun -np 8 -f machinefile ./solveGrid.out 

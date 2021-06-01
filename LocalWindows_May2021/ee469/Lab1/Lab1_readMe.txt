Lab 1 Read Me

Compile With: 
gcc -fopenmp laplace_serial.c -lm -o laplace_serial

Description:
The description on this lab was very vague and I missed class on thursday so I did my best to understand what was being asked. 
I read that while loops couldn't be parallelized and the lecture slides only gave examples of for loops so I opted to parallelize the two for loops included in main, however,
this seems to have broken the initial pourpose of the code by running all the iterations. 
despite the original code stopping at 3372, the new code runs all 4000 iterations. 
I belive this is beacause when the threads are done, dt gets reset to 0 so the while loop only exits once all 4000 iterations are complete.



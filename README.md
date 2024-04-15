# linearTimeCheckpointing

This is the implementation of linear-time checkpoints finding algorithm in the paper: GPU Memory Usage Optimization for Backward Propagation in
Deep Network Training.

After executed, the program will ask the user to fill in each parameter.
The number of layers should be less than 100000 to avoid segmentational faults in c++ program.
The number of parameters in each DNN layer should be less than 2^32 to avoid overflow in c++ program.

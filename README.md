# linearTimeCheckpointing

This is the implementation of linear-time dynamic checkpoint algorithm in the paper: GPU Memory Usage Optimization for Backward Propagation in
Deep Network Training.

After executed, the program will ask the user to fill in
- The number of layers in DNN, and
- The number of parameters in each layer.

There are restrictions on the size of the parameters: 
- The number of layers should be less than 100000 to avoid segmentational faults in c++ program, and
- The number of parameters in each DNN layer should be less than 2^32 to avoid overflow in c++ program.

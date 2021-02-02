# Machine Learning Experiments

This code contains all the linear and nonlinear models that have been investigated. Please refer to the original paper to understand some of the terms being used here.

Here are some important points to note when using the code:

census = The dataset consisting of "seen" ciphers.
censustest = The dataset consisting of the "unseen" ciphers for generalization experiments.
label_fix = The function to modify the number of Active S-boxes into the secure (1) and insecure (0) classes. The threshold is currently set to 1.5.
perm_fix = The function to modify the permutation pattern from 4 separate values to a singular value (rep_2 to rep_1).

See the comments in the code for further instructions.

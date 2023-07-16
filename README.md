# Deep Dive: SIMD Programming
by Jose Anton S. Alonzo | CEPARCO S11

## Project Specification (from Attempt 1)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/457e537a-1978-4838-9e60-4eb5a8fda0a6)

For this project, the input is assumed to be [0, 1, 2, 3, ..., n-1]. Thus, the first five non-zero values of the output are expected to be [21, 28, 35, 42, 49]

## BONUS: Best CUDA Implementation
Assuming Block Size = 1024 <br>
https://colab.research.google.com/drive/1zqJSL-JUWQnzbzWs7tM8ADjbBfq9xfyM?usp=sharing

## Comparative Results

### Average Execution Time

| Vector Size | C | x86-64 | SIMD-YMM | Best CUDA |
| :---: | :---: | :---: | :---: | :---: | 
| 2^20 | 14.67 ms | 23.93 ms | 25.07 ms | 213.74 us |
| 2^24 | 184.47 ms | 250.17 ms | 259.83 ms | 3.26 ms |
| 2^28 | 2.60 s | 3.82 s | 3.98 s | 23.59 ms |

### Console Output

#### *n = 2^20*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/f3022d93-af7b-467b-aff4-fe1a713fbc56)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/ed77f75c-2673-4d23-8b22-5b0df67adcd1)

#### *n = 2^24*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/d2381386-5341-46c8-b468-c95ef59d9fe5)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/e039d6c4-c768-45ab-ba26-1a73c5ad11b0)

#### *n = 2^28*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/414d305b-2454-4ded-8de3-401759e2f263)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/assets/87627127/44147ee3-5e99-4f14-bbee-0a5018501fe6)

## Analysis of Results

It is expected that other optimized implementations of the program will have a faster execution time in comparison to the initial C implementation. However, this project reports that the assembly language implementations of the program execute slower than the C implementation. Furthermore, the execution time of the x86-64 version of the program and the execution time of the SIMD version using YMM registers are relatively close in speed. Thus, the results unfortunately do not align with the expected trend. Various reasons for such outcomes have been hypothesized. Primarily, the manner in which the programs were written may not be in its most optimized form, implying the need for further refactorization of the code and maximization of the x86-64 and SIMD features. <br>

It is also important to note that while the outputs of the three main implementations appear to be correct as displayed by the first five non-zero values of the vector, the recorded error count claims that the x86-64 version of the program produces a correct output with respect to the output of the C program. On the other hand, the SIMD-YMM version of the program recorded multiple errors which are unseen. It is inferred that the current implementation of the SIMD-YMM program possesses a logical error that does not account for the very last group of elements in the input vector. Specifically, this implementation utilizes multiple (i.e. 7) YMM registers, in which the input vector shifts a certain number of times for every register. In hindsight, this would allow for the vertical addition of all 7 registers simultaneously to produce the desired result in the output vector. However, this algorithm is susceptible to the accessing of undeclared memory spaces that are out-of-bounds. <br>

In terms of the bonus CUDA implementation, it utilizes the grid-stride approach within the process kernel and overall pre-fetching and memory advising. This eliminates any overhead time caused by memory fault segmentations and so on that can affect the execution time fo the program. As expected, the runtime of the CUDA implementation of the program is significantly faster than that of the C implementation. Although, considering the inconclusive results of the assembly-language implementations, the performance of the CUDA implementation in contrast is uncertain, but it is expected to be at par. <br>

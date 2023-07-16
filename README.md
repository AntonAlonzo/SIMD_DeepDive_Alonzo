# Deep Dive: SIMD Programming
by Jose Anton S. Alonzo | CEPARCO S11

## Project Specification (from Attempt 1)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/specs.png)

For this project, the input is assumed to be [0, 1, 2, 3, ..., n-1]. Thus, the first five non-zero values of the output are expected to be [21, 28, 35, 42, 49]

## BONUS: Best CUDA Implementation
Assuming Block Size = 1024 <br>
https://colab.research.google.com/drive/1zqJSL-JUWQnzbzWs7tM8ADjbBfq9xfyM?usp=sharing

## Comparative Results

### Average Execution Time

| Vector Size | C | x86-64 | SIMD-YMM | Best CUDA |
| :---: | :---: | :---: | :---: | :---: | 
| 2^20 | 16.50 ms | 28.70 ms | 30.57 ms | 213.88 us |
| 2^24 | 264.20 ms | 343.73 ms | 354.37 ms | 3.26 ms |
| 2^28 | 3.29 s | 5.22 s | 5.42 s | 23.59 ms |

### Console Output

#### *n = 2^20*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/20_asm.PNG)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/20_cuda.PNG)

#### *n = 2^24*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/24_asm.PNG)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/24_cuda.PNG)

#### *n = 2^28*
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/28_asm.PNG)
![image](https://github.com/AntonAlonzo/SIMD_DeepDive_Alonzo/tree/main/imgs/28_cuda.PNG)

## Analysis of Results

The results were gathered when the project was built in Debug Mode. <br>

It is expected that other optimized implementations of the program will have a faster execution time in comparison to the initial C implementation. However, this project reports that the assembly language implementations of the program execute slower than the C implementation. Furthermore, the execution time of the x86-64 version of the program and the execution time of the SIMD version using YMM registers are relatively close in speed. Thus, the results unfortunately do not align with the expected trend. Various reasons for such outcomes have been hypothesized. Primarily, the manner in which the programs were written may not be in its most optimized form, implying the need for further refactorization of the code and maximization of the x86-64 and SIMD features. <br>

It is also important to note that while the outputs of the three main implementations appear to be correct as displayed by the first five non-zero values of the vector, the recorded error count claims that the x86-64 version of the program produces a correct output with respect to the output of the C program. On the other hand, the SIMD-YMM version of the program recorded multiple errors which are unseen. It is inferred that the current implementation of the SIMD-YMM program possesses a logical error that does not account for the very last group of elements in the input vector. Specifically, this implementation utilizes multiple (i.e. 7) YMM registers, in which the input vector shifts a certain number of times for every register. In hindsight, this would allow for the vertical addition of all 7 registers simultaneously to produce the desired result in the output vector. However, this algorithm is susceptible to the accessing of undeclared memory spaces that are out-of-bounds. <br>

In terms of the bonus CUDA implementation, it utilizes the grid-stride approach within the process kernel and overall pre-fetching and memory advising. This eliminates any overhead time caused by memory fault segmentations and so on that can affect the execution time fo the program. As expected, the runtime of the CUDA implementation of the program is significantly faster than that of the C implementation. Although, considering the inconclusive results of the assembly-language implementations, the performance of the CUDA implementation in contrast is uncertain, but it is expected that the assembly-language versions will perform significantly better due to the reduced data transfer time. <br>

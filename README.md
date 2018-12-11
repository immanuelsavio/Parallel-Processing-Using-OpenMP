# Parallel-Processing-Using-OpenMP

### Parallel Processing
Parallel Processing is the method of programming using the smallest unit of a program called a thread. Using threads while programming makes the program faster during execution and also easy to identify errors.

### OpenMP
[OpenMP©](https://www.openmp.org/) is a library by Intel which uses the power of the intel processors to process any program parallely. I have written the program in C Language as any program written in C language is atleast 40% faster during execution than the same program written in any other programming language.

I have used some parallel programs to find the extent of parallelization of my computer which has a Intel Core i5 6200u processor.

### How to use?
The programs have been written in Microsoft Visual Studio and have used certain Visual Studio functions to calculate speed of the processor etc. So running this in Ubuntu will give you certain errors.

For convinence the programs have been made into header files and then included into a parent program ```OpenMP.c``` All you have to do is to donwload the [OpenMP](https://www.openmp.org/resources/openmp-compilers-tools/) library and then run the program. If you want to run the program in another IDLE or in windows then you must remove the Visual Studio codes which comes in ```Windows.h``` and run it with ```gcc <filename> -fopenmp```.

Please leave a Star if you liked it. Please fork it and experiment. happy Open Sourcing!!!!

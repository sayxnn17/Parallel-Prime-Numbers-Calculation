# FASTprime – Parallel Prime Number Computation

## Description

This project is based on computing prime numbers using parallel processing.  
The main idea is to divide the given range into multiple parts and assign each part to a child process created using `fork()`.

Each process computes prime numbers in its assigned range, and the results are written into an output file. Execution time is measured to analyze performance improvement when the number of processes increases.

---

## Objective

- To understand parallel processing using processes  
- To implement multi-process computation using `fork()`  
- To divide workload among child processes  
- To measure execution time  
- To analyze performance using graphs  

---

## System Calls Used

The following system calls and functions are used in this project:

- `fork()` → To create child processes  
- `signal()` → To handle signals  
- `kill()` → To notify parent process  
- `open()` → To create/open output file  
- `write()` → To store prime numbers  
- `close()` → To close file  
- `gettimeofday()` → To measure execution time  
- `system("lscpu")` → To display CPU details  

---

## How the Program Works

1. The program first displays CPU information.  
2. User enters the range and number of processes.  
3. The range is divided equally among all processes.  
4. Child processes are created using `fork()`.  
5. Each child computes prime numbers in its sub-range.  
6. Prime numbers are written into `prime.txt`.  
7. Execution time is measured.  
8. Performance is analyzed using graphs.  

---

## Files Included

- `fastprime.c` :Source code of the program  
- `Report.pdf` : Detailed project report  
- `Graphs.pdf`: Exection time vs no. of children
- `Tables.pdf` : Execution time tables  
- `prime.txt` : Sample output file containing prime numbers  

---

## Experimental Details

The program was tested for different numbers of processes:
1,2,3,4,5,6,7,8,9,10,11,12

Ranges tested include:

- 1000 – 10000  
- 50000 – 100000  
- 1000 – 100000  

Graphs were plotted between number of processes and execution time.

---

## Observations

- Execution time decreased as the number of processes increased.  
- Parallel processing improved performance.  
- Best performance was observed near the number of CPU cores.  
- Too many processes caused overhead.  
- Larger ranges showed better speedup.  

---

## Conclusion

This project demonstrates that parallel processing significantly reduces execution time. By dividing the workload among multiple processes, CPU utilization improves and computation becomes faster. However, creating more processes than available cores may reduce efficiency due to overhead.

---

## Author

Name: Anudeep  
Roll No: 24CS8100

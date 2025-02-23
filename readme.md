# Implementing PBWT

> This is my implementation of algorithm 1-4 from Richard Durbin's [Efficient haplotype matching and storage using the positional Burrows-Wheeler transform (PBWT)](https://pubmed.ncbi.nlm.nih.gov/24413527/) paper.

## project structure

```
pbwt_project/
│
├── include/
│   └── pbwt.h                   # header file for PBWT class and function declarations
│
├── src/
│   ├── main.cpp                 # entry point
│   ├── pbwt_algos.cpp           # implementation of algorithms 1-4 (Separate mode)
│   ├── pbwt_algos_single_sweep.cpp # implementation of algorithms 1-4 (Single Sweep mode)
│   ├── utils.cpp                # utility functions
│
├── makefile                    
└── readme.md                   
```

---

## run the code

**build**

```bash
git clone https://github.com/sajontahsen/positional-burrows-wheeler-transform.git
cd positional-burrows-wheeler-transform
mkdir build
make
```
**run algorithms on separate mode (default)**
```bash
./build/pbwt
```
**run algorithms on single-sweep mode (default)**
```bash
./build/pbwt single 
```

---

## console output

- TBA

---
*PRs and suggestions are always welcome!*


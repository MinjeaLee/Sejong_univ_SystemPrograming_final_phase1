# Network-Based Calculation Server and Clients

## Overview
This project implements a server capable of performing addition and multiplication operations, serving requests from multiple clients. Each client request is processed in a separate thread, allowing concurrent handling of multiple clients.

## Author Information
- **Author:** Lee Minjae
- **ID:** 21011741
- **Department:** Information Security
- **Date:** 2023.12.06
- **Contact:** leejoy2@sju.ac.kr

## Installation
To set up the server and client programs, follow these steps:
1. Clone the repository to your local machine.
2. Compile the code using the provided Makefile:
```bash
make all
```

## Usage
1. Start the server by running: 
   ```bash
   ./server
   ```
2. In separate terminal windows, start one or more clients by running:
   ```bash
   ./client_add
   ```
   or
   ```bash
   ./client_mul
   ```
   depending on the desired operation (addition or multiplication).

3. Follow the on-screen prompts on each client to input numbers and receive the calculation results from the server.

## Features
- The server handles each client request in a separate thread.
- Supports addition (`client_add`) and multiplication (`client_mul`) operations.
- Clients communicate with the server over TCP/IP.

## License
This project is open-source and freely available for modification and distribution.
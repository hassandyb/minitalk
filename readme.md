# Minitalk

## Overview
**Minitalk** is a project designed to develop a small data exchange program using UNIX signals. It provides an opportunity to practice inter-process communication (IPC) with signals and to deepen your understanding of signal handling in C.

## Project Goals
- Create a client-server communication system using UNIX signals.
- Implement robust error handling and manage memory efficiently.
- Understand and apply signal handling in C programming.
- Design a system that supports concurrent communication from multiple clients.

## Features
### Mandatory Part
- **Server**:
  - Starts and prints its PID.
  - Receives strings from clients using UNIX signals.
  - Prints received strings promptly.
  - Can handle multiple clients sequentially without needing a restart.
  
- **Client**:
  - Takes two parameters: server PID and the string to send.
  - Sends the string to the server using UNIX signals.
  
- **Communication**:
  - Uses `SIGUSR1` and `SIGUSR2` signals for communication.
  - Does not use any other type of signal.

### Bonus Features
- **Acknowledgement**:
  - The server sends an acknowledgment signal back to the client for each message received.

- **Unicode Support**:
  - The system can handle and transmit Unicode characters.

## Implementation Details
### Signal Handling
The core of Minitalk relies on UNIX signals to facilitate communication between the client and server. The signals used are:
- `SIGUSR1`
- `SIGUSR2`

The client sends data to the server, which then decodes the received signals to reconstruct the transmitted string. The server processes these signals and prints the message efficiently.

### Error Handling
- Thorough error checking is implemented to ensure that the program does not quit unexpectedly.
- The client and server handle all potential errors gracefully and maintain stable operation.

### Memory Management
- The project ensures no memory leaks occur by properly freeing allocated memory.
- The use of global variables is minimized and justified.

### Makefile
- A Makefile is provided to compile the source files into the `client` and `server` executables.
- The Makefile includes rules for compiling, cleaning, and rebuilding the project, without relinking unnecessarily.

## Setup and Usage
1. **Compiling the Project**:
   ```bash
   make

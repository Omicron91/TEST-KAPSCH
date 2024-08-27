# TEST-KAPSCH

The task involves implementing a simple number factorization application using a **CLIENT-SERVER** model. The client requests the factorization of a number, while the server is responsible for calculating the factorization and returning the result. The task requires the creation of two console applications, client and server, which communicate via the TCP protocol.

#### OBJECTIVES

* Implementation of CLIENT and SERVER using TCP connections.
* Optimize bandwidth usage and dynamic memory.
* The server must handle up to 10 simultaneous connections.
* Use of multithreading.
* The CLIENT must send a list of numbers to factorize.
* A connection will be opened for each number in the list.
* Each connection will be processed by a separate thread.
* Print data in "FIFO" order.
* The development must be done in C and run on Linux.

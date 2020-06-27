README

My Threads Project is simulating the ticket ordering system for the Tonight show. This is done by using
the phonecall function which tries to connect each call to a line. it checks this using by comparing a 
variable connected to the NUM_LINES, if they are equal all the lines are full and gets message
'Thread [id] is calling line, busy signal the call can't be connected. 
If the lines are not full the caller gets a message 'Thread [id] has available line, call ringing'.
This is done inside of a critical section using conected_lock semaphore which allows only one thread to use
1 line at a time. Then the connected variable is updated. The callers speaking to operators is shown 
by printing 'Thread [id] is speaking to operator' and ordering a ticket is simulated by sleeping for a 
few seconds. The message 'Thread [id] has bought a ticket!' is printed and connected is updated inside a
critical section of connected_lock. The meassage 'Thread [id] has hung up!'is printed at the end.
The main function is used to initialize all the semaphores and to create all the threads using pthread_create
inside of a for loop. The number of call to be simulated is taken as an argument for the main function and 
if the number of calls is less than 1 or greater than 240, an error message is printed.The threads are 
reaped at the end using pthread_join inside of a for loop.


Video Link - https://www.youtube.com/watch?v=WMeoPOrrntg&feature=youtu.be
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

// 1) you need a test in case you chnaged the process id
// 2) understand what is the relink




// void handler(int signum)
// {
//     printf("SIGUSR1 have been recieved ...\n");
// }
// int main ()
// {
//     signal (SIGUSR1, &handler);


//     int a = kill(getpid(), SIGUSR1);
//     int b = kill(12121, SIGUSR1);
//     int c = kill(getpid(), SIGUSR1);
//     printf("%d\n%d\n%d\n", a, b, c);
// }

// kill function is used to send a signal to a process or a group of processes;
// signal function is used to change the behavior of a signal.
// sigaction function is used to change the behavior of a specified signal.

//----------------------------
// int kill(pid_t pid, int sig);
// void (*signal(int sig, void (*func)(int)))(int) | example : signal(SIGINT, sigint_handler)

// int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
// struct sigaction {
    // union {
    //     void (*sa_handler)(int);
    //     void (*sa_sigaction)(int, siginfo_t*, void*);
    // } sa_u;
    // sigset_t sa_mask;
    // int sa_flags;
    // };

//------------------------------
// The kill function returns 0 on success, and -1 on error. The errno global variable is set to indicate the error.
//------------------------------
// to find out the ascii of a chr and it s binary ==> type python the for ascii type >>>>> ord('char') <<<<<
// - for binary type bin (ord('char'))
//-----------------------------------------------------------------
// sigaction function parameters meaning :
// int: This is the signal number that triggered the signal handler. It can be used to determine which signal caused the signal handler to be invoked.

// siginfo_t*: This is a pointer to a structure containing information about the signal. The structure contains information about the signal, such as the process ID of the sender and the signal value. This parameter is only passed to the signal handler if the SA_SIGINFO flag is set in the sa_flags field.

// void*: This is an optional parameter that can be used to pass additional data to the signal handler. It is not used in many cases, and its usage is implementation-dependent.
//--------------------------------
// n C, siginfo_t is a struct that is used to store information about a signal. It is defined in the <signal.h> header file 
// and contains various fields that provide information about the signal, such as the signal number, 
// the sender's process ID, and the signal's value (if applicable). The struct is used in conjunction with the sigaction() function, 
// which allows a program to specify how it should handle signals.
// example of how siginfo_t struct looks like :
// struct siginfo {
//     int      si_signo;    /* Signal number */
//     int      si_errno;    /* If non-zero, an errno value associated with this signal */
//     int      si_code;     /* Signal code */
//     pid_t    si_pid;      /* Sending process ID */
//     uid_t    si_uid;      /* Real user ID of sending process */
//     void    *si_addr;     /* Address of faulting instruction */
//     int      si_status;   /* Exit value or signal */
//     long     si_band;     /* Band event (was int in glibc 2.3.2 and earlier) */
//     union sigval si_value; /* Signal value */
// };





// an example  prints the pid the it stops until it received a signal (like usr1 2 and sigint)the it does an action that we handled :
// void sigusr1_signal_handler ( int signum)
// {
// 	printf("A SIGUSR1 signl have been received ...\n");
// }
// void sigusr2_signal_handler ( int signum)
// {
// 	printf("A SIGUSR2 signl have been received ...\n");
// }
// void sigint_signal_handler ( int signum)
// {
// 	printf("A SIGINT signl have been received ...\n");
// }

// int main ()
// {
// 	struct sigaction ssusr1, ssusr2, ssint;
// 	ssusr1.sa_handler = &sigusr1_signal_handler;
// 	ssusr2.sa_handler = &sigusr2_signal_handler;
// 	ssint.sa_handler = &sigint_signal_handler;

// 	sigaction (SIGUSR1, &ssusr1, NULL);
// 	sigaction (SIGUSR2, &ssusr2, NULL);
// 	sigaction (SIGINT, &ssint, NULL);
// 	printf("%d\n", getpid());
// 	while(1)
// 	{
// 		// printf("waiting a signal ... | %d\n", getpid());
// 		pause();
// 		// sleep(1);
// 	}

// how can we user only one signal handler?
// void sh (int signum)
// {
//     if(signum == SIGUSR1)
//         printf("A SIGUSR1 signl have been received ...\n");
//     else if(signum == SIGUSR2)
//         printf("A SIGUSR2 signl have been received ...\n");
//     else if(signum == SIGINT)
//         printf("A SIGINT signl have been received ...\n");
//     else
//         printf("Signal not recognized...\n");

// }


// int main ()
// {
// 	struct sigaction sr;// signals receiver
// 	sr.sa_handler = &sh;


// 	sigaction (SIGUSR1, &sr, NULL);
// 	sigaction (SIGUSR2, &sr, NULL);
// 	sigaction (SIGINT, &sr, NULL);
// 	printf("%d\n", getpid());
// 	while(1)
// 	{
// 		// printf("waiting a signal ... | %d\n", getpid());
// 		pause();
// 		// sleep(1);
// 	}
// }
//-------------------------------------------------------------
// example shows how can we user info paramter to show the process pid
// Other fields in the siginfo_t structure include:

// si_pid  to process identefication
// si_uid: the user ID of the sender of the signal
// si_status: the exit status of a child process that sent the signal
// si_value: a union that can hold the signal value.


// void my_sigaction(int signum, siginfo_t *info, void *ptr) 
// {

//     printf("%d\n", info->si_uid);
// }

// int main() {
//     struct sigaction action;
//     action.sa_sigaction = &my_sigaction;
//     action.sa_flags = SA_SIGINFO;
//     // sigemptyset(&action.sa_mask);
//     sigaction(SIGINT, &action, NULL);
//     while (1) {
// 		printf("Wainting a signal ... - pid = %d - prent id = %d\n", getpid(), getppid());
//         sleep(1);
//     }
//     return 0;
// }

//----------------------------------------------------------
// struct sigaction {
// void (*sa_handler)(int);
// void (*sa_sigaction)(int, siginfo_t *, void *);
// sigset_t sa_mask;
// int sa_flags;
// void (*sa_restorer)(void);
// };

// ###### in case you want to use SA_sigaction
// void signal_handler(int test, siginfo_t *p, void *v)
// {
// 	(void)test;
// 	(void)*p;
// 	(void)*v;
//     printf("Signal received succussfuly");
// }

// ######in case you want to use sa_handler
// void signal_handler()
// {
//     printf("Signal received succussfuly");
// }

// int main ()
// {
//     struct sigaction sigstruct;
//     // sigstruct.sa_sigaction = signal_handler;//any one you use it will work but if you want to work with paramers like signum, *p...you need to add SIGINFO FLANG
//     sigstruct.sa_handler = signal_handler;

//     sigaction (SIGINT, &sigstruct, NULL);

// 	while(1)
// 	{
// 		printf("waiting for a signal ... | %d\n", getpid());
// 		sleep (2);
// 		// pause();

// 	}
// 	return 0;
// }
//______________________________________________________________________________________________________
void signal_handler()
{
    printf("Signal received succussfuly");
}

int main ()
{
    struct sigaction sigstruct;
    sigstruct.sa_handler = signal_handler;

    sigaction (SIGINT, &sigstruct, NULL);

	while(1)
	{
		printf("waiting for a signal ... | %d\n", getpid());
		sleep (2);
		// pause();
	}
	return 0;
}

// void signal_handler(int signal) {
//     printf("Caught signal %d\n", signal);
// }

// int main() {
//     struct sigaction sighand; // Declare a struct sigaction variable called sa
//     sighand.sa_handler = signal_handler; // Assign the address of the signal handling function to sa_handler field
//     //sigemptyset(&sighand.sa_mask); // Initialize the signal mask to be empty
//     sighand.sa_flags = 0; // Set the flags to 0 (no special behavior)

//     int r = sigaction(SIGINT, &sighand, NULL); // Register the sa struct as the signal handler for the SIGINT signal

//     while (1) {
//         printf("waiting a signal ... - r = %d\n", r);
// 		sleep (2);
//     }

//     return 0;
// }

// int main()
// {
//     pid_t pid = 1234;
//     int sig = SIGINT;
//     int ret = kill(pid, sig);
//     if (ret == -1) {
//         perror("kill");
//     }
//     return 0;
// }

// PROGRAM THAT SHOWS SIGNAL NUMBER FOR SIGNALS :----------------------------------------------
// SIGUSR1 (my system : 30) (The signal number for SIGUSR1 and SIGUSR2 is determined by the operating system and can vary depending on the specific implementation.)
// SIGUSR2 (my system  : 31)
// SIGINT 2 /* Interrupt the process */
// SIGHUP  1   /* Hangup the process */
// SIGQUIT 3   /* Quit the process */
// SIGILL  4   /* Illegal instruction. */
// SIGTRAP 5   /* Trace trap. */
// SIGABRT 6   /* Abort. */

// int main()
// {
//     int sig1 = SIGUSR1;
//     int sig2 = SIGUSR2;
// 	int sig3 = SIGINT;
//     int sig4 = SIGHUP;
// 	int sig5 = SIGQUIT;
//     int sig6 = SIGILL;
// 	int sig7 = SIGTRAP;
//     int sig8 = SIGABRT;

// 	printf("SIGUSR1 = %d\nSIGUSR2 = %d\n SIGINT = %d\n SIGHUP = %d\n SIGQUIT = %d\n SIGILL = %d\n SIGTRAP = %d\n SIGABRT = %d\n", sig1, sig2, sig3, sig4, sig5, sig6, sig7, sig8);
//     return 0;
// }

//--------------------------------------------
// void signal_handler(int signum)
// {
// 	printf("message aftter handling the signal.... | %d\n", signum);

// }

// int main ()
// {
// 	signal (SIGINT, signal_handler);
// 	printf("out of the while!\n");
// 	while(1)
// 	{
// 		printf("waiting for a signal ... | %d\n", getpid());
// 		// sleep (2);
// 		pause();

// 	}
// 	return 0;
// }
//------------------------------------------------
// int main (int argc, char *argv[])
// {
//   int x = 0;
//   x = 228 & 10;
//   printf("%d", x);
// }
//----------------------------------------------------
// int main ()
// {
// 	int x = 6; // 6 =  0000 0110
// 	int y = 12;// 12 = 0000 1100
// 	int z = 0;// 0 = 0000 0000

// 	z = x & y; //(and)
// 	printf("%d\n", z);

// 	z = x | y;// (or)
// 	printf("%d\n", z);

// 		z = x ^ y;// XOR = exclusive or (if deference put 1 ; similar put 0)
// 	printf("%d\n", z);

// 	z = x<<6;
// 	printf("%d\n", z);

//   z = y>>4;
// 	printf("%d\n", z);

// }
//-----------------------------------------------------------
// int main ()
// {
// 	int x = 5 << 3; //note 3 in binary = 0000 0011;
// 	printf("%d", x);
// 	return 0;
// }
// ----------------------------
// int main ()
// {
// 	 int x = 1, y = 2;
// 	 if (x)
// 	 	printf("Result of x&y is 1\n");
// 	if (x||y)
// 		printf("Result of x&&y is 1");
// 	return 0;

// }
// KILL ------------------------------------
// int kill(pid_t pid, int sig);

// signal number:
// SIGUSR1 (my system : 30) (The signal number for SIGUSR1 and SIGUSR2 is determined by the operating system and can vary depending on the specific implementation.)
// SIGUSR2 (my system  : 31)
// SIGINT 2 /* Interrupt the process */
// SIGTSTP 20 (generated by the CTRL+Z keystroke)
// SIGCONT 18 (generated by the CTRL+Z keystroke)
// SIGHUP  1   /* Hangup the process */
// SIGQUIT 3   /* Quit the process */
// SIGILL  4   /* Illegal instruction. */
// SIGTRAP 5   /* Trace trap. */
// SIGABRT 6   /* Abort. */

//--------------------------------------------------------------------------------------------------------------------------

// void sig_handler(int signum) {
//   switch (signum) {
// 	 case SIGHUP:
// 		printf("Received SIGHUP! - signum = %d\n", signum);
// 		break;
// 	case SIGCONT:
// 		printf("Received SIGCONT! - signum = %d\n", signum);
// 		break;
// 	case SIGTSTP:
//       printf("Received SIGTSTP!\n - signum = %d\n", signum);
//       break;
//     case SIGINT:
//       printf("Received SIGINT! - signum = %d\n", signum);
//       break;
//     case SIGUSR1:
//       printf("Received SIGUSR1! - signum = %d\n", signum);
//       break;
// 	case SIGUSR2:
//       printf("Received SIGUSR2! - signum = %d\n", signum);
//       break;
//     default:
//       printf("The signal recieved is not recognized - signum = %d\n", signum);
//       break;
//   }
//   sleep (2);
// }

// int main() {
//   // Install signal handlers
//   signal(SIGINT, sig_handler);// use ctr + c  or kill -SIGINT <pid>
//   signal(SIGUSR1, sig_handler); // use kill -SIGUSR1 <pid>
//   signal(SIGUSR2, sig_handler);// use kill -SIGUSR2 <pid>
//   signal(SIGTSTP, sig_handler); // use ctr + z or ctr + s
//   signal (SIGCONT, sig_handler); // use ctr + q
//   signal (SIGHUP, sig_handler);
//   // Wait for signals
//   while (1) {
//     printf("Waiting for signal... - %d\n", getpid ());
//     sleep(2);
//   }

//   return 0;
// }

//--------------------------------------------------------------------------------------------------------------------------
// void sighandler(int signum) {
//    printf("\n The message that should be desplayed .... - %d\n", signum);
// 	//exit(0); //(if you use this line the programe will stop when you use ctr + c)
// 	// exit (1);

// }
// void cont_sig_handler( int x)
// {
// }
// int main () {
// 	//signal (SIGINT, sighandler); //you can send this signal using ctr + c === terminate the process.
// 	//signal(SIGTSTP, sighandler);

// 		//you can send this signal using ctr + z ===  stop the process.
// 		// you can send this signal using ctr + s  (stop) === stops all processes running in the terminal until the ctrl-Q key is pressed.
// 	//signal(SIGCONT, cont_sig_handler); //you can send this signal using ctr + q ===  continu all processes that were stopped by the ctrl-S

//    while(1) {
//       printf("Hi hassan...\n");
//       sleep(1);
//    }
//    return(0);
// }

// ctrl-C: Sends the SIGINT signal to the foreground process group. The default action for this signal is to terminate the process.
// ctrl-Z: Sends the SIGTSTP signal to the foreground process group. The default action for this signal is to stop the process.
// ctrl-D: Sends the EOF (end-of-file) signal to the terminal. This signal is not directly sent to a process, but it can cause a process to terminate if it is reading from the terminal and receives an EOF.
// ctrl-\: Sends the SIGQUIT signal to the foreground process group. The default action for this signal is to terminate the process and dump core (create a file with a snapshot of the process's memory at the time it received the signal).
// ctrl-S: Sends the SIGTSTP signal to the terminal itself, which stops all processes running in the terminal until the ctrl-Q key is pressed.
// ctrl-Q: Sends the SIGCONT signal to the terminal, which resumes all processes that were stopped by the ctrl-S key combination.
// ctrl-T: Sends the SIGINFO signal to the foreground process group. The default action for this signal is to display system information, such as the status of stopped processes and the resource usage of running processes.

// SOLUTION OF THE PROBLEM UNDER THIS TEST ###########################
// int x = 0;

// void handle_siguser1 (int sig)
// {
// 	if ( x == 0)
// 		printf("\n(HINT) 5 seconds are gone please inter an ansawer !\n");
// }

// int main ()
// {
// 	int pid = fork();
// 	if (pid == -1)
// 		return 0;
// 	if (pid == 0)
// 	{
// 		//child process
// 		sleep(5);
// 		kill(getppid(), SIGUSR1);
// 	}
// 	else {
// 		//parent process
// 		//SET UP A STRUCT
// 		struct sigaction sa; //the perpece from the st
// 		sa.sa_flags = SA_RESTART;
// 		//SET UP A HANDLER
// 		sa.sa_handler = &handle_siguser1;

// 		sigaction(SIGUSR1, &sa, NULL);

// 		printf("What is the result of 3 * 5: ");
// 		scanf("%d", &x);
// 		if (x == 15)
// 			printf("right");
// 		else
// 			printf("wrong");
// 		wait (NULL); //wait the child process to finish (not neccessary)
// 	}
// }

// #####################################################################################################
//  sending a signal to a process (the probele is our message is sendding in
// both case wish mmeas you wll get it even if you enter an ansawer in less than 5 seconds

// void handle_siguser1 (int sig)
// {
// 	printf("\n(HINT) 5 seconds are gone please inter an ansawer !\n");
// }

// int main ()
// {
// 	int pid = fork();
// 	if (pid == -1)
// 		return 0;
// 	if (pid == 0)
// 	{
// 		//child process
// 		sleep(5);
// 		kill(getppid(), SIGUSR1);
// 	}
// 	else {
// 		//parent process
// 		//SET UP A STRUCT
// 		struct sigaction sa; //the perpece from the st
// 		sa.sa_flags = SA_RESTART;
// 		//SET UP A HANDLER
// 		sa.sa_handler = &handle_siguser1;

// 		sigaction(SIGUSR1, &sa, NULL);

// 		int x;
// 		printf("What is the result of 3 * 5: ");
// 		scanf("%d", &x);
// 		if (x == 15)
// 			printf("right");
// 		else
// 			printf("wrong");
// 		wait (NULL); //wait the child process to finish (not neccessary)
// 	}
// }

// #########################################
// fork : return value 0 : for the child process;
// 		return a value > 0 for the parent process (the value is the pid of the child process)
// #########################################

// Parent Child Communication with Signals  #############################
//  void sig_handler_parent(int signum){
//    printf("Parent : Received a response signal from child \n");
//  }

// void sig_handler_child(int signum){
//   printf("Child : Received a signal from parent \n");
//   sleep(1);
//   kill(getppid(),SIGUSR1);
// }

// int main(){
//   pid_t pid;
//   if((pid=fork())<0){
//     printf("Fork Failed\n");
//     exit(1);
//   }
//   /* Child Process */
//   else if(pid==0){
//     signal(SIGUSR1,sig_handler_child); // Register signal handler
//     printf("Child: waiting for signal\n");
//     pause();
//   }
//   /* Parent Process */
//   else{
//     signal(SIGUSR1,sig_handler_parent); // Register signal handler
//     sleep(1);
//     printf("Parent: sending signal to Child\n");
//     kill(pid,SIGUSR1);
//     printf("Parent: waiting for response\n");
//     pause();
//   }
//   return 0;
// }
//---------------------------------------------------------------------------------------------------------------
// void sig_handler(int signum){
//   printf("Inside handler function\n");
// }

// int main(){
//   signal(SIGUSR1,sig_handler); // Register signal handler
//   printf("Inside main function\n");
//   int a = raise(SIGUSR1);
//   printf ("%d\n", a);

//   return 0;
// }
//---------------------------------------------------------------------------------------------------------------
// void sig_handler(int signum){
//   printf("\nInside handler function\n");
//   signal(SIGINT,SIG_DFL);   // Re Register signal handler for default action
// }

// int main(){
//   signal(SIGINT,sig_handler); // Register signal handler
//   for(int i=1;;i++){    //Infinite loop
//     printf("%d : Inside main function\n",i);
//     sleep(1);  // Delay for 1 second
//   }
//   return 0;
// }
//---------------------------------------------------------------------------------------------------------------
// int main(){
//   signal(SIGINT,SIG_IGN); // Register signal handler for ignoring the signal

//   for(int i=1;;i++){    //Infinite loop
//     printf("%d : Inside main function\n",i);
//     sleep(1);  // Delay for 1 second
//   }
//   return 0;
// }

//---------------------------------------------------------------------------------------------------------------

// void sig_handler(int signum){

//   //Return type of the handler function should be void
//   write(1, "\nInside handler function\n", 26);
// }

// int main(){
//   signal(SIGINT,sig_handler); // Register signal handler

//   for(int i=1;;i++)
//   {    //Infinite loop
//     printf("%d : Inside main function\n",i);
//     sleep(1);  // Delay for 1 second
//   }
//   return 0;
// }

//---------------------------------------------------------------------------------------------------------------
// void handler (int num) {
// 	write (1, " I won't die !", 13);
// }

// void seghandler (int num)
// {
// 	write (1, "Seg fault -------\n", 19);
// }
// int main ()
// {
// 	struct sigaction sa;
// 	sa.sa_handler = handler;

// 	sigaction (SIGINT, &sa, NULL);
// 	sigaction (SIGTERM, &sa, NULL);

// 	while(1)
// 	{
// 		printf("Hi hassan _ pid = %d\n", getpid());
// 		sleep (2);
// 	}

// }

//---------------------------------------------------------------------------------------------------------------
// void handler (int num){
// 	write (1, "I won't die !\n", 13);
// }

// int main ()
// {

// 	signal ( SIGINT, handler); // then the user uses ctr + c - The SIGINT signal is sent to a process by its controlling terminal when a user wishes to interrupt the process.
// 	signal ( SIGTERM, handler); // you can use kill -kill pid || SIGTERM (signal 15) is used in Unix-based operating systems, such as Linux, to terminate a process. The SIGTERM signal provides an elegant way to terminate a program, giving it the opportunity to prepare to shut down and perform cleanup tasks, or refuse to shut down under certain circumstances.
// 	signal ( SIGKILL, handler); // a signal that immediately terminate a process. It is used by Linux operators, and also by container orchestrators like Kubernetes, when they need to shut down a container or pod on a Unix-based operating system.

// 	while ( 1)
// 	{
// 		printf("hi hassan - pid = %d\n", getpid());
// 		sleep (2);
// 	}

// }

//-----------------------------------------------------------------------

// void seghandler (int num)
// {
// 	write(1, "Seg Fault------------!\n", 24);
// }
// int main ()
// {

// 	// signal ( SIGSEGV, seghandler);

// 	int *p = NULL;
// 	*p = 45;

// }

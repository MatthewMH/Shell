# Shell

A simple shell program written in C. You can use it like a normal Linux terminal. 

Below are how the shell works:
1. Create a variable that will contain an array of string. The purpose of this variable is to list all the commands inputed in the shell. We call this variable "pendata" and it is declared using dynamic memory allocation. To access the string array, create an integer variable that will be used as an index to access the string array. The variable is called "kosong".
2. Create a string variable to hold the command and the tokens of the arguments.
3. Create a loop that will run forever until it is terminated. In the loop, parse all the commands using split_words function and use fork() to create a child process. The execution will be done during child process. The parent will wait until the child process is done. Use execvp() in the child process to execute the commands provided as input.
4. In the loop, if the command provided as input is exit, terminate the loop using C break command.   
5. In the loop, if the command provided as input is cd, change the current directory using chdir(). 

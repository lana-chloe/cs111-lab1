#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	dup2(1, 2);
	if (argc <= 1) {
		return EINVAL;
	}
	else {
		int fds[2];
		int prev_fd = STDIN_FILENO;
		int i;
		for(i=1;i<=argc-1;i++) {
			dup2(fds[0], prev_fd);
			pipe(fds);
			int return_code = fork();
			// child process
			if (return_code == 0) {
				if (i != argc-1) {
					dup2(0, fds[0]);
					dup2(fds[1], 1);
             		execlp(argv[i], argv[i], NULL);
                	return errno;
				}
				else {
					dup2(0, fds[0]);
					execlp(argv[i], argv[i], NULL);
                	return errno;
				}
			}
			// parent process
			else if (return_code > 0) {
				int status;
				int wait_result = waitpid(return_code, &status, 0);	
				if (wait_result == -1) { // waitpid unsuccessful
					perror("waitpid");
					return errno;
				}
				if (WIFEXITED(status)) { // child exited successfully
					//printf("child exited with status of %d\n", WEXITSTATUS(status));
					if (WEXITSTATUS(status) != 0) 
						return WEXITSTATUS(status);
				}
      			else return ECHILD; // child killed by signal
				dup2(prev_fd, fds[1]);
			}
			// could not create child process
			else if (return_code < 0) {
				perror("fork");
				return errno;
			}
		}
	}
	return(0);
}

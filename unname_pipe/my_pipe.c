#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
	//int pipe_fd[2];
	//if(pipe(pipe_fd) < 0)
	//{
	//	perror("pipe");
	//	return -1;
	//}

	//int ret;
	//int count = 0;
	//while(1)
	//{
	//	ret = write(pipe_fd[1], "A", 1);
	//	if(ret < -1)
	//	{
	//		perror("write");
	//		return -1;
	//	}
	//	count++;
	//	printf("pipe capacity:%d\n",count);
	//}

	int pipe_fd[2];
	if(pipe(pipe_fd) < 0)
	{
		perror("pipe");
	}

	pid_t pid = fork();
	if(pid == 0)
	{
		//child
		close(pipe_fd[0]);
		const char* msg = "I'm a child\n";
		int count = 5;
		int i = 1;
		while(1)
		{
			write(pipe_fd[1],msg,strlen(msg));
			if(count-- == 0)
				break;
			sleep(1);
			printf("write data:%d\n",i++);
		}
		close(pipe_fd[1]);
	}
	else
	{
		//father
		close(pipe_fd[1]);
		char buf[128];
		while(1)
		{	
			memset(buf,'\0',sizeof(buf));
			ssize_t s = read(pipe_fd[0],buf,sizeof(buf)-1);
			if(s > 0)
			{
				printf("client->server:%s",buf);
			}
			else if(s == 0)
			{
				printf("read pipe erro!!!\n");
				break;
			}
			else
			{
				break;
			}
		}
		close(pipe_fd[0]);

		int status = 0;
		pid_t ret = waitpid(pid,&status,0);
		if(ret == pid)
		{
			printf("Wait child succeed...\n");
		}
	}

	return 0;
}

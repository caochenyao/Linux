#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd = open("./myfifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}

	char buf[128];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		printf("Please Enter# ");
		fflush(stdout);
		ssize_t s = read(1,buf,sizeof(buf));
		if(s > 0)
		{
			buf[s-1]='\0';
			write(fd,buf,strlen(buf));
		}
	}
	close(fd);

	return 0;
}

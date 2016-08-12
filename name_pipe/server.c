#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	if(mkfifo("./myfifo",S_IFIFO | 0644) < 0)
	{
		perror("mkfifo");
		return 1;
	}

	int fd = open("./myfifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}

	char buf[128];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		ssize_t s = read(fd,buf,sizeof(buf)-1);
		if(s > 0)
		{
			printf("client# %s\n",buf);
		}
		else
		{
			break;
		}
	}

	close(fd);
	return 0;
}

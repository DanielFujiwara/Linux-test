#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>

void touch(int *x, int *y)
{
	int fd = open("/dev/input/event0", O_RDWR);
	if(fd<0)
	{
		perror("open");
		return ;
	}
	
	struct input_event buf;
	int tmp_x=0, tmp_y=0;
	while(1)
	{
		read(fd, &buf, sizeof(buf));
	
		if(buf.type==EV_ABS && buf.code==ABS_X)
		{
			tmp_x = buf.value;
		}	
		
		if(buf.type==EV_ABS && buf.code==ABS_Y)
		{
			tmp_y = buf.value;
		}
		
		if(tmp_x!=0 && tmp_y!=0)
		{
			*x = tmp_x;
			*y = tmp_y;
			break;
		}
	}
	close(fd);
}



int show_bmp(char *name)
{
	int fd_p = open(name,O_RDWR);
	if(fd_p < 0)
	{
		perror("open");
		return -1;
	}

	int fd_s = open("/dev/fb0", O_RDWR);
	if(fd_s < 0)
	{
		perror("open");
		return -1;
	}

	lseek(fd_p,54,SEEK_SET);
	int tempbuf[800*480] = {0};
	int lcdbuf[800*480] = {0};
	unsigned char bmpbuf[800*480*3] = {0};
	read(fd_p,bmpbuf,800*480*3);

	int i = 0;
	for(i;i<800*480;i++)
	{
		lcdbuf[i] = bmpbuf[3*i+2]<<16 | bmpbuf[3*i+1]<<8 | bmpbuf[3*i+0];

						//R               //G                    //B
	}

	int x,y;
	for(x=0; x<800; x++)
	{
		for(y=0; y<480; y++)
			tempbuf[(479-y)*800+x]=lcdbuf[y*800+x];
	}
	// write(fd_s,lcdbuf,800*480*4);


	int *mmap_bmp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd_s,0);

	for(i=0;i<800*480;i++)
		*(mmap_bmp+i) = tempbuf[i];



	close(fd_p);
	close(fd_s);



}
int main(int argc, char const *argv[])

{	
	int i;
	char ad[10];
	
	for(i=1;i<12;i++)
	{
		sprintf(ad,"%d",i);
		strcat(ad,".bmp");
		printf("%s\n",ad );
		show_bmp(ad);
		// sleep(1/2);
		usleep(10000);
		memset(ad,0,sizeof(ad));
		if(i == 11)
			i = 1;

	}
	
	

	
	

	

	return 0;
}
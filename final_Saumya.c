/* Author: Saumya Saxena
Final Project - Computing in the Small
Date: June 14, 2018
*/
#include <u.h>
#include <libc.h>

void
main()
{
	int fd, fd1, fd2;
	uchar buf[34];
	short x, y, z;

	fd = open("/dev/i2c.18.data", ORDWR);
	if(fd < 0) {
		bind("#J18", "/dev", MAFTER);
		fd = open("/dev/i2c.18.data", ORDWR);
		if(fd < 0)
			print("open error: %r\n");
	}

	bind("#G","/dev",MAFTER); 
  	fd2=open("/dev/gpio",ORDWR);
  	fprint(fd2, "set 4 0");

	buf[0] = 0x1f;
	buf[1] = 0x80;
	pwrite(fd, buf, 2, 0);

	buf[0] = 0x24;
	buf[1] = 0;
	pwrite(fd, buf, 2, 0);

	buf[0] = 0x20;
	buf[1] = 0x27;
	pwrite(fd, buf, 2, 0);

	buf[0] = 0x23;
	buf[1] = 0x20;
	pwrite(fd, buf, 2, 0);

	fd1 = open("/dev/i2c.18.ctl", ORDWR);
	fprint(fd1, "subaddress 1");

	while(1) {
		sleep(300);
		pread(fd, buf, 16, (0x20 | 0x80));
		fprint(fd2, "set 4 0");
		x = (buf[9] << 8) | buf[8];
		y = (buf[11] << 8) | buf[10];
		z = (buf[13] << 8) | buf[12];
		if(x > 3000){
		fprint(fd2, "function 4 out\n");
		fprint(fd2,"set 4 1\n");
		}
	}
}
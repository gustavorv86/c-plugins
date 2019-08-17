
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t plugin_read(void *buf, size_t nbytes) {
	printf("%s:%s \n", __FILE__, __func__);
	const char * message = "Hello Read!!";
	snprintf(buf, nbytes, message);
	return strlen(buf);
}

ssize_t plugin_write(const void * buf, size_t num) {
	printf("%s:%s \n", __FILE__, __func__);
	const char * str = (const char *)buf;
	for(unsigned int i=0; i<num; i++) {
		if(str[i] == 0) {
			break;
		}
		printf("%c", str[i]);
	}
	printf("\n");
	return num;
}


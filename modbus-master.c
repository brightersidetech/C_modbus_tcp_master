#include <stdio.h>
#include <modbus/modbus.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
    	modbus_t *ctx;
	int rc_read = 0 ;
	int rc_write = 0 ;
	int i;
	uint16_t tab_dest[64];
	uint16_t tab_src[10] = {1};

	// creating context
	ctx = modbus_new_tcp("192.168.1.104", 502);
	
	// try connection
	while(modbus_connect(ctx) == -1) {

   		 fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
	}
	
	// write to holding registers and read from input registers
	while(1)
	{
		// modify data in source buffer
		for(i=0; i<10; i++){
			tab_src[i] += i;
		}
		// write to holding registers
		rc_write = modbus_write_registers(ctx, 0, 10, tab_src); 
		// read from input registers
		rc_read = modbus_read_input_registers(ctx, 0, 10, tab_dest);
		// check if read and write operations where successfull
		if (rc_write == -1 || rc_read== -1) {
    			fprintf(stderr, "%s\n", modbus_strerror(errno));
			break;
		}
		
		printf("Written %d Registers\n", rc);
		// print out read data
		for (i=0; i < rc; i++) {
    			printf("reg[%d]=%d (0x%X)\n", i, tab_dest[i], tab_dest[i]);
		}
		printf("----------------------------------------\n");
		sleep(2);
	}
	// free up resources and close connection
	printf("freeing up resources\n");
	modbus_close(ctx);
	modbus_free(ctx);
	return 0;
}

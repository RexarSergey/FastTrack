#include <Message.h>
#include <EMessageStatus.h>
#include <stdio.h>
#include <sys/types.h>



int main(int argc, char* argv[])
{
	char buf[1024];
	asn_dec_rval_t decoder;
	Message_t* message = 0;
	FILE* fr_w;
	size_t size;
	char* filename;

	if (argc != 2)
	{
		printf("filename was not specified for read\n");
		exit(1);
	}
	else
	{
		filename = argv[1];
	}

	fr_w = fopen(filename, "rb");
	if (!fr_w)
	{
		perror("can not open file for reading\n");
		exit(-1);
	}

	size = fread(buf, 1, sizeof(buf), fr_w);
	fclose(fr_w);
	if (!size)
	{
		printf("file is empty or broken\n");
		exit(1);
	}

	decoder = ber_decode(0, &asn_DEF_Message, (void**)&message, buf, size);
	if (decoder.code != RC_OK)
	{
		printf("can not decode the message\n");
		exit(1);
	}

	message->messageStatus = EMessageStatus_server;
	xer_fprint(stdout, &asn_DEF_Message, message);
	return 0;
}
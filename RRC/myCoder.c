#include <Message.h>
#include <EMessageStatus.h>
#include <OCTET_STRING.h>
#include <stdio.h>
#include <sys/types.h>


static int write_to_file(const int* buffer, size_t size, void* fstream)
{
	FILE* out_stream = fstream;
	size_t wrote_size = fwrite(buffer, 1, size, out_stream);
	return (wrote_size == size) ? 0 : -1;
}

int main(int argc, char* argv[])
{
	Message_t* message;
	asn_enc_rval_t encoder;

	message = calloc(1, sizeof(Message_t));
	if (!message)
	{
		perror("message calloc() failed\n");
		exit(-1);
	}

	char text[] = "Hello, World!";
	OCTET_STRING_t s;
	s.buf = text;
	s.size = sizeof(text) - 1;

	message->messageStatus = EMessageStatus_client;
	message->number = s;

	if (argc < 2)
	{
		printf("filename was not specified for write\n");
		exit(1);
	}
	else
	{
		const char* filename = argv[1];
		FILE* fw = fopen(filename, "wb");
		if (!fw)
		{
			perror("can not open file for writing\n");
			exit(-1);
		}

		encoder = der_encode(&asn_DEF_Message, message, write_to_file, fw);
		fclose(fw);

		if (encoder.encoded == -1)
		{
			printf("can not encode the message\n");
			exit(1);
		}
		else
		{
			printf("successful encoded the message\n");
		}
	}

	xer_fprint(stdout, &asn_DEF_Message, message);
	return 0;
}
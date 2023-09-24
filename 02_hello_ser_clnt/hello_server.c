#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<unistd.h> // linux system file
#include<sys/socket.h> // socket file
#include <arpa/inet.h> // IP

int main(int argc, const char* argv[])
{
	int serv_sock = 0;
	int client_sock = 0;
	struct sockaddr_in serv_addr; // store server address
	struct sockaddr_in client_addr; //store client address
	socklen_t client_addr_size = 0ul;

	const char message[] = { "Welcome my server."};
	if(argc != 2)
	{
		printf("USE : %s 9999 \r\n ", argv[0]);
		return 0;
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);  //(IPv4, TCP, IP_PROTO)
	if(serv_sock == -1)
	{
		fputs("socket() error\r\n" , stderr);
		return 0;
	}
	memset(&serv_addr, 0, sizeof serv_addr); 
	memset(&client_addr, 0, sizeof client_addr); // 
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	int bind_status = bind(serv_sock, (const struct sockaddr*)&serv_addr, sizeof serv_addr);
	if(bind_status == -1)
	{
		fputs("bind() error\r\n", stderr);
		return 0;
	}
	int listen_state = listen(serv_sock, 5);  // default 5
	if(listen_state == -1)
	{
		fputs("listen() error\r\n", stderr);
		return 0;
	}
	client_sock = accept(serv_sock, (struct sockaddr*)&client_sock, (socklen_t*)&client_addr);
	
	fprintf(stdout, "%s : %d\r\n", "Client Bridge", client_sock);
	if(client_sock == -1)
	{
		fputs("accept() error\r\n", stderr);
		return 0;
	}
	client_addr_size = sizeof client_addr; // accept() 
	
	write(client_sock, message, sizeof message);
	close(client_sock);
	close(serv_sock);
	return 0;
}
		
		
		
	

#include "udp.h"


	const char  *IP_SERV 	= "127.0.0.1";
	const size_t PORT_NUM	= 65535;
	const size_t BUFF_SIZE 	= 1024;
	const size_t IP_SIZE 	= 22;

	bool REGIME = SERVER;


int main (int argc, char **argv) {

/////////////////////////////////////////////////CMD LINE
	if (argc < 2) {
		printf ("You didnt specify the regime, so EXITING....");
		return 0;
	}
	
	if (strcmp (argv[1], "server") == 0) {
		REGIME = SERVER;
	}
	else if (strcmp (argv[1], "client") == 0) {
		REGIME = CLIENT;
	}
	else {
		printf ("Regime not specified. EXITING....");
		return 0;
	}
/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////WinSock initialization
	WSADATA sock_data;

	if (WSAStartup (MAKEWORD (2,2), &sock_data)) {

		printf ("Error WinSock version initializaion # %d", WSAGetLastError());
		return SOCKET_VERSION_ERROR;
	}

/////////////////////////////////////////////////socket initialization
	SOCKET sock = socket (AF_INET, SOCK_DGRAM, 0);

	if (sock == INVALID_SOCKET) {

		printf ("Error initialization socket # %d \n", WSAGetLastError ()); 
		closesocket (sock);
		WSACleanup ();

		return SOCKET_INIT_ERROR;
	}

/////////////////////////////////////////////////SOCKET INFO FILLIN
	sockaddr_in sock_info = {};
				
	sock_info.sin_family 	= AF_INET;
	sock_info.sin_port 		= htons (PORT_NUM);
	
	in_addr ip_to_num = {};

	if (inet_pton (AF_INET, IP_SERV, &ip_to_num) <= 0) {

		printf ( "Error in IP translation to special numeric format #%d", WSAGetLastError ());
		closesocket (sock);
		WSACleanup ();

		return IP_TRANSLATION_ERROR;
	}

	sock_info.sin_addr 	= ip_to_num;

/////////////////////////////////////////////////SERVER REGIME
	if (REGIME == SERVER) {

	/////////////////////////////////////////////////BINDING THE SOCKET TO INFO
		if (bind (sock, (sockaddr*)&sock_info, sizeof (sock_info))) {

			printf ("Error Socket binding to server info. Error # %d \n", WSAGetLastError ());
			closesocket (sock);
			WSACleanup 	();
			return BINDIN_ERROR;
		}

	/////////////////////////////////////////////////CLIENT INFO INIT
		sockaddr_in client_info = {}; 

		int 	client_info_size 	= sizeof (client_info);
		char 	buff[BUFF_SIZE]    	= {};
		char 	client_ip[IP_SIZE]	= {};

	/////////////////////////////////////////////////MAIN CYCLE
		while (1) {

			if (recvfrom (sock, buff, BUFF_SIZE, 0, (sockaddr*)&client_info, &client_info_size) == SOCKET_ERROR) {

				printf ("ERROR IN RECEIVING #", WSAGetLastError ());
				closesocket (sock);
				WSACleanup ();
				return RECEIVIN_ERROR;
			}

			if (!inet_ntop (AF_INET, &client_info.sin_addr, client_ip, INET_ADDRSTRLEN)) {
				
				printf ("ERROR IN CONVERTING CLIENT'S IP #%d", WSAGetLastError ());
				closesocket (sock);
				WSACleanup ();
				return IP_TRANSLATION_ERROR;
			}

			printf ("Client connected with IP address: %s\n", client_ip);

		}
	}
/////////////////////////////////////////////////CLIENT REGIME
	else {

		char buff[] = "AHAH";

		if (sendto (sock, buff, sizeof (buff), 0, (sockaddr *)&sock_info, sizeof (sock_info)) == SOCKET_ERROR) {

			printf ("UNABLE TO SEND DATA # %d\n", WSAGetLastError ());
			closesocket (sock);
			WSACleanup ();
			return SENDIN_ERROR;
		}
	}

/////////////////////////////////////////////////SUCCESSFUL ENDIN
	puts ("GOOD ENDING =)");
	closesocket (sock);
	WSACleanup ();
	return 0;
}
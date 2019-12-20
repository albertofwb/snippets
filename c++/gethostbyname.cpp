#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool GetHostByNameWrapper(const char* hostName, string& ip) {
	hostent* host;
	unsigned int addr;

	/* start initialize windows socket library */
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(1, 1);
	int ret = WSAStartup(wVersionRequested, &wsaData);
	if (ret != 0) {
		return 1;
	}

	if (isalpha(hostName[0])) {   /* host address is a name */
		host = gethostbyname(hostName);
	}
	else {
		addr = inet_addr(hostName);
		host = gethostbyaddr((char*)&addr, 4, AF_INET);
	}

	if (WSAGetLastError() != 0) {
		if (WSAGetLastError() == 11001)
			printf("Host not found...\nExiting.\n");
		else
			printf("error#:%ld\n", WSAGetLastError());
		return false;
	}

	ip = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
	return true;
}

int main(int argc, char* argv[]) {
	const char* hostName = "google.com";
	string ip;

	if (GetHostByNameWrapper(hostName, ip)) {
		printf("%s => %s\n", hostName, ip.c_str());
	}
	return 0;
}

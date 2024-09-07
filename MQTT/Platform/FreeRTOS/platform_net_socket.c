#include "IH_ATcommand.h"

#include "mqtt_log.h"
#include "platform_net_socket.h"

#include <portmacro.h>

#define SSID "PRAYMERRY"
#define PASSWORD "12345678C"

int platform_net_socket_connect(const char *host, const char *port, int proto)
{
	int i = 1;
	char cmd[100];
	int errs;

	while (1)
	{
		switch (i)
		{	
		/*配置WiFi模式-station模式*/
		case 1:
			errs = AT_SendCmd("AT+CWMODE=1", NULL, 0, 2000);
			if (!errs)
			{
				i++;
				printf("AT+CWMODE err = %d\r\n", errs);
			}
			break;
		/*连接Wifi*/
		case 2 :
			errs = AT_SendCmd("AT+CWJAP=\""SSID "\",\"" PASSWORD "\"", NULL, 0, 10000);
			if (!errs)
			{
				i++;
				printf("AT+CWJAP err = %d\n", errs);
			}
			break;
		/*开启服务器*/
		case 3:
			if (proto == PLATFORM_NET_PROTO_TCP)
			{
				/* AT+CIPSTART="TCP","192.168.3.116",8080	 */
				sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", host, port);
			}
			else
			{
				sprintf(cmd, "AT+CIPSTART=\"UDP\",\"%s\",%s", host, port);
			}
			errs = AT_SendCmd(cmd, NULL, 0, 20000);
			if (!errs)
			{
				i++;
				printf("AT+CIPSTART err = %d\n", errs);
			}
			break;
		}
		if(i>3)
		{
			break;
		}
	}
	return 0;
}

#if 0
int platform_net_socket_recv(int fd, void *buf, size_t len, int flags)
{
	//    return recv(fd, buf, len, flags);
	return 0;
}
#endif

int platform_net_socket_recv_timeout(int fd, unsigned char *buf, int len, int timeout)
{
	int i = 0;
	int err;

	while(i<len)
	{
		err = ATReadData(&buf[i], timeout);
		if (err)
		{
			return 0;
		}
		i++;
	}
	return len;
}

#if 0

int platform_net_socket_write(int fd, void *buf, size_t len)
{
	//    return write(fd, buf, len);
	return 0;
}
#endif

int platform_net_socket_write_timeout(int fd, unsigned char *buf, int len, int timeout)
{
	int err;
	char cmd[20];
	char resp[100];

	sprintf(cmd, "AT+CIPSEND=%d", len);
	err = AT_SendCmd(cmd, resp, 100, timeout);
	if (err)
	{
		resp[99] = '\0';
		printf("%s err = %d, timeout = %d\r\n", cmd, err, timeout);
		printf("resp : %s\r\n", resp);
		return err;
	}
	err = ATSendData(buf, len, timeout);/*send data*/
	if (err)
	{
		printf("ATSendData err = %d\r\n", err);
		return err;
	}
	
	return len;
}

int platform_net_socket_close(int fd)
{
	return AT_SendCmd("AT+CIPCLOSE", NULL, 0, 2000);
}



int platform_net_socket_set_block(int fd)
{
	//    unsigned long mode = 0;
	//    return ioctlsocket(fd, FIONBIO, &mode);
	return 0;
}

int platform_net_socket_set_nonblock(int fd)
{
	//    unsigned long mode = 1;
	//    return ioctlsocket(fd, FIONBIO, &mode);
	return 0;
}

int platform_net_socket_setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
	//    return setsockopt(fd, level, optname, optval, optlen);
	return 0;
}




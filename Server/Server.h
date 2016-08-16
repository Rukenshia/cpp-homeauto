/*
 * Server.h
 *
 *  Created on: Jun 15, 2014
 *      Author: kyou
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

#define BUFSIZE 2048

class Server
{
public:
  typedef std::string (*ServerCallback)(std::string);
  static Server* m_spInstance;
  int m_iSocket;
  int m_iPort;
  std::string m_strAddress;
  bool m_bAddressAny;
  int m_iMessageLength;
  sockaddr_in m_sClient;
  socklen_t m_sizeClient;
private:

  ServerCallback m_cHandler;
public:
  Server(std::string addr, int port);
  ~Server();

  bool Start();
  void Process();
  void Stop();

  static Server* GetInstance () { return m_spInstance; }
  int GetSocket() { return m_iSocket; }

  void SetHandler (ServerCallback handler) { m_cHandler = handler; }
  std::string Handle(std::string data);


};

#endif /* SERVER_H_ */

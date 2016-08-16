#include <pthread.h>
#include <Common.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"

Server* Server::m_spInstance = nullptr;


Server::Server (std::string addr, int port)
        : m_bAddressAny(false),
          m_cHandler(nullptr)
{
  m_sizeClient = sizeof(m_sClient);
  if (!addr.compare("INADDR_ANY"))
  {
    m_bAddressAny = true;
  }
  m_strAddress = addr;
  m_iPort = port;
  m_spInstance = this;

  m_iSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (m_iSocket < 0)
  {
    Log("Could not create Server socket.");
    return;
  }
}

Server::~Server()
{
  Stop();
}

bool Server::Start()
{
  if (m_iSocket < 0)
    return false;

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(m_iPort);
  if (m_bAddressAny)
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    addr.sin_addr.s_addr = inet_addr(m_strAddress.c_str());

  if (bind(m_iSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
  {
    Log("Could not bind socket");
    return false;
  }

  return true;
}

void Server::Process()
{
  if (this->m_iSocket < 0) {
	  return;
  }

  char szBuffer [BUFSIZE];

#ifdef OUTPUT_EVERY_PACKET
	Logf("Server is listening on %s:%d", this->m_strAddress.c_str(), this->m_iPort);
#endif
  this->m_iMessageLength = recvfrom(this->m_iSocket, szBuffer, BUFSIZE, 0, (struct sockaddr *)&this->m_sClient, &this->m_sizeClient);
  if (this->m_iMessageLength > 0)
  {
    szBuffer[this->m_iMessageLength] = 0;
#ifdef OUTPUT_EVERY_PACKET
		Logf("Recevied [%s]", szBuffer);
#endif

    std::string strResponse = this->Handle(std::string(szBuffer));
    size_t responseSize = strResponse.length();
#ifdef OUTPUT_EVERY_PACKET
		Logf("Response size: %d", responseSize);
#endif
    if (responseSize > 0)
    {
      if(sendto(this->m_iSocket, strResponse.c_str(), responseSize, 0, (struct sockaddr*)&this->m_sClient, this->m_sizeClient) == responseSize)
      {
#ifdef OUTPUT_EVERY_PACKET
				Logf("Response [%s] sent.", strResponse.c_str());
#endif
      }
      else
      {
        Log("Response could not be sent !");
      }
    }
    else
      Log("No Response sent.");
  }
  szBuffer[0] = '\0';
}

void Server::Stop()
{
  if (m_iSocket < 0)
    return;

  close(m_iSocket);
}

std::string Server::Handle(std::string data)
{

  if (m_cHandler != nullptr)
  {
    std::string retn = m_cHandler(data);
    if (strcmp(retn.c_str(), ""))
      return retn;
  }
  return std::string("0");
}


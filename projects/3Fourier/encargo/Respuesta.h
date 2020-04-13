#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
#ifndef RESPUESTA_H
#define RESPUESTA_H
class Respuesta
{
public:
  Respuesta(int);
  struct mensaje *getRequest(void);
  void sendReply(char *);
private:
  SocketDatagrama *socketlocal;
};
#endif

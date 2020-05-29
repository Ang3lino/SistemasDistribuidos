#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
#ifndef SOLICITUD_H
#define SOLICITUD_H
class Solicitud
{
public:
   Solicitud();
   char * doOperation(char *, int , int , char *);
private:
  SocketDatagrama *socketlocal;
};
#endif

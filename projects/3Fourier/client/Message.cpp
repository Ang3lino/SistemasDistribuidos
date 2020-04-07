#include "Message.h"


Message::Message(MessageType type, int requestid, OperationId opid, int argument_length, char *args):
        messageType(type),  
        requestId(requestid),
        operationId(opid), 
        argumentLength(argument_length) {
    // arguments = new char(argument_length);
    if (args != NULL)
        memcpy(arguments, args, argument_length);
}

Message::Message() { }

std::ostream& operator << (std::ostream &out, const Message &msg) {
    out << " requestId=" << msg.requestId << "\n";
    out << " operationId=" << msg.operationId << "\n";
    out << " sizeof(args)=" << msg.argumentLength << "\n";
    out << " args" << msg.arguments << "\n";
    return out; 
}

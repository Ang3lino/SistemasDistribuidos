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

void Message::serialize(char *data) {
    int *q = (int *) data;    
    *q = messageType; q++;    
    *q++ = requestId;   
    *q++ = operationId;     
    *q++ = argumentLength;     
    char *p = (char *) q;
    for (int i = 0; i < argumentLength; ++i) {
        *p++ = arguments[i];
    }
}

std::ostream& operator << (std::ostream &out, const Message &msg) {
    out << "Message --> ";
    out << " messageType: " << msg.messageType << ", ";
    out << " requestId: " << msg.requestId << ", ";
    out << " operationId: " << msg.operationId << ", ";
    out << " sizeof(args): " << msg.argumentLength << "\n";
    // out << " args" << msg.arguments << "\n";
    return out; 
}

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

Message::Message(char *msg_serialized, unsigned len) {
    ByteBuffer bb(msg_serialized, MSG_LEN);

    // for some reason you MUST store the values in int variables and contruct the instance with them
    int msg_type = bb.readInt();
    int req_id = bb.readInt();
    int op_id = bb.readInt();
    int arg_len = bb.readInt();

    messageType = (MessageType) msg_type;
    requestId = req_id;
    operationId = (OperationId) op_id;
    argumentLength = arg_len;
    if (arg_len > 0) {
        for (int i = 0; i < arg_len; ++i)
            arguments[i] = bb.read();
    }
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

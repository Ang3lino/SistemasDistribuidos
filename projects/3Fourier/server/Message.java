import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Message {
    public static final int DATA_LENGTH = 1 << 15, MESSAGE_SIZE = DATA_LENGTH + 16;
    public static final int UNKNOWN = -1, SUM = 1, PLOT = 2, SET_X_AXIS = 3;
    public static final int REQUEST = 1, REPLY = 2;

    public int type, requestId, operationId, dataLength;
    public byte[] data;


    public Message(int msgType, int reqId, int opId, int dataLen, byte[] src) {
        type = msgType;
        requestId = reqId;
        operationId = opId;
        dataLength = dataLen;
        data = src;  // src.length must be equal to DATA_LENGTH
    }

    public Message(int msgType, int reqId, int opId) {
        type = msgType;
        requestId = reqId;
        operationId = opId;
        dataLength = 0;
        data = new byte[DATA_LENGTH];
    }

    public Message(byte[] bytes) {
        ByteBuffer bb = ByteBuffer.wrap(bytes);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        type = bb.getInt();
        requestId = bb.getInt();
        operationId = bb.getInt();
        dataLength = bb.getInt();
        data = new byte[DATA_LENGTH];
        for (int i = 0; i < data.length; ++i) 
            data[i] = bb.get();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Float size: " + Float.SIZE + ", ");
        sb.append("Int size: " + Integer.SIZE + ", ");
        sb.append("Message type: " + type + ", ");
        sb.append("request id: " + requestId + ", ");
        sb.append("operation id: " + operationId + ", ");
        sb.append("argument length: " + dataLength + ", ");
        sb.append("\n");
        return sb.toString();
    }

    public byte[] serialize() {
        byte result[] = new byte[MESSAGE_SIZE];
        ByteBuffer byteBuffer = ByteBuffer.wrap(result);
        byteBuffer.putInt(type); 
        byteBuffer.putInt(requestId); 
        byteBuffer.putInt(operationId); 
        byteBuffer.putInt(dataLength); 
        for (int i = 0; i < DATA_LENGTH; ++i)
            byteBuffer.put(data[i]);
        return byteBuffer.array();
    }
}
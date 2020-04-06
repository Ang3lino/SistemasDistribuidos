import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Message {
    public static final int UNKNOWN = -1, SUM = 1, DUMMY = 3;
    public static final int REQUEST = 1, REPLY = 2;
    public static final int MESSAGE_SIZE = 4112, DATA_LENGTH = 4096;

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

    public void asString() {
        System.out.println("Float size: " + Float.SIZE);
        System.out.println("Int size: " + Integer.SIZE);
        System.out.println("Message type: " + type);
        System.out.println("request id: " + requestId);
        System.out.println("operation id: " + operationId);
        System.out.println("argument length: " + dataLength);
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
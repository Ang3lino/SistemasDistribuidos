import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Contestador {
    private DatagramSocket socket;
    private byte[] buf;
    private int port;
    InetAddress remoteAddress;

 
    public Contestador (int puerto) {
        buf = new byte[Const.TAM_MAX_MSG];
        port = puerto;
        try {
            socket = new DatagramSocket(port);
        } catch (SocketException e) {
            System.out.println(e);
        }
    }

    public void printBytes(byte[] bytes, int from, int to) {
        int j = 0, lineCount = 0;
        System.out.printf("\n%04d:   ", ++lineCount);
        for (int i = from; i < to; ++i) {
            byte b = bytes[i];
            String st = String.format("%02X", b);
            System.out.print(st + " ");
            if (++j == 16) {
                System.out.printf("\n%04d: ", ++lineCount);
                j = 0;
            }
            if (j % 4 == 0) 
                System.out.print("\t"); 
        }
        System.out.println();
    }

    public byte[] getRequest() {
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        System.out.println("Waiting for a request\n");
        try {
            socket.receive(packet);
        } catch (IOException e) {
            System.out.println(e);
        }
        remoteAddress = packet.getAddress();
        port = packet.getPort();
        byte[] data = packet.getData();
        printBytes(data, 0, 32);
        return data;
    }

    public static Mensaje messageFromBytes(byte[] source, double[] dst) {
        ByteBuffer byteBuffer = ByteBuffer.wrap(source);
        Mensaje m = new Mensaje();
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
        m.messageType = byteBuffer.getInt();
        m.requestId = byteBuffer.getInt();
        m.operationId = byteBuffer.getInt();
        m.argumentLength = byteBuffer.getInt();
        for (int i = 0; i < m.argumentLength / 8; ++i) {
            dst[i] = byteBuffer.getDouble();
        }
        return m;
    }

    public byte[] messageAsBytes(Mensaje m) {
        byte buff[] = new byte[Const.TAM_MAX_MSG];
        ByteBuffer byteBuffer = ByteBuffer.wrap(buff);
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
        byteBuffer.putInt(m.messageType);
        byteBuffer.putInt(m.requestId);
        byteBuffer.putInt(m.operationId); 
        byteBuffer.putInt(m.argumentLength);
        for (int i = 0; i < m.argumentLength; ++i)
            byteBuffer.put(m.arguments[i]);
        return byteBuffer.array();
    }

    public boolean notificar() {
        Mensaje reply = new Mensaje();
        reply.messageType = 1;
        reply.argumentLength = 0;
        byte[] response = messageAsBytes(reply);
        DatagramPacket pack = new DatagramPacket(response, response.length, remoteAddress, port);
        try {
            socket.send(pack);
            System.out.println("Reply sent: ");
            printBytes(response, 0, 32);
            return true;
        } catch (IOException e) {
            System.out.println(e);
        } finally {
            return false;
        }
    }

    public void close() {
        socket.close();
    }
}
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class Replier {
    private DatagramSocket socket;
    private byte[] buf;
    private int port;
    InetAddress remoteAddress;

 
    public Replier () {
        try {
            buf = new byte[Message.MESSAGE_SIZE];
            port = 5400;
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

    public boolean sendReply(int replyType, int requestId, int operationId) {
        Message reply = new Message(replyType, requestId, operationId);
        byte[] response = reply.serialize();
        DatagramPacket pack = new DatagramPacket(response, response.length, remoteAddress, port);
        try {
            socket.send(pack);
            System.out.println("Reply sent: ");
            printBytes(response, 0, 32);
            return true;
        } catch (IOException e) {
            System.out.println(e);
            return false;
        }
        // close();
    }

    public void close() {
        socket.close();
    }
}
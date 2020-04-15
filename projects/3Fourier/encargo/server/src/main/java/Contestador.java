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
    private int puerto;
    InetAddress direccionForanea;

    public Contestador (int puerto) {
        buf = new byte[Const.TAM_MAX_MSG];
        puerto = puerto;
        try {
            socket = new DatagramSocket(puerto);
        } catch (SocketException e) {
            System.out.println(e);
        }
    }

    public byte[] getRequest() {
        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        System.out.println("Esperando solicitud \n");
        try {
            socket.receive(packet);
        } catch (IOException e) {
            System.out.println(e);
        }
        direccionForanea = packet.getAddress();
        puerto = packet.getPort();
        byte[] data = packet.getData();
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

    /**
     * Notifica al cliente que puede continuar con la siguiente suma.
     * @return
     */
    public boolean notificar() {
        Mensaje reply = new Mensaje();
        reply.messageType = 1;
        reply.argumentLength = 0;
        byte[] response = messageAsBytes(reply);
        DatagramPacket pack = new DatagramPacket(response, response.length, direccionForanea, puerto);
        try {
            socket.send(pack);
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

public class Mensaje {
    public int messageType;
    public int requestId;
    public int operationId;
    public int argumentLength;
    public byte arguments[] = new byte[Const.TAM_MAX_DATA];
}

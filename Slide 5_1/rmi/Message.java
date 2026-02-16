import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Message extends Remote {
    String sendMessage(String str) throws RemoteException;
}

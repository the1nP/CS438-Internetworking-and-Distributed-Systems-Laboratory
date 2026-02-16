import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ass3_interface extends Remote {
    int[] sortNumbers(int[] numbers) throws RemoteException;
}

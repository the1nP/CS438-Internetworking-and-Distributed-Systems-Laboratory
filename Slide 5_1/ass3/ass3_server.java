import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Arrays;

public class ass3_server implements ass3_interface {

    public ass3_server() {}

    @Override
    public int[] sortNumbers(int[] numbers) throws RemoteException {
        System.out.println("Received array of size: " + numbers.length);
        int[] sortedArray = numbers.clone();
        Arrays.sort(sortedArray);
        System.out.println("Processing complete. Returning sorted array.");
        return sortedArray;
    }

    public static void main(String args[]) {
        try {
            ass3_server obj = new ass3_server();
            ass3_interface stub = (ass3_interface) UnicastRemoteObject.exportObject(obj, 0);

            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("SortService", stub);

            System.err.println("Server ready (SortService)");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

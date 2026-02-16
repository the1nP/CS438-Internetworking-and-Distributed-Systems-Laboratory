import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
	
public class Server implements Message {
	
    public Server() {}

    public String sendMessage(String str) {
        String capital = str.toUpperCase();
	return capital;
    }
	
    public static void main(String args[]) {
	
	try {
	    Server obj = new Server();
	    Message stub = (Message) UnicastRemoteObject.exportObject(obj, 0);

	    // Bind the remote object's stub in the registry
	    Registry registry = LocateRegistry.getRegistry();
	    registry.bind("Message", stub);

	    System.err.println("Server ready");
	} catch (Exception e) {
	    System.err.println("Server exception: " + e.toString());
	    e.printStackTrace();
	}
    }
}


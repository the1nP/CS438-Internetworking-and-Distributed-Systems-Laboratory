import java.io.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {

    private Client() {}

    public static void main(String[] args) {

	String host = (args.length < 1) ? null : args[0];
	try {
	    Registry registry = LocateRegistry.getRegistry(host);
	    Message stub = (Message) registry.lookup("Message");
           BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

            System.out.print("Enter Message: ");
            String sentence = inFromUser.readLine();
	    String response = stub.sendMessage(sentence);
	    System.out.println("Response: " + response);
	} catch (Exception e) {
	    System.err.println("Client exception: " + e.toString());
	    e.printStackTrace();
	}
    }
}

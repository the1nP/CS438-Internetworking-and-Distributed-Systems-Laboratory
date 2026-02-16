import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;
import java.util.Arrays;

public class ass3_client {

    private ass3_client() {}

    public static void main(String[] args) {
        String host = (args.length < 1) ? null : args[0];
        try (Scanner scanner = new Scanner(System.in)) {
            Registry registry = LocateRegistry.getRegistry(host);
            ass3_interface stub = (ass3_interface) registry.lookup("SortService");

            System.out.println("Enter integers separated by space (then press Enter):");
            String input = scanner.nextLine();
            
            if (input == null || input.trim().isEmpty()) {
                System.out.println("No input provided.");
                return;
            }

            String[] tokens = input.trim().split("\\s+");
            int[] numbers = new int[tokens.length];
            
            for (int i = 0; i < tokens.length; i++) {
                try {
                    numbers[i] = Integer.parseInt(tokens[i]);
                } catch (NumberFormatException e) {
                    System.err.println("Invalid integer: " + tokens[i]);
                    return;
                }
            }

            System.out.println("Sending to server: " + Arrays.toString(numbers));
            int[] sortedNumbers = stub.sortNumbers(numbers);
            System.out.println("Sorted result from server: " + Arrays.toString(sortedNumbers));

        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}

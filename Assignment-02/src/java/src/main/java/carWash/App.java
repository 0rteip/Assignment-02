package carWash;

public class App {
    public static void main(String[] args) throws Exception {
        CommChannel channel = new SerialCommChannel("/dev/ttyACM0", 9600);
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");

        /* while (true) {
            System.out.println("Sending ping");
            channel.sendMsg("ping");
            String msg = channel.receiveMsg();
            System.out.println("Received: " + msg);
            Thread.sleep(500);
        } */
    }
}

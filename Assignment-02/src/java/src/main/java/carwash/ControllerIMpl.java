package carwash;

public class ControllerIMpl {
    
    public ControllerIMpl() throws Exception {
        CommChannel channel = new SerialCommChannel("/dev/ttyACM0", 9600);
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");
    }
}

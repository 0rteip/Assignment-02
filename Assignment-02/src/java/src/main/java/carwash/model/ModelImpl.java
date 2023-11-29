package carwash.model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import carwash.model.arduino.CommChannel;
import carwash.model.arduino.SerialCommChannel;
import carwash.model.message.MessageType;
import jssc.SerialPortException;

public class ModelImpl implements Model {

    private final String TEMP_FIXED ="Fixed";
    final PropertyChangeSupport pcs = new PropertyChangeSupport(this);
    private CommChannel channel;
    public ModelImpl() {
        pcs.firePropertyChange(MessageType.WARNING.getTitle(), "message", "msg");
        try {
            channel = new SerialCommChannel("/dev/ttyACM0", 9600);
            System.out.println("Waiting Arduino for rebooting...");
            Thread.sleep(4000);
        } catch (SerialPortException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Ready.");
    }

    @Override
    public void addListener(final PropertyChangeListener listener) {
        this.pcs.addPropertyChangeListener(listener);
    }

    @Override
    public void sendMessage() {
       channel.sendMsg(TEMP_FIXED);
       System.out.println("fixeddddddddd");
    }

    @Override
    public CommChannel getChannel() {
        return this.channel;
    }
}

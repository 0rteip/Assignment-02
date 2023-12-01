package carwash.model;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import carwash.model.arduino.CommChannel;
import carwash.model.arduino.SerialCommChannel;
import jssc.SerialPortException;

public class ModelImpl implements Model {

    private static final Logger logger = LoggerFactory.getLogger(ModelImpl.class);
    private static final String TEMP_FIXED = "Fixed";

    final PropertyChangeSupport pcs = new PropertyChangeSupport(this);
    private CommChannel channel;

    public ModelImpl() {
        // pcs.firePropertyChange(MessageType.WARNING.getTitle(), "message", "msg");
        try {
            channel = new SerialCommChannel("/dev/ttyACM0", 115200);
            logger.info("Waiting Arduino for rebooting...");
            Thread.sleep(4000);

        } catch (SerialPortException e) {
            logger.error("Error while creating serial port. ", e);
            e.printStackTrace();

        } catch (InterruptedException e) {
            e.printStackTrace();
            Thread.currentThread().interrupt();
        }
        logger.info("Ready.");
    }

    @Override
    public void addListener(final PropertyChangeListener listener) {
        this.pcs.addPropertyChangeListener(listener);
    }

    @Override
    public void sendMessage() {
        channel.sendMsg(TEMP_FIXED);
        logger.info("fixeddddddddd");
    }

    @Override
    public CommChannel getChannel() {
        return this.channel;
    }
}

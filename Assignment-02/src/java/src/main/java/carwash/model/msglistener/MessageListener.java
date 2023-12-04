package carwash.model.msglistener;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import carwash.controller.Controller;
import carwash.model.arduino.CommChannel;

public class MessageListener extends Thread {

    private static final Logger logger = LoggerFactory.getLogger(MessageListener.class);
    private static final String STATE_PREFIX = "st:";
    private static final String TEMP_PREFIX = "tp:";
    private static final String CARS_WASHED_PREFIX = "cw:";

    private CommChannel channel;
    private Controller controller;

    public MessageListener(final CommChannel channel, final Controller controller) {
        this.controller = controller;
        this.channel = channel;
    }

    @Override
    public void run() {

        while (true) {
            try {
                String newMsg = channel.receiveMsg();
                if (newMsg.startsWith(STATE_PREFIX)) {
                    newMsg = newMsg.substring(STATE_PREFIX.length());
                    controller.setState(newMsg);
                } else if (newMsg.startsWith(TEMP_PREFIX)) {
                    newMsg = newMsg.substring(TEMP_PREFIX.length());
                    controller.setTemp(newMsg);
                } else if (newMsg.startsWith(CARS_WASHED_PREFIX)) {
                    newMsg = newMsg.substring(CARS_WASHED_PREFIX.length());
                    controller.setCarsWashed(newMsg);
                }

            } catch (InterruptedException e) {
                logger.error("Error while receiving message. ", e);
                Thread.currentThread().interrupt();
            }
        }
    }
}

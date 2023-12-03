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
                String msg = channel.receiveMsg();
                String newMsg = msg;
                if (msg.startsWith(STATE_PREFIX)) {
                    newMsg = newMsg.substring(STATE_PREFIX.length());
                    controller.setState(newMsg);
                } else if (msg.startsWith(TEMP_PREFIX)) {
                    newMsg = newMsg.substring(TEMP_PREFIX.length());
                    controller.setTemp(findString(newMsg));
                } else if (msg.startsWith(CARS_WASHED_PREFIX)) {
                    newMsg = newMsg.substring(CARS_WASHED_PREFIX.length());
                    controller.setCarsWashed(findString(newMsg));
                }

            } catch (InterruptedException e) {
                logger.error("Error while receiving message. ", e);
                Thread.currentThread().interrupt();
            }
        }
    }

    private String findString(final String string) {
        final StringBuilder finalString = new StringBuilder();
        String tmp = string;
        while (string.length() > 0 && !tmp.startsWith(TEMP_PREFIX)) {
            finalString.append(tmp.charAt(0));
            if (tmp.length() < 2) {
                break;
            }
            tmp = tmp.substring(1);
        }
        return finalString.toString();
    }
}
package carwash.model;

import java.beans.PropertyChangeListener;

import carwash.model.arduino.CommChannel;

/**
 * Model for GlobalOutbreak app.
 */
public interface Model {

    /**
     * Add a listener for the News.
     * 
     * @param listener
     *                 listener
     */
    void addListener(PropertyChangeListener listener);

    /**
     * Send a message to serial line.
     * 
     */
    void sendMessage();

    /**
     * Return the channel class.
     * @return
     */
    CommChannel getChannel();
}
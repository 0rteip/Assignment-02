package carwash.controller;

import carwash.model.message.Message;

/**
 * Controller interface.
 */
public interface Controller {

    /**
     * Display the message notification.
     * 
     * @param message
     *                message to display
     */
    void displayMessage(Message message);

    /**
     * Quits from application.
     */
    void quit();

     /**
     * Update state value in view.
     * @param state
     */
    void setState(String state);

    /**
     * Update temp value in view.
     * 
     * @param temp
     */
    void setTemp(String temp);
    /**
     * Send a message to arduino.
     */
    void fixTemp();
}
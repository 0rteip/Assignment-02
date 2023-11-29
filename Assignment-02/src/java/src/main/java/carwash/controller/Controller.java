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
}
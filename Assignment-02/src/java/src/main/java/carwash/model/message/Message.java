package carwash.model.message;

/**
 * Message interface.
 */
public interface Message {

    /**
     * Returns the MessageType of the message.
     * 
     * @return
     *         MessageType
     */
    MessageType getType();
}
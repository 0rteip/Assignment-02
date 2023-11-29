package carwash.model.message;

/**
 * Type of Message.
 */
public enum MessageType {

    /**
     * Error message.
     */
    WARNING("Warning");

    private final String title;

    MessageType(final String title) {
        this.title = title;
    }

    /**
     * Returns the title.
     * 
     * @return
     *         title
     */
    public String getTitle() {
        return this.title;
    }

}
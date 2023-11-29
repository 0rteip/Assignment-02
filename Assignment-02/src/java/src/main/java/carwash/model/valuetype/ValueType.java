package carwash.model.valuetype;

public enum ValueType {

    /**
     * Temperature.
     */
    TEMPERATURE("Temperature"),

    /**
     * Status.
     */
    STATUS("Status");

    private final String value;

    ValueType(String value) {
        this.value = value;
    }

    /**
     * Get value.
     * 
     * @return value
     */
    public String getValue() {
        return this.value;
    }

}

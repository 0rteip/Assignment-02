package carwash.controller;

import carwash.model.Model;
import carwash.model.ModelImpl;
import carwash.model.message.Message;
import carwash.model.msg_listener.MessageListener;
import carwash.model.valuetype.ValueType;
import carwash.view.View;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

public final class ControllerImpl implements Controller {

    // private final Logger logger = LoggerFactory.getLogger(this.getClass());

    private final Model model = new ModelImpl();
    private final View view;

    private MessageListener checker;

    /**
     * Create a controller.
     * 
     * @param view
     *             View
     */
    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP",
        justification = "We need to use the correct instance of View"
    )
    // @formatter:on
    public ControllerImpl(final View view) {
        this.view = view;
        try {
            this.checker = new MessageListener(model.getChannel(), this);
            checker.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
        // this.model.addListener(new NewsObserver(this));
    }

    @Override
    public void displayMessage(Message message) {
        this.view.displayMessage(message);
    }

    @Override
    public void quit() {
        this.view.quit();
    }

    @Override
    public void setState(String state) {
        this.view.updateValue(ValueType.STATUS, state);
    }

    @Override
    public void setTemp(String temp) {
        this.view.updateValue(ValueType.TEMPERATURE, temp);

    }

    @Override
    public void fixTemp() {
        this.model.sendMessage();
    }
}
package carwash.controller;

import carwash.model.Model;
import carwash.model.ModelImpl;
import carwash.model.message.Message;
import carwash.view.View;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

public final class ControllerImpl implements Controller {

    // private final Logger logger = LoggerFactory.getLogger(this.getClass());

    private final Model model = new ModelImpl();
    private final View view;

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
}
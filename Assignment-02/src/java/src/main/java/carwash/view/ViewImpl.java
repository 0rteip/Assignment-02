package carwash.view;

import java.util.concurrent.CountDownLatch;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import carwash.controller.Controller;
import carwash.model.message.Message;
import carwash.view.scenemanager.SceneManager;
import carwash.view.scenemanager.SceneManagerImpl;
import carwash.view.settings.WindowSettings;
import carwash.view.settings.WindowSettingsImpl;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

import javafx.application.Platform;
import javafx.stage.Stage;

/**
 * Class ViewImpl.
 */
public final class ViewImpl implements View {

    private final Logger logger = LoggerFactory.getLogger(this.getClass());
    private final WindowSettings settings = new WindowSettingsImpl();
    private final SceneManager manager;

    private Controller controller;

    /**
     * Creates a VIewImpl.
     * 
     * @param stage
     *              stage
     */
    public ViewImpl(final Stage stage) {
        this.manager = new SceneManagerImpl(stage, this);
    }

    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP",
        justification = "We need to use the correct instance of Controller"
    )
    // @formatter:on
    @Override
    public void start(final Controller controller) {
        this.controller = controller;
        logger.info("Starting a new game");
        this.manager.openInitialMenu();
    }

    @Override
    public void displayMessage(final Message message) {
        final CountDownLatch latch = new CountDownLatch(1);

        Platform.runLater(() -> this.manager.openMessage(message, latch));

        try {
            latch.await();
        } catch (InterruptedException e) {
            this.logger.warn("Latch interrupted", e);
            Thread.currentThread().interrupt();
        }

    }

    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP",
        justification = """
            We need to access WindowSettings from the SceneLoader, 
            it could be done by calling methods on the view, 
            but we preferred to leave the modification to WindowSettings
        """
    )
    // @formatter:on
    @Override
    public WindowSettings getWindowSettings() {
        return this.settings;
    }

    @Override
    public SceneManager getSceneManager() {
        return this.manager;
    }

    @Override
    public void quit() {
        this.controller.quit();
    }

    @Override
    public void render() {
        throw new UnsupportedOperationException("Unimplemented method 'render'");
    }
}
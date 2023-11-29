package carwash;

import carwash.controller.Controller;
import carwash.controller.ControllerImpl;
import carwash.view.View;
import carwash.view.ViewImpl;
import javafx.application.Application;
import javafx.stage.Stage;

/**
 * Application.
 */
public class CarWash extends Application {

    @Override
    public final void start(final Stage primaryStage) throws Exception {
        final View view = new ViewImpl(primaryStage);
        final Controller controller = new ControllerImpl(view);
        view.start(controller);
    }

    /**
     * Entry point for the App.
     * 
     * @param args
     *             passed to launch
     */
    public static void main(final String[] args) {
        launch(args);
    }
}
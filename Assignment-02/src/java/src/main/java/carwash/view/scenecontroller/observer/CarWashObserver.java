package carwash.view.scenecontroller.observer;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import carwash.model.valuetype.ValueType;
import carwash.view.scenecontroller.MainSceneSetter;
import edu.umd.cs.findbugs.annotations.SuppressFBWarnings;

/**
 * WorldFields observer.
 */
public final class CarWashObserver implements PropertyChangeListener {

    private final MainSceneSetter mainSceneSetter;
    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    /**
     * Create an observer.
     * 
     * @param mainSceneSetter
     *                        the MainSceneSetter
     */
    // @formatter:off
    @SuppressFBWarnings(
        value = "EI_EXPOSE_REP2",
        justification = "We need to use the correct instance of the MainSceneSetter"
    )
    // @formatter:on
    public CarWashObserver(final MainSceneSetter mainSceneSetter) {
        this.mainSceneSetter = mainSceneSetter;
        logger.info("CarWashObserver created");
    }

    @Override
    public void propertyChange(final PropertyChangeEvent arg0) {
        if (arg0.getOldValue().equals(ValueType.TEMPERATURE.getValue())) {
            this.mainSceneSetter.setTemperature(arg0.getNewValue().toString());
        } else if (arg0.getOldValue().equals(ValueType.STATUS.getValue())) {
            this.mainSceneSetter.setStatus(arg0.getNewValue().toString());
        } else if (arg0.getOldValue().equals(ValueType.CARS_WASHED.getValue())) {
            this.mainSceneSetter.setCarsWashed(arg0.getNewValue().toString());
        }
    }

}
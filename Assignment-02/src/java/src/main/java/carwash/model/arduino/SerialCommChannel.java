package carwash.model.arduino;

import java.util.concurrent.*;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import jssc.*;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci
 *
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

	private static final Logger logger = LoggerFactory.getLogger(SerialCommChannel.class);

	private final SerialPort serialPort;
	private BlockingQueue<String> queue;
	private StringBuffer currentMsg = new StringBuffer("");

	public SerialCommChannel(String port, int rate) throws SerialPortException {
		queue = new ArrayBlockingQueue<>(100);

		serialPort = new SerialPort(port);
		serialPort.openPort();

		serialPort.setParams(rate,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);

		serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
				SerialPort.FLOWCONTROL_RTSCTS_OUT);

		serialPort.addEventListener(this);
	}

	@Override
	public void sendMsg(String msg) {
		char[] array = (msg + "\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++) {
			bytes[i] = (byte) array[i];
		}
		try {
			synchronized (serialPort) {
				serialPort.writeBytes(bytes);
			}
		} catch (SerialPortException ex) {
			logger.error("Error while sending message. ", ex);
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		return !queue.isEmpty();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public void serialEvent(SerialPortEvent event) {
		/* if there are bytes received in the input buffer */
		if (event.isRXCHAR()) {
			try {
				String msg = serialPort.readString(event.getEventValue());

				msg = msg.replaceAll("\r", "");

				currentMsg.append(msg);

				boolean goAhead = true;

				while (goAhead) {
					String msg2 = currentMsg.toString();
					int index = msg2.indexOf("\n");
					if (index >= 0) {
						queue.put(msg2.substring(0, index));
						currentMsg = new StringBuffer("");
						if (index + 1 < msg2.length()) {
							currentMsg.append(msg2.substring(index + 1));
						}
					} else {
						goAhead = false;
					}
				}

			} catch (InterruptedException ex) {
				logger.error("Error in receiving string from COM-port: {}", ex.getMessage());
				Thread.currentThread().interrupt();
			} catch (SerialPortException e) {
				logger.error("Error in receiving string from COM-port: {}", e.getMessage());
			}
		}
	}
}

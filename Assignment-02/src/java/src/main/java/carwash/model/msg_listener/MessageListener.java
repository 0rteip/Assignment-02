package carwash.model.msg_listener;

import carwash.controller.Controller;
import carwash.model.arduino.CommChannel;

public class MessageListener extends Thread {
    CommChannel channel;
	Controller controller;
	
	static final String STATE_PREFIX 	=  "st:";
	static final String TEMP_PREFIX 	=  ":tp:";
    int count = 0;
	
	public MessageListener(CommChannel channel, Controller controller) throws Exception {
		this.controller = controller;
		this.channel = channel;
	}
	
	public void run(){
        
		while (true){
			try {
                String msg = channel.receiveMsg();
                String newMsg = msg;
                if (msg.startsWith(STATE_PREFIX)) {
                    newMsg=newMsg.substring(STATE_PREFIX.length());
                    String stateMsg = findString(newMsg);
                    controller.setState(stateMsg);
                    newMsg = newMsg.substring(stateMsg.length());
                }
                if (newMsg.startsWith(TEMP_PREFIX)) {
                    newMsg=newMsg.substring(TEMP_PREFIX.length());
                    controller.setTemp(findString(newMsg));
                }

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
	}

    private String findString(String string) {
        String finalString = "";
        String tmp = string;
        while (string.length() > 0 && !tmp.startsWith(TEMP_PREFIX)) {
            finalString += tmp.charAt(0);
            if(tmp.length() < 2) {
                break;
            }
            tmp = tmp.substring(1);
        }
        return finalString;
    }
}

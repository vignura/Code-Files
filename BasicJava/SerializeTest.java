import java.io.Serializable;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

class Device implements Serializable {
	String name;

	public Device(String name){
		this.name = name;
	}

	public void setDevName(String name){
		this.name = name;
	}

	public String getDevName(){
		return this.name;
	}
}

public class SerializeTest {
	private static final String FILENAME = "DeviceList.dat";

	public static void main(String[] args) {

		ArrayList<Device> devList =  new ArrayList<Device>();
		
		for(int i = 0; i < 10; i++){
			Device dev = new Device("Device"+String.valueOf(i +1));
			devList.add(dev);
			System.out.println("adding "+dev.getDevName());	
		}		
		
		writeDevList(devList);
		devList.clear();
		devList = ReadDevList();
	}

	private static void writeDevList(ArrayList<Device> devList){
		System.out.print("writing to file " + FILENAME);
		try {
			FileOutputStream fos = new FileOutputStream(FILENAME);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(devList);
            System.out.println(" success");
		} catch (FileNotFoundException e) {
            e.printStackTrace(); 
        } catch (IOException e) {
            e.printStackTrace();
        }
	}

	private static ArrayList<Device> ReadDevList(){
		System.out.println("Reading from file " + FILENAME);
		ArrayList<Device> devList = new ArrayList<Device>();
		try {
			FileInputStream fis = new FileInputStream(FILENAME);
            ObjectInputStream ois = new ObjectInputStream(fis);
            Object obj = ois.readObject();
            devList = (ArrayList) obj;
            for (Device dev: devList) {
                System.out.println(dev.getDevName());
            }
		} catch (FileNotFoundException e) {
            e.printStackTrace(); 
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        return devList;
	}
}
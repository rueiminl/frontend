import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.json.simple.parser.ParseException;


public class Q3Reducer {
	
	public static void main(String[] args) throws IOException, ParseException {
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in));
			//BufferedReader r = new BufferedReader(new FileReader("output.txt"));
			
			String line;
			String prev1 = "";
			String prev2 = ""; 
			while ((line = r.readLine()) != null) {
				if (line.length() > 0) {
					String[] ids = line.split("_", 2);
					if (!(ids[0].equals(prev1) && ids[1].equals(prev2))) {
						System.out.println(ids[0] + "\t" + ids[1]);
						prev1 = ids[0];
						prev2 = ids[1];
					} 
				}
			}
	}
}

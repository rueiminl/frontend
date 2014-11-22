import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q6Mapper {
	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in, "UTF-8"));
		//BufferedReader r = new BufferedReader(new FileReader("15619f14twitter-parta-aa"));
		
		String line = "";
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
				JSONParser parser=new JSONParser();
				JSONObject obj=(JSONObject) parser.parse(line);				
				JSONObject user = (JSONObject)obj.get("user");
				JSONArray media = (JSONArray) ((JSONObject) obj.get("entities")).get("media");
				if (media != null) {
					int count = 0;
					for (Object o : media) {
						JSONObject j = (JSONObject)o;
						if (j.get("type").equals("photo"))
							count++;
					}
					System.out.println(user.get("id") + "\t" + obj.get("id") + "\t" + count);
				}
			}
		}	
	}
}

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q5Mapper {

	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in, "UTF-8"));
		//BufferedReader r = new BufferedReader(new FileReader("q5test.txt"));
		
		String line = "";
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
				JSONParser parser=new JSONParser();
				JSONObject obj=(JSONObject) parser.parse(line);				
				JSONObject user = (JSONObject)obj.get("user");
				JSONObject retweet = (JSONObject)obj.get("retweeted_status");
				if (retweet != null) {
					if ((((JSONObject)retweet.get("user")).get("id")).equals(user.get("id"))) {
						System.out.println(((JSONObject)retweet.get("user")).get("id") + "\t" + obj.get("id") + "\t" + "Y" + "_" + user.get("id"));
					}
					else {
						System.out.println(((JSONObject)retweet.get("user")).get("id") + "\t" + obj.get("id") + "\t" + "Y" + "_" + user.get("id"));
						System.out.println(user.get("id") + "\t" + obj.get("id") + "\t" + "N");	
					}
				}
				else 
					System.out.println(user.get("id") + "\t" + obj.get("id") + "\t" + "N");	
			}
		}	
	}
}

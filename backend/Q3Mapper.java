import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q3Mapper {
	
	public static void main(String[] args) throws IOException, ParseException {
		BufferedReader r = new BufferedReader
			(new InputStreamReader(System.in));
		//BufferedReader r = new BufferedReader(new FileReader("15619f14twitter-parta-aa"));
		String line;
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
				JSONParser parser=new JSONParser();
				JSONObject obj=(JSONObject) parser.parse(line);				
				JSONObject user = (JSONObject)obj.get("user");
				JSONObject retweet = (JSONObject)obj.get("retweeted_status");
				if (retweet != null) 
					System.out.println(((JSONObject)retweet.get("user")).get("id")+ "_" + user.get("id"));			
			}
		}	
	}
}

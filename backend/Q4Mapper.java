import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TimeZone;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q4Mapper {

	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in, "UTF-8"));
			//BufferedReader r = new BufferedReader(new FileReader("15619f14twitter-parta-aa"));
			final OutputStreamWriter w = new OutputStreamWriter(System.out, "UTF-8");
			
			SimpleDateFormat sf = new SimpleDateFormat("EEE MMM dd HH:mm:ss ZZZZZ yyyy");
			SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
			sdf.setTimeZone(TimeZone.getTimeZone("GMT"));
			
			String line;
			while ((line = r.readLine()) != null) {
				if (line.length() > 0) {
					String location = "";
					JSONParser parser=new JSONParser();
					JSONObject obj=(JSONObject) parser.parse(line);	
					JSONObject user = (JSONObject)obj.get("user");	
					if (obj.get("place") != null) {
						JSONObject place = (JSONObject)obj.get("place");
						String name = (String) place.get("name");
						if (name == null || name.length() == 0)
							location = checkTimeZone(user);
						else
							location = name;
					}
					else
						location = checkTimeZone(user);
					if (location.length() > 0) {
						Date d = sf.parse((String) obj.get("created_at"));
						//System.out.println(location + "_" + sdf.format(d) + "_" + obj.get("id"));
						JSONArray hashtags = (JSONArray) ((JSONObject) obj.get("entities")).get("hashtags");
						//System.out.println(hashtags);
						HashSet<String> tags = new HashSet<String>();
						for (Object o : hashtags) {
							  JSONObject ht = (JSONObject)o;
							  String text = (String) ht.get("text");
							  if (!tags.contains(text)) {
								  tags.add(text);
								  //System.out.println(ht.get("indices"));
								  //System.out.println(((JSONArray) ht.get("indices")).get(0));
								  w.write(location + "____" + sdf.format(d) + "\t\t" + String.format("%025d", obj.get("id")) + "\t\t" + text + "\t\t" + String.format("%05d", ((JSONArray) ht.get("indices")).get(0)) + "\n");
								  w.flush();
								  //System.out.println(location + "____" + sdf.format(d) + "    " + text + "    " + String.format("%025d", obj.get("id")) + "    " + String.format("%05d", ((JSONArray) ht.get("indices")).get(1)));
							  }
						}
					}
				}
			}
			
			

	}
	public static String checkTimeZone(JSONObject user) {
		if (user.get("time_zone") != null){
			if (((String) user.get("time_zone")).toLowerCase().matches(".*\\btime\\b.*")) 
				return "";
			else 
				return (String) user.get("time_zone");
		}
		return "";
	}
	
}

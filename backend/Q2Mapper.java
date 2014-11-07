import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;



public class TweetMapper {

	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		
		//choose between reading from stdin and a file
		//BufferedReader r = new BufferedReader
		//		(new InputStreamReader(System.in, "UTF-8"));
		final OutputStreamWriter w = new OutputStreamWriter(System.out, "UTF-8");
		BufferedReader r = new BufferedReader(new FileReader("test.txt"));
		
		String line;

		//used to convert tweet time format to new format
		SimpleDateFormat sf = new SimpleDateFormat("EEE MMM dd HH:mm:ss ZZZZZ yyyy");
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		sdf.setTimeZone(TimeZone.getTimeZone("GMT"));
		
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
			    JSONParser parser=new JSONParser();
				JSONObject obj=(JSONObject) parser.parse(line);				
				JSONObject user = (JSONObject)obj.get("user");
				JSONObject ob=new JSONObject();
				//put text in json format to avoid parsing newline
				ob.put("text", (String)obj.get("text"));
			    Date d = sf.parse((String) obj.get("created_at"));
			    System.out.println("hi");
				w.write(user.get("id") + "_" + sdf.format(d) + "  " + String.format("%025d", obj.get("id")) + "\t" + ob + "\n");
				w.flush();
			}
	    }
	}

}

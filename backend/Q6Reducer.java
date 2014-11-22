import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashSet;

import org.json.simple.parser.ParseException;


public class Q6Reducer {
	public static void main(String[] args) throws IOException, ParseException {
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in, "UTF-8"));
		final OutputStreamWriter w = new OutputStreamWriter(System.out, "UTF-8");
		//BufferedReader r = new BufferedReader(new FileReader("q6inter.txt"));
		
		String line;
		String currid = "";
		int count = 0;
		HashSet<String> idss = new HashSet<String>();
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
				String[] ids = line.split("\t", 3);
				if (ids[0].equals(currid)) {
					if(!idss.contains(ids[1]))
						count += Integer.parseInt(ids[2]);
				}
				else {
					if (currid.length() > 0)
						System.out.println(currid + "\t" + count);
					currid = ids[0];
					count = Integer.parseInt(ids[2]);
				}
				idss.add(ids[1]);
					
			}
			
		}
		System.out.println(currid + "\t" + count);
	}
}

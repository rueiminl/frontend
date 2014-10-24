import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.ParseException;
import java.util.HashMap;
import java.util.Scanner;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;

public class HBaseImport {
	
	//Reads tweets in csv file store tweets to Hbase database
	public static void main(String[] args) throws FileNotFoundException, 
		IOException, ParseException {
		
		Scanner input = new Scanner(System.in);
		input.useDelimiter(";`\t\n");
		Put put;
		
		//Create Hbase table
		Configuration config = HBaseConfiguration.create();
		HBaseAdmin hba = new HBaseAdmin(config);
		HTableDescriptor desc = new HTableDescriptor("tweets");
		desc.addFamily(new HColumnDescriptor("id"));
		desc.addFamily(new HColumnDescriptor("sentiment"));
		desc.addFamily(new HColumnDescriptor("text"));
		hba.createTable(desc);
		
		//Create table object
		HTable table = new HTable(config, "tweets");
		
		//Create Map to keep track of unique id time combinations
		HashMap<String, Integer> map = new HashMap<String, Integer>();
		String prevId = "";
		int counter = 0;
		
		//Load data to table with id and time as key
		while (input.hasNext()) {
			String[] tweet = input.next().split(",", 5);
		    	if (!tweet[0].equals(prevId)) {
		    		map.clear();
		    		prevId = tweet[0];
		    		map.put(tweet[1], 0);
		    		counter = 0;
		    	}
		    	else {
		    		if(map.containsKey(tweet[1])) {
		    			counter = map.get(tweet[1]) + 1;
		    			map.put(tweet[1], counter);
		    		}
		    		else {
		    			map.put(tweet[1], 0);
		    			counter = 0;
		    		}
		    	}
		    	put = new Put(Bytes.toBytes(tweet[0] + "_" + tweet[1] + "_" + counter));
		    	put.add(Bytes.toBytes("id"), Bytes.toBytes(tweet[2]), Bytes.toBytes(tweet[2]));
		    	put.add(Bytes.toBytes("sentiment"), Bytes.toBytes(tweet[3]), Bytes.toBytes(tweet[3]));
		    	put.add(Bytes.toBytes("text"), Bytes.toBytes(tweet[4]), Bytes.toBytes(tweet[4].substring(1, tweet[4].length()-1)));
		    	table.put(put);
		}
		//close stuff
		table.flushCommits();
		table.close();
		input.close();
		hba.disableTable("tweets");
		hba.deleteTable("tweets");
		hba.close();
	}
}

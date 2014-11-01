package mypackage;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.math.*;
import java.util.*;
import java.sql.*;

// Extend HttpServlet class
public class q3 extends HttpServlet {

    static final String CONNECTION = "jdbc:mysql://localhost/db15619";

    public void init() throws ServletException {
        // Do required initialization
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/plain");
        // Actual logic goes here.
        PrintWriter out = response.getWriter();
        out.println("Wolken,5534-0848-5100,0299-6830-9164,4569-9487-7416");
	try 
	{
		Class.forName("com.mysql.jdbc.Driver");
   		Properties p = new Properties();
	    	p.put("user","root");
    		p.put("password","wolken");
		Connection conn = DriverManager.getConnection(CONNECTION, p);
		String query = "select rid from q3 where uid=" + request.getParameter("userid") + ";";
		Statement st = conn.createStatement();
		ResultSet rs = st.executeQuery(query);
		while (rs.next())
		{
			String rid = rs.getString("rid");
			out.println(rid.replace(",", "\n"));
		}
		conn.close();
	}
	catch (Exception e)
	{
		out.println(e + "?\n");
	}
    }

    public void destroy() {
        // do nothing.
    }
}

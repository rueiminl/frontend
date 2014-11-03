package mypackage;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.math.*;
import java.util.*;
import java.sql.*;

// Extend HttpServlet class
public class q3_peek extends HttpServlet {

    static Connection conn;
    public void init() throws ServletException 
    {
	try
	{
		reconnect();
	}
	catch (Exception e)
	{
	}
    }

    public void reconnect() throws SQLException 
    {
	try 
	{
		Class.forName("com.mysql.jdbc.Driver");
		conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/db15619?user=root&password=wolken");
	}
	catch (Exception e)
	{
	}
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
		String query = "select rid from q3 where uid=" + request.getParameter("userid") + ";";
		Statement st = conn.createStatement();
		ResultSet rs = st.executeQuery(query);
		while (rs.next())
		{
			String rid = rs.getString("rid");
			out.println(rid.replace(",", "\n"));
		}
		rs.close();
		st.close();
	}
	catch (Exception e)
	{
		out.println(e);
	}
    }

    public void destroy() {
        // do nothing.
	try
	{
		conn.close();
	}
	catch (Exception e)
	{
	}
    }
}

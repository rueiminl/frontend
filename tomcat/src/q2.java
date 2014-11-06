package mypackage;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.math.*;
import java.util.*;
import java.sql.*;
import org.apache.tomcat.jdbc.pool.DataSource;
import org.apache.tomcat.jdbc.pool.PoolProperties;
// Extend HttpServlet class
public class q2 extends HttpServlet {
    private DataSource dataSource;
    public void init() throws ServletException 
    {
            PoolProperties p = new PoolProperties();
            p.setUrl("jdbc:mysql://localhost:3306/db15619?autoReconnect=true&characterEncoding=UTF-8");
            p.setUsername("root");
            p.setPassword("wolken");
            p.setDriverClassName("com.mysql.jdbc.Driver");
            p.setJmxEnabled(true);
            p.setTestWhileIdle(false);
            p.setTestOnBorrow(true);
            p.setValidationQuery("SELECT 1");
            p.setTestOnReturn(false);
            p.setValidationInterval(30000);
            p.setTimeBetweenEvictionRunsMillis(30000);
            p.setMaxActive(100);
            p.setInitialSize(10);
            p.setMaxWait(10000);
            p.setRemoveAbandonedTimeout(60);
            p.setMinEvictableIdleTimeMillis(30000);
            p.setMinIdle(10);
            p.setLogAbandoned(true);
            p.setRemoveAbandoned(true);
            p.setJdbcInterceptors("org.apache.tomcat.jdbc.pool.interceptor.ConnectionState;org.apache.tomcat.jdbc.pool.interceptor.StatementFinalizer");
            dataSource = new DataSource();
            dataSource.setPoolProperties(p); 
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/plain; charset=UTF-8");
	response.setCharacterEncoding("UTF-8");
        // Actual logic goes here.
        PrintWriter out = response.getWriter();
        out.println("Wolken,5534-0848-5100,0299-6830-9164");
	try 
	{
		Connection conn = dataSource.getConnection();
		String query = "select concat(tid, \":\", s, \":\", msg) as reply from q2 where uid=" + request.getParameter("userid") + " and ts='" + request.getParameter("tweet_time") + "' order by tid;";
		Statement st = conn.createStatement();
		ResultSet rs = st.executeQuery(query);
		while (rs.next())
		{
			out.println(rs.getString("reply"));
		}
		rs.close();
		st.close();
		conn.close();
	}
	catch (Exception e)
	{
		out.println(e);
	}
    }

    public void destroy() {
    }
}

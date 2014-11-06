package mypackage;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.math.*;
import java.util.*;
import java.text.*;

// Extend HttpServlet class
public class q1 extends HttpServlet {

    public void init() throws ServletException {
        // Do required initialization
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/plain");
        // Actual logic goes here.
        PrintWriter out = response.getWriter();
        BigInteger x = new BigInteger("6876766832351765396496377534476050002970857483815262918450355869850085167053394672634315391224052153");
	BigInteger xy = new BigInteger(request.getParameter("key"));
        BigInteger y = xy.divide(x);
	SimpleDateFormat ft = new SimpleDateFormat ("yyyy-MM-dd hh:mm:ss");
        out.println(y + "\nWolken,5534-0848-5100,0299-6830-9164\n" + ft.format(new Date()));
    }

    public void destroy() {
        // do nothing.
    }
}

package mypackage;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.math.*;

// Extend HttpServlet class
public class q4 extends HttpServlet {

    public void init() throws ServletException {
        // Do required initialization
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
        // Actual logic goes here.
        PrintWriter out = response.getWriter();
        BigInteger x = new BigInteger("6876766832351765396496377534476050002970857483815262918450355869850085167053394672634315391224052153");
        BigInteger xy = new BigInteger("20630300497055296189489132603428150008912572451445788755351067609550255501160184017902946173672156459");
        BigInteger y = xy.divide(x);
        out.println(y + "\nWolken,5534-0848-5100,0299-6830-9164,4569-9487-7416\n");
    }

    public void destroy() {
        // do nothing.
    }
}

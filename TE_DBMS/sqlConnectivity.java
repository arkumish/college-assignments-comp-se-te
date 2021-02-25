package sqlConnectivity;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.util.Scanner;


public class sqlConnectivity {
	
    private Connection connect = null;
    private Statement statement = null;
    private ResultSet resultSet = null;
    private PreparedStatement prepStatement = null;

    public void readDataBase() throws Exception {
        try {
            
            Class.forName("com.mysql.jdbc.Driver");
            connect = DriverManager.getConnection("jdbc:mysql://localhost/feedback?" + "user=student&password=student37");
            statement = connect.createStatement();
            resultSet = statement.executeQuery("select * from feedback.comments");
            while (resultSet.next()) {
                String id = resultSet.getString("id");
                String email = resultSet.getString("email");
                String data = resultSet.getString("data");
               
                System.out.println("id:: " + id);
                System.out.println("email:: " + email);
                System.out.println("data:: " + data);
            }

        } catch (Exception e) {
            throw e;
        } finally {
            close();
        }

    }
    
    public void insertDataBase() throws Exception {
        try {
        	String id = new String();
            String email = new String();
            String data = new String();
            Scanner in = new Scanner(System. in);
            System.out.println("Enter the id:");
            id=in.nextLine();

            System.out.println("Enter the email:");
            email=in.nextLine();
            
            System.out.println("Enter the data:");
            data=in.nextLine();
            
            
            Class.forName("com.mysql.jdbc.Driver");
            connect = DriverManager.getConnection("jdbc:mysql://localhost/feedback?" + "user=student&password=student37");
            prepStatement = connect.prepareStatement("insert into feedback.comments values (?,?,?)");
            
            
            prepStatement.setString(1, id);
            prepStatement.setString(2, email);
            prepStatement.setString(3, data);
            
            prepStatement.executeUpdate();

        } catch (Exception e) {
            throw e;
        } finally {
            close();
        }

    }


    private void close() {
        try {
            if (resultSet != null) {
                resultSet.close();
            }

            if (statement != null) {
                statement.close();
            }

            if (connect != null) {
                connect.close();
            }
        } catch (Exception e) {

        }
    }
    
    public static void main(String[] args) throws Exception {
    	sqlConnectivity cnn = new sqlConnectivity();
        cnn.readDataBase();
        cnn.insertDataBase();
        cnn.readDataBase();
    }

}

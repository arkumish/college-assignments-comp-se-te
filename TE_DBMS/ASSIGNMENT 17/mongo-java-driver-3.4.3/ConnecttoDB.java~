import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.FindIterable; 
import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.MongoCredential;
import java.util.*; 

public class ConnecttoDB
{
     public static void main(String args[])
     {
          MongoClient mongo = new MongoClient("localhost",27017);
    
          System.out.println("connected successfully");
          
          MongoDatabase database = mongo.getDatabase("first");
      
          System.out.println("collection created successfully");
          
        
          MongoCollection<Document> collection = database.getCollection("Employee");
          
   	   FindIterable<Document> iterDoc = collection.find();
  	    int i=1;
      
     	 Iterator it = iterDoc.iterator();
      
    	  while(it.hasNext())
   	   {
        	  System.out.println(it.next());
       		   i++;
      	   }
     }
}

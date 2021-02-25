import java.util.Date;

import com.mongodb.client.*;
import org.bson.*;
import org.bson.types.*;
import com.mongodb.MongoClient;
import com.mongodb.MongoCredential;
import org.json.simple.*;
import java.util.*;

interface DBInfo
{
    //databases
    String d_assign14 = "assign14";
    //collections
    String c_userInfo = "userInfo";

    //fields
    String f_username = "username";
    String f_password = "password";
    String f_notes = "notes";
    String f_notes_dateAdded = "dateAdded";
    String f_notes_tittle = "tittle";
    String f_notes_content = "content";
}


class DBManager
{
    private static MongoClient mongo = new MongoClient();
    private static MongoDatabase db = mongo.getDatabase(DBInfo.d_assign14);
    private static MongoCollection<Document> userInfo = db.getCollection(DBInfo.c_userInfo);

    static
    {
        System.out.println("Database Initialized");
        // System.out.println("Proud Database Users:"+userInfo.countDocuments());
    }

    private static String getUserObjId(Document doc) throws Exception
    {
        
        doc = userInfo.find(doc).first();
        if(doc==null)
            throw new Exception("Cannot Find Document");
        
        return doc.getObjectId("_id").toString(); 
        
    }

    public static String signUpUser(String username,String password) throws Exception
    {   
        //find({username:"kalu"})
        Document clientDoc = new Document("username",username.toLowerCase());
        Document query = userInfo.find(clientDoc).first();  
        if(query!=null)
            throw new Exception("Username Taken By Another User:(\nPlease Choose Another");
        
        clientDoc.append(DBInfo.f_password,password);
        userInfo.insertOne(clientDoc);
        
        //{},{$set:{username:"karan"}}
        // Document query = new Document("$set",new Document("username","karan"));

        return getUserObjId(clientDoc);
    }

    public static String logInUser(String username,String password) throws Exception
    {
        Document clientDoc = new Document(DBInfo.f_username,username.toLowerCase());
        Document query = userInfo.find(clientDoc).first();
        if(query == null)
            throw new Exception(username+" not registerd");
        
        if(!password.equals((String)query.get(DBInfo.f_password)))
            throw new Exception("Invalid password");
        
        // clientDoc.append(DBInfo.f_password,password);
        return query.getObjectId("_id").toString();
    }

    public static String getUsername(String objId)throws Exception
    {
        Document clientDoc = new Document("_id",new ObjectId(objId));
        clientDoc = userInfo.find(clientDoc).first();
        if(clientDoc == null)
            throw new Exception("Invalid ID");
        
        return (String)clientDoc.get(DBInfo.f_username);
    }

    public static boolean saveNote(String objId, String tittle, String content)
    {
        try 
        {
            Document clientDoc = new Document("_id",new ObjectId(objId));
            clientDoc = userInfo.find(clientDoc).first();
            if(clientDoc == null)
                throw new Exception("Invalid ID");
            
            //save note
            Document query = new Document(
                "$push",new Document(
                    "notes",new Document().append(DBInfo.f_notes_dateAdded,new Date())
                                                 .append(DBInfo.f_notes_tittle,tittle)
                                                 .append(DBInfo.f_notes_content,content)
                )
            );
            
            userInfo.updateOne(clientDoc,query);
            return true;
        } 
        catch (Exception e) 
        {
            System.out.println("Note save Failed");
            e.printStackTrace();
            return false;
        }
    }

    public static JSONArray getNotes(String objId)throws Exception
    {
        Document clientDoc = new Document("_id",new ObjectId(objId));
        clientDoc = userInfo.find(clientDoc).first();
        if(clientDoc == null)
            throw new Exception("Invalid ID");
        
        JSONArray notesArr = new JSONArray();
        
        List<Document> noteList = (List<Document>)clientDoc.get(DBInfo.f_notes);
        if(noteList == null)
            return notesArr;
        
        for(Document d:noteList)
            notesArr.add(d);

        return notesArr;
    }
}
import org.json.simple.*;
import org.json.simple.parser.*;

import java.util.*;
import java.io.*;

class JsonEncodeDemo {

   public static void main(String[] args) {
      JSONObject obj = new JSONObject();

      obj.put("name", "foo");
      obj.put("num", new Integer(100));
      obj.put("balance", new Double(1000.21));
      obj.put("is_vip", new Boolean(true));

     try 
        {
            FileWriter fout = new FileWriter("a.json");
            fout.write(obj.toJSONString());
            fout.close();
            
        } 
        catch (Exception e) 
        {
       
        }

      System.out.print(obj);
   }
}
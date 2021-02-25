import java.util.* ;
import java.net.* ;
import java.io.* ;

public class subnet{
    public static void main(String args[]){
        String ip;
        System.out.print("Enter the IP Address: ");
        Scanner in = new Scanner(System.in);
        ip=in.nextLine();
        String[] split_ip= ip.split("\\.");
        int split_bip[] = new int[4];
        for(int i=0;i<4;i++){
            split_bip[i]=Integer.parseInt(split_ip[i]);
        }
        System.out.print("IP Address in Binary: ");
        ipToBinary(split_bip);
        System.out.println();
        int mask,s_mask;
        System.out.print("Enter the network mask: ");
        mask=in.nextInt();
        System.out.print("Enter the number of subnets: ");
        s_mask=in.nextInt();
        //-------------------------------------------------------------------------------------
        int net_m[] =  new int[4];
        int sub_m[] = new int[4];
        int temp=mask,z=0;
        while(temp>=8){
            net_m[z++]=255;
            temp-=8;
        }
        if(temp!=0){
            int y=7;
            while(temp!=0){
                net_m[z]+=(int)Math.pow(2,y);
                y--;
                temp--;
            }
        }
        System.out.print("Network Mask: ");
        display(net_m);
        System.out.println();
        //-------------------------------------------------------------------------------------
        int subnetbits=(int)Math.ceil(Math.log(s_mask)/Math.log(2));
        int host=32-(mask+subnetbits);
        int inc=(int)Math.pow(2,host);
        temp=mask+subnetbits;
        int total_mask_bits = mask + subnetbits;
        z=0;
        while(temp>=8){
            sub_m[z++]=255;
            temp-=8;
        }
        if(temp!=0){
            int y=7;
            while(temp!=0){
                sub_m[z]+=(int)Math.pow(2,y);
                y--;
                temp--;
            }
        }
        System.out.print("Subnet Mask: ");
        display(sub_m);
        System.out.println();
        //-------------------------------------------------------------------------------------
        int net_id[] = new int[4];
        for(int i=0;i<4;i++){
            net_id[i] = split_bip[i] & net_m[i];
        }
        System.out.print("Network Id: ");
        display(net_id);
        System.out.println();
        //-------------------------------------------------------------------------------------
        System.out.println("------------------Subnet Range------------------- ");
        int s_addr[] = new int[4];
        int e_addr[] = new int[4];
        for(int i=0;i<4;i++){
            s_addr[i] = net_id[i];
        }
        for(int i=0;i<s_mask;i++){
            for(int j=0;j<4;j++){
                e_addr[j]=s_addr[j];
            }
            e_addr[3]=e_addr[3]+inc-1;
            for(int j=3;j>=0;j--){
                if(e_addr[j]>=256){
                    e_addr[j-1]+=(e_addr[j]/256);
                    e_addr[j]%=256;
                }
            }

            System.out.print("Mask "+(i+1)+ " Range: ");
            display(s_addr);
            System.out.print("/"+total_mask_bits+" - ");
            display(e_addr);
            System.out.println("/"+total_mask_bits);

            System.out.print("In Binary: ");
            ipToBinary(s_addr);
            System.out.print(" - ");
            ipToBinary(e_addr);
            System.out.println();
            for(int j=0;j<4;j++){
                s_addr[j]=e_addr[j];
            }
            s_addr[3]++;

            for(int j=3;j>=0;j--){
                if(s_addr[j]>=256){
                    s_addr[j-1]+=(s_addr[j]/256);
                    s_addr[j]%=256;
                }
            }
        }

    }
    public static void ipToBinary(int arr[]){
        int z=31,count;
        int ip[] = new int[32];
        for(int i=3;i>=0;i--){
            int dec=arr[i];
            count=0;
            while(dec!=0){
                ip[z--]=dec%2;
                dec=dec/2;
                count++;
            }
            z=z-(8-count);
        }
        for(int i=0;i<32;i++){
            System.out.print(ip[i]);
            if((i+1)%8==0)System.out.print(" ");
        }
    }
    public static void display(int arr[]){
        for(int i=0;i<4;i++){
            System.out.print(arr[i]);
            if(i!=3)
                System.out.print(".");
        }
    }

}

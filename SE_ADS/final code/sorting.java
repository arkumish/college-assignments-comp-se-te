import java.util.*;
class Sorting{
	static void heapSort(int arr[], int n) 
    { 
        for (int i = n / 2 - 1; i >= 0; i--) 
            heapify(arr, n, i); 
  		for (int i=n-1; i>=0; i--) 
        { 
            int temp = arr[0]; 
            arr[0] = arr[i]; 
            arr[i] = temp; 
  			heapify(arr, i, 0); 
        }
    } 
  
   	private static void heapify(int arr[], int n, int i) 
    { 
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
  		if (l < n && arr[l] > arr[largest]) 
            largest = l; 
	  	if (r < n && arr[r] > arr[largest]) 
            largest = r; 
	  	if (largest != i) 
        { 
            int swap = arr[i]; 
            arr[i] = arr[largest]; 
            arr[largest] = swap; 
  			heapify(arr, n, largest); 
        } 
    }
	static void shellSort(int arr[], int n){
		for (int gap = n/2; gap > 0; gap /= 2) 
        { 
            for (int i = gap; i < n; i += 1) 
            { 
                int temp = arr[i]; 
                int j; 
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                    arr[j] = arr[j - gap]; 
                arr[j] = temp; 
            } 
        }
	}
	static void bubbleSort(int arr[], int n) 
	{ 
	   int i, j, temp;
	   for (i = 0; i < n-1; i++)       
	  		for (j = 0; j < n-i-1; j++)  
	           if (arr[j] > arr[j+1]) {
	           	temp = arr[j];
	           	arr[j] = arr[j+1];
	           	arr[j+1] = temp;
	           }
	} 
}

class SortingComplexity{
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		int n;
		System.out.print("Enter the number of elements : ");
		n = in.nextInt();
		int arr[] = new int[n];
		int cp[] = new int[n];

  try{
		for (int i = 0; i<n; i++){
			arr[i] = (int)(Math.random() * n);
		}

    }
    catch(ArrayIndexOutOfBoundsException e)
  {
   System.out.println(" your are trying to access out of bound array elements "+ e);
  }		
		
		long startTime,endTime;
		System.out.println("\n\nSorting using shell sort : ");
		for (int i = 0; i<n; i++)
			cp[i] = arr[i];
		startTime = System.nanoTime();
		Sorting.shellSort(cp,n);
		endTime = System.nanoTime();
		System.out.println("Time elapsed : "+ (endTime-startTime)+" nanoseconds\n");

		System.out.println("Sorting using heap sort : ");
		for (int i = 0; i<n; i++)
			cp[i] = arr[i];
		startTime = System.nanoTime();
		Sorting.heapSort(cp,n);
		endTime = System.nanoTime();
		System.out.println("Time elapsed : "+ (endTime-startTime)+" nanoseconds\n");

		System.out.println("Sorting using bubble sort : ");
		for (int i = 0; i<n; i++)
			cp[i] = arr[i];
		startTime = System.nanoTime();
		Sorting.bubbleSort(cp,n);
		endTime = System.nanoTime();
		System.out.println("Time elapsed : "+ (endTime-startTime)+" nanoseconds\n");
	}
}


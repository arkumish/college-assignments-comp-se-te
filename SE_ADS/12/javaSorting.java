import java.util.*;
class Sorting{
	int arr[];
	int n;
	int heapSize;
	Sorting(){
		n = heapSize = 10;
		arr = new int[10];
		for(int i=0 ; i<n ; i++){
			arr[i] = (int)(Math.random()*n);
		}
	}
	void heapSort(){ 
		heapSize = n;
        for (int i = n/2-1 ; i >= 0; i--) 
            heapify(i); 
  		for (int i=n-1; i>=0; i--){ 
            int temp = arr[0]; 
            arr[0] = arr[i]; 
			arr[i] = temp; 
			heapSize--;
  			heapify(0); 
        }
    } 
  
   	void heapify(int i){ 
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
  		if (l < heapSize && arr[l] > arr[largest]) 
            largest = l; 
	  	if (r < heapSize && arr[r] > arr[largest]) 
            largest = r; 
	  	if (largest != i){ 
            int swap = arr[i]; 
            arr[i] = arr[largest]; 
            arr[largest] = swap; 
  			heapify(largest); 
        } 
	}
	
	void shellSort(){
		for (int gap = n/2; gap > 0; gap /= 2){ 
            for (int i = gap; i < n; i += 1){ 
                int temp = arr[i]; 
                int j; 
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                    arr[j] = arr[j - gap]; 
                arr[j] = temp; 
            } 
        }
	}

	void display(){
		for(int i=0  ;i<n ; i++)
			System.out.print(arr[i] + " ");
		System.out.println();
	}

	void randomize(){
		for(int i=0  ; i<n ; i++){
			arr[i] = (int)(Math.random()*n);
		}
	}
}

class javaSorting{
	public static void main(String args[]){
		Sorting s = new Sorting();
		s.heapSort();
		s.display();
		s.randomize();
		s.shellSort();
		s.display();
	}
}
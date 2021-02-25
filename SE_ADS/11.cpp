#include <bits/stdc++.h> 
using namespace std; 
struct MinHeapNode{ 
    int element; 
    int i; 
}; 

class MinHeap{ 
    MinHeapNode* harr;  
    int heapSize;    
public: 
    MinHeap(MinHeapNode a[], int size){
        heapSize = size; 
        harr = a; 
        int i = (heapSize - 1) / 2; 
        while (i >= 0){ 
            MinHeapify(i); 
            i--; 
        }         
    }
    void MinHeapify(int i);
    MinHeapNode getMin() ;
    void replaceMin(MinHeapNode x);
};  

void MinHeap :: replaceMin(MinHeapNode x){ 
        harr[0] = x; 
        MinHeapify(0); 
} 

MinHeapNode MinHeap :: getMin(){  
        return harr[0]; 
} 

void MinHeap :: MinHeapify(int i){
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
    int smallest = i; 
    if (l < heapSize && harr[l].element < harr[i].element) 
        smallest = l; 
    if (r < heapSize && harr[r].element < harr[smallest].element) 
        smallest = r; 
    if (smallest != i){ 
        swap(harr[i], harr[smallest]); 
        MinHeapify(smallest); 
    } 
}

FILE* openFile(char *fileName , char* mode){
    FILE* fp = fopen(fileName,mode);
    if(fp== NULL){
         perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE); 
        //cout << "ERROR OPENING FILE" << endl;
       // exit(1);
    }
    return fp;
}

void createInitialRuns(char *inputFile, int numWays, int runSize){
    FILE *in = openFile(inputFile , "r");
    FILE *out[numWays];
    char fileName[2];
    for(int i=0 ; i<numWays ; i++){
        snprintf(fileName , sizeof(fileName) , "%d" , i);
        out[i] = openFile(fileName, "w");
    }

    int* arr = (int*)malloc(runSize * sizeof(int));
    bool moreInput = true;
    int outputFilesCount = 0;
    while(moreInput){
        int i;//***
        for(i =0 ; i<runSize ; i++){
            if(fscanf(in, "%d " , &arr[i])!=1){
                moreInput = false;
                break;
            }
        }
        sort(arr,arr+i);
        for(int j=0  ; j<i ; j++)
            fprintf(out[outputFilesCount] , "%d " , arr[j]);
        outputFilesCount++;
    }
    
    for(int i=0 ; i<numWays ; i++)
        fclose(out[i]);
    fclose(in);
}

void mergeFiles(char *outputFile, int numWays, int runSize){
    FILE *in[numWays];
    char fileName[2];
    for(int i=0 ; i<numWays ; i++){
        snprintf(fileName , sizeof(fileName) , "%d" , i);
        in[i] = openFile(fileName, "r");
    }

    FILE *out = openFile(outputFile, "w"); 
    MinHeapNode* harr = new MinHeapNode[numWays]; 
    int i; 
    for (i = 0; i < numWays; i++){ 
        fscanf(in[i], "%d ", &harr[i].element); 
        harr[i].i = i; 
    } 
    MinHeap hp(harr, i); 
    int count = 0; 
    while (count != numWays){ 
        MinHeapNode root = hp.getMin(); 
        fprintf(out, "%d ", root.element); 
        if (fscanf(in[root.i], "%d ", &root.element) != 1 ){ 
            root.element = INT_MAX; 
            count++; 
        } 
        hp.replaceMin(root); 
    } 
    for (int i = 0; i < numWays; i++) 
        fclose(in[i]); 
    fclose(out); 
}

void externalSort(char *inputFile, char *outputFile, int numWays, int runSize){
    createInitialRuns(inputFile, numWays, runSize);
    mergeFiles(outputFile, numWays, runSize);
}

int main(){
    int numWays = 10;
    int runSize = 1000;
    char inputFile[] = "input.txt";
    char outputFile[] = "output.txt";
    FILE *in = openFile(inputFile, "w");
    srand(time(NULL));
    for(int i=0 ; i<numWays*runSize ; i++){
        fprintf(in , "%d " , rand());
    }
    fclose(in);
    externalSort(inputFile,outputFile,numWays,runSize);
    return 0;
}
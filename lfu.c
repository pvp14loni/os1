#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20


int getLFU(int frames[], int freq[], int f) {
    int minFreq = 1000; 
    int index = -1;
    for (int i = 0; i < f; i++) {
        if (freq[i] < minFreq) {
            minFreq = freq[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int pageFaults = 0, n, f, freq[MAX_FRAMES] = {0};

   
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    
    printf("Enter number of frames: ");
    scanf("%d", &f);

    
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
    }


    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                freq[j]++;
                break;
            }
        }


        if (!found) {
            pageFaults++;


            int emptyFrame = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1) {
                frames[emptyFrame] = page;
                freq[emptyFrame] = 1;
            } else {
               
                int index = getLFU(frames, freq, f);
                frames[index] = page;
                freq[index] = 1;
            }
        }

        
        printf("After accessing page %d: ", page);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    // Output the total page faults
    printf("Total page faults: %d\n", pageFaults);

    return 0;
}

#include "gradient.h"

path_point find_highest_point(){

    path_point finding_peak;
    finding_peak.y = 190;
    finding_peak.x = 190;
    float view[VIEW_SIZE][VIEW_SIZE];
    float current_highest;
    int tempxCoords = 0;
    int tempyCoords = 0;
    int gCounter = 0;
    int outOfBoundsX;
    int outOfBoundsY;
    int bounds = 1000;
    
    // Loop that continues until declare_peak is called or 20000 loops
    for (int reps = 0; reps <= 20000; reps++) {
        
        generate_view(view, finding_peak.y, finding_peak.x);
        gCounter++;
        tempxCoords = 0;
        tempyCoords = 0;
        current_highest = 0;
        
        // If view is out of bounds it will see which is bigger x or y and then make that the new bounds, essentially tightens the bounds 
        if (outOfBoundsX > outOfBoundsY) {
            bounds = outOfBoundsX;
        } else if (outOfBoundsY > outOfBoundsX) {
            bounds = outOfBoundsY;
        }  
        
        // Checks the view and finds the largest position sees where that is and records the movement to that position
        for (int i=0;i<11;i++) {
            for (int j=0;j<11;j++) {
                if (view[i][j]>current_highest) {
                    current_highest = view[i][j];
                    if (i<=5) {
                        tempyCoords = -5 +i;
                    } else {
                        tempyCoords = i - 5;
                    }
                    if (j<=5) {
                        tempxCoords = -5 +j;
                    } else {
                        tempxCoords = j - 5;
                    }
                } 
            }
        }
    
        // if the program is within the first 7 loops it will increase the movment because we know the rough direction
        if (gCounter <= 5) {
            tempxCoords = tempxCoords*7;
            tempyCoords = tempyCoords*7;
        } else if (gCounter <= 6) {
            tempxCoords = tempxCoords*3;
            tempyCoords = tempyCoords*3;
        } else if (gCounter <= 7) {
            tempxCoords = tempxCoords*2;
            tempyCoords = tempyCoords*2;
        }
        
        // adding the new movment to the previous view position to get the new view position for next loop
        finding_peak.y = finding_peak.y + tempyCoords;
        finding_peak.x = finding_peak.x + tempxCoords;
        
        // checking if the view is otuside of bounds and jumping to a random location if it is and resets the loop counter
        if (view[0][0] == -1 && view[10][10] == -1) {
            outOfBoundsX = finding_peak.x; 
            outOfBoundsY = finding_peak.y;
            finding_peak.x = rand() % bounds;
            finding_peak.y = rand() % bounds;
            gCounter = 0;
        }
        
        // checks for a peak by seeing if the position above, below, left and right are smaller
        if (view[5][5] > view[5][6] && view[5][5] > view[5][4] && view[5][5] > view[4][5] && view[5][5] > view[6][5]) {
            if (declare_peak(finding_peak.x, finding_peak.y)) {
                printf("Right guess\n");
                break; 
            } else {
                finding_peak.x = rand() % bounds;
                finding_peak.y = rand() % bounds;
                gCounter = 0;
            }
        }
        
        // if the view has gotten stuck for some reason and isn't moving then it jumps to a random location and resets the loop counter
         if (tempxCoords == 0 && tempyCoords == 0) {
            finding_peak.x = rand() % bounds;
            finding_peak.y = rand() % bounds;
            gCounter = 0;
        }
    
    }
    
    return finding_peak;
}


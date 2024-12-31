#include "function.h"
#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char *argv[]) {
    int choice;     
    int choiceDanhmuc; 

    do {
        lobbyMenu(choice);
        scanf("%d", &choice);
        switch(choice){
            case 1:
                do {
                    danhmucMenu(choiceDanhmuc); 
                    scanf("%d", &choiceDanhmuc);
                    switch(choiceDanhmuc){
                        case 1:
                            viewdanhmuc();
                            break;
                        case 2:
                            adddanhmuc();
                            break;
                        case 3:
                            editdanhmuc(); 
                            break;
                        case 4:
                            deleteDanhMuc();
                            break;
                    }
                } while(choiceDanhmuc != 6);
                break;
            case 2:
                break;    
            case 3:
			    printf("=====CAM ON DA SU DUNG HE THONG=====\n");
                printf("===========HEN GAP LAI==============\n");
				break; 
		}   
    } while(choice != 3);
    return 0;
}


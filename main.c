/// Onur Karakaya - 140201051 - Prolab2 - 1.Proje
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define MAX 82
#define INFINITY 9999

void dijkstra_algorithm(int distance_matrix[MAX][MAX],int n,int starting_city,int end_city,char city[MAX][MAX]);
int main(){
    ///kullanilacak olan degiskenler tanimlanir
    int distance_matrix[MAX][MAX],i,j,k,city_count,starting_city=-1,end_city=-1,n,distance[MAX];
    FILE *file_citycode,*file_citydistance;
    char read[MAX][MAX],city[MAX][MAX],first_city[MAX][MAX],second_city[MAX][MAX],city_distance[MAX][MAX],start[MAX],finish[MAX];
    ///sehir kod dosyasi acilir
    file_citycode = fopen("sehir kod.txt","r");
    ///okunan satirlar city degiskenine atilir
    for(n=0; n<=MAX; n++){
        fgets(read[n], 20, file_citycode);
        strcpy(city[n],strtok(read[n],"-"));
        if(feof(file_citycode)){
            break;
        }
    }
    city_count = n;
    ///sehir mesafe dosyasi acilir
    file_citydistance = fopen("sehir mesafe.txt","r");
    ///sehirler ile mesafeleri degiskenlere atilir
    for(n=0; n<=MAX; n++){
        fgets(read[n], 50, file_citydistance);
        strcpy(first_city[n],strtok(read[n],"-"));
        strcpy(second_city[n],strtok(NULL,"-"));
        strcpy(city_distance[n],strtok(NULL,"-"));
        distance[n] = atoi(city_distance[n]);
        if(feof(file_citydistance)){
            break;
        }
    }
    ///sehirlerin kodlari bulunup uzakliklar mesafe matrisine eklenir
    for(i=0; i<=MAX; i++){
        if(strlen(first_city[i])==0){
            break;
        }
        for(j=0; j<=MAX; j++){
            if(strcmp(first_city[i],city[j])==0){
                for(k=0; k<=MAX; k++){
                    if(strcmp(second_city[i],city[k])==0){
                        distance_matrix[j-1][k-1] = distance[i];
                        distance_matrix[k-1][j-1] = distance[i];
                    }
                }
            }
        }
    }
    ///baslangic sehri istenip sorgulamasi yapilir
    try1:
    printf("Baslangic sehrini girin: ");
    gets(start);
    ///baslangic sehrinin kontrolu yapilir ve kodu bulunur
    for(i=0; i<=MAX; i++){
        if(strcmp(start,city[i])==0){
            starting_city=i-1;
        }
    }
    if (starting_city==-1){
        printf("Yanlis bir sehir ismi girdiniz!\n\n");
        goto try1;
    }
    ///bitis sehri istenip sorgulamasi yapilir
    try2:
    printf("\nBitis sehrini girin: ");
    scanf("%s", finish);
    ///bitis sehrinin kontrolu yapilir ve kodu bulunur
    for(i=0; i<=MAX; i++){
        if(strcmp(finish,city[i])==0){
            end_city=i-1;
        }
    }
    if (end_city==-1){
        printf("Yanlis bir sehir ismi girdiniz!\n\n");
        goto try2;
    }
    ///dijkstra_algorithm fonksiyonu gerekli degiskenler ile cagirilir
    dijkstra_algorithm(distance_matrix,city_count,starting_city,end_city,city);
    return 0;
}

/** http://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
    websitesindeki algoritma orneginden esinlenilmis, ihtiyac dogrultusunda duzenlenmistir                 */
void dijkstra_algorithm(int distance_matrix[MAX][MAX],int n,int starting_city,int end_city,char city[MAX][MAX]){
    ///kullanilacak olan degiskenler tanimlanir
    int cost[MAX][MAX],distance[MAX],memory[MAX];
    int visited[MAX],city_count,mindistance,next_city,i,j;
    ///distance matrix girdileri cost matrisine okutulur
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(distance_matrix[i][j]==0){
                cost[i][j]=INFINITY;
            }
            else{
                cost[i][j]=distance_matrix[i][j];
            }
        }
    }
    for(i=0;i<n;i++){
        distance[i]=cost[starting_city][i];
        memory[i]=starting_city;
        visited[i]=0;
    }
    distance[starting_city]=0;
    visited[starting_city]=1;
    city_count=1;
    while(city_count<n-1){
        mindistance=INFINITY;
        ///next_city degiskenine minimum uzaklik verilir
        for(i=0;i<n;i++){
            if(distance[i]<mindistance&&!visited[i]){
                mindistance=distance[i];
                next_city=i;
            }
        }
        ///next_city degiskeni uzerinden daha iyi bir yol olup olmadigi sorgulanir
        visited[next_city]=1;
        for(i=0;i<n;i++){
            if(!visited[i]){
                if(mindistance+cost[next_city][i]<distance[i]){
                    distance[i]=mindistance+cost[next_city][i];
                    memory[i]=next_city;
                }
            }
        }
        city_count++;
    }
    ///tum sehirlere olan uzaklik ve yol yazdirilir
    printf("\n\n\n1.CIKTI\nBir sehirden diger sehirlere olan en kisa yolun (gecilen sehirler) ve toplam mesafenin ekrana yazdirilmasi.\nBurada kullanicidan hangi sehrin baslangic dugumu olacaginin alinmasi gerekmektedir.\n");
    for(i=0;i<n;i++){
        if(i!=starting_city){
            printf("\n\n%s-%s sehirleri arasi mesafe = %d km\n",city[starting_city+1],city[i+1],distance[i]);
            printf("Yol Haritasi =  %s",city[i+1]);
            j=i;

            while(j!=starting_city){
                j=memory[j];
                printf(" << %s",city[j+1]);
            }
        }
    }
    ///bitis sehrine olan uzaklik ve yol yazdirilir
    for(i=0;i<n;i++){
        if(i!=starting_city){
            if(i==end_city){
                printf("\n\n\n\n2.CIKTI\nKullanici tarafindan girilen iki sehir arasindaki en kisa yolun (gecilen sehirler) ve mesafenin ekrana yazdirilmasi\n");
                printf("\n\n%s-%s sehirleri arasi mesafe = %d km\n",city[starting_city+1],city[i+1],distance[i]);
                printf("Yol Haritasi =  %s",city[i+1]);
                j=i;

                while(j!=starting_city){
                    j=memory[j];
                    printf(" << %s",city[j+1]);
                }
            }
        }
    }
    printf("\n\n\n\nProgram sonlanmistir.. \n\n");
}

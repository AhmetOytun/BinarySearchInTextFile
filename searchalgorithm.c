#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"
#include "errno.h"

int binary_search(char arr[][20],int l,int r);
void txt_file_to_arr(FILE *fp,char arr[][20]);
int get_line_num(FILE *fp);
void show_arr(char *arr);
bool cmp(char str1[],char str2[]);

char KEY[20];
char fileName[20];
char MAX_LINE[20];
int LINE_NUM;

int main(){

    //Space complexity=O(n)[Çünkü text dosyasındakileri arrayde tutuyorum ve text dosyasının uzunluğunu bilmiyoruz]
    //Time complexity=0(n)[Çünkü for döngülerimiz var ancak hiçbiri iç içe değil]

    /*Tamamını kendim yazdım başta dosya üzerinde lseek ve fseek kullanarak hafızada yer tutmadan aramayı denedim fakat
     dosyanın her satırındaki kelime uzunluğu farklı olduğu için bunu başaramadım.*/

    //ÖNEMLİ NOT: Soruda verilen dosyanın satır düzeyinde sıralı olduğunu söylüyordu o sebeple txt dosyamızı sort edilmiş varsayıyorum.

    FILE *fp;

    printf("Aranacak dosyanın adını giriniz:");
    scanf("%s",fileName);

    fp = fopen(fileName,"r");//dosyayı açıyorum

    if(fp==NULL){//Dosyayı açarken hata oluştuysa sebebiyle birlikte print ediyorum
        perror("Dosyayı Açarken Hata Oluştu!");
        return 0;
    }

    LINE_NUM=get_line_num(fp);//txt dosyasındaki satır sayısını alıyorum

    fp = fopen(fileName,"r");//dosyada kaldığım satırı en sondan en başa çekiyorum

    printf("Aranacak kelimeyi giriniz:");

    scanf("%s",KEY);

    char arr[LINE_NUM][20];//arrayi önceden bulduğum uzunluğa göre oluşturuyorum.

    txt_file_to_arr(fp,arr);//txt dosyasının içeriğini arraye çeviriyorum.

    int index=binary_search(arr,0,LINE_NUM-1);//binary search gerçekleştiriyorum sonucu index isimli değişkende tutuyorum

    if(index!=-1){
        printf("Bulunan Satır: %d\n Kelime: %s",index+1,KEY);
    }else{
        printf("Bulunamadı!");
    }

    return 0;
}

int get_line_num(FILE *fp){
    int count=0;
    while(fgets(MAX_LINE,20,fp)){//satır sayısını almak için her satır atladığında sayacı arttırıyorum
        count++;
    }
    return count;
}

void txt_file_to_arr(FILE *fp,char arr[][20]){//txt dosyasını arraye çeviren fonksiyon
    for (int i = 0; i < LINE_NUM; ++i) {
        fgets(MAX_LINE,20,fp);
        strcpy(arr[i],MAX_LINE);//MAX_LINE dediğim satırın içindekini arr[i]'nin içine kopyalıyorum.
    }
}
int binary_search(char arr[][20],int l,int r){//bildiğimiz binary search
    while (l<=r){
        int m=(r+l)/2;
        int res=cmp(arr[m],KEY);//karşılaştırma fonksiyonumun değerini res değerinde tutuyorum
        if(res){
            return m;
        }else if(strcmp(arr[m],KEY)>0){
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return -1;
}
bool cmp(char str1[],char str2[]){
    for (int i = 0; i < strlen(str1) ; ++i) {//str2'nin uzunluğuna göre alıyorum sebebi ise kısa olan kelime Josh gibi Joshua ile karşılaştığında Joshua'yı Josh'a eşit görmesini engelliyorum
        if (str1[i]==str2[i] || (str1[i]<32 && str2[i]<32)){//32den küçük değer vermemin sebebi bazen boş arraylerin içini ascii değeri 32den küçük rastgele değerlerle dolduruyor(gözlemlerimde öyleydi)
            continue;
        }else{
            return false;//eşit değer görmediğinde çıkıyor
        }
    }
    return true;
}

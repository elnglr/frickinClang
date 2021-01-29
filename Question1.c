#include <stdio.h>

void swap(int *xp, int *yp); //bubble sort algoritmasi icin gereken fonksiyon
void bubbleSort(int arr[], int n); //sayilari kucukten buyuluge siralayan fonksiyon.
void printArray(int arr[], int size);// dizinin boyutunu alan ve dizinin elemanlarini yazdiran fonksiyon.
void findMaxMin(int arr[], int size, int *num_max, int *num_min);//bu fonksiyonda max ve min degiskenleri pointer tipindeler cunku fonksiyondan veri almak istiyoruz.
//return ile tek bir veri donderebildigimiz icin void tip fonksiyon kullandik.

int main()
{
	int num_max = 0;
	int num_min = 0;

    //bu degerler min ve max degerlerini dizi icinden topluyor.
    int arr_result_0[4] = { 0 }; //terminal node'dan gelen degerlerle olusturulan maximizer arrayi, yani 9, 10, 4 ve 6 degerlerini tasiyor.
	int arr_result_1[2] = { 0 };//5 ve 4 degerlerini tasiyor.

	int arr_0[] = { 0, 5, 6	};//ilk dizi
    int n = 0; //arraylerin dinamik boyutu icin kullandigimiz yegane degisken.
	n = sizeof(arr_0) / sizeof(arr_0[0]); //n=12/4 ten 3 olur
	//sizeof ile dizilerin boyutunu byte cinsinden aliyoruz.
	//dizinin ilk elemani 4 bytelik bir int oldugundan sizeof ile bu dizi toplam kac byte onu buluruz.
	printArray(arr_0, n);
	findMaxMin(arr_0, n, &num_max, &num_min);//fonksiyonu cagirirken pointer degil adress vermemiz gerek, bu yuzden & kullandik.
	printf("en buyuk deger: %d\n", num_max); //en buyuk sayiyi ekrana yazdir
	arr_result_0[0] = num_max;//su an burada sadece 6 var simdilik

	int arr_1[] = { 3, 2, 4 };//ikinci dizi
	n = sizeof(arr_1) / sizeof(arr_1[1]);//yukaridaykiyle ayni olay
	printArray(arr_1, n);//bu fonksiyonu cagirarak 3 2 4 ekrana yazdirilir.
	findMaxMin(arr_1, n, &num_max, &num_min);// en buyuk elemani bulma fonk
	printf("en buyuk deger: %d\n", num_max);//ekrana en buyugu yazdir
	arr_result_0[1] = num_max;//sonuc arrayinin 2. elemani da 4 oldu.

	int arr_2[] = { 8, 10, 2 };//ucuncu dizi
	n = sizeof(arr_2) / sizeof(arr_2[0]);//array 2nin kac tane degisken tasidigi bulundu
	printArray(arr_2, n);// array 2nin elemanlari ekrana yazdiriliyor
	findMaxMin(arr_2, n, &num_max, &num_min);//en buyuk degeri bulan fonk cagiriliyor.
	printf("en buyuk deger: %d\n", num_max); // en buyuk deger ekrana yazdir
	arr_result_0[2] = num_max; // sonuc arrayinin 3.elemani da 10 oluyor

	int arr_3[] = { 9, 2 }; //dorduncu dizi
	n = sizeof(arr_3) / sizeof(arr_3[0]);// 4. arrayin boyutu 2 olarak belirlendi
	printArray(arr_3, n); //9 ve 2 ekrana yazdirildi
	findMaxMin(arr_3, n, &num_max, &num_min); // en buyuk degeri bulan fonksiyonu cagir
	printf("en buyuk deger: %d\n", num_max); //ustteki fonksiyonda bulunan deger ekrana yazdiriliyor
	arr_result_0[3] = num_max; //9, arr_result'in son elemani olarak ataniyor


	n = sizeof(arr_result_0) / sizeof(arr_result_0[0]);// burada arr_result_0 4 elemanli olarak bulunur
	printArray(arr_result_0, n);//9 10 4 6 ekrana yazdirildi
	findMaxMin(arr_result_0, n, &num_max, &num_min); //bu sefer downward triangle oldugu icin min degeri buluyor fonksiyon
	printf("en kucuk deger: %d\n", num_min);//bu sefer ekrana 4 yazdiriliyor
	arr_result_1[0] = num_min;//yeni bir result arrayi olusturularak ilk eleman 4 olarak belirleniyor


	//simdiki islemlerde ise solda kalan ve min degeri yani 5i bulduran fonksiyon yukardakilerle ayni mantikta calisiyor.
	int arr_4[] = { 8, 6, 7, 5 };
	n = sizeof(arr_4) / sizeof(arr_4[0]);
	printArray(arr_4, n);
	findMaxMin(arr_4, n, &num_max, &num_min);
	printf("en kucuk deger: %d\n", num_min);
	arr_result_1[1] = num_min;//yeni result arrayinin ikinci elemani da 5 oldu.

	n = sizeof(arr_result_1) / sizeof(arr_result_1[0]);//arr result 1 in boyutunu aliyor
	printArray(arr_result_1, n);//ekrana 5 ve 4 yazdir
	findMaxMin(arr_result_1, n, &num_max, &num_min);//max valueyi almak icin fonk cagir
	printf("buyuk olan deger: %d\n", num_max);//ekrana 5 yazdir

	return 0;
}

void swap(int *xp, int *yp)//xp 1., yp ise 2. eleman. sayilarin yerini degistirip siralamak icin bize bubble sort fonksiyonunda lazim olan fonksiyon.
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(int arr[], int n)//her bir dizideki elemanlari kucukten buyuge siralamak icin.
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)//burada i=0 iken j en fazla n-1. array elemanina kadar gidebilir
		{
			if (arr[j] > arr[j + 1])//eger eger ardisik dizi elemanlarindan soldaki sagdakinden buyukse yer degistiriyor.
				swap(&arr[j], &arr[j + 1]);//yer degistirme islemi burada olur. en buyuk elemani en sona kadar goturmus oluruz.
		}

	}
}

void printArray(int arr[], int size)//dizinin icinde dolasip elemanlari ekrana yazdiran fonk
{
	int i;
	for (i = 0; i < size; i++)//index dizi boyutundan buyuk olana kadar devam et
		printf("%d ", arr[i]);//i. elemani yazdir

	printf("\n");
}

void findMaxMin(int arr[], int size, int * num_max, int * num_min)//
{
	bubbleSort(arr, size);//bubble sort fonksiyonunu cagirarak max ya da min sayiyi buluyoruz dizideki
	*num_min = arr[0];//pointer kullandik cunku mainden gelen bir degerin icerigini degistirip tekrardan oraya gonderiyoruz
	*num_max = arr[size - 1];//en buyuk yani sonuncu elemani num_max degerine atayip geri yolladik.
}

//kaynaklar:1-https://www.javatpoint.com/mini-max-algorithm-in-ai
//2-https://tsafaelmali.medium.com/bubble-sort-algoritması-nedir-9811bd921b8d
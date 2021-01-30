
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW (10)
#define COL (10)
#define MAKE_POS(row, col) (row * 10 + col)//bu makro verilen row ve col'u alip tek bir sayi haline donusturuyor.ornegin 4. satir 4. sutun icin 4*10+4= 44 yaziyor outputta.
#define GET_ROW(pos) (pos / ROW)//birler basamaginda sutundaki yerini, onlar basamaginda da satirdaki yerini sakliyorum.Cunku plane pozisyonu normal bir int olarak tutuldu
#define GET_COL(pos) (pos % COL)//get_row ve get_col fonskiyon makrosu icine deger aliyor ve o degeri gonderiyorlar. aslinda getPlaneCoordinates fonksiyonu ile ayni islevde.
//burada asil amac plane pozisyonunu normal bir integer olarak tutmak,
//yani onlar basamagi satir no, birler basamagi sutun no oluyor.
typedef enum Direction
{
    DIR_NONE = 0,
    DIR_SOUTH = 1,
    DIR_SOUTH_WEST = 2,
    DIR_SOUTH_EAST = 3,
    DIR_WEST = 4,
    DIR_NORTH = 5,
    DIR_NORTH_WEST = 6,
    DIR_NORTH_EAST = 7,
    DIR_EAST = 8
} Direction;
//enumeration metodu ile her yone bir int atadim.
//const charlar da outputta yeni pozisyonu yazdirmak icin gerekli.
const char* DIRECTION_NAMES[] = {
        "NO CHANGE",
        "DIR_SOUTH",
        "DIR_SOUTH_WEST",
        "DIR_SOUTH_EAST",
        "DIR_WEST",
        "DIR_NORTH",
        "DIR_NORTH_WEST",
        "DIR_NORTH_EAST",
        "DIR_EAST",
};
void printMatrix(int* matrix);//matrisleri ekrana yazdiran fonk
void getPlaneCoordinates(int pos, int* row, int* col); //yukaridaki GET_ROW ve GET_COL makrolariyla ayni islevdeki fonskiyon. olur da hata yaparsam diye back-up olarak ekledim. Struct dondurmeyi basaramadim.
Direction getPlaneDirection(const int* planePos, int t);//ucagin pozisyonlarini ve o anki zamani alip su anki ve bir onceki zamandaki konumdan ucagin yonunu hesaplayan fonksiyon.
int predictNewPosition(Direction dir, const int* planePositions, int currentTime);

int main()
{
    srand(time(NULL));// random generator
    int planePositions[ROW] = { MAKE_POS(1, 2), MAKE_POS(2, 3) };//burasi PPI screen degerlerine gore manuel olarak da degisebilir.
    int PPIScreen[ROW][COL] = { 0 };//vektor degiskenimiz yani radar ekrani. matrise 0 lari atadik, ilk t(0,1) haric

    // print initial state
    PPIScreen[1][2] = 1;//burayi kendim belirledim
    PPIScreen[2][3] = 1;//burayi da.
    printf("Initial state of the plane\n");
    printMatrix(&PPIScreen[0][0]);
    printf("\n\n");

    for (int t = 2; t < 8; t++)//buradaki for dongusuyle ucagin konumlari 45 derecelik acilar ile rastgele belirlendi.
    {
        Direction planeDir = getPlaneDirection(planePositions, t - 1);
        int newPos = predictNewPosition(planeDir, planePositions, t - 1);//45 derece soluna ya da sagina gidebilir, veya duz ayni yonde
        //devam edebilecek sekilde ayarli.
        planePositions[t] = newPos;
        PPIScreen[GET_ROW(newPos)][GET_COL(newPos)] = 1;
        printf("Time(%d) -> previous direction: %s, New position: %d\n", t, DIRECTION_NAMES[planeDir], newPos);
        printMatrix(&PPIScreen[0][0]);
        printf("\n\n");
    }

    return 0;
}

int predictNewPosition(Direction dir, const int* planePositions, int prevTime)
{
    int planeX, planeY; //x ve y koordinatlari
    getPlaneCoordinates(planePositions[prevTime], &planeY, &planeX);// ucagin konumunu alan fonksiyon

    // saat yönünün tersine göre gidecegi yeri tahmin et
    int r = rand() % 3;  //vektor 45 derecelik manevralar yapabilir, 3 secimi var.
    if(dir<=DIR_EAST && dir>=DIR_NONE) { //aslinda burada >=0 ve <=8 de yapabilirdim ama her statein degeri valid. state’ler precise oldugundan DIR_MAX gibi bir boundary ayarlamaya gerek kalmadi.

        if (r == 0) {
            planeY++;
        } else if (r == 1) {
            planeX++;
            planeY++;
        } else {
            planeX++;
        }
    }
    return MAKE_POS(planeY, planeX); //
}

void getPlaneCoordinates(int pos, int* row, int* col)//bu fonksiyon sadece yardimci bir fonksiyon. bu fonksiyonda
//position degeri degismiyor. sadece bir data formatindan baska bir formata cevirmis oluyorum.
{
    *row = pos / ROW;
    *col = pos % COL;
}

Direction getPlaneDirection(const int* planePos, int t)//ucagin pozisyonlarini ve o anki zamani alip,su anki ve bir onceki
//zamandaki konumdan ucagin yonunu hesaplayan fonksiyon
{
    Direction direction = DIR_NONE; //enumdan ilk konumu none al

    int planeX1, planeY1;//ucagin ilk konum vektorleri
    getPlaneCoordinates(planePos[t - 1], &planeY1, &planeX1);//t-1 cunku bir sonraki konumu predict edebilmek icin bir onceki konuma ihtiyacimiz var.

    int planeX2, planeY2; //ucagin son konum vektorleri
    getPlaneCoordinates(planePos[t], &planeY2, &planeX2);
    //koordinat sistemindeki gibi, noktalar arasi fark.
    int xDir = planeX2 - planeX1;
    int yDir = planeY2 - planeY1;

    if (xDir == -1)
    {
        if (yDir == 1)//normalde koordinat sisteminde 2. bolge oluyor burasi fakat 2 boyutlu dizide row asagi dogru artiyor.ucak asagi dogru giderken t1’de row degeri 5 olacak t0 da row degeri 4 olacak and so forth.
        {
            // güney bati
            direction = DIR_SOUTH_WEST;
        }
        else if (yDir == -1)//yukaridaki aciklamanin aynisi, y ekseninde tersi oldugundan yon guneybati yerine kuzeybati oluyor.
        {
            // kuzey bati
            direction = DIR_NORTH_WEST;
        }
        else
        {
            // bati
            direction = DIR_WEST;//(-1,0) noktasi bati vektoru.
        }
    }
    else if (xDir == 1)//kuzey dogu yerine guney dogu, ucagin ilk konumundan dolayi
    {
        if (yDir == 1)
        {
            // güney dogu
            direction = DIR_SOUTH_EAST;
        }
        else if (yDir == -1)
        {
            // kuzey dogu
            direction = DIR_NORTH_EAST;
        }
        else
        {
            // dogu
            direction = DIR_EAST;
        }
    }
    else
    {
        if (yDir == 1)
        {
            // güney
            direction = DIR_SOUTH;
        }
        else if (yDir == -1)
        {
            // kuzey
            direction = DIR_NORTH;
        }
        else
        {
            // oldugu yerde
            direction = DIR_NONE;
        }
    }

    return direction;//if else statementlarina gore yonu bul ve fonskiyonda dondur.
}

void printMatrix(int* matrix)//matrisleri yazdirmak icin gerekli fonksiyon
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("%d ", matrix[ROW * i + j]);
        }
        printf("\n");
    }
}

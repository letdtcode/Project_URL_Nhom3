#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<string>
#include<time.h>
#pragma warning (disable: 4996)

int M;
int step;
using namespace std;

struct URL {
    string data = "";
    int* idlk = new int[M];
    int count;
};

struct HastTable {
    int key;
    URL* table = new URL[M];
};



int n;
int** matrix;
int* move_id;
int m;
int* index;
URL url;
HastTable* hast = nullptr;

void menu();
int selection(int start, int end, int y);
void move_url(int id);
void check2url();
int checklk(int url1, int url2, int* way);
void find_way(int* way, int count);
void createMatrix();
void search_url();
void insertChild(string url1, string url2);
void insertParent(string S);
int string_tokey(string S);
int selection(int start, int end, int location);
void gotoxy(int x, int y);
void updateURL(int id);
void deleteURL(int id);
void tracing(int key);


void SetTeColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0; wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void start() // create value.
{

    step = 0;
    SetTeColor(15);
    n = 1;
    m = 0;

    hast = new HastTable;
    index = new int[M];
    move_id = new int[M];
    for (int i = 0; i < M; i++)
    {
        index[i] = 0;
        for (int j = 0; j < M; j++)
            hast->table[i].idlk[j] = 0;
        hast->table[i].count = 1;
        move_id[i] = 0;
    }

}

void end() //delete value
{
    delete[] move_id;
    move_id = nullptr;
    delete[] index;
    index = nullptr;


    delete[] hast->table->idlk;
    hast->table->idlk = nullptr;

}

void insert()
{
    insertParent("https://uex.hctmute.edu.vn/my/");

    insertChild("https://uex.hctmute.edu.vn/my/", "https://utex.hcmute.edu.vn/course/view.php?id=5004"); //  CTDL
    insertChild("https://uex.hctmute.edu.vn/my/", "https://utex.hcmute.edu.vn/course/view.php?id=5256"); //nhap mon xa hoi hoc
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=5004", "https://utex.hcmute.edu.vn/mod/lesson/view.php?id=151626"); // video week 1 CTDL
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=5004", "https://utex.hcmute.edu.vn/mod/lesson/view.php?id=160581"); //video week 2  CTDL
    insertChild("https://uex.hctmute.edu.vn/my/", "https://utex.hcmute.edu.vn/course/view.php?id=8826"); //lap trinh huong doi tuong
    insertChild("https://uex.hctmute.edu.vn/my/", "https://utex.hcmute.edu.vn/course/view.php?id=11328"); //phap luat dai cuong
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=5004", "https://utex.hcmute.edu.vn/mod/lesson/view.php?id=180507"); // video week 3  CTDL
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=11328", "https://utex.hcmute.edu.vn/mod/page/view.php?id=74202"); //video 1 PLDC
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=11328", "https://utex.hcmute.edu.vn/mod/page/view.php?id=74217"); //video 2 PLDCC
    insertChild("https://utex.hcmute.edu.vn/course/view.php?id=11328", "https://www.youtube.com/watch?v=-HhoQMzLSqg"); //video 3 PLDC
    insertChild("https://utex.hcmute.edu.vn/mod/lesson/view.php?id=151626", "https://drive.google.com/file/d/15bVvDB09E89Js61FUdKdwvUftFhcTZKp/view");  //video CTDL
}

int findStepMin(int STEP[]) {
    int min = STEP[0], indexMin = 0;
    for (int i = 1; i < 20; i++) {
        if (min >= STEP[i]) {
            min = STEP[i];
            indexMin = i;
        }
    }
    return indexMin;
}

int main()
{
    int i = 0;
    int TableSize[] = { 101, 97, 89, 83, 79, 73, 71, 67, 61, 59, 53, 47, 43, 41, 37, 31, 29, 23, 19, 17 };
    int STEP[100];
    while (i < 20) {
        M = TableSize[i];
        start();
        insert();
        STEP[i] = step;
        end();
        i++;
    }

    for (int i = 0; i < 20; i++) {
        cout << "size: " << TableSize[i] << "\t" << "Step: " << STEP[i] << endl;
    }

    string option;
    do {
        cout << "nhap 1 de tiep tuc: ";
        cin >> option;

    } while (option != "1");

    int indexMin = findStepMin(STEP);
    M = TableSize[indexMin];

    start();
    insert();
    menu();
}

int string_tokey(string S)
{
    int key = 0;
    for (int i = 1; i < S.length(); i++)
        key += S[i] * i;
    key = int(key) % (M);
    step++;
    int i = 1;
    while (hast->table[index[key]].data != S && index[key] != 0)
    {
        key = (key + i) % M;
        i++;
        step++;
    }
    step += 2;
    return key;
}
void insertParent(string S)
{
    int key = string_tokey(S);
    index[key] = n;
    hast->table[n].data = S;
    n++;
}
void insertChild(string url1, string url2)
{
    int key1 = string_tokey(url1);
    if (index[key1] == 0)
    {
        hast->table[n].data = url1;
        index[key1] = n;
        n++;
    }
    int key2 = string_tokey(url2);

    if (index[key2] == 0)
    {
        hast->table[n].data = url2;
        index[key2] = n;
        n++;
    }

    int count = hast->table[index[key1]].count;
    hast->table[index[key1]].idlk[count] = index[key2];
    hast->table[index[key1]].count++;
}

void search_url()
{
    string s;
    int key, select = -1;

    system("CLS");
    cout << "------Search URL------- \n\n";
    cout << "Enter URL: ";
    cin >> s;
    key = string_tokey(s);
    if (index[key] != 0)
    {
        cout << "Found URL" << endl << endl
            << "    Move URL :" << endl
            << "    Enter URL:" << endl
            << "    Menu :" << endl
            << "    Exit" << endl;

        while (true)
        {
            select = selection(1, 4, 5);
            if (select == 1)
                move_url(index[key]);
            else if (select == 2)
                system(std::string("start " + hast->table[index[key]].data).c_str());
            else if (select == 3)
                menu();
            else
                exit(0);
        }

    }
    else
    {
        cout << " Not found URL" << endl << endl
            << "    Search web :" << endl
            << "    Menu :" << endl
            << "    Exit" << endl;
        while (true)
        {
            select = selection(1, 3, 5);
            if (select == 1)
                system(std::string("start " + hast->table[index[key]].data).c_str());
            else if (select == 2)
                menu();
            else
                exit(0);
        }
    }
}
void createMatrix()
{
    matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < hast->table[i].count; j++)
        {
            matrix[i][hast->table[i].idlk[j]] = 1;
            matrix[hast->table[i].idlk[j]][i] = 1;
        }
    }
}
void find_way(int* way, int count)
{
    for (int i = 1; i < count; i++)
        cout << "\n\n >>>>>>>>> \n"
        << endl << hast->table[way[i]].data;
}
int checklk(int url1, int url2, int* way)
{
    int* check;
    check = new int[n];
    for (int i = 0; i < n; i++) // Cháº¡y n láº§n (vá»›i n lÃ  sá»‘ cÃ¡c pháº§n tá»­ trong cáº¥u trÃºc)
        check[i] = 0;
    int b = 1;
    way[b] = url1;
    check[way[b]] = 1;
    while (b != 0)   // Duyá»‡t tá»«ng URL theo CHIá»€U SÃ‚U (tá»‘i Ä‘a n láº§n)
    {
        int kt = 0;
        for (int i = 1; i < n; i++)         // Duyá»‡t cÃ¡c URL liÃªn káº¿t vá»›i URL hiá»‡n táº¡i
            if (matrix[way[b]][i] > 0)      // Má»—i URL Ä‘Æ°á»£c duyá»‡t 1 láº§n
                if (check[i] == 0)          // Tá»‘i Ä‘a n láº§n
                {                           // Tá»‘t nháº¥t 1 láº§n
                    way[++b] = i;           //
                    check[i] = 1;           //
                    if (i == url2)          //
                        return b + 1;       //
                    kt = 1;                 //
                    break;                  //
                }                           //
        if (kt == 0)
        {
            way[b] = 0;
            b--;
        }
    }
    return 0;
}
void check2url()
{
    int id1, id2, count, select, y = 1;
    int* way = new int[n];
    createMatrix();

    system("CLS");
    cout << "------Check URL------- \n\n";

    for (int i = 1; i < n; i++)
    {
        cout << "   " << hast->table[i].data << endl;
        y++;
    }

    cout << "Select 2 URLs to check";
    id1 = selection(1, n - 1, 2);
    SetTeColor(4);
    cout << "  " << hast->table[id1].data;
    SetTeColor(15);
    id2 = selection(1, n - 1, 2);
    SetTeColor(4);
    cout << "  " << hast->table[id2].data;
    SetTeColor(15);

    count = checklk(id1, id2, way);
    if (count > 0)
    {
        gotoxy(0, y);
        cout << "\n\n2 Linked URLs" << endl << endl
            << "    Find the way " << endl
            << "    Menu" << endl
            << "    Exit " << endl;
        y += 4;

        while (1 != 0)
        {
            select = selection(1, 3, y);
            if (select == 1)
            {
                gotoxy(0, y + 4);
                find_way(way, count);
            }
            else if (select == 2)
                menu();
            else
                exit(0);

        }

    }
    else
    {
        gotoxy(0, y);
        cout << "\n\n2 Not Link URLs" << endl << endl;
        cout << "   Menu: " << endl;
        cout << "   Exit: " << endl;
        y += 4;
        while (true)
        {
            select = selection(1, 2, y);
            while (select < 1 && select>2)
            {
                cout << "Choose select: ";
                cin >> select;
            }
            if (select == 1)
                menu();
            else
                exit(0);
        }

    }
}
void tracing(int key) { // Duyệt tuần tự theo chiều sâu.
    if (index[key] != 0) {
        int dem = 1;
        while (dem < hast->table[index[key]].count)
        {
            int key1 = string_tokey(hast->table[hast->table[index[key]].idlk[dem]].data);
            tracing(key1);
            dem++;
        }
        hast->table[index[key]].count = 1;
        index[key] = 0;
    }
    else
        return;
}
void deleteURL(int id) {
    int key = string_tokey(hast->table[id].data);

    int idele = 0;

    for (int i = 1; i < hast->table[move_id[m - 1]].count; i++)
        if (hast->table[move_id[m - 1]].idlk[i] == index[key])
        {
            idele = i;
            break;
        }
    tracing(key);

    if (move_id[m - 1] != 0)
    {
        for (int i = idele; i < hast->table[move_id[m - 1]].count - 1; i++)
        {
            hast->table[move_id[m - 1]].idlk[i] = hast->table[move_id[m - 1]].idlk[i + 1];
        }
        hast->table[move_id[m - 1]].count--;
    }
    move_id[m] = 0;
    m--;
    move_url(move_id[m]);
}
void updateURL(int id)
{
    system("CLS");
    cout << "Enter new URL: ";
    string S;
    cin >> S;
    hast->table[id].data = S;
    int key = string_tokey(S);

    index[key] = id;
    cout << "   Access to URL" << endl;
    move_url(id);
}
void move_url(int id)
{
    int select = 0, y = 0;
    if (m <= 0 && id == 0)
    {
        m = 0;
        menu();
    }
    if (id != move_id[m])
        move_id[++m] = id;
    system("CLS");
    for (int i = 1; i < m; i++)
    {
        cout << "------" << hast->table[move_id[i]].data << endl
            << "VVVVVVVVV" << endl;
        y += 2;
    }
    if (index[string_tokey(hast->table[id].data)] != 0)
    {
        cout << "------" << hast->table[id].data << "\n\n";
        y += 2;
    }
    cout << "Linked URLs: " << endl << endl;
    y += 2;
    int i = 1;
    if (hast->table[id].count == 1)
    {
        cout << "\n   Not found URL\n\n";
        y += 3;
    }

    else
    {
        for (i = 1; i < hast->table[id].count; i++)
        {
            int idshow = hast->table[id].idlk[i];
            cout << "   " << i << "   " << hast->table[idshow].data << endl;
        }
    }
    cout << "   Access to URL" << endl
        << "    Insert URL" << endl
        << "    Back" << endl
        << "    Update url" << endl
        << "    Delete URL" << endl
        << "    Menu" << endl
        << "    Exit" << endl;

    while (true)
    {
        select = selection(1, hast->table[id].count + 6, y);
        if (select >= 1 && select < i)
        {
            move_url(hast->table[id].idlk[select]);
        }
        else if (select == i)
        {
            system(std::string("start " + hast->table[id].data).c_str());
            system("pause>>null");
        }

        else if (select == i + 1)
        {
            gotoxy(0, hast->table[id].count + y + 5);
            cout << "Enter URL:";
            string S;
            cin >> S;
            insertChild(hast->table[id].data, S);
            move_url(id);
        }
        else if (select == i + 2)
        {
            move_id[m] = 0;
            m--;
            move_url(move_id[m]);
        }
        else if (select == i + 3)
            updateURL(move_id[m]);
        else if (select == i + 4)
            deleteURL(move_id[m]);
        else if (select == i + 5)
            menu();
        else
            exit(0);
    }
}
void gotoxy(int x, int y)
{
    static HANDLE  h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x,y };
    SetConsoleCursorPosition(h, c);
}
int selection(int start, int end, int y)
{
    int select = 1;
    int y0 = -1;
    gotoxy(0, select + y - 1);
    cout << char(16);

    while (1)
    {
        char key;
        if (kbhit())
        {
            key = getch();

            if (key == 13)
            {
                gotoxy(0, y0);
                cout << char(32);
                break;
            }
            if (key == 80 || key == 77)
                select++;

            if (key == 72 || key == 75)
                select--;

            if (select > end)
                select = start;
            else if (select < start)
                select = end;

            gotoxy(0, y0);
            cout << char(32);
            gotoxy(0, select + y - 1);
            cout << char(16);


            y0 = select + y - 1;
        }
    }
    return select;
}
void menu()
{
    for (int i = 0; i < m; i++)
        move_id[i] = 0;
    m = 0;

    int imenu = 1;
    while (true)
    {
        int x = 2, y = 0;
        system("CLS");
        gotoxy(x, y++);
        cout << "------MENU------- \n\n";
        gotoxy(x, y++);
        cout << " Exit\n";
        gotoxy(x, y++);
        cout << " Move URL \n";
        gotoxy(x, y++);
        cout << " Search URL\n";
        gotoxy(x, y++);
        cout << " Check URL\n";

        imenu = selection(1, 4, 1);

        if (imenu == 1)
        {
            system("CLS");
            exit(0);
        }
        if (imenu == 2)
        {
            move_url(1);
        }
        if (imenu == 3)
        {
            search_url();
        }
        if (imenu == 4)
            check2url();
    }
}

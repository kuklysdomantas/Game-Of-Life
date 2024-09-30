#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <omp.h>

using namespace std;

/*
Šiame projekte naudojamos funkcijos:
printGrid -> atspausdina tinklelį (grid);
determineState -> Prilygina pradinį tinklelį su laikinu tinkeliu;
clearScreen -> atnaujina ekraną;
Check_Grid -> patikrina, ar visi gyvi langeliai sudaro stabilų raštą, ar nesusiformuoja ribinis/begalinis ciklas;
Print_Coordinates -> Išrašo į ekraną gyvų langelių koordinates.
*/
const int gridSize = 25;

void printGrid(int gridOne[gridSize+1][gridSize+1]);
void determineState(int gridOne[gridSize+1][gridSize+1], int iterations, int To_Print[gridSize+1][gridSize+1]);
void clearScreen(void);
void Check_Grid(int gridOne[gridSize+1][gridSize+1], int saved_grid[gridSize+1][gridSize+1], int iterations,
                int To_Print[gridSize+1][gridSize+1]);
void Print_Coordinates(int gridOne[gridSize+1][gridSize+1]);

int main(int argc, char** argv)
{
    clearScreen();


    int gridOne[gridSize+1][gridSize+1] = {0};                      // Pagrindinis tinklelis
    int x,y, iterations = 1;                                        // x,y - koordinatės. iterations - iteracijų skaičius
    int Saved_Grid_Period_Of_2[gridSize+1][gridSize+1] = {0};       // Saugo tinklelį, kurio periodas = 2. Prevencija nuo "Blinker", "Toad", "Beacon" modelių
    int Saved_Grid_Period_Of_3[gridSize+1][gridSize+1] = {0};       // Saugo tinklelį, kurio periodas = 3. Prevencija nuo "Pulsar" osciliatoriaus
    int Saved_Grid_Period_Of_4[gridSize+1][gridSize+1] = {0};       // Saugo tinklelį, kurio periodas = 4. Prevencija nuo "Spaceship" tipo modelių
    int Saved_Grid_Period_Of_5[gridSize+1][gridSize+1] = {0};       // Saugo tinklelį, kurio periodas = 5. Prevencija nuo "Penta-decathlon" osciliatoriaus
    int To_Print[gridSize+1][gridSize+1] = {0};                     // Išsaugo tinklelį, kurio koordinates išsspausdina.
    int threads;                                                    // Gijų skaičius
    double start_time;                                              //
    double end_time;                                                // Parametrai skaičiuoti laiką
    double time_spent = 0;                                          //
    string nc;
    string start;
    string filename;


    cout << "                         Conway`s Game Of Life " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Taisykles" << endl;
    cout << "Kiekviename laiko zingsnyje vyksta sie perejimai:" << endl;
    cout << "1. Bet kuri gyva lastele, turinti maziau nei dvi gyvas kaimynines lasteles, mirsta." << endl;
    cout << "2. Bet kuri gyva lastele, turinti du ar tris gyvus kaimynus, gyvena kitoje kartoje." << endl;
    cout << "3. Bet kuri gyva lastele, turinti daugiau nei tris gyvus kaimynus, mirsta." << endl;
    cout << "4. Bet kuri mirusi lastele, turinti lygiai tris gyvus kaimynus, tampa gyva lastele. " << endl;
    cout << endl;
    cout << "O - gyva lastele" << endl;
    cout << ". - mirusi lastele" << endl;
    cout << endl;
    cout << "Iveskite procesu skaiciu: " << endl;
    cin >> threads;
    omp_set_num_threads(threads);


    cout << "Iveskite lasteliu skaiciu arba 'r', jeigu norite nuskaityti is failo:" << endl;
    cin >> nc;
    cout << endl;


    if ( nc == "r" )                    //Sąlyga, jei norime duomenis nuskaityti iš failo.
    {
        while (true)
        {
            cout << "Iveskite failo pavadinima: "<<endl;
            cin  >> filename;

            ifstream readfile(filename);
            if ( readfile.is_open() )
            {
                string fileline,xx,yy;

                while (getline(readfile,fileline))
                {
                    stringstream ss(fileline);

                    getline(ss,xx,' ');
                    getline(ss,yy,' ');

                    x = stoi(xx);
                    y = stoi(yy);

                    gridOne[x][y] = 1;
                }
                break;
            }
            else
            {
                cout << "FAILAS NERASTAS." << endl;
            }
        }
    }

    else
    {
        for(int i=0; i<stoi(nc); i++)
        {
            cout << "Iveskite lasteles koordinates " << i+1 << " : ";
            cin >> x >> y;
            gridOne[x][y] = 1;
            printGrid(gridOne);
        }
    }

    cout << "Norite pradeti zaidima? (y/n)" << endl;
    printGrid(gridOne);
    cin >> start;
    if( start == "y" || start == "Y" )
    {
        while (true)
        {

            if(iterations % 2 == 0 && iterations % 4 != 0)      //Saugome tinklelį kas 2 iteracijas
            {
                #pragma omp parallel for collapse(2)
                for(int a = 1; a < gridSize; a++)
                {
                    for(int b = 1; b < gridSize; b++)
                    {
                        #pragma omp critical
                        Saved_Grid_Period_Of_2[a][b] = gridOne[a][b];
                    }
                }
            }

            else if(iterations % 3 == 0)                        //Saugome tinklelį kas 3 iteracijas
            {
                #pragma omp parallel for collapse(2)
                for(int a = 1; a < gridSize; a++)
                {
                    for(int b = 1; b < gridSize; b++)
                    {
                        #pragma omp critical
                        Saved_Grid_Period_Of_3[a][b] = gridOne[a][b];
                    }
                }
            }
            else if(iterations % 4 == 0)                        //Saugome tinklelį kas 4 iteracijas
            {
                #pragma omp parallel for collapse(2)
                for(int a = 1; a < gridSize; a++)
                {
                    for(int b = 1; b < gridSize; b++)
                    {
                        #pragma omp critical
                        Saved_Grid_Period_Of_4[a][b] = gridOne[a][b];
                    }
                }
            }
            else if(iterations % 5 == 0)                        //Saugome tinklelį kas 5 iteracijas
            {
                #pragma omp parallel for collapse(2)
                for(int a = 1; a < gridSize; a++)
                {
                    for(int b = 1; b < gridSize; b++)
                    {
                        #pragma omp critical
                        Saved_Grid_Period_Of_5[a][b] = gridOne[a][b];
                    }
                }
            }

            printGrid(gridOne);
            cout << endl;
            #pragma omp parallel for collapse(2)
            for(int a = 1; a < gridSize; a++)
            {
                for(int b = 1; b < gridSize; b++)
                {
                    #pragma omp critical
                    To_Print[a][b] = gridOne[a][b];
                }
            }

            start_time = omp_get_wtime();
            determineState(gridOne, iterations, To_Print);
            Check_Grid(gridOne, Saved_Grid_Period_Of_2, iterations, To_Print);
            Check_Grid(gridOne, Saved_Grid_Period_Of_3, iterations, To_Print);
            Check_Grid(gridOne, Saved_Grid_Period_Of_4, iterations, To_Print);
            Check_Grid(gridOne, Saved_Grid_Period_Of_5, iterations, To_Print);
            end_time = omp_get_wtime();

            usleep(0);

            time_spent += end_time - start_time;
            ++iterations;

            clearScreen();
            printf("Skaiciavimai uztruko: %f s\n", time_spent);

        }
    }
    else
    {

        clearScreen();
        return 0;
    }
}

void clearScreen(void)
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (hStdOut == INVALID_HANDLE_VALUE) return;

    GetConsoleScreenBufferInfo( hStdOut, &csbi );
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count);

    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

    SetConsoleCursorPosition( hStdOut, homeCoords );
}

void Check_Grid(int gridOne[gridSize+1][gridSize+1], int saved_grid[gridSize+1][gridSize+1], int iterations, int To_Print[gridSize+1][gridSize+1] )
{
    //Tikriname ar visi gyvi langeliai sudaro stabilų raštą arba modeliai kartojasi cikliškai.
    #pragma omp parallel
    {
        for(int a = 0; a < gridSize; a++)
        {
            for(int b = 0; b < gridSize; b++)
            {
                #pragma omp  critical
                if(gridOne[a][b] != saved_grid[a][b]) a = gridSize;
            }
            #pragma omp single
            if(a == gridSize - 1)
            {
                cout << "GAME OVER!" << endl;
                printf("Zaidimas baigesi po %i iteraciju.\n", iterations);
                Print_Coordinates(To_Print);
                exit(0);
            }
        }
        //Tikriname ar gyvi langeliai kas kelis ejimus nesikartoja (Glider`iui kai eina iš viršaus į apačią)
        //#pragma omp parallel for collapse(2)
        for(int a = 0; a < gridSize; a++)
        {
            for(int b = 0; b < gridSize; b++)
            {
                #pragma omp  critical
                if(gridOne[a][b] != saved_grid[a-1][b-1] && gridOne[a][b] != saved_grid[a-1][b+1]) a = gridSize;
            }
            #pragma omp single
            if(a == gridSize - 1)
            {
                cout << "GAME OVER!" << endl;
                printf("Zaidimas baigesi po %i iteraciju.\n", iterations);
                Print_Coordinates(To_Print);
                exit(0);
            }
        }

        //Tikriname ar gyvi langeliai kas kelis ejimus nesikartoja (Glider`iui kai eina iš apačios į viršų)
        //#pragma omp parallel for collapse(2)
        for(int a = 0; a < gridSize; a++)
        {
            for(int b = 0; b < gridSize; b++)
            {
                #pragma omp  critical
                if(gridOne[a][b] != saved_grid[a+1][b+1] && gridOne[a][b] != saved_grid[a+1][b-1]) a = gridSize;
            }
            #pragma omp single
            if(a == gridSize - 1)
            {
                cout << "GAME OVER!" << endl;
                printf("Zaidimas baigesi po %i iteraciju.\n", iterations);
                Print_Coordinates(To_Print);
                exit(0);
            }
        }

        //Tikriname ar gyvi langeliai kas kelis ejimus nesikartoja (Visiems likusiems spaceship`ams)
        //#pragma omp parallel for collapse(2)
        for(int a = 0; a < gridSize; a++)
        {
            for(int b = 0; b < gridSize; b++)
            {
                #pragma omp  critical
                if(gridOne[a][b] != saved_grid[a][b-2] && gridOne[a][b] != saved_grid[a][b+2]) a = gridSize;
            }
            #pragma omp single
            if(a == gridSize - 1)
            {
                cout << "GAME OVER!" << endl;
                printf("Zaidimas baigesi po %i iteraciju.\n", iterations);
                Print_Coordinates(To_Print);
                exit(0);
            }
        }
    }
}


void printGrid(int gridOne[gridSize+1][gridSize+1])
{
    for(int a = 1; a < gridSize; a++)
    {
        for(int b = 1; b < gridSize; b++)
        {
            if(gridOne[a][b] == 1)
            {
                cout << " O ";
            }
            else
            {
                cout << " . ";
            }
            if(b == gridSize-1)
            {
                cout << endl;
            }
        }
    }
}

void compareGrid (int gridOne[gridSize+1][gridSize+1], int gridTwo[gridSize+1][gridSize+1])
{
    #pragma omp parallel for collapse(2)
    for(int a = 0; a < gridSize; a++)
    {
        for(int b = 0; b < gridSize; b++)
        {
            #pragma omp critical
            gridTwo[a][b] = gridOne[a][b];
        }
    }
}

void determineState(int gridOne[gridSize+1][gridSize+1], int iterations, int To_Print[gridSize+1][gridSize+1])
{
    int gridTwo[gridSize+1][gridSize+1] = {0};
    compareGrid(gridOne, gridTwo);
    #pragma omp parallel for collapse(2)
    for(int a = 1; a < gridSize; a++)
    {
        for(int b = 1; b < gridSize; b++)
        {
            int alive = 0;
            #pragma omp parallel for collapse(2) reduction(+: alive)
            for(int c = -1; c < 2; c++)
            {
                for(int d = -1; d < 2; d++)
                {
                    if(!(c == 0 && d == 0))
                    {
                        if(gridTwo[a+c][b+d] == 1)
                        {
                            ++alive;
                        }
                    }
                }
            }
            if(alive < 2)               //Taisyklė 1. Bet kuri gyva lastele, turinti maziau nei dvi gyvas kaimynines lasteles, mirsta.
            {
                gridOne[a][b] = 0;
            }
            else if(alive == 3)         //Taisyklė 2. Bet kuri mirusi lastele, turinti lygiai tris gyvus kaimynus, tampa gyva lastele.
            {
                gridOne[a][b] = 1;
            }
            else if(alive > 3)          //Taisyklė 3. Bet kuri gyva lastele, turinti daugiau nei tris gyvus kaimynus, mirsta.
            {
                gridOne[a][b] = 0;
            }
        }
    }
    Check_Grid(gridOne, gridTwo, iterations, To_Print);
}

void Print_Coordinates(int To_Print[gridSize+1][gridSize+1])
{
    cout << "Gyvu lasteliu koordinates: " << endl;
    for(int a = 1; a < gridSize; a++)
    {
        for(int b = 1; b < gridSize; b++)
        {
            if(To_Print[a][b] == 1)
            {
                cout << a << " " << b << endl;              //Spausdiname gyvų langelių koordinates
            }
        }
    }
}

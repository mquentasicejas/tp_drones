#include <iostream>
#include <conio.h>
#include <string>
#include <cstdio>
using namespace std;

struct Orden {
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = 0;
    int siguientey = 0;
};
struct ordenArchivo {
    int x = 0;
    int y = 0;
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = 0;
    int siguientey = 0;
};
int encontrarRegistro(FILE *f,int x,int y, ordenArchivo &buffer)
{
        while(fread(&buffer,sizeof(ordenArchivo),1,f))
        {
            if(buffer.x == x && buffer.y == y)
            return 1;
        }
        return 0;

}
void pedirCoordenadas(int &x, int &y)
{
    do {
    cout << "Ingrese la coordenda en x (entre 0-199): " << endl;
    cin >> x;
    } while(x<0 || x>199);
    do {
        cout << "Ingrese la coordenada en y (entre 0-199): " << endl;
        cin >>y;
    } while(y<0 || y>199);
    return;
}
void pedirAtaques(ordenArchivo &buffer)
{
    cout << "Ingrese el valor de soltarGranada1: " << endl;
    cin >> buffer.soltarGranada1;
    cout << "Ingrese el valor de soltarGranada2: " << endl;
    cin >> buffer.soltarGranada2;
    cout << "Ingrese el valor de ataqueKamikaze: " << endl;
    cin >> buffer.ataqueKamikaze;
    return;
}
void pedirSiguienteCoor(ordenArchivo &buffer)
{
    do{
    cout << "Ingrese el valor de siguientex (entre 0-199): "<< endl;
    cin >> buffer.siguientex;
    } while(buffer.siguientex < 0 || buffer.siguientex > 199);
    do {
    cout << "Ingrese el valor de siguientey (entre 0-199): " << endl;
    cin >> buffer.siguientey;
    } while(buffer.siguientey < 0 || buffer.siguientey > 199);
}
void mostrarDatos(ordenArchivo &buffer)
{
    cout << "Coordenada en x: " << buffer.x << endl;
    cout << "Coordenada en y: " << buffer.y << endl;
    cout << "El tiempo de espera es de: " << buffer.espera << endl;
    cout << "El valor del ataque soltarGranada1 es: "<< buffer.soltarGranada1 << endl;
    cout << "El valor del ataque soltarGranada2 es: "<< buffer.soltarGranada2 << endl;
    cout << "El valor del ataqueKamikaze es: "<< buffer.ataqueKamikaze << endl;
    cout << "El valor del aterrizaje es: " << buffer.aterrizaje << endl;
    cout << "El valor del despegue es: " << buffer.despegue << endl;
    cout << "El valor de siguientex es: " << buffer.siguientex << endl;
    cout << "El valor de siguientey es: " << buffer.siguientey << endl;
    return;
}
void mostrarDatosSinXeY(Orden &buffer)
{
    cout << "El tiempo de espera es de: " << buffer.espera << endl;
    cout << "El valor del ataque soltarGranada1 es: "<< buffer.soltarGranada1 << endl;
    cout << "El valor del ataque soltarGranada2 es: "<< buffer.soltarGranada2 << endl;
    cout << "El valor del ataqueKamikaze es: "<< buffer.ataqueKamikaze << endl;
    cout << "El valor del aterrizaje es: " << buffer.aterrizaje << endl;
    cout << "El valor del despegue es: " << buffer.despegue << endl;
    cout << "El valor de siguientex es: " << buffer.siguientex << endl;
    cout << "El valor de siguientey es: " << buffer.siguientey << endl;
    return;
}
void mostrarDatosEnTabla(Orden tabla[200][200], int x, int y) // esta funcion la hice con ayuda de claude.
{
    Orden buffer;
    buffer = tabla[x][y];
    cout << "El tiempo de espera es de: " << tabla[x][y].espera << endl;
    cout << "El valor del ataque soltarGranada1 es: "<< tabla[x][y].soltarGranada1 << endl;
    cout << "El valor del ataque soltarGranada2 es: "<< tabla[x][y].soltarGranada2 << endl;
    cout << "El valor del ataqueKamikaze es: "<< tabla[x][y].ataqueKamikaze << endl;
    cout << "El valor del aterrizaje es: " << tabla[x][y].aterrizaje << endl;
    cout << "El valor del despegue es: " << tabla[x][y].despegue << endl;
    cout << "El valor de siguientex es: " << tabla[x][y].siguientex << endl;
    cout << "El valor de siguientey es: " << tabla[x][y].siguientey << endl;
    return;
}
// Operacion 1 (tuve bastante ayuda de claude con esta operacion).
void cargarArchivoEnMemoria(Orden tabla[200][200])
{
    ordenArchivo buffer;
    Orden actual;
    Orden vacia;
    char ocupada[200][200] = {0};
    char ruta[200];
    FILE* f;
    int x, y;
    int despegues = 0, finales = 0, registros = 0;
    int despegueX = 0, despegueY = 0;
    int pasos, aledana;
    int valido = 1;

    cout << "Ingrese el nombre del archivo: " << endl;
    cin >> ruta;
    f = fopen(ruta,"rb");
    if(f == NULL)
    {
        cout << "No se pudo abrir el archivo. " << endl;
        return;
    }

    for(x=0;x<200;x++)
    {
        for(y=0;y<200;y++)
        {
            tabla[x][y] = vacia;
        }
    }

    while(valido == 1 && fread(&buffer,sizeof(ordenArchivo),1,f) == 1)
    {
        registros++;

        if(buffer.x < 0 || buffer.x > 199 || buffer.y < 0 || buffer.y > 199)
        {
            cout << "Coordenadas fuera de la tabla." << endl;
            valido = 0;
        }
        if(valido == 1 && ocupada[buffer.x][buffer.y] == 1)
        {
            cout << "Se repite la coordenada ( " << buffer.x << " , " << buffer.y << " ) " << endl;
            valido = 0;
        }
        if(valido == 1 && buffer.despegue != 0 && (buffer.soltarGranada1 != 0 || buffer.soltarGranada2 != 0 ||
           buffer.ataqueKamikaze != 0 || buffer.aterrizaje != 0))
        {
            cout << "No se puede despegar y hacer un ataque o aterrizar a la vez." << endl;
            valido = 0;
        }
        if(valido == 1 && buffer.ataqueKamikaze != 0 && buffer.aterrizaje != 0)
        {
            cout << "El ataqueKamikaze y el aterrizaje no pueden estar activos a la vez." << endl;
            valido = 0;
        }
        if(valido == 1 && buffer.aterrizaje == 0 && buffer.ataqueKamikaze == 0 &&
           (buffer.siguientex < 0 || buffer.siguientex > 199 || buffer.siguientey < 0 || buffer.siguientey > 199))
        {
            cout << "La siguiente coordenada de ( " << buffer.x << " , " << buffer.y << " ) esta fuera de la tabla." << endl;
            valido = 0;
        }

        if(valido == 1)
        {
            ocupada[buffer.x][buffer.y] = 1;
            if(buffer.despegue != 0)
            {
                despegues++;
                despegueX = buffer.x;
                despegueY = buffer.y;
            }
            if(buffer.aterrizaje != 0 || buffer.ataqueKamikaze != 0)
            {
                finales++;
            }
            tabla[buffer.x][buffer.y].espera = buffer.espera;
            tabla[buffer.x][buffer.y].soltarGranada1 = buffer.soltarGranada1;
            tabla[buffer.x][buffer.y].soltarGranada2 = buffer.soltarGranada2;
            tabla[buffer.x][buffer.y].ataqueKamikaze = buffer.ataqueKamikaze;
            tabla[buffer.x][buffer.y].aterrizaje = buffer.aterrizaje;
            tabla[buffer.x][buffer.y].despegue = buffer.despegue;
            tabla[buffer.x][buffer.y].siguientex = buffer.siguientex;
            tabla[buffer.x][buffer.y].siguientey = buffer.siguientey;
        }
        if(valido == 1 && despegues > 1)
        {
            cout << "Error hay mas de un despegue en el archivo. " << endl;
            valido = 0;
        }
        if(valido == 1 && finales > 1)
        {
            cout << "Hay mas de un aterrizaje o ataque kamikaze en el archivo. " << endl;
            valido = 0;
        }
    }
    fclose(f);

    if(valido == 1 && despegues != 1)
    {
        cout << "El archivo debe tener un unico despegue." << endl;
        valido = 0;
    }
    if(valido == 1 && finales != 1)
    {
        cout << "El archivo debe tener un unico aterrizaje o ataque kamikaze." << endl;
        valido = 0;
    }

    if(valido == 1)
    {
        x = despegueX;
        y = despegueY;
        pasos = 1;
        actual = tabla[x][y];
        while(valido == 1 && actual.aterrizaje == 0 && actual.ataqueKamikaze == 0)
        {
            aledana = 0;
            if(actual.siguientex == x && (actual.siguientey == y + 1 || actual.siguientey == y - 1))
            {
                aledana = 1;
            }
            if(actual.siguientey == y && (actual.siguientex == x + 1 || actual.siguientex == x - 1))
            {
                aledana = 1;
            }
            if(aledana == 0)
            {
                cout << "La celda ( " << x << " , " << y << " ) no apunta a una celda aledania." << endl;
                valido = 0;
            }
            if(valido == 1 && ocupada[actual.siguientex][actual.siguientey] == 0)
            {
                cout << "Hay un hueco en la ruta, en la coordenada ( " << actual.siguientex << " , " << actual.siguientey << " ) " << endl;
                valido = 0;
            }
            if(valido == 1 && pasos >= registros)
            {
                cout << "La ruta no llega al aterrizaje o ataque kamikaze." << endl;
                valido = 0;
            }
            if(valido == 1)
            {
                x = actual.siguientex;
                y = actual.siguientey;
                actual = tabla[x][y];
                pasos++;
            }
        }
        if(valido == 1 && pasos != registros)
        {
            cout << "Hay registros que no pertenecen a la ruta del dron." << endl;
            valido = 0;
        }
    }

    if(valido == 0)
    {
        for(x=0;x<200;x++)
        {
            for(y=0;y<200;y++)
            {
                tabla[x][y] = vacia;
            }
        }
        cout << "No se cargo el archivo." << endl;
    }
    if(valido == 1)
    {
        cout << "Archivo cargado correctamente. Registros cargados: " << registros << endl;
    }
    return;
}


void mostrarAtaques(Orden tabla[200][200])
{
    int x,y, mostrados=0;
    Orden buffer;
    for(x=0;x<200;x++)
    {
        for(y=0;y<200;y++)
        {
            buffer = tabla[x][y];
            if(buffer.despegue || buffer.aterrizaje || buffer.soltarGranada1 || buffer.soltarGranada2 ||
            buffer.ataqueKamikaze || buffer.espera > 0|| buffer.siguientex != 0 || buffer.siguientey != 0)
            {
                cout << "Coordenada: ( " << x << " , " << y << " ) " << endl;
                cout << "Despegue: " << buffer.despegue << endl;
                cout << "Aterrizaje: " << buffer.aterrizaje << endl;
                cout << "soltarGranada1: " << buffer.soltarGranada1 << endl;
                cout << "soltarGranada2: " << buffer.soltarGranada2 << endl;
                cout << "ataqueKamikaze: " << buffer.ataqueKamikaze << endl;
                cout << "Esperar: " << buffer.espera << endl;
                cout << "Siguiente x: " << buffer.siguientex << endl;
                cout << "Siguiente y: " << buffer.siguientey << endl;
                if(buffer.ataqueKamikaze || buffer.aterrizaje)
                {
                    cout << "Fin del archivo." << endl;
                } else {
                    cout << "Las siguientes coordenadas son: " << " ( " << buffer.siguientex << " , " << buffer.siguientey << " ) " << endl;

                }
                mostrados++;
                if(mostrados%20 == 0)
                {
                    cout << "Para ir a la siguiente pagina presione una tecla." << endl;
                    getch();
                }
            }
        }
    }
    if(mostrados == 0)
    cout << "No hay datos en la tabla " << endl;
    return;
}
void crearAtaque()
{
    char otro;
    FILE *f;
    char nombre[200];
    ordenArchivo buffer;
    cout << "Ingrese el nombre del archivo" << endl;
    cin >> nombre;
    f = fopen(nombre,"wb");
    if(f == NULL)
    {
        cout << "No se pudo crear el archivo" << endl;
    } else {
        do {
        cout << "Ahora usted va a cargar los datos del archivo. "<< endl;
        cout << "Ingrese las posiciones de x e y: " << endl;
        pedirCoordenadas(buffer.x,buffer.y);
        cout << "Ingrese la espera: " << endl;
        cin >> buffer.espera;
        pedirAtaques(buffer);
        cout << "Ingrese el valor a despegue: " << endl;
        cin >> buffer.despegue;
        cout << "Ingrese el valor a aterrizaje: " << endl;
        cin >> buffer.aterrizaje;
        if(buffer.aterrizaje != 0 || buffer.ataqueKamikaze != 0)
        {
            buffer.siguientex = 0;
            buffer.siguientey = 0;
        } else {
            cout << "Ingrese las cordenadas de siguiente: " << endl;
            pedirCoordenadas(buffer.siguientex,buffer.siguientey);
            }
        fwrite(&buffer,sizeof(ordenArchivo),1,f);
        cout << "Desea cargar otro registro? S/N" << endl;
        cin >> otro;
        } while(otro == 's' || otro == 'S');
        fclose(f);
    }
    return;
}
void corregirArchivo(int x, int y)
{
    FILE *f;
    ordenArchivo buffer;
    char nombre[200];
    cout << "Ingrese el nombre del archivo:" << endl;
    cin >> nombre;
    f = fopen(nombre,"rb+");
    if(f == NULL)
    {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    } else {
        int encontrar = encontrarRegistro(f,x,y,buffer);
        if(encontrar == 0)
        {
            cout << "No se encontró el registro" << endl;
            return;
        } else {
            cout << "Se encontró el registro." << endl;
            mostrarDatos(buffer);
            // una vez que encontré el registro tengo que volver con fseek para sobreescribir el registro.
            fseek(f,-1*sizeof(ordenArchivo),SEEK_CUR);
            do {
            pedirAtaques(buffer);
            cout << "Ingrese el tiempo de espera: " << endl;
            cin >> buffer.espera;
            cout << "Ingrese el valor del despegue: " << endl;
            cin >> buffer.despegue;
            cout << "Ingrese el valor del aterrizaje: " << endl;
            cin >> buffer.aterrizaje;
            pedirSiguienteCoor(buffer);
            if(buffer.ataqueKamikaze == 1 && buffer.aterrizaje == 1)
            {
            cout << "El ataqueKamikaze y el aterrijaze no pueden tener valor true a la vez. Intenta de nuevo." << endl;
            }
            } while(buffer.ataqueKamikaze == 1 && buffer.aterrizaje == 1);
            fwrite(&buffer,sizeof(ordenArchivo),1,f);
            fclose(f);
        }
    }
    fclose(f);
    return;
}
void corregirMemoria(Orden tabla[200][200])
{
    int x,y;
    ordenArchivo buffer;
    do {
    cout << "Ingrese las coordenadas que quiere cambiar: " << endl;
    pedirCoordenadas(x,y);
    mostrarDatosEnTabla(tabla,x,y);
    if(tabla[x][y].aterrizaje == 0 && tabla[x][y].despegue == 0 &&
             tabla[x][y].ataqueKamikaze == 0 && tabla[x][y].espera == 0 &&
             tabla[x][y].soltarGranada1 == 0 && tabla[x][y].soltarGranada2 == 0 &&
             tabla[x][y].siguientex == 0 && tabla[x][y].siguientey == 0)
    {
        cout << "Estas coordenadas no tienen memoria cargada. Intente de nuevo." << endl;
    }
    } while (tabla[x][y].aterrizaje == 0 && tabla[x][y].despegue == 0 &&
             tabla[x][y].ataqueKamikaze == 0 && tabla[x][y].espera == 0 &&
             tabla[x][y].soltarGranada1 == 0 && tabla[x][y].soltarGranada2 == 0 &&
             tabla[x][y].siguientex == 0 && tabla[x][y].siguientey == 0);
             do {
    cout << "Encontramos datos en esas coordenadas. Ingrese los nuevos datos (1 para SI y 0 para No): " << endl;
    cout << "Ingrese el valor de espera: " << endl; cin >> tabla[x][y].espera;
    cout << "Ingrese el valor de soltarGranada1: " << endl; cin >> tabla[x][y].soltarGranada1;
    cout << "Ingrese el valor de soltarGranada2: " << endl; cin >> tabla[x][y].soltarGranada2;
    cout << "Ingrese el valor de ataqueKamikaze: " << endl; cin >> tabla[x][y].ataqueKamikaze;
    cout << "Ingrese el valor de aterrizaje: " << endl; cin >> tabla[x][y].aterrizaje;
    cout << "Ingrese el valor de despegue: " << endl; cin >> tabla[x][y].despegue;
    cout << "Ingrese el valor de siguientex: " << endl; cin >> tabla[x][y].siguientex;
    cout << "Ingrese el valor de siguientey: " << endl; cin >> tabla[x][y].siguientey;
    if(tabla[x][y].ataqueKamikaze != 0  && tabla[x][y].aterrizaje != 0)
    {
        cout << "AtaqueKamikaze y Aterrizaje estan activos a la vez. Intente de nuevo" << endl;
    }
    } while(tabla[x][y].ataqueKamikaze != 0  && tabla[x][y].aterrizaje != 0);
}
void guardarMemoria(Orden tabla[200][200])
{
    FILE *f;
    char nombre[200];
    ordenArchivo buffer;
    int x, y, guardados = 0;

    cout << "Ingrese el nombre del archivo nuevo: " << endl;
    cin >> nombre;

    f = fopen(nombre,"wb");
    if(f == NULL)
    {
        cout << "No se pudo crear el archivo." << endl;
        return;
    }

    for(x=0;x<200;x++)
    {
        for(y=0;y<200;y++)
        {
            if(tabla[x][y].aterrizaje != 0 || tabla[x][y].despegue != 0 ||
               tabla[x][y].ataqueKamikaze != 0 || tabla[x][y].espera != 0 ||
               tabla[x][y].soltarGranada1 != 0 || tabla[x][y].soltarGranada2 != 0 ||
               tabla[x][y].siguientex != 0 || tabla[x][y].siguientey != 0)
            {
                buffer.x = x;
                buffer.y = y;
                buffer.espera = tabla[x][y].espera;
                buffer.soltarGranada1 = tabla[x][y].soltarGranada1;
                buffer.soltarGranada2 = tabla[x][y].soltarGranada2;
                buffer.ataqueKamikaze = tabla[x][y].ataqueKamikaze;
                buffer.aterrizaje = tabla[x][y].aterrizaje;
                buffer.despegue = tabla[x][y].despegue;
                buffer.siguientex = tabla[x][y].siguientex;
                buffer.siguientey = tabla[x][y].siguientey;

                fwrite(&buffer,sizeof(ordenArchivo),1,f);
                guardados++;
            }
        }
    }

    fclose(f);

    if(guardados == 0)
        cout << "No habia datos en la tabla, el archivo quedo vacio." << endl;
    else
        cout << "Se guardaron " << guardados << " registros en el archivo." << endl;
    return;
}

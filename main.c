// This program will provide a system that sells tickets to the user for "The Benefit of Mr G"
//
// Name: Alejandro Ramírez Michel
// Date: 6 de noviembre del 2018

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// funciones del programa

// función del menu principal
void menu(){
    printf("Welcome to the show.\n"
           "Choose the option you'd like."
           "\n0. Buy."
           "\n1. Save sells data."
           "\n2. Reports."
           "\n3. Exit.\n");
}

// función de los resultados del show
void menuResults(){
    printf("Choose the option you'd like to know."
           "\n1. Total tickets sold."
           "\2. Total tickets sold per zone."
           "\n3. Total income."
           "\n4. Total income per zone."
           "\n5. Occupation rate."
           "\n6. Occupation rate per zone.\n");
}

// diferentes zonas
void zones(){
    printf("Which zone would you like to be in?\n"
           "1. VIP: $100"
           "\n2. Platinum: $85"
           "\n3. Gold: $70"
           "\n4. Silver: $55"
           "\n5. Green: $45"
           "\n6. Yellow: $40"
           "\n7. Red: $30"
           "\n8. Sky Blue: $50"
           "\n9. Navy Blue: $35"
           "\n10. Deep Blue: $20\n");
}

// método de pago
void paymentMethod(){
    printf("How are you going to pay?"
           "\n1. Visa"
           "\n2. MasterCard"
           "\n3. American Express\n");
}

// struct para guardar los datos
struct seats{
    char name[50];
    int ticket;
    int paymethod;
    bool seat;
} seats[400][200];

// función para abrir file
void openFile(FILE *fp) {
    // abre el archivo o lo crea en caso de ser necesario
    fp = fopen("benMrG.txt", "wb");

    // establezco valores iniciales
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 200; j++) {
            strcpy(seats[i][j].name, "");
            seats[i][j].paymethod = 0;
            seats[i][j].seat = false;

            // aquí establezco condiciones para los precios, varían de la zona

            if (j < 50 || j > 149) {
                if (i < 100) {
                    seats[i][j].ticket = 50;
                } else if (i < 300) {
                    seats[i][j].ticket = 35;
                } else {
                    seats[i][j].ticket = 20;
                }

            } else {
                if (i < 5) {
                    seats[i][j].ticket = 100;
                } else if (i < 10) {
                    seats[i][j].ticket = 85;
                } else if (i < 50) {
                    seats[i][j].ticket = 70;
                } else if (i < 100) {
                    seats[i][j].ticket = 55;
                } else if (i < 250) {
                    seats[i][j].ticket = 45;
                } else if (i < 350) {
                    seats[i][j].ticket = 40;
                } else {
                    seats[i][j].ticket = 30;
                }

            }
        }
    }

    fwrite(&seats, sizeof(seats), 1, fp);
}

// funcion para comprar tickets
void buy() {
    char name[30];
    char option;
    int row;
    int seat;
    int payment;
    int primero;
    int ultimo;


    zones();
    printf("Choose the zone where you'd like to sit in:\n");
    scanf("%d", &option);

    // switch de las zonas con sus respectivas filas
    switch (option) {
        case 1:
            primero = 1;
            ultimo = 5;
            break;
        case 2:
            primero = 6;
            ultimo = 10;
            break;
        case 3:
            primero = 11;
            ultimo = 50;
            break;
        case 4:
            primero = 51;
            ultimo = 100;
            break;
        case 5:
            primero = 101;
            ultimo = 250;
            break;
        case 6:
            primero = 251;
            ultimo = 350;
            break;
        case 7:
            primero = 351;
            ultimo = 400;
            break;
        case 8:
            primero = 1;
            ultimo = 100;
            break;
        case 9:
            primero = 101;
            ultimo = 300;
            break;
        case 10:
            primero = 301;
            ultimo = 400;
            break;
        default:
            printf("Invalid!.\n");
            return;
    }

    do {
        printf("Choose a row between %d-%d\n", primero, ultimo);
        scanf("%d", &row);
    } while (row < primero || row > ultimo);

    if (option > 7) {
        do {
            printf("Please, choose a seat between 1-50 or 151-200\n");
            scanf("%d", &seat);
        } while ((seat < 1 || seat > 50) && (seat < 151 || seat > 200));

    } else {
        do {
            printf("Now, choose a seat between 51-150\n");
            scanf("%d", &seat);
        } while (seat < 51 || seat > 150);
    }

    paymentMethod();
    printf("Select a payment method.\n");
    scanf("%d", &payment);

    if (payment < 1 || payment > 3) {
        printf("Back.\n");
        return;
    }

    printf("Type your name:\n");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    printf("Tab to accept.\n");
    scanf("%c", &option);

    if (!option) {
        if (seats[row - 1][seat - 1].seat) {
            printf("This seat is taken.\n");
        } else {
            seats[row - 1][seat - 1].seat = true;
            seats[row - 1][seat - 1].paymethod = payment;
            strcpy(seats[row - 1][seat - 1].name, name);
            printf("Done! Your transaction is completed.\n");
        }
    } else{
        printf("Back.");
    }
}

// funcion para contar los insumos totales
int income(int first, int last, int firstseat, int lastseat, int sold) {
    int count = 0;
    int sales = 0;
    for (int i = first - 1; i < last; i++) {
        for (int j = firstseat - 1; j < lastseat; j++) {
            if (seats[i][j].seat) {
                count++;
                sales += seats[i][j].ticket;
            }
        }
    }
    // si sold es 1, regresar las ventas totales
    if (sold) {
        return count;
    }
    // regresar el insumo total
    return sales;
}

// funcion para el insumo de todas las zonas
int totalZones(int zone,
        int sold) {
    int c = 0;
    int first;
    int last;

    switch (zone) {
        case 1:
            first = 1;
            last = 5;
            break;
        case 2:
            first = 6;
            last = 10;
            break;
        case 3:
            first = 11;
            last = 50;
            break;
        case 4:
            first = 51;
            last = 100;
            break;
        case 5:
            first = 101;
            last = 250;
            break;
        case 6:
            first = 251;
            last = 350;
            break;
        case 7:
            first = 351;
            last = 400;
            break;
        case 8:
            first = 1;
            last = 100;
            break;
        case 9:
            first = 101;
            last = 300;
            break;
        case 10:
            first = 301;
            last = 400;
            break;
        default:
            first = 1;
            last = 200;
            break;
    }

    if (zone > 7) {
        c += income(first, last, 1, 50, sold);
        c += income(first, last, 151, 200, sold);
    } else {
        c += income(first, last, 51, 150, sold);
    }
    return c;
}

// menu de reportes
void Reports() {
    int option;
    int c = 0;
    int zone = 0;
    float filasz;

    //llamo al menu que hice primero
    menuResults();
    printf("Please, choose an option:\n");
    scanf("%d", &option);

    switch (option) {
        case 1:
            c = totalZones(zone, 1);
            printf("The total of tickets sold: %d", c);
            break;
        case 2:
            do {
                zones();
                printf("Enter the zone you'd like to know about:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            c = totalZones(zone, 1);
            printf("The total of tickets sold in this zone: %d", c);
            break;
        case 3:
            c = totalZones(zone, 0);
            printf("Total income: $%d", c);
            break;
        case 4:
            do {
                zones();
                printf("Enter a zone you'd like to know about:\n");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            c = totalZones(zone, 0);
            printf("The total income in this zone: $%d", c);
            break;
        case 5:
            c = totalZones(zone, 1);
            printf("Occupation rate: %f%%", c * 100.0 / 80000);
            break;
        case 6:
            do {
                zones();
                printf("Enter a zone you'd like to know about:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);
            c = totalZones(zone, 1);

            // The rows have different sizes depending on the zone.
            switch (zone) {
                case 1:
                case 2:
                    filasz = 5;
                    break;
                case 3:
                    filasz = 40;
                    break;
                case 4:
                case 6:
                case 7:
                    filasz = 50;
                    break;
                case 8:
                case 10:
                    filasz = 100;
                    break;
                case 5:
                    filasz = 150;
                    break;
                case 9:
                default:
                    filasz = 200;
                    break;
            }
            printf("Occupation rate in this zone: %f%%", c/filasz);
            break;
        default:
            printf("Invalid!");
            return;
    }

}

// para cambiar el archivo con los datos recibidos
void wFile(FILE *fp) {
    fp = fopen("benMrG.txt", "wb");
    fwrite(&seats, sizeof(seats), 1, fp);
    fclose(fp);
}

int main() {
    FILE *mrgfile;
    int opcion;

    //abrir file
    mrgfile = fopen("benMrG.txt", "rb");

    //si el archivo abierto no existe
    if (mrgfile == NULL) {
        openFile(mrgfile);
    } else {
        // si el archivo existe se guarda los datos recibidos
        while (fread(&seats, sizeof(seats), 1, mrgfile));
    }

    //para cerrar file
    fclose(mrgfile);


    do {
        menu();
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 0:
                buy();
                break;
            case 1:
                wFile(mrgfile);
                printf("Data saved.\n");
                break;
            case 2:
                Reports();
                break;
            case 3:
                wFile(mrgfile);
                printf("\nSee you later!.\n");
                break;
            default:
                printf("\nChoose a valid option please.\n");
                break;
        }

    } while (opcion != '0');

    return 0;
}
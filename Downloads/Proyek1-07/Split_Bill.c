// Project Name: Split-Bill Calculator
// Group        : 07
// - Bonifasius Raditya Pandu Hendrianto 2306242350
// - Calvin Wirathama Katoroy 2306242395
// Version      : 3.0
// Date         : 18/03/2024
// Short Desc.  : soon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define REKENING_MEMORY 20

typedef struct{
    char nama_makanan[50];
    int harga_makanan;
}beli;

typedef struct{
    char nama[50];
    int nominal_rekening;
    int result;
    
    beli list[5];
}database;

typedef struct{
    char name_sort[50];
    int nominal_sort;
}rekening_sort;

// Function Prototypes
void open_rekening(char nama_rekening[], int saldo_rekening, database pembeli[]);
void open_splitbill(database pembeli[], int n, int m);
int open_patungan(void);
char *read_file(char *filename);
int clear_screen(void);
void clear_input_buffer(void);

int main()
{
    FILE *rek;
    FILE *pat;
    int n, i, j, m, choice;
    database pembeli[n];
    char filename[1024];
    char nama_rekening[50];
    int saldo_rekening;
    int result[n];
    float hasil;
    while (choice != 5) {
        clear_screen();
        printf("/======================================================\\\n");
        printf("||             Split-Bill Calculator v3.0             ||\n");
        printf("||====================================================||\n");
        printf("||                     Main Menu                      ||\n");
        printf("||====================================================||\n");   
        printf("|| 1. Open Rekening                                   ||\n");
        printf("|| 2. Splitbill                                       ||\n");
        printf("|| 3. Patungan                                        ||\n");
        printf("|| 4. Lihat Data                                      ||\n");
        printf("|| 5. Exit Program                                    ||\n");
        printf("\\======================================================/\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                clear_screen();
                open_rekening(nama_rekening, saldo_rekening, pembeli);
                printf("\nPress enter to continue...");
				while (getchar() != '\n');
				clear_input_buffer();
            break;

            case 2:
                open_splitbill(pembeli, n, m);
                printf("\nPress enter to continue...");
                while (getchar() != '\n');clear_input_buffer();
            break;

            case 3:
                hasil = open_patungan();
                printf("Per Orang Membayar %.2f\n", hasil);
                FILE *file = fopen("split.txt", "a");
                fprintf(file, "Biaya Per Orang: Rp %.2f\n", hasil);
                fclose(file);
                printf("\nPress enter to continue...");
                while (getchar() != '\n');
				clear_input_buffer();
            break;

            case 4:
                printf("File: ");
                scanf("%s", filename);
                strcat(filename, ".txt");
                
                char *file_contents = read_file(filename);

                if (file_contents == NULL)
                {
                    printf("Error reading file.\n");
                    return 1;
                }

                clear_screen();
                printf("====================\n");
                printf("File Contents\n");  
                printf("====================\n\n");
                printf("%s", file_contents);

                free(file_contents);
                printf("\nPress enter to continue...");
                while (getchar() != '\n');
                clear_input_buffer();
            break;

            case 5:
                printf("Exiting program. Goodbye!\n");
            break;
                
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }
    }
    return 0;
}

void open_rekening(char nama_rekening[], int saldo_rekening, database pembeli[])
{
    FILE *rek;
    int input;
    int i = 0, n, a = 0, b = 0;
    rekening_sort sort[REKENING_MEMORY];
    char name[50];
    char nama_rekening_void[50];
    int saldo_rekening_void;
    printf("/======================================================\\\n");
    printf("||             Split-Bill Calculator v3.0             ||\n");
    printf("||====================================================||\n");   
    printf("||                   Open Rekening                    ||\n");
    printf("||====================================================||\n");
    printf("|| 1. Tambah Buku Rekening                            ||\n");
    printf("|| 2. Searching Rekening                              ||\n");
    printf("|| 3. Sorting Rekening (Tinggi ke Rendah)             ||\n");
    printf("|| 4. Sorting Rekening (Rendah ke Tinggi)             ||\n");
    printf("\\======================================================/\n\n");
    do{
        printf("Enter your choice: ");
    scanf("%d", &input);
    }while(input < 0 || input > 4);

    switch(input)
    {
        case 1:
            rek = fopen("rekening.txt", "r");
            FILE *temp = fopen("temp_rekening.txt", "w");
            printf("Banyak Rekening: ");
            scanf("%d", &n);
            for(int i = 0; i < n; i++)
            {
                printf("==========================\n");
                printf("Input User ke-%d\n", i + 1);
                printf("==========================\n");
                printf("Nama Rekening: ");
                scanf("%s", pembeli[i].nama);
                printf("Nominal Rekening: ");
                scanf("%d", &pembeli[i].nominal_rekening);
                printf("==========================\n\n");
                while(fscanf(rek, "%s %d", sort[a].name_sort, &sort[a].nominal_sort) != EOF)
                {
                    if(strcasecmp(sort[a].name_sort, pembeli[i].nama) == 0)
                    {
                        sort[a].nominal_sort += pembeli[i].nominal_rekening;
                        b++;
                    }
                    fprintf(temp, "%s %d\n", sort[a].name_sort, sort[a].nominal_sort);
                    a++;
                }
                fclose(rek);
                fclose(temp);
                
                if(b == 0)
                {
                    rek = fopen("rekening.txt", "a");
                    fprintf(rek, "%s %d\n", pembeli[i].nama, pembeli[i].nominal_rekening);
                    fclose(rek);
                }
                else
                {
                    remove("rekening.txt");
                    rename("temp_rekening.txt", "rekening.txt");
                }
            }
        break;

        case 2:
            rek = fopen("rekening.txt", "r");
            printf("Search Name: ");
            scanf("%s", name);
            printf("------------------------\n");
            printf("%-10s %-10s\n", "Nama", "Nominal");
            printf("------------------------\n");
            while(fscanf(rek, "%s %d", nama_rekening_void, &saldo_rekening_void) != EOF)
            {
                if(strcasestr(nama_rekening_void, name) > 0) printf("%-10s %-10d\n", nama_rekening_void, saldo_rekening_void);
            }
            fclose(rek);
        break;
            
        case 3:
            rek = fopen("rekening.txt", "r");
            while(fscanf(rek, "%s %d", sort[i].name_sort, &sort[i].nominal_sort) != EOF)
            {
                i++;
            }

            for (int k = 0; k < i - 1; k++)
            {
                for (int j = 0; j < i - 1; j++)
                {
                    if (sort[j].nominal_sort < sort[j + 1].nominal_sort)
                    {
                        float temp = sort[j].nominal_sort;
                        char temp_name[50];
                        strcpy(temp_name, sort[j].name_sort);

                        sort[j].nominal_sort = sort[j + 1].nominal_sort;
                        strcpy(sort[j].name_sort, sort[j + 1].name_sort);

                        sort[j + 1].nominal_sort = temp;
                        strcpy(sort[j + 1].name_sort, temp_name);
                    }
                }
            }
            fclose(rek);

            rek = fopen("rekening.txt", "w");

            printf("------------------------\n");
            printf("%-10s %-10s\n", "Nama", "Nominal");
            printf("------------------------\n");
            for(int k = 0; k < i; k++) printf("%-10s %-10d\n", sort[k].name_sort, sort[k].nominal_sort);
            for(int k = 0; k < i; k++) fprintf(rek, "%s %d\n", sort[k].name_sort, sort[k].nominal_sort);
            fclose(rek);
        break;

        case 4:
            rek = fopen("rekening.txt", "r");
            while(fscanf(rek, "%s %d", sort[i].name_sort, &sort[i].nominal_sort) != EOF)
            {
                i++;
            }

            for (int k = 0; k < i - 1; k++)
            {
                for (int j = 0; j < i - 1; j++)
                {
                    if (sort[j].nominal_sort > sort[j + 1].nominal_sort)
                    {
                        float temp = sort[j].nominal_sort;
                        char temp_name[50];
                        strcpy(temp_name, sort[j].name_sort);

                        sort[j].nominal_sort = sort[j + 1].nominal_sort;
                        strcpy(sort[j].name_sort, sort[j + 1].name_sort);

                        sort[j + 1].nominal_sort = temp;
                        strcpy(sort[j + 1].name_sort, temp_name);
                    }
                }
            }
            fclose(rek);

            rek = fopen("rekening.txt", "w");

            printf("------------------------\n");
            printf("%-10s %-10s\n", "Nama", "Nominal");
            printf("------------------------\n");
            for(int k = 0; k < i; k++) printf("%-10s %-10d\n", sort[k].name_sort, sort[k].nominal_sort);
            for(int k = 0; k < i; k++) fprintf(rek, "%s %d\n", sort[k].name_sort, sort[k].nominal_sort);
            fclose(rek);
        break;
    }
}

void open_splitbill(database pembeli[], int n, int m)
{
    rekening_sort sort[REKENING_MEMORY];
    bool status;
    bool nama_aman;
    int j = 0, z;
    int t = 0;
    float tax;
    printf("Banyak Orang: ");
    scanf("%d", &z);
    printf("Pajak (dalam persen): ");
    scanf("%f", &tax);
    tax += 100;
    tax /= 100;
    int a = 0, i = 0;

    for(int c = 0; c < z; c++)
    {
        FILE *pat = fopen("patungan.txt", "a");;
        FILE *rek = fopen("rekening.txt", "r");
        FILE *temp = fopen("temp_rekening.txt", "w");
        printf("\n==========================\n");
        printf("Input Splitbill\n");
        printf("==========================\n");
        printf("Nama: ");
        scanf("%s", pembeli[i].nama);
        printf("Beli Berapa Banyak? ");
        scanf("%d", &m);
        fprintf(pat, "%s\n", pembeli[i].nama);
        pembeli[0].result = 0;
        
            for(j = 0; j < m; j++)
            {
                printf("Nama Pembelian ke-%d: ", j + 1);
                scanf(" %[^\n]s", pembeli[i].list[j].nama_makanan);
                printf("Harga: ");
                scanf("%d", &(pembeli[i].list[j].harga_makanan));
                fprintf(pat, "%s %d\n", pembeli[i].list[j].nama_makanan, pembeli[i].list[j].harga_makanan);
                pembeli[i].result = pembeli[i].result + pembeli[i].list[j].harga_makanan;
            }
            pembeli[i].result *= tax;
            fprintf(pat, "Total: %d\n", pembeli[i].result);
            fprintf(pat, "\n");
            
            while(fscanf(rek, "%s %d", sort[a].name_sort, &sort[a].nominal_sort) != EOF)
            {
                if(strcasecmp(sort[a].name_sort, pembeli[i].nama) == 0)
                {
                    if(sort[a].nominal_sort > pembeli[i].result) {
                        status = true;
                    }
                    else {
                        status = false;
                    }
                    sort[a].nominal_sort -= pembeli[i].result;
                    t++;
                }
                fprintf(temp, "%s %d\n", sort[a].name_sort, sort[a].nominal_sort);
                a++;        
            }

        printf("==========================\n\n");
        fprintf(pat, "--------------------\n\n");

        if(status == true && t == 1) printf("%s AMAN membayar %d\n", pembeli[i].nama, pembeli[i].result);
        else if(status == false && t == 1) printf("%s BERHUTANG %d\n", pembeli[i].nama, pembeli[i].result);
        if(t == 0) printf("%s membayar %d\n", pembeli[i].nama, pembeli[i].result);
        fclose(pat);
        fclose(rek);
        fclose(temp);
        
        remove("rekening.txt");
        rename("temp_rekening.txt", "rekening.txt");
    }
}

int open_patungan()
{
    int harga, orang;
    float tax;
    printf("Harga Barang: ");
    scanf("%d", &harga);
    printf("Berapa Orang: ");
    scanf("%d", &orang);
    printf("Pajak (dalam persen): ");
    scanf("%f", &tax);
    tax += 100;
    tax /= 100;
     
    float result = tax * (harga/orang);
    return result;
}

char *read_file(char *filename)
{
  FILE *file;
  
  file = fopen(filename, "r");
  
  
  if (file == NULL) return NULL;
  fseek(file, 0, SEEK_END); 
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  char *string = malloc(sizeof(char) * (length+1));

  char c;

  int i = 0;
  
  while ( (c = fgetc(file)) != EOF)
  {
    string[i] = c;

    i++;
  }
  
  string[i] = '\0';
  
  fclose(file);
  
  return string;
}

int clear_screen () {
    printf("\e[1;1H\e[2J");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } // Loop until we reach a newline or EOF.
}
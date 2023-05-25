#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 15
#define Lon 45

typedef struct
{
	char nomPelicula[Lon], actorP[Lon], director[Lon], productora[Lon];
	char estreno[Lon];
	float duracion;
} cartelera;

void menu()
{
	printf("	\nProyecto Final Archivos ... Cartelera de peliculas\n");
	printf("Nombre:Jorge Rodolfo Alfredo Apodaca Ramos --- Matricula:1193345");
	printf("\n");
	printf("Menu:\n");
	printf(" a) Altas en Cartelera \n");
	printf(" b) Cartelera\n");
	printf(" c) Salir\n");
}
void menu2()
{
	printf("Menu:\n");
	printf(" 1) Altas generales en texto \n");
	printf(" 2) Altas generales en binario\n");
	printf(" 3) Salir\n");
}
void menu3()
{
	printf("Menu:\n");
	printf(" 1) Consultas generales en texto \n");
	printf(" 2) Consultas generales en binario\n");
	printf(" 3) Salir\n");
}

cartelera capturaDatos();

cartelera capturaDatos()
{
	cartelera pel;

	printf("\nIngrese el nombre de la pelicula:\n");
	fflush(stdin);
	scanf("%[^\n]", pel.nomPelicula); //%[^\n] lo utilize como regular expresion

	printf("\nIngrese el nombre del actor principal:\n");
	fflush(stdin);
	scanf("%[^\n]", pel.actorP);

	printf("\nIngrese el nombre del Director:\n");
	fflush(stdin);
	scanf("%[^\n]", pel.director);

	printf("\nIngrese la productora:\n");
	fflush(stdin);
	scanf("%[^\n]", pel.productora);

	printf("\nLa pelicula es de estreno o ya fue estrenada?\n");
	fflush(stdin);
	scanf("%[^\n]", pel.estreno);

	printf("\nIngrese la duracion de la pelicula:\n");
	scanf("%f", &pel.duracion);

	return pel;
}

void altas(char tipo_archivo);

void altas(char tipo_archivo)
{
	cartelera pel;

	if (tipo_archivo == 't')
	{
		FILE *altatxt = fopen("altas.txt", "a+");

		if (altatxt == NULL)
		{
			printf("Error opening file.\n");
			return;
		}

		pel = capturaDatos();

		fprintf(altatxt, "%s,%s,%s,%s,%s,%.2f", pel.nomPelicula, pel.actorP, pel.director, pel.productora, pel.estreno, pel.duracion);
		fprintf(altatxt, "\n");
		fclose(altatxt);
	}
	else
	{
		FILE *altabin = fopen("altas.bin", "ab");

		if (altabin == NULL)
		{
			printf("Error opening file.\n");
			return;
		}

		pel = capturaDatos();

		fwrite(&pel, sizeof(cartelera), 1, altabin);

		fclose(altabin);
	}
}

void consultas(char tipo_archivo);

void consultas(char tipo_archivo)  //el reutilizar metodos me sirve para disminuir lineas de codigo y centralizar logica de negocio
{
	if (tipo_archivo == 't')
	{
		FILE *file;
		char line[300];
		char *token;

		file = fopen("altas.txt", "r");
		if (file == NULL)
		{
			printf("Failed to open the file.\n");
			return;
		}

		printf("\n\n%-20s %-20s %-20s %-20s %-20s %-20s\n", "Peliculas", "Actores", "Director", "Productora", "Estreno", "Duracion");

		while (fgets(line, sizeof(line), file) != NULL)
		{
			// Process the current line (print it in this example)
			// printf("%s", line);

			token = strtok(line, ",");

			while (token != NULL)
			{
				printf("%-20s ", token);
				token = strtok(NULL, ",");
			}

			printf("\n");
		}

		// Close the file
		fclose(file);
	}
	else
	{
		FILE *file = fopen("altas.bin", "rb");
		cartelera pel;
		int firstTime = 1;

		if (file == NULL)
		{
			printf("Failed to open the file.\n");
			return;
		}

		while (fread(&pel, sizeof(cartelera), 1, file) == 1)
		{
			if (firstTime == 1)
			{
				printf("\n\n%-20s %-20s %-20s %-20s %-20s %-20s\n", "Peliculas", "Actores", "Director", "Productora", "Estreno", "Duracion");
				firstTime = 0;
			}

			printf("%-20s %-20s %-20s %-20s %-20s %-20f\n", pel.nomPelicula, pel.actorP, pel.director, pel.productora, pel.estreno, pel.duracion);
		}

		fclose(file);
	}
}

int main()
{
	int x = 0, opc, opc2;
	cartelera pel;
	char opcion;

	do
	{
		menu();
		printf("Ingresa la opcion: ");
		fflush(stdin);
		scanf("%c", &opcion);

		switch (opcion)
		{
		case 'a':
			do
			{
				menu2();
				printf("Ingresa la opcion:\n");
				scanf("%d", &opc2);
				switch (opc2)
				{
				case 1:
					printf("Se selecciono la opcion 1\n");
					altas('t');
					break;
				case 2:
					printf("Se selecciono la opcion 2\n");
					altas('b');
					break;
				case 3:
					printf("Se selecciono la opcion 3\n");
					break;
				}
				printf("\n\n");
				printf("Ingresa cualquier tecla para continuar...");

				fflush(stdin);
				getchar();

				system("cls");

			} while (opc2 != 3);
			break;
		case 'b':

			do
			{
				menu3();
				printf("Ingresa la opcion:\n");
				scanf("%d", &opc);
				switch (opc)
				{
				case 1:
					printf("Se selecciono la opcion 1\n");
					consultas('t');
					break;
				case 2:
					printf("Se selecciono la opcion 2\n");
					consultas('b');
					break;
				case 3:
					printf("Se selecciono la opcion 3\n");
					break;
				}
				printf("\n\n");
				printf("Ingresa cualquier tecla para continuar...");

				fflush(stdin);
				getchar();

				system("cls");

			} while (opc != 3);
			break;
		case 'c':
			printf("Opcion c seleccionada.\n");
			break;
		default:
			printf("Opcion invalida. Vuelve a intentar.\n");
			break;
		}

		printf("\n\n");
		printf("Ingresa cualquier tecla para continuar...");

		fflush(stdin);
		getchar();

		system("cls");

	} while (opcion != 'c');

	return 0;
}
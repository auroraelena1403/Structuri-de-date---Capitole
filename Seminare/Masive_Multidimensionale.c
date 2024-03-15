#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void inserareLocuinta(struct Locuinta** vector, int* dim,
	struct Locuinta l)
{
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * 
		(++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++)
	{
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL)
	{
		free((*vector));
	}
	(*vector) = copie;
}

//void citesteFisier(const char* nume_fisier, struct Locuinta** vector,
//	int* dim) {
//	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
//		FILE* f = fopen(nume_fisier, "r");
//		if (f != NULL) {
//			(*dim) = 0;
//			char buffer[100];
//			char delimitator[] = ",\n";
//			while (fgets(buffer, 100, f) != NULL) {
//				char* token;
//				token = strtok(buffer, delimitator);
//				struct Locuinta locuinta;
//				locuinta.id = atoi(token);
//				token = strtok(NULL, delimitator);
//				locuinta.strada = (char*)malloc(strlen(token) + 1);
//				strcpy(locuinta.strada, token);
//				token = strtok(NULL, delimitator);
//				locuinta.numar = atoi(token);
//				inserareLocuinta(vector, dim, locuinta);
//			}
//			fclose(f);
//		}
//	}
//}
void afisareLocuinta(struct Locuinta l) {
	printf("ID-ul: %d\t%s numarul %d\t", 
		l.id, l.strada, l.numar);
}
void afisareVectorLocuinte(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++)
		afisareLocuinta(vector[i]);
}


void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag==1) { //avem o locuinta de sters
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta)
			*((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		if ((*vector) != NULL)
		{
			free((*vector));
		}
		(*vector) = copie;
	}
}

//crearea unei matrici
//citirea unei matrici din fisier:modificam functia de mai sus
void citireMatriceLocuinte(const char* nume_fisier, struct Locuinta** matrice, int nrLinii, int* nrColoane ) { //nu realoc blocul de memorie, deci practic nu se modifica matricea
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				int pozitie=locuinta.numar%2;
				inserareLocuinta(&(matrice[pozitie]), &(nrColoane[pozitie]), locuinta);
			}
			fclose(f);
		}
	}
}
//functie de afisare matrice
void afisareMatrice(struct Locuinta** matriceLocuinte, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareLocuinta(matriceLocuinte[i][j]);
		}
		printf("\n");
	}
}

//id urile locuintelor de la numarul par
void afisareIdDPOParte(int paritate, struct Locuinta** matrice, int nrLinii, int* nrColoane) {
	paritate = paritate % 2;
	
		for (int j = 0; j < nrColoane[paritate]; j++) {
			printf(" %d  ", matrice[paritate][j].id);
		}
		printf("\n");
	
}

//cautare locuinta dupa id
struct Locuinta cautareLocuintaInMatrice(struct Locuinta** matrice, int id, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].id == id) {
				struct Locuinta locuintaReturnata;
				locuintaReturnata.id = matrice[i][j].id;
				locuintaReturnata.numar = matrice[i][j].numar;
				locuintaReturnata.strada = matrice[i][j].strada;
				return locuintaReturnata;
			}
			
		}
		
	}
	struct Locuinta locuintaNull;
	locuintaNull.id = -1;
	locuintaNull.numar = -1;
	locuintaNull.strada = NULL;
	return locuintaNull;
}

//dezalocare matrice
void dezalocareMatrice(struct Locuinta*** matrice, int** nrLinii, int** nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			free((*matrice)[i][j].strada);
			(*matrice)[i][j].strada = NULL; //nu trb folosit neaparat deoarece il dezaloc cu free
		}
		free((*matrice)[i]);
		
	}
	free(*matrice);
	*matrice = NULL;
	(*nrLinii) = 0;
	free(*nrColoane);
	*nrColoane = NULL;
}

void schimbareNrLocuinta(struct Locuinta** matrice, int nrLinii, int* nrColoane, int numarLocuinta) {
	int pozitie = numarLocuinta % 2;
	int idLocuinta = -1;
	int indexInVector = -1;
	for (int i = 0; i < nrColoane[pozitie]; i++) {
		if (matrice[pozitie][i].numar == numarLocuinta) {
			//l-am identificat
			matrice[pozitie][i].numar++; //creste cu o unitate
			idLocuinta = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}
	if (idLocuinta != -1) {
		//inseram inainte structura cu id ul respectiv
		int index = (numarLocuinta + 1) % 2; //ca sa ne duca in cealalta pozitie
		inserareLocuinta(&(matrice[index]), &(nrColoane[index]), matrice[pozitie][indexInVector]); //SHALLOW COPY
		//apelam f de stergere din vector : vector de vector, tocmai de asta folosesc functia
		stergeLocuinta(&(matrice[pozitie]), &(nrColoane[pozitie]), idLocuinta);
		
	}
}

void main() {
	/*struct Locuinta *locuinte = NULL;
	int dim = 3;
	citesteFisier("locuinte.txt", &locuinte, &dim);
	printf("Initial\n\n");
	afisareVectorLocuinte(locuinte, dim);
	
	printf("\n\nUlterior\n\n");
	stergeLocuinta(&locuinte, &dim, 22);
	afisareVectorLocuinte(locuinte, dim);*/

	//crearea unei matrici
	int nrLinii;
	int* nrColoane;
	struct Locuinta** matriceLocuinte;
	nrLinii = 2;
	nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	matriceLocuinte = (struct Locuinta**)malloc(sizeof(struct Locuinta*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		matriceLocuinte[i] = NULL;
		nrColoane[i] = 0; //vector de intregi, nu poate fi intializat cu NULL
	}
	citireMatriceLocuinte("locuinte.txt", matriceLocuinte, nrLinii, nrColoane);
	afisareMatrice(matriceLocuinte, nrLinii, nrColoane);
	afisareIdDPOParte(1, matriceLocuinte, nrLinii, nrColoane);
	struct Locuinta locuintaID = cautareLocuintaInMatrice(matriceLocuinte, 12, nrLinii, nrColoane);
	afisareLocuinta(locuintaID);
 
	// !!!!!!!!!!!!!!!!!!!!
	//dezalocareMatrice(&matriceLocuinte, &nrLinii, &nrColoane); trb sa corectez
	printf("\nmatrice dupa eliminare---------------------------\n");
	schimbareNrLocuinta(matriceLocuinte, nrLinii, nrColoane, 5);
	afisareMatrice(matriceLocuinte, nrLinii, nrColoane);
}
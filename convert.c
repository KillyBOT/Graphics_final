#include "convert.h"
#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "kdTree.h"
#include "gmath.h"
#include "material.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

struct kdTree* convert(struct matrix* p, struct matrix* t, double matID, char* fileName){
	FILE* f = fopen(fileName,"r");
	if(f == NULL){
		printf("ERROR! Mesh file %s could not be loaded!\n", fileName);
		exit(1);
	}

	char* fileType;
	char* buffer;
	float* binaryVertex;
	float* normalVertex;
	char* sBuffer;
	int vCount = 0;
	double vertex[3];
	double texture[3];
	double normal[3];
	double vertexLarge[4];
	double textureLarge[4];
	double normalLarge[4];
	double vTemp[3];
	double vnTemp[3];
	int bufferPlace = 0;
	int done = 0;
	int currentMatID = -1;

	int regCompile = 0;
	int reti;
	char regErrorBuffer[256];

	extern regex_t qF;
	extern regex_t qFT;
	extern regex_t qFN;
	extern regex_t qFTN;

	extern regex_t tF;
	extern regex_t tFT;
	extern regex_t tFN;
	extern regex_t tFTN;

	extern struct material* m;

	//q = quadrilateral, t = triangle, F = faces included, T = texture included, N = Normal included

	//printf("%s\n", "\\d\\/\\d\\/\\d \\d\\/\\d\\/\\d \\d\\/\\d\\/\\d \\d\\/\\d\\/\\d");

	buffer = malloc(BUFFER_SIZE);

	fileType = strrchr(fileName, '.');
	fileType++;

	//if(kd == NULL) kd = kdCreate();
	struct kdTree* kd = kdCreate();

	if(!strcmp(fileType,"stl")){ //Stl file
		fgets(buffer, BUFFER_SIZE, f);
		fseek(f, 0, SEEK_SET);

		if(!strncmp(buffer,"solid",5)){ //ASCII STL file

			while(fgets(buffer,BUFFER_SIZE,f) != NULL){
				buffer[strlen(buffer)-1]='\0';
				sBuffer = strdup(buffer);

				while(sBuffer[0] == ' ' || sBuffer[0] == '\t'){
					strsep(&sBuffer," \t");
				}
				//printf("%s\n", sBuffer);

				if(sBuffer[0] == 'v'){

					//printf("%s\n", buffer);

					sscanf(sBuffer,"vertex %lf %lf %lf", vertex, vertex+1, vertex+2);

					//print_vertex(vertex);

					add_point(p, vertex[0], vertex[1], vertex[2]);
					add_point(t, -1, -1, matID);
					kd = kdInsert(kd, vertex, normal);

				} else if(sBuffer[0] == 'f'){
					//printf("Normal\n");
					sscanf(sBuffer,"facet normal %lf %lf %lf",normal, normal+1,normal+2);
					//print_vertex(normal);
				}
				//printf("\n");

				free(sBuffer);
			}

		} else { //Binary STL file

			unsigned int tNum;
			short int data;
			normalVertex = malloc(sizeof(float) * 3);
			binaryVertex = malloc(sizeof(float) * 3);

			fread(buffer, sizeof(char), 80, f);
			//printf("Mesh name: %s\n", buffer);

			fread(&tNum, sizeof(unsigned int), 1, f);
			//printf("Number of polygons: %d\n", tNum);

			for(unsigned int n = 0; n < tNum; n++){
				fread(normalVertex, sizeof(float), 3, f);
				normal[0] = normalVertex[0];
				normal[1] = normalVertex[1];
				normal[2] = normalVertex[2];

				for(int o = 0; o < 3; o++){
					fread(binaryVertex, sizeof(float),3,f);
					vertex[0] = (double)binaryVertex[0];
					vertex[1] = (double)binaryVertex[1];
					vertex[2] = (double)binaryVertex[2];

					add_point(p, vertex[0], vertex[1], vertex[2]);
					add_point(t, -1, -1, matID);
					kd = kdInsert(kd, vertex, normal);
					//printf("%lf %lf %lf\n", vertex[0], vertex[1], vertex[2]);
				}

				fread(&data, sizeof(short int), 1, f);

			}

			free(normalVertex);
			free(binaryVertex);

		}
	}

	else if(!strcmp(fileType,"obj")){ //Obj file

		struct matrix* vList = new_matrix(4, 4096);
		struct matrix* vtList = new_matrix(4, 4096);
		struct matrix* vnList = new_matrix(4, 4096);
		add_point(vList, 0, 0, 0);
		add_point(vtList, 0, 0, 0);
		add_point(vnList, 0, 0, 0);

		char* lineType;
		char* lengthCheck;
		int spaceNum;

		struct material* currentMat;

		while(fgets(buffer,BUFFER_SIZE,f) != NULL){
			buffer[strlen(buffer)-1] = '\0';
			sBuffer = strdup(buffer);
			//printf("Raw data: %s\n", sBuffer);

			lineType = strsep(&sBuffer," ");
			if(sBuffer != NULL){

				while(sBuffer != NULL && (sBuffer[0] == ' ' || sBuffer[0] == '\t')) strsep(&sBuffer," \t");

				if(sBuffer != NULL){
					//printf("Line type: {%s}\n", lineType);
					//printf("%s\n", sBuffer);

					if(!strcmp(lineType,"mtllib")){
						//printf("%s\n", sBuffer);
						create_materials(sBuffer);
					}

					else if(!strcmp(lineType,"usemtl")){
						currentMatID = find_material(sBuffer)->id;
						//printf("%d\n", currentMatID);
					}

					else if(!strcmp(lineType,"v")){
						sscanf(sBuffer, "%lf %lf %lf", vertex, vertex+1, vertex+2);
						add_point(vList,vertex[0],vertex[1],vertex[2]);
					}

					else if(!strcmp(lineType,"vt")){
						sscanf(sBuffer, "%lf %lf", texture, texture + 1);
						add_point(vtList, texture[0], texture[1], 0);
					}

					else if(!strcmp(lineType, "vn")){
						sscanf(sBuffer, "%lf %lf %lf", normal, normal + 1, normal+2);
						add_point(vnList,normal[0],normal[1],normal[2]);
					}

					else if(!strcmp(lineType,"f")){

						//printf("%s\n", sBuffer);
						done = 0;


						reti = regexec(&qFTN, sBuffer, 0, NULL, 0);
						if(!reti){

							sscanf(sBuffer, "%lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf",
								vertexLarge, textureLarge, normalLarge,
								vertexLarge+1, textureLarge+1, normalLarge+1,
								vertexLarge+2, textureLarge+2, normalLarge+2,
								vertexLarge+3, textureLarge+3, normalLarge+3);

							for(int n = 0; n < 3; n++){
								add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
								add_point(t, vtList->m[0][(int)textureLarge[n]], vtList->m[1][(int)textureLarge[n]], (double)currentMatID);

								vTemp[0] = vList->m[0][(int)vertexLarge[n]];
								vTemp[1] = vList->m[1][(int)vertexLarge[n]];
								vTemp[2] = vList->m[2][(int)vertexLarge[n]];

								vnTemp[0] = vnList->m[0][(int)normalLarge[n]];
								vnTemp[1] = vnList->m[1][(int)normalLarge[n]];
								vnTemp[2] = vnList->m[2][(int)normalLarge[n]];

								//print_vertex(vTemp);
								//print_vertex(vnTemp);
								//printf("\n");

								kd = kdInsert(kd, vTemp, vnTemp);

							}

							for(int n = 0; n < 4; n++){
								add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
								add_point(t, vtList->m[0][(int)textureLarge[n]], vtList->m[1][(int)textureLarge[n]], (double)currentMatID);

								vTemp[0] = vList->m[0][(int)vertexLarge[n]];
								vTemp[1] = vList->m[1][(int)vertexLarge[n]];
								vTemp[2] = vList->m[2][(int)vertexLarge[n]];

								vnTemp[0] = vnList->m[0][(int)normalLarge[n]];
								vnTemp[1] = vnList->m[1][(int)normalLarge[n]];
								vnTemp[2] = vnList->m[2][(int)normalLarge[n]];

								kd = kdInsert(kd, vTemp, vnTemp);
								if(n == 0) n++;

							}

							done = 1;
						} else if(!done || reti == REG_NOMATCH){
							//printf("Failed to match qFTN\n");
						} else if(!done){
							regerror(reti, &qFTN, regErrorBuffer, sizeof(regErrorBuffer));
							fprintf(stderr, "Match qFTN failed!\n");
							exit(1);
						}

						if(!done){
							reti = regexec(&qFN, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf//%lf %lf//%lf %lf//%lf %lf//%lf",
									vertexLarge, normalLarge,
									vertexLarge+1, normalLarge+1,
									vertexLarge+2, normalLarge+2,
									vertexLarge+3, normalLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
									add_point(t, -1, -1, (double)currentMatID);

									vTemp[0] = vList->m[0][(int)vertexLarge[n]];
									vTemp[1] = vList->m[1][(int)vertexLarge[n]];
									vTemp[2] = vList->m[2][(int)vertexLarge[n]];

									vnTemp[0] = vnList->m[0][(int)normalLarge[n]];
									vnTemp[1] = vnList->m[1][(int)normalLarge[n]];
									vnTemp[2] = vnList->m[2][(int)normalLarge[n]];

									kd = kdInsert(kd, vTemp, vnTemp);

								}

								for(int n = 0; n < 4; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
									add_point(t, -1, -1, (double)currentMatID);

									vTemp[0] = vList->m[0][(int)vertexLarge[n]];
									vTemp[1] = vList->m[1][(int)vertexLarge[n]];
									vTemp[2] = vList->m[2][(int)vertexLarge[n]];

									vnTemp[0] = vnList->m[0][(int)normalLarge[n]];
									vnTemp[1] = vnList->m[1][(int)normalLarge[n]];
									vnTemp[2] = vnList->m[2][(int)normalLarge[n]];

									kd = kdInsert(kd, vTemp, vnTemp);
									if(n == 0) n++;

								}

								done = 1;
							} else if(reti == REG_NOMATCH) {
								//printf("Failed to match qFN\n");
							} else {
								regerror(reti, &qFN, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match qFN failed!\n");
								exit(1);
							}
						}

						if(!done){
							reti = regexec(&qFT, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf/%lf %lf/%lf %lf/%lf %lf/%lf",
									vertexLarge, textureLarge,
									vertexLarge+1, textureLarge+1,
									vertexLarge+2, textureLarge+2,
									vertexLarge+3, textureLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
									add_point(t, vtList->m[0][(int)textureLarge[n]], vtList->m[1][(int)textureLarge[n]], currentMatID);
								}

								for(int n = 0; n < 4; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
									add_point(t, vtList->m[0][(int)textureLarge[n]], vtList->m[1][(int)textureLarge[n]], currentMatID);
									if(n == 0) n++;

								}

								done = 1;
							} else if (reti == REG_NOMATCH){
								//printf("Failed to match qFT\n");
							} else {
								regerror(reti, &qFT, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match qFT failed!\n");
								exit(1);
							}
						}	

						if(!done){
							reti = regexec(&qF, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf %lf %lf %lf",
									vertexLarge,
									vertexLarge+1,
									vertexLarge+2,
									vertexLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
								}

								for(int n = 0; n < 4; n++){
									add_point(p, vList->m[0][(int)vertexLarge[n]], vList->m[1][(int)vertexLarge[n]], vList->m[2][(int)vertexLarge[n]]);
									if(n == 0) n++;

								}

								done = 1;
							} else if(reti == REG_NOMATCH){
								//printf("Failed to match qF\n");
							} else {
								regerror(reti, &qF, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match qF failed!\n");
								exit(1);
							}
						}

						if(!done){
							reti = regexec(&tFTN, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf",
									vertex, textureLarge, normal,
									vertex+1, textureLarge+1, normal+1,
									vertex+2, textureLarge+2, normal+2);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertex[n]], vList->m[1][(int)vertex[n]], vList->m[2][(int)vertex[n]]);
									add_point(t, vtList->m[0][(int)texture[n]], vtList->m[1][(int)texture[n]], currentMatID);

									vTemp[0] = vList->m[0][(int)vertex[n]];
									vTemp[1] = vList->m[1][(int)vertex[n]];
									vTemp[2] = vList->m[2][(int)vertex[n]];

									vnTemp[0] = vnList->m[0][(int)normal[n]];
									vnTemp[1] = vnList->m[1][(int)normal[n]];
									vnTemp[2] = vnList->m[2][(int)normal[n]];

									kd = kdInsert(kd, vTemp, vnTemp);

								}

								done = 1;
							} else if(reti == REG_NOMATCH){
								//printf("Failed to match tFTN\n");
							} else {
								regerror(reti, &tFTN, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match tFTN failed!\n");
								exit(1);
							}
						}

						if(!done){
							reti = regexec(&tFN, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf//%lf %lf//%lf %lf//%lf",
									vertex,normal,
									vertex+1,normal+1,
									vertex+2,normal+2);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertex[n]], vList->m[1][(int)vertex[n]], vList->m[2][(int)vertex[n]]);
									add_point(t, -1, -1, currentMatID);

									vTemp[0] = vList->m[0][(int)vertex[n]];
									vTemp[1] = vList->m[1][(int)vertex[n]];
									vTemp[2] = vList->m[2][(int)vertex[n]];

									vnTemp[0] = vnList->m[0][(int)normal[n]];
									vnTemp[1] = vnList->m[1][(int)normal[n]];
									vnTemp[2] = vnList->m[2][(int)normal[n]];

									kd = kdInsert(kd, vTemp, vnTemp);

								}

								done = 1;
							} else if(reti == REG_NOMATCH){
								//printf("Failed to match tFN\n");
							} else{
								regerror(reti, &tFN, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match tFN failed!\n");
								exit(1);
							}
						}

						if(!done){
							reti = regexec(&tFT, sBuffer, 0, NULL, 0);
							if(!reti){
								sscanf(sBuffer, "%lf/%lf %lf/%lf %lf/%lf",
									vertex, textureLarge,
									vertex+1, textureLarge+1,
									vertex+2, textureLarge+2);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertex[n]], vList->m[1][(int)vertex[n]], vList->m[2][(int)vertex[n]]);
									add_point(t, vtList->m[0][(int)texture[n]], vtList->m[1][(int)texture[n]], currentMatID);
								}

								done = 1;
							} else if(reti == REG_NOMATCH){
								//printf("Failed to match tFT\n");
							} else {
								regerror(reti, &tFT, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match tFT failed!\n");
								exit(1);
							}

							reti = regexec(&tF, sBuffer, 0, NULL, 0);
							if(!done && !reti){
								sscanf(sBuffer, "%lf %lf %lf",
									vertex,
									vertex+1,
									vertex+2);

								for(int n = 0; n < 3; n++){
									add_point(p, vList->m[0][(int)vertex[n]], vList->m[1][(int)vertex[n]], vList->m[2][(int)vertex[n]]);
								}

								done = 1;
							} else if(!done || reti == REG_NOMATCH){
								//printf("Failed to match tF\n");
							} else if(!done){
								regerror(reti, &qFTN, regErrorBuffer, sizeof(regErrorBuffer));
								fprintf(stderr, "Match tF failed!\n");
								exit(1);
							}
						}


					}

				}
				
			}

			
		}

		free_matrix(vList);
		free_matrix(vnList);
	}

	free(buffer);
	fclose(f);

	return kd;
}

void create_materials(char* fileName){

	extern struct material* m;

	FILE* f = fopen(fileName, "r");
	if(f == NULL){
		printf("%s\n", fileName);
		printf("ERROR! MTL file could not be loaded! Check if it actually exists...\n");
		exit(1);
	}

	char* buffer;
	char* sBuffer;
	char* lineType;
	char* currentName;
	struct material* current = NULL;
	char* mapFileName;
	char nameBuffer[256];

	buffer = malloc(BUFFER_SIZE);
	currentName = NULL;

	double valBuffer[3];
	int numBuffer[3];

	while(fgets(buffer, BUFFER_SIZE, f) != NULL){
		//printf("Test\n");
		buffer[strlen(buffer)-1] = '\0';
		sBuffer = strdup(buffer);

		while(sBuffer[0] == ' ' || sBuffer[0] == '\t') strsep(&sBuffer, " \t");


		lineType = strsep(&sBuffer," ");

		if(sBuffer != NULL){
			while(sBuffer[0] == ' ' || sBuffer[0] == '\t') strsep(&sBuffer, " \t");

			if(sBuffer != NULL){

				//printf("%s\n", sBuffer);

				if(currentName != NULL) current=find_material(currentName);

				if(!strcmp(lineType, "newmtl")){
					add_material(sBuffer);
					if(currentName != NULL)free(currentName);
					currentName = strdup(sBuffer);
					//printf("%s\n", currentName);
				}

				if(!strcmp(lineType, "illum")){
					sscanf(sBuffer,"%d",numBuffer);
					current->illum = numBuffer[0];
				}

				if(!strcmp(lineType, "Ka")){
					sscanf(sBuffer,"%lf %lf %lf",valBuffer, valBuffer + 1, valBuffer + 2);
					current->ka[0] = valBuffer[0];
					current->ka[1] = valBuffer[1];
					current->ka[2] = valBuffer[2];
				}

				if(!strcmp(lineType, "Kd")){
					sscanf(sBuffer,"%lf %lf %lf",valBuffer, valBuffer + 1, valBuffer + 2);
					current->kd[0] = valBuffer[0];
					current->kd[1] = valBuffer[1];
					current->kd[2] = valBuffer[2];
				}

				if(!strcmp(lineType, "Ks")){
					sscanf(sBuffer,"%lf %lf %lf",valBuffer, valBuffer + 1, valBuffer + 2);
					current->ks[0] = valBuffer[0];
					current->ks[1] = valBuffer[1];
					current->ks[2] = valBuffer[2];
				}

				if(!strcmp(lineType, "Ns")){
					sscanf(sBuffer, "%lf", valBuffer);
					current->ns = valBuffer[0];
				}

				if(!strcmp(lineType, "map_Kd")){
					mapFileName = strrchr(sBuffer, ' ');
					if(mapFileName != NULL) mapFileName++;
					else {
						mapFileName = sBuffer;
					}
					//printf("%s\n", mapFileName);
					FILE* texture = fopen(mapFileName, "r"); //We'll assume it's a PPM file for now...
					unsigned char colorBuffer[3];

					current->map_kd = strdup(mapFileName);

					fgets(buffer,BUFFER_SIZE, texture);
					//printf("%s\n", buffer);
					fgets(buffer,BUFFER_SIZE, texture);
					//printf("%s\n", buffer);

					sscanf(buffer, "%d %d", numBuffer, numBuffer+1);
					current->map_kd_cols = numBuffer[0];
					current->map_kd_rows = numBuffer[1];

					fgets(buffer, BUFFER_SIZE, texture);

					sscanf(buffer, "%d", numBuffer);
					current->map_kd_colorDepth = numBuffer[0];

					current->map_kd_raw = (color **)malloc(sizeof(color*)*current->map_kd_cols);
					for(int x = 0; x < current->map_kd_cols; x++){
						current->map_kd_raw[x] = (color*)malloc(sizeof(color)*current->map_kd_rows);
					}

					for(int x = 0; x < current->map_kd_cols; x++){
						for(int y = 0; y < current->map_kd_rows; y++){
							fread(colorBuffer, 1, 3, texture);
							current->map_kd_raw[x][y].red = (unsigned char)(255 * (colorBuffer[0]/current->map_kd_colorDepth));
							current->map_kd_raw[x][y].green = (unsigned char)(255 * (colorBuffer[1]/current->map_kd_colorDepth));
							current->map_kd_raw[x][y].blue = (unsigned char)(255 * (colorBuffer[2]/current->map_kd_colorDepth));
						}
					}

					fclose(texture);

				}
			}
		}

		//print_materials();

	}

	free(buffer);
	free(currentName);

	fclose(f);
}
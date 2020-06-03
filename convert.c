#include "convert.h"
#include "ml6.h"
#include "matrix.h"
#include "draw.h"
#include "kdTree.h"
#include "gmath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

struct kdTree* convert(struct matrix* m, char* fileName){
	FILE* f = fopen(fileName,"r");

	char* fileType;
	char* buffer;
	float* binaryVertices;
	float* normalVertices;
	char* sBuffer;
	int vCount = 0;
	double vertices[3];
	double textureCoords[3];
	double vNormals[3];
	double verticesLarge[4];
	double textureCoordsLarge[4];
	double vNormalsLarge[4];
	double vTemp[3];
	double vnTemp[3];
	int bufferPlace = 0;
	int done = 0;

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

					sscanf(sBuffer,"vertex %lf %lf %lf", vertices, vertices+1, vertices+2);

					//printf("%lf %lf %lf\n", vertices[0], vertices[1], vertices[2]);

					add_point(m, vertices[0], vertices[1], vertices[2]);
					kd = kdInsert(kd, vertices, vNormals);

				} else if(sBuffer[0] == 'f'){
					sscanf(sBuffer,"facet normal %lf %lf %lf",vNormals, vNormals+1,vNormals+2);

					//printf("%lf %lf %lf\n", vNormals[0], vNormals[1], vNormals[2]);
				}
				//printf("\n");
			}

		} else { //Binary STL file

			unsigned int tNum;
			short int data;
			normalVertices = malloc(sizeof(float) * 3);
			binaryVertices = malloc(sizeof(float) * 3);

			fread(buffer, sizeof(char), 80, f);
			//printf("Mesh name: %s\n", buffer);

			fread(&tNum, sizeof(unsigned int), 1, f);
			//printf("Number of polygons: %d\n", tNum);

			for(unsigned int n = 0; n < tNum; n++){
				fread(normalVertices, sizeof(float), 3, f);
				vNormals[0] = normalVertices[0];
				vNormals[1] = normalVertices[1];
				vNormals[2] = normalVertices[2];

				for(int o = 0; o < 3; o++){
					fread(binaryVertices, sizeof(float),3,f);
					vertices[0] = (double)binaryVertices[0];
					vertices[1] = (double)binaryVertices[1];
					vertices[2] = (double)binaryVertices[2];

					add_point(m, vertices[0], vertices[1], vertices[2]);
					kd = kdInsert(kd, vertices, vNormals);
					//printf("%lf %lf %lf\n", vertices[0], vertices[1], vertices[2]);
				}

				fread(&data, sizeof(short int), 1, f);

			}

			free(normalVertices);
			free(binaryVertices);

		}
	}

	else if(!strcmp(fileType,"obj")){ //Obj file

		struct matrix* vList = new_matrix(4, 4096);
		struct matrix* vnList = new_matrix(4, 4096);
		add_point(vList, 0, 0, 0);
		add_point(vnList, 0, 0, 0);

		char* lineType;
		char* lengthCheck;
		int spaceNum;

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

					if(!strcmp(lineType,"v")){
						sscanf(sBuffer, "%lf %lf %lf", vertices, vertices+1, vertices+2);
						add_point(vList,vertices[0],vertices[1],vertices[2]);
					}

					else if(!strcmp(lineType, "vn")){
						sscanf(sBuffer, "%lf %lf %lf", vNormals, vNormals + 1, vNormals+2);
						add_point(vnList,vNormals[0],vNormals[1],vNormals[2]);
					}

					else if(!strcmp(lineType,"f")){

						//printf("%s\n", sBuffer);


						reti = regexec(&qFTN, sBuffer, 0, NULL, 0);
						if(!reti){

							sscanf(sBuffer, "%lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf",
								verticesLarge, textureCoordsLarge, vNormalsLarge,
								verticesLarge+1, textureCoordsLarge+1, vNormalsLarge+1,
								verticesLarge+2, textureCoordsLarge+2, vNormalsLarge+2,
								verticesLarge+3, textureCoordsLarge+3, vNormalsLarge+3);

							for(int n = 0; n < 3; n++){
								add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

								vTemp[0] = vList->m[0][(int)verticesLarge[n]];
								vTemp[1] = vList->m[1][(int)verticesLarge[n]];
								vTemp[2] = vList->m[2][(int)verticesLarge[n]];

								vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
								vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
								vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

								//print_vertex(vTemp);
								//print_vertex(vnTemp);
								//printf("\n");

								kd = kdInsert(kd, vTemp, vnTemp);

							}

							for(int n = 0; n < 4; n++){
								add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

								vTemp[0] = vList->m[0][(int)verticesLarge[n]];
								vTemp[1] = vList->m[1][(int)verticesLarge[n]];
								vTemp[2] = vList->m[2][(int)verticesLarge[n]];

								vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
								vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
								vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

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
									verticesLarge, vNormalsLarge,
									verticesLarge+1, vNormalsLarge+1,
									verticesLarge+2, vNormalsLarge+2,
									verticesLarge+3, vNormalsLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

									vTemp[0] = vList->m[0][(int)verticesLarge[n]];
									vTemp[1] = vList->m[1][(int)verticesLarge[n]];
									vTemp[2] = vList->m[2][(int)verticesLarge[n]];

									vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
									vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
									vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

									kd = kdInsert(kd, vTemp, vnTemp);

								}

								for(int n = 0; n < 4; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

									vTemp[0] = vList->m[0][(int)verticesLarge[n]];
									vTemp[1] = vList->m[1][(int)verticesLarge[n]];
									vTemp[2] = vList->m[2][(int)verticesLarge[n]];

									vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
									vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
									vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

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
									verticesLarge, textureCoordsLarge,
									verticesLarge+1, textureCoordsLarge+1,
									verticesLarge+2, textureCoordsLarge+2,
									verticesLarge+3, textureCoordsLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);
								}

								for(int n = 0; n < 4; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);
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
									verticesLarge,
									verticesLarge+1,
									verticesLarge+2,
									verticesLarge+3);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);
								}

								for(int n = 0; n < 4; n++){
									add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);
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
									vertices, textureCoords, vNormals,
									vertices+1, textureCoords+1, vNormals+1,
									vertices+2, textureCoords+2, vNormals+2);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)vertices[n]], vList->m[1][(int)vertices[n]], vList->m[2][(int)vertices[n]]);

									vTemp[0] = vList->m[0][(int)vertices[n]];
									vTemp[1] = vList->m[1][(int)vertices[n]];
									vTemp[2] = vList->m[2][(int)vertices[n]];

									vnTemp[0] = vnList->m[0][(int)vNormals[n]];
									vnTemp[1] = vnList->m[1][(int)vNormals[n]];
									vnTemp[2] = vnList->m[2][(int)vNormals[n]];

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
									vertices,vNormals,
									vertices+1,vNormals+1,
									vertices+2,vNormals+2);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)vertices[n]], vList->m[1][(int)vertices[n]], vList->m[2][(int)vertices[n]]);

									vTemp[0] = vList->m[0][(int)vertices[n]];
									vTemp[1] = vList->m[1][(int)vertices[n]];
									vTemp[2] = vList->m[2][(int)vertices[n]];

									vnTemp[0] = vnList->m[0][(int)vNormals[n]];
									vnTemp[1] = vnList->m[1][(int)vNormals[n]];
									vnTemp[2] = vnList->m[2][(int)vNormals[n]];

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
									vertices, textureCoords,
									vertices+1, textureCoords+1,
									vertices+2, textureCoords+2);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)vertices[n]], vList->m[1][(int)vertices[n]], vList->m[2][(int)vertices[n]]);

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
									vertices,
									vertices+1,
									vertices+2);

								for(int n = 0; n < 3; n++){
									add_point(m, vList->m[0][(int)vertices[n]], vList->m[1][(int)vertices[n]], vList->m[2][(int)vertices[n]]);
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
						

						

						// spaceNum = 0;

						// lengthCheck = strdup(sBuffer);
						// while(*lengthCheck != '\0'){
						// 	if(*lengthCheck == ' ') spaceNum++;
						// 	lengthCheck++;
						// }

						// if(spaceNum == 2){ //Triangle
						// 	sscanf(sBuffer, "%lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf",
						// 		vertices, textureCoords, vNormals,
						// 		vertices+1, textureCoords+1, vNormals+1,
						// 		vertices+2, textureCoords+2, vNormals+2);

						// 	for(int n = 0; n < 3; n++){
						// 		add_point(m, vList->m[0][(int)vertices[n]], vList->m[1][(int)vertices[n]], vList->m[2][(int)vertices[n]]);

						// 		vTemp[0] = vList->m[0][(int)vertices[n]];
						// 		vTemp[1] = vList->m[1][(int)vertices[n]];
						// 		vTemp[2] = vList->m[2][(int)vertices[n]];

						// 		vnTemp[0] = vnList->m[0][(int)vNormals[n]];
						// 		vnTemp[1] = vnList->m[1][(int)vNormals[n]];
						// 		vnTemp[2] = vnList->m[2][(int)vNormals[n]];

						// 		kd = kdInsert(kd, vTemp, vnTemp);

						// 	}

						// } else { //Rectangle
						// 	sscanf(sBuffer, "%lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf %lf/%lf/%lf",
						// 		verticesLarge, textureCoordsLarge, vNormalsLarge,
						// 		verticesLarge+1, textureCoordsLarge+1, vNormalsLarge+1,
						// 		verticesLarge+2, textureCoordsLarge+2, vNormalsLarge+2,
						// 		verticesLarge+3, textureCoordsLarge+3, vNormalsLarge+3);

						// 	for(int n = 0; n < 3; n++){
						// 		add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

						// 		vTemp[0] = vList->m[0][(int)verticesLarge[n]];
						// 		vTemp[1] = vList->m[1][(int)verticesLarge[n]];
						// 		vTemp[2] = vList->m[2][(int)verticesLarge[n]];

						// 		vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
						// 		vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
						// 		vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

						// 		kd = kdInsert(kd, vTemp, vnTemp);

						// 	}

						// 	for(int n = 0; n < 4; n++){
						// 		add_point(m, vList->m[0][(int)verticesLarge[n]], vList->m[1][(int)verticesLarge[n]], vList->m[2][(int)verticesLarge[n]]);

						// 		vTemp[0] = vList->m[0][(int)verticesLarge[n]];
						// 		vTemp[1] = vList->m[1][(int)verticesLarge[n]];
						// 		vTemp[2] = vList->m[2][(int)verticesLarge[n]];

						// 		vnTemp[0] = vnList->m[0][(int)vNormalsLarge[n]];
						// 		vnTemp[1] = vnList->m[1][(int)vNormalsLarge[n]];
						// 		vnTemp[2] = vnList->m[2][(int)vNormalsLarge[n]];

						// 		kd = kdInsert(kd, vTemp, vnTemp);
						// 		if(n == 0) n++;

						// 	}

						// 	// add_point(m, vList->m[0][(int)verticesLarge[0]], vList->m[1][(int)verticesLarge[0]], vList->m[2][(int)verticesLarge[0]]);
						// 	// add_point(m, vList->m[0][(int)verticesLarge[1]], vList->m[1][(int)verticesLarge[1]], vList->m[2][(int)verticesLarge[1]]);
						// 	// add_point(m, vList->m[0][(int)verticesLarge[2]], vList->m[1][(int)verticesLarge[2]], vList->m[2][(int)verticesLarge[2]]);

						// 	// add_point(m, vList->m[0][(int)verticesLarge[0]], vList->m[1][(int)verticesLarge[0]], vList->m[2][(int)verticesLarge[0]]);
						// 	// add_point(m, vList->m[0][(int)verticesLarge[2]], vList->m[1][(int)verticesLarge[2]], vList->m[2][(int)verticesLarge[2]]);
						// 	// add_point(m, vList->m[0][(int)verticesLarge[3]], vList->m[1][(int)verticesLarge[3]], vList->m[2][(int)verticesLarge[3]]);
						// }


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
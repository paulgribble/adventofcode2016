#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y, z;
	int xd, yd, zd;
	int pot, kin, tot;
} planet;

planet *newPlanet(int x, int y, int z) {
	planet *P = malloc(sizeof(planet));
	P->x = x;
	P->y = y;
	P->z = z;
	P->xd = 0;
	P->yd = 0;
	P->zd = 0;
	P->pot = 0;
	P->kin = 0;
	P->tot = 0;
	return(P);
}

void applyGravity(planet *A, planet *B) {
	if (A->x > B->x) {
		A->xd -=1;
		B->xd +=1;
	}
	else if (A->x < B->x) {
		A->xd +=1;
		B->xd -=1;
	}
	if (A->y > B->y) {
		A->yd -=1;
		B->yd +=1;
	}
	else if (A->y < B->y) {
		A->yd +=1;
		B->yd -=1;
	}
	if (A->z > B->z) {
		A->zd -=1;
		B->zd +=1;
	}
	else if (A->z < B->z) {
		A->zd +=1;
		B->zd -=1;
	}
}

void applyVelocity(planet *P) {
	P->x += P->xd;
	P->y += P->yd;
	P->z += P->zd;
}

void computeEnergy(planet *P) {
	P->pot = abs(P->x) + abs(P->y) + abs(P->z);
	P->kin = abs(P->xd) + abs(P->yd) + abs(P->zd);
	P->tot = P->pot * P->kin;
}

void debug(planet *P) {
	printf("%3d %3d %3d %3d %3d %3d %3d %3d %3d\n", 
		P->x, P->y, P->z, P->xd, P->yd, P->zd, P->pot, P->kin, P->tot);
}

int stateIsEqual(planet *A, planet *B) {
	return((A->x==B->x) & (A->y==B->y) & (A->z==B->z) &
		   (A->xd==B->xd) & (A->yd==B->yd) & (A->zd==B->zd));
}

long int gcd(long int a, long int b) 
{
  if (b == 0) {
  	return a;
  }
  else {
    return gcd(b, a % b);
  }
}

long int lcm(long int a, long int b) {
	if ((a==0) || (b==0)) {
		return(0);
	}
	else {
		return((a*b)/gcd(a,b));
	}
}

int main(int argc, char *argv[]) {

	planet *I = newPlanet( -3,  10, -1);
	planet *I0 = newPlanet( -3,  10, -1);
	planet *E = newPlanet(-12, -10, -5);
	planet *E0 = newPlanet(-12, -10, -5);
	planet *G = newPlanet( -9,   0, 10);
	planet *G0 = newPlanet( -9,   0, 10);
	planet *C = newPlanet(  7,  -5, -3);
	planet *C0 = newPlanet(  7,  -5, -3);

	// debug(I); debug(E); debug(G); debug(C);
	long int i=0;
	long int matchX = 0; int matchY = 0; int matchZ = 0;
	long int done = matchX && matchY && matchZ;
	while (done==0) {
		applyGravity(I,E);
		applyGravity(I,G);
		applyGravity(I,C);
		applyGravity(E,G);
		applyGravity(E,C);
		applyGravity(G,C);
		applyVelocity(I);
		applyVelocity(E);
		applyVelocity(G);
		applyVelocity(C);
		computeEnergy(I);
		computeEnergy(E);
		computeEnergy(G);
		computeEnergy(C);
		// printf("-----------------------------------\n");
		// debug(I); debug(E); debug(G); debug(C);
		if (i==999) {
			int total_energy = I->tot + E->tot + G->tot + C->tot;
			printf("Part 1: answer is %d\n", total_energy);
		}
		if ((I->x == I0->x) && (I->xd == I0->xd) &&
			(E->x == E0->x) && (E->xd == E0->xd) && 
			(G->x == G0->x) && (G->xd == G0->xd) && 
			(C->x == C0->x) && (C->xd == C0->xd)) {
			if (matchX==0) {
				printf("matchX: i=%ld\n", i);
				matchX = i+1;
			}
		}
		if ((I->y == I0->y) && (I->yd == I0->yd) &&
			(E->y == E0->y) && (E->yd == E0->yd) && 
			(G->y == G0->y) && (G->yd == G0->yd) && 
			(C->y == C0->y) && (C->yd == C0->yd)) {
			if (matchY==0) {
				printf("matchY: i=%ld\n", i);
				matchY = i+1;
			}
		}
		if ((I->z == I0->z) && (I->zd == I0->zd) &&
			(E->z == E0->z) && (E->zd == E0->zd) && 
			(G->z == G0->z) && (G->zd == G0->zd) && 
			(C->z == C0->z) && (C->zd == C0->zd)) {
			if (matchZ==0) {
				printf("matchZ: i=%ld\n", i);
				matchZ = i+1;
			}
		}
		if (matchX && matchY && matchZ) {
			done = 1;
		}
		else {
			i += 1;
		}
	}

	long int tmp = (matchX*matchY)/gcd(matchX,matchY);
	long int lcm = (tmp*matchZ)/gcd(tmp,matchZ);
	printf("Part 2: answer is %ld\n", lcm);

	free(I); free(E); free(G); free(C);
	free(I0); free(E0); free(G0); free(C0);
	return 0;
}


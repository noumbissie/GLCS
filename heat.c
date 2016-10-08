#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

#define VAL2D(arr, xx, yy) (arr[(xx)+width*(yy)])

void init(double* dat, int width, int height, int px, int py)
{
	py = py; // prevent unused warning
	for (int yy=0; yy<height; ++yy) {
		for(int xx=0; xx<width; ++xx) {
			VAL2D(dat,xx,yy) = 0;
		}
	}
	if ( px == 0 ) {
		for (int yy=0; yy<height; ++yy) {
			VAL2D(dat,0,yy) = 1000000;
		}
	}
}

void iter(double* cur, double* next, int width, int height)
{
	int xx, yy;
	for(xx=0; xx<width; ++xx) {
		VAL2D(next,xx,0) = VAL2D(cur,xx,0);
	}
	for (yy=1; yy<height-1; ++yy) {
		VAL2D(next,0,yy) = VAL2D(cur,0,yy);
		for(xx=1; xx<width-1; ++xx) {
			VAL2D(next,xx,yy) =
					  (VAL2D(cur,xx,yy)   *.5)
					+ (VAL2D(cur,xx-1,yy) *.125)
					+ (VAL2D(cur,xx+1,yy) *.125)
					+ (VAL2D(cur,xx,yy-1) *.125)
					+ (VAL2D(cur,xx,yy+1) *.125);
		}
		VAL2D(next,width-1,yy) = VAL2D(cur,width-1,yy);
	}
	for(xx=0; xx<width; ++xx) {
		VAL2D(next,xx,height-1) = VAL2D(cur,xx,height-1);
	}
}


void exchange(MPI_Comm cart_com, double *cur, int width, int height)
{
	MPI_Status status;
	int rank_source, rank_dest;
	static MPI_Datatype column, row;
	static int initialized = 0;
	
	if ( !initialized ) {
		MPI_Type_vector(height-2, 1, width, MPI_DOUBLE, &column);
		MPI_Type_commit(&column);
		MPI_Type_contiguous(width-2, MPI_DOUBLE, &row);
		MPI_Type_commit(&row);
		initialized = 1;
	}
	
	
	/* send to the right */
	MPI_Cart_shift(cart_com, 0, 1, &rank_source, &rank_dest);
	MPI_Sendrecv(&VAL2D(cur, width-2, 1), 1, column, rank_dest,   100, /* send column before ghost */ 
	             &VAL2D(cur, 0,       1), 1, column, rank_source, 100, /* receive 1st column (ghost) */
	             cart_com, &status);

	/* send to the left */
	MPI_Cart_shift(cart_com, 0, -1, &rank_source, &rank_dest);
	MPI_Sendrecv(&VAL2D(cur, 1,       1), 1, column, rank_dest,   100, /* send column after ghost */
	             &VAL2D(cur, width-1, 1), 1, column, rank_source, 100, /* receive last column (ghost) */
	             cart_com, &status);

	/* send down */
	MPI_Cart_shift(cart_com, 1, 1, &rank_source, &rank_dest);
	MPI_Sendrecv(&VAL2D(cur, 1, height-2), 1, row, rank_dest,   100, /* send row before ghost */
	             &VAL2D(cur, 1, 0       ), 1, row, rank_source, 100, /* receive 1st row (ghost) */
	             cart_com, &status);

	/* send up */
	MPI_Cart_shift(cart_com, 1, -1, &rank_source, &rank_dest);
	MPI_Sendrecv(&VAL2D(cur, 1, 1       ), 1, row, rank_dest,   100, /* send column after ghost */
	             &VAL2D(cur, 1, height-1), 1, row, rank_source, 100, /* receive last column (ghost) */
	             cart_com, &status);
}

//premier commentaire de test


int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	
	if ( argc != 4 ) {
		printf("Usage: %s <Nb_iter> <height> <width>\n", argv[0]);
		exit(1);
	}
	
	int size; MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int pwidth = sqrt(size);
	if ( ! pwidth ) pwidth=1; 
	int pheight = size/pwidth;
	assert(pwidth * pheight == size);
	
	int nb_iter = atoi(argv[1]);
	int height = atoi(argv[2]);
	int width = atoi(argv[3]);
	
	// get local & add ghosts to sizes
	assert(width %pwidth ==0); width  = width /pwidth  + 2;
	assert(height%pheight==0); height = height/pheight + 2;
	assert(pwidth*pheight == size);
	
	int cart_dims[2] = { pwidth, pheight };
	int cart_period[2] = { 0, 0 };
	MPI_Comm cart_com; MPI_Cart_create(MPI_COMM_WORLD, 2, cart_dims, cart_period, 1, &cart_com);
	int car_coord[2]; MPI_Cart_coords(cart_com, rank, 2, car_coord);

	double *cur = malloc(sizeof(double)*width*height);
	double *next = malloc(sizeof(double)*width*height);

	
	init(cur, width, height, car_coord[0], car_coord[1]);
	
       printf("i am there, do you see me? \n");

	int ii;	
	
	for(ii=0; ii<nb_iter; ++ii) {
		iter(cur, next, width, height);
		exchange(cart_com, next, width, height);
		double *tmp = cur; cur = next; next = tmp;
	}
	
	free(cur);
	free(next);

	MPI_Finalize();
	return 0;
}

#include <mpi.h>
#include <cstdio>
#include <cstdlib>


void print_status(unsigned int msg, int rank)
{
  printf("Rank = %d\nCurrent msg = %d\n", rank, msg);
}

void do_zero(unsigned int msg, unsigned int commsize)
{
  print_status(msg, 0);
  unsigned int dst = 1, from = commsize - 1;
  if (commsize == 1)
  {
    dst = 0;
    from = 0;
  }

  MPI::COMM_WORLD.Send(&msg, 1, MPI::UNSIGNED, dst, 0);

  MPI::COMM_WORLD.Recv(&msg, 1, MPI::UNSIGNED, from, 0);
  print_status(++msg, 0);
}

void ring_msg(unsigned int msg, int rank, unsigned int commsize)
{
  if (rank == 0)
  {
    do_zero(msg, commsize);
    return;
  }

  unsigned int from_rank = rank - 1;
  unsigned int to_rank = (unsigned int)rank == commsize - 1 ? 0 : rank + 1;
  unsigned int cur_msg = 0;
  MPI::COMM_WORLD.Recv(&cur_msg, 1, MPI::UNSIGNED, from_rank, 0);

  print_status(++cur_msg, rank);

  MPI::COMM_WORLD.Send(&cur_msg, 1, MPI::UNSIGNED, to_rank, 0);
}

int main( int argc, char *argv[] )
{
  MPI::Init(argc, argv);
  std::setbuf(stdout, nullptr);

  ring_msg(0, MPI::COMM_WORLD.Get_rank(), MPI::COMM_WORLD.Get_size());

  MPI::Finalize();
}
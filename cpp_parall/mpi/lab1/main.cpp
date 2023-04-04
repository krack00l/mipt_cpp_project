#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <mpi.h>
#include <string>
#include <vector>

constexpr std::size_t ISIZE = 5000;
constexpr std::size_t JSIZE = 5000;

using ArrayType = std::vector<std::vector<double>>;
using Dumper = std::function<void(const ArrayType &, std::ostream &)>;
using ProcFunc = std::function<void(ArrayType &)>;

void outputArray(const ArrayType &arr, std::ostream &ost)
{
    for (auto &&row : arr)
    {
        for (auto elem : row)
            ost << elem << " ";
        ost << std::endl;
    }
}

void ethalon(ArrayType &arr)
{
    auto rank = MPI::COMM_WORLD.Get_rank();
    auto commsize = MPI::COMM_WORLD.Get_size();

    for (std::size_t i = rank; i < ISIZE; i += commsize)
        for (std::size_t j = 0; j < JSIZE; j++)
            arr[i][j] = std::sin(2 * arr[i][j]);

    for (std::size_t i = rank; i < ISIZE; i += commsize)
    {
        if (rank != 0)
        {
            MPI::COMM_WORLD.Send(arr[i].data(), ISIZE, MPI::DOUBLE, 0, static_cast<int>(i));
            continue;
        }

        for (std::size_t id = 1; static_cast<int>(id) < commsize; ++id)
            if (i + id < ISIZE)
                MPI::COMM_WORLD.Recv(arr[i + id].data(), ISIZE, MPI::DOUBLE, id, static_cast<int>(i + id));
    }
}

void processArr(ArrayType &arr)
{
    for (std::size_t i = 1; i < ISIZE; i++)
        for (std::size_t j = 3; j < JSIZE - 1; j++)
            arr[i][j] = std::sin(2 * arr[i - 1][j - 3]);
}


void processArrPar(ArrayType &arr)
{
    auto rank = MPI::COMM_WORLD.Get_rank();
    auto commsize = MPI::COMM_WORLD.Get_size();

    constexpr auto JSIZE_USED = JSIZE - 4;

    for (std::size_t i = rank; i < JSIZE_USED; i += commsize)
        for (std::size_t j = 0; j < ISIZE - 1; j++)
            arr[i + 3][j + 1] = std::sin(2 * arr[i][j]);

    for (std::size_t i = rank; i < JSIZE_USED; i += commsize)
    {
        auto idx = i + 3;
        if (rank != 0)
        {
            MPI::COMM_WORLD.Send(arr[idx].data() + 1, ISIZE - 1, MPI::DOUBLE, 0, static_cast<int>(idx));
            continue;
        }

        for (std::size_t id = 1; static_cast<int>(id) < commsize; ++id)
            if (i + id < JSIZE_USED)
                MPI::COMM_WORLD.Recv(arr[idx + id].data() + 1, ISIZE - 1, MPI::DOUBLE, id, static_cast<int>(idx + id));
    }
}

void measureDump(ProcFunc f, ArrayType &arr, std::string_view filename,
                                 Dumper dumper)
{
    auto rank = MPI::COMM_WORLD.Get_rank();
    MPI::COMM_WORLD.Barrier();
    auto tic = MPI::Wtime();
    f(arr);
    MPI::COMM_WORLD.Barrier();
    auto toc = MPI::Wtime();

    if (rank != 0)
    {
        arr.clear();
        return;
    }

    std::cout << "Elapsed time " << (toc - tic) * 1000 << " ms" << std::endl;

    std::ofstream of(filename.data());
    if (!of)
    {
        std::cerr << "Cannot open file for results" << std::endl;
        return;
    }
    dumper(arr, of);
}

void initArr(ArrayType &a)
{
    a.resize(ISIZE);
    // Fill array with data
    for (std::size_t i = 0; i < a.size(); i++)
    {
        auto &ai = a[i];
        ai.resize(JSIZE);
        for (std::size_t j = 0; j < ai.size(); j++)
            ai[j] = 10 * i + j;
    }
}

void InitializationArr(ArrayType &a)
{
    a.resize(JSIZE);
    // Fill array with data
    for (std::size_t j = 0; j < a.size(); j++)
    {
        auto &aj = a[j];
        aj.resize(ISIZE);
        for (std::size_t i = 0; i < aj.size(); i++)
            aj[i] = 10 * i + j;
    }
}

void printTArr(const ArrayType &a, std::ostream &ost)
{
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        for (std::size_t j = 0; j < a[i].size(); ++j)
            ost << a[j][i] << " ";
        ost << std::endl;
    }
}

void doSeq()
{
    ArrayType a{};
    initArr(a);

    std::cout << "Sequential:" << std::endl;
    measureDump(processArr, a, "seq.txt", outputArray);
}

void doPar()
{
    ArrayType a{};
    InitializationArr(a);

    if (MPI::COMM_WORLD.Get_rank() == 0)
        std::cout << "Parallel:" << std::endl;
    measureDump(processArrPar, a, "par.txt", printTArr);
}

void doEth()
{
    ArrayType a{};
    initArr(a);

    if (MPI::COMM_WORLD.Get_rank() == 0)
        std::cout << "Ethalon:" << std::endl;
    measureDump(ethalon, a, "eth.txt", outputArray);
}

int main(int argc, char *argv[])
{
    MPI::Init(argc, argv);
    auto commsz = MPI::COMM_WORLD.Get_size();

    if (commsz == 1)
        doSeq();
    else if (commsz == 3)
        doPar(), doEth();
    else if (MPI::COMM_WORLD.Get_rank() == 0)
        std::cerr << "Commsize is not right " << commsz << " (required 3)" << std::endl;

    MPI::Finalize();
}

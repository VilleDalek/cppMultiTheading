#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

#include <boost/thread.hpp>
#include <boost/timer.hpp>

typedef unsigned int uint;


struct Vector {
    float x, y, z;

    Vector() : x(0.f), y(0.f), z(0.f) {}

    float len() {
        return sqrtf(x*x + y*y + z*z);
    }

};


float norm(int a) {
    return float((a % 10) + 1) / 10.f;
}


void genVectors(std::vector<Vector>& examples) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    
    srand(t.tv_nsec);

    for (uint i = 0; i < examples.size(); ++i) {
        examples[i].x = norm(rand());
        examples[i].y = norm(rand());
        examples[i].z = norm(rand());
    }

}

typedef std::vector<Vector> Data;
typedef Data::iterator DataIter;

typedef std::vector<float> Result;
typedef Result::iterator ResultIter;


struct Worker {
    Data   data;
    Result result;

    Worker(DataIter& dataStart,
           const DataIter& dataEnd,
           ResultIter& resultStart,
           ResultIter& resultEnd) : data(dataStart, dataEnd), result(resultStart, resultEnd) {
        assert(data.size() == result.size());
    }

    void operator()() {
        DataIter di = data.begin();
        ResultIter ri = result.begin();

        const DataIter dend = data.end();

        for (; di != dend; ++di, ++ri) {
            *ri = di->len();
        }
    }
};


int main(int argc, char **argv) {
    const uint numThreads = 4;
    const uint seqLen = 13107200;

    std::vector<Vector> a;
    a.resize(seqLen);

    genVectors(a);  

    std::vector<float> singleThreadResult(a.size());
    assert(a.size() == singleThreadResult.size());

    boost::timer singleThreadTimer;
    for (uint i = 0; i < a.size(); ++i) {
        singleThreadResult[i] = a[i].len();
    }
    double singleThreadTime = singleThreadTimer.elapsed();

    std::vector<float> multiThreadResult(a.size());

    Worker* workers[numThreads];
    for (uint i = 0; i < numThreads; ++i) {
        uint chunkSize = seqLen / numThreads;
        assert(numThreads * chunkSize == seqLen);
        DataIter a1 = a.begin() + i * chunkSize;
        DataIter a2 = a.begin() + (i + 1) * chunkSize;
        ResultIter mTR1 = multiThreadResult.begin() + i * chunkSize;
        ResultIter mTR2 = multiThreadResult.begin() + (i+1)*chunkSize;

        workers[i] = new Worker(a1,
                                a2,
                                mTR1,
                                mTR2);
    }

    boost::timer multiThreadTimer;
    boost::thread_group threads;
    for (uint i = 0; i < numThreads; ++i) {
        threads.create_thread(boost::ref(*workers[i]));
    }
    threads.join_all();
    double multiThreadTime = multiThreadTimer.elapsed();

    using namespace std;
    cout << "Single thread time: " << singleThreadTime << endl;
    cout << numThreads << " threads time: " << multiThreadTime << endl;

    return 0;
}

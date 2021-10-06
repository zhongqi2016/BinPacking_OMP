#include "Algorithm.h"


using namespace std;


vector<string> readFileDir(const string &PATH) {
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(PATH.c_str());
    vector<string> files;
    while ((ptr = readdir(dir)) != nullptr) {
        if (ptr->d_name[0] == '.')
            continue;
//        printf("%s\n", ptr->d_name);
        files.emplace_back(ptr->d_name);
    }
    return files;
}

DataInput getData(const string &filename) {
    int n, c;
    vector<int> items;

    ifstream infile(filename);
    string line;

    getline(infile, line);
    istringstream iss_n(line);
    iss_n >> n;
    getline(infile, line);
    istringstream iss_c(line);
    iss_c >> c;

    items.reserve(n);

    while (getline(infile, line)) {
        int num;
        istringstream iss(line);
        iss >> num;
        items.emplace_back(num);
    }
    infile.close();

    return DataInput(n, c, items);
}


int main() {
    //The folder where the test sample is located
    string path = "./bin1data/";
    //The number of threads to be tested
    array<int, 5> threads = {1, 2, 4, 8, 16};

    printf("Filename    ");
    for (int th:threads) {
        printf("    Time%d",th);
    }
    printf("  Result\n");

    vector<string> files = readFileDir(path);
    for (int i = 0; i < files.size(); ++i) {
        int result=-1;
        printf("%s", files[i].c_str());
        for (int th:threads) {
            omp_set_num_threads(th);
//
            string fileName = path;
            fileName.append(files[i]);
            DataInput data = getData(fileName);
            double start, end;
            start = omp_get_wtime();

            int res = BNB(data);
            end = omp_get_wtime();
            if (result==-1){
                result=res;
            } else if(result!=res){
                printf(" error");
            }
            double time = (double) (end - start);
            printf(" %lf", time);
        }
        printf(" %d\n",result);
    }

    return 0;
}

#include <bits/stdc++.h>

#include <cmath>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void cpu() {
	const double MAX = 105000000;
	double seno = 0, coseno = 0, tangente = 0, logaritmo = 0, raizCuadrada = 0;
	for (double i = 1; i < MAX; ++i) {
		seno += sin(i);
		coseno += cos(i);
		tangente += tan(i);
		logaritmo += log(i);
		raizCuadrada += sqrt(i);
	}
}

// -------------------------------------------------------------------------------------------------
string random_sequence(const int &word_count, const int &word_length, const string &separator=" ") {
    const int n = word_count * (word_length + separator.size());
    string ans;
    ans.reserve(n);
    random_device rd;
    default_random_engine generator(rd()); // rd() provides a random seed
    uniform_int_distribution<int> distribution((int) 'A', (int) 'Z');
    for (int i = 0; i < word_count; ++i) {
        string word;
        word.resize(word_length);
        for (int j = 0; j < word_length; ++j) {
            const char c = (char) distribution(generator); 
            word[j] = c;
        }
        ans += word + separator;
    }
    return ans;
}

// |source| mod substr_length must be 0
void create_random_file(const char *source, const char* &filename, const int &substr_length) {
    int destino;
    if ((destino = open(filename, O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1) {
        perror(filename);
        exit(-1);
    }
    const int src_len = strlen(source);
    int i;
    cout << "empezando a escribir\n";
    for (i = 0; i < src_len - substr_length; i += substr_length) {
        write(destino, source + i, substr_length);
    }
    cout << "escritura completada\n";
    write(destino, source + i, src_len % substr_length);
    fsync(destino);
    close(destino);
}

void dd(const char *filename) {
    const int word_count = 26*26*26*100;
    const int word_length = 3; 
    const string separator = " ";
    string sequence = random_sequence(word_count, word_length, separator);
    cout << "Sequencia generada\n";
    const int buff_size = 1;
    create_random_file(sequence.c_str(), filename, buff_size);
    cout << endl;
}


// ---------------------------------------------------------------------
#define numeroElementos 100000000
#define RAM_COUNT 400000000

void ram() {
    int *arreglo, i;
    arreglo = new int[numeroElementos];
    for(i = 0; i < numeroElementos; i++)
        arreglo[i] = 0;
    for(i = 0; i < RAM_COUNT; i++){
        arreglo[rand() % numeroElementos] = rand();
        if (i % 10000000 == 0) cout << i << "/" << RAM_COUNT << endl;
    }
}


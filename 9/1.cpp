#include <bits/stdc++.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;


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
    for (i = 0; i < src_len - substr_length; i += substr_length) {
        write(destino, source + i, substr_length);
        cout << i << "/" << src_len << "  ";
    }
    write(destino, source + i, src_len % substr_length);
    fsync(destino);
    close(destino);
}

int main() {
    const int word_count = 26*26*26*100;
    const int word_length = 3; 
    const string separator = " ";
    string sequence = random_sequence(word_count, word_length, separator);
    cout << sequence << endl;
    const char* filename = "output.txt";
    const int buff_size = BUFSIZ;
    create_random_file(sequence.c_str(), filename, buff_size);
    cout << endl;
    return 0;
}

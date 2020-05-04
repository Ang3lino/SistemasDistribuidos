
#include "reg_util.h"


void print_structure(void *ptr, int size) {
	write(1, ptr, size);
	puts("");
}

inline unique_ptr<FILE, int(*)(FILE*) > 
fopen_smart(const char *fname, const char *mode) {
	return unique_ptr<FILE, int(*)(FILE*) >(fopen(fname, mode), &fclose);
}

inline int file_descriptor(FILE *fp) {
	return fileno(fp);
}

void 
alter_reg_in_file(const char *fname, const char *mode, registro &r) {
	auto fp = fopen_smart(fname, mode);
	fwrite (&r, sizeof(registro), 1, fp.get()); 
}

void 
alter_regs_in_file(const char *fname, const char *mode, vector<registro > &regs) 
{
	auto fp = fopen_smart(fname, mode);
	int fd = file_descriptor(fp.get());
	for (auto &reg: regs) {
		write(fd, &reg, sizeof(reg));
	}
}

void save_registers(const char *fname, vector<struct registro > &registers) {
	//Aleatoriza el vector de registros e imprime el resultado
	random_shuffle(registers.begin(), registers.end());
	alter_regs_in_file(fname, "w", registers);
}

registro read_first_register(const char *fname) {
	auto fp = fopen_smart(fname, "r");
	int fd = fileno(fp.get());
	registro reg{};
	read(fd, &reg, sizeof(reg));
	return reg;
}

vector<registro > read_registers(const char *fname, const int n) {
	auto fp = fopen_smart(fname, "r");
	int fd = fileno(fp.get());
	vector<registro > registros;
	registros.resize(n);
	registro reg{};
	for (int i = n - 1; i >= 0; --i) {
		read(fd, &reg, sizeof(reg));
		registros[i] = reg;	
	}
	return registros;
}

vector<struct registro > get_random_registers(int n) {
	char telefono[11], curp[19], sexo;
    vector<struct registro> registros_vector; 
	struct registro reg1;

	registros_vector.resize(n);
	// Genera un numeros telefonicos inicial de 9 digitos y despues se obtendran su secuenciales para evitar repeticion
	int inicial = 500000000 + rand()%100000000;

	// Crea todos los registros con numero de telefono consecutivo y los almacena en un vector
	for (int j = n - 1, i; j >= 0; --j) {
		sprintf(telefono, "5%9d", inicial);
		inicial++;
		strcpy(reg1.celular, telefono);
		sexo = (rand()%2 == 0) ? 77: 72;
		i = rand() % 32;
		sprintf(curp, "%c%c%c%c%c%c%c%c%c%c%c%s%c%c%c%c%c", 65 + rand()%25 , 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, rand()%10 + 48, 
			sexo, entidad[i], 65 + rand()%25, 65 + rand()%25, 65 + rand()%25, rand()%10 + 48, rand()%10 + 48);
		strcpy(reg1.CURP, curp);
		i = rand() % 9;
		strcpy(reg1.partido, partidos[i]);
		registros_vector[j] = reg1;
	}
	return registros_vector;
}

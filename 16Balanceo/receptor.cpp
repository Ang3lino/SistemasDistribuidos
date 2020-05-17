
// Author: Angel Manriquez


#include <bits/stdc++.h>

#include "./lib/MulticastSocket.h"
#include "./lib/Reply.h"
#include "./lib/reg_util.h"
#include "./lib/dbase.h"

using namespace std;


template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}


// https://stackoverflow.com/questions/1195675/convert-a-char-to-stdstring
string timestamp_to_str(timeval tv) {
	// struct timeval tv;
	time_t nowtime;
	struct tm *nowtm;
	char tmbuf[64];
	char buf[64];

	// gettimeofday(&tv, NULL);
	nowtime = tv.tv_sec;
	nowtm = localtime(&nowtime);
	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
	snprintf(buf, sizeof buf, "%s.%06ld", tmbuf, tv.tv_usec);
	string result(buf);
	return result;
}

void insert_reg(sqlite3 *db, registro &reg) {
	string timestamp = timestamp_to_str(reg.timestamp);
	cout << timestamp << endl;
	string query = string_format(  
		"INSERT INTO registro(celular, partido, curp, timestamp)"
		"VALUES ('%s', '%s', '%s', '%s');", 
		reg.celular, reg.partido, reg.CURP, timestamp.c_str());
	cout << query << endl;
	db_query(db, query);
}

void select_all_registers(sqlite3 *db) {
	ResultSet rset = db_query_values(db, "SELECT * FROM registro; ");
	rset.print();
}

void parse_args(int argc, char *argv[], string &multicast, 
		int &port, int &a, int &b, char **fname) {
	if (argc != 6) {
		printf("[%s] [MULTICAST] [PORT] [a] [b] [fname]\n", argv[0]);
		exit(1);
	} 
	multicast = argv[1];
	port = atoi(argv[2]);
	a = atoi(argv[3]);
	b = atoi(argv[4]);
	*fname = argv[5];
}

int main(int argc, char *argv[]) {
	Reply replier;
	string multicast_ip = "224.0.0.0";
	int port = 7777;
	int a = 0, b = 3;
	char *fname = (char *) ":memory:";
	parse_args(argc, argv, multicast_ip, port, a, b, &fname);
	sqlite3 *db = db_open(fname);
	string db_definition = str_from_file("db.sql");
	db_query(db, db_definition);

	MulticastSocket msock(port);
	msock.joinGroup(0, multicast_ip); 
	cout << "Esperando la primer solicitud" << endl;
	while (true) {
		Message *msg = replier.processRequest(msock);
		if (msg == nullptr) {
			cout << "Solicitud repetida.\n";
		} else {
			registro reg = *(registro *) msg->arguments;	
			cout << *msg << endl;
			char c = reg.celular[9] - '0';
			cout << c << endl;
			if (a <= c && c <= b) {
				cout << "Ejecutando consulta :D" << endl;
				insert_reg(db, reg);
			}
			select_all_registers(db);
		}
	}	

	return 0;
}

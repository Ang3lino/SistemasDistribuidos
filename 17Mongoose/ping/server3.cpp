#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>


using namespace std;


static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

#include "./lib/MulticastSocket.h"
#include "./lib/Request.h"
vector<pair<string, int64_t > > 
ping(MulticastSocket &msock, string multicast_ip, int receptors) 
{
    int port = 7777; 
    Request request(multicast_ip, port);
    int _; // not used
    auto response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    response_multicast = request.doOperationMulticast( 
            OperationId::PING, (char *) &_, sizeof(int), receptors);
    return response_multicast;
}

static void handle_size(struct mg_connection *nc, struct http_message *hm) {
	MulticastSocket msock;
	char key[256]; // here we'll store the multicast ip
	strncpy(key, hm->body.p, hm->body.len);
	auto ip_time_vec = ping(msock, string(key), 2); // Ping each server, obtain ip -> ms vector
    // nc->flags |= MG_F_SEND_AND_CLOSE;

	// build the JSON string
	string res = "{\n \"ipList\": [";
	for (unsigned i = 0; i < ip_time_vec.size(); ++i) {
		if (i) res += ", ";
		res += "\"" + ip_time_vec[i].first + "\"";
	}
	res += "], \"timeList\": [";
	for (unsigned i = 0; i < ip_time_vec.size(); ++i) {
		if (i) res += ", ";
		res += "\"" + to_string(ip_time_vec[i].second) + "\"";
	}
	res += "] }";
	// configure headers to send JSON
	mg_printf(nc, "%s",
			"HTTP/1.1 200 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Content-Type: application/json\r\n"
			"Transfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, res.c_str()); // body
	mg_send_http_chunk(nc, "", 0); // flush ?

}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
 	struct http_message *hm = (struct http_message *) p;

	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) { // localhost:port//search requested
			// mg_get_http_var(&hm->body, "query", query,sizeof(query));
			// printf("Cadena introducida: %s\n",query);
		    handle_size(nc, hm); // use the controller function
		}else{
			mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
		}
	}

}


int main(void) {
	struct mg_mgr mgr; // manager
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);

	printf("Starting web server on port %s\n", s_http_port);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL) {
		printf("Failed to create listener\n"); // the port may be busy
		return 1;
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory, no used in this case
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}

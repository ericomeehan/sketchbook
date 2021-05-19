//
//  client.c
//  sketch
//
//  Created by Eric Meehan on 5/13/21.
//

#include "mongoose.h"

static const char *s_listening_address = "tcp://0.0.0.0:1234/test";

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    printf("%d\n", ev);
    if (ev == MG_EV_CONNECT) {
        mg_send(c, "hello world", 12);
    }
}

int main(int argc, char *argv[]) {
    struct mg_mgr mgr;
    int done = 0;
    mg_mgr_init(&mgr);
    mg_connect(&mgr, s_listening_address, cb, &done);
    for (;;) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return 0;
}

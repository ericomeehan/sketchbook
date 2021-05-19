//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "mongoose.h"

static const char *s_listening_address = "tcp://0.0.0.0:1234/";

static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev != MG_EV_POLL)
    {
        printf("%d\n", ev);
    }
    if (ev == MG_EV_READ)
    {
        mg_send(c, "hello yourself", 15);
    }
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  mg_listen(&mgr, s_listening_address, cb, &mgr);
  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr);
  return 0;
}

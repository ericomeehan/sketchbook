//
//  main.c
//  sketch
//
//  Created by Eric Meehan on 3/24/21.
//

#include "../../libeom/libeom.h"

#include "ExampleStructure.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <time.h>

struct DataGram
{
    int x;
    char y;
};


void * server_function(void *arg)
{
    printf("Server running.\n");
    struct PeerToPeer *p2p = (struct PeerToPeer *)arg;
    struct sockaddr *address = (struct sockaddr *)&p2p->server.address;
    socklen_t address_length = (socklen_t)sizeof(p2p->server.address);
    while (1)
    {
        int client = accept(p2p->server.socket, address, &address_length);
        void *data = malloc(1000);
        read(client, data, 1000);
        struct ExampleStructure ex = decode_ex(data);
        char *client_address = inet_ntoa(p2p->server.address.sin_addr);
        printf("\t\t\t%s says: %lu, %lu, %s.\n", client_address, ex.nonce, ex.size, ex.data);
        

//        if (strcmp(request, "/known_hosts\n") == 0)
//        {
//            struct ServerRoute *route = p2p->server.routes.search(&p2p->server.routes, request, sizeof(request));
//            char *response = route->route_function(arg);
//            write(client, response, sizeof(char[strlen(response)]));
//            close(client);
//        }
//        else
//        {
//
//            printf("\t\t\t%s says: %s\n", client_address, request);
//            close(client);
//        }
        short found = 0;
        for (int i = 0; i < p2p->known_hosts.length && !found; i++)
        {
            if (strcmp(client_address, p2p->known_hosts.retrieve(&p2p->known_hosts, i)) == 0)
            {
                found = 1;
            }
        }
        if (!found)
        {
            p2p->known_hosts.insert(&p2p->known_hosts, p2p->known_hosts.length, client_address, sizeof(client_address));
        }
    }
    return NULL;
}

void * client_function(void *arg)
{
    struct PeerToPeer *p2p = arg;
    
// MARK: TEST SITE
    
    struct DataGram dg;
    dg.x = 5;
    dg.y = 'c';
    
    struct ExampleStructure ex;
    for (int i = 0; i < 64; i++)
    {
        ex.i[i] = i;
        ex.previous_hash[i] = 63 - i;
    }
    ex.nonce = 1234;
    char *test = "eric meehan";
    ex.data = test;
    ex.size = sizeof(char[strlen(test)]);
    
    
    while (1)
    {
        clock_t start = clock();
        struct Client client = client_constructor(p2p->domain, p2p->service, p2p->protocol, p2p->port, p2p->interface);
        char request[255];
        memset(request, 0, 255);
        fgets(request, 255, stdin);
        for (int i = 0; i < p2p->known_hosts.length; i++)
        {
            printf("%s\n", client.request(&client, p2p->known_hosts.retrieve(&p2p->known_hosts, i), &ex, sizeof(ex)));
        }
        clock_t end = clock();
        if ((end - start) > 500)
        {
            char *response = client.request(&client, p2p->known_hosts.retrieve(&p2p->known_hosts, 0), "/known_hosts\n", 14);
            printf("%s\n", response);
        }
    }
}

int int_compare(void *a, void *b)
{
    int *x = a;
    int *y = b;
    if (*x > *y)
    {
        return 1;
    }
    else if (*x < *y)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    struct PeerToPeer p2p = peer_to_peer_constructor(AF_INET, SOCK_STREAM, 0, 1248, INADDR_ANY, server_function, client_function);
    p2p.user_portal(&p2p);
    
}

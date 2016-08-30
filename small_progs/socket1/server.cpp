
void server()
{
    signal(SIGINT, sig_int_handler);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("socket failed\n");
        return false;
    }

    int enable = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) != 0)
    {
        printf("setsockopt failed\n");
        close(sockfd);
        return false;
    }

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr_in)) != 0)
    {
        printf("bind failed: %s\r\n", strerror(errno));
        close(sockfd);
        return false;
    }



}


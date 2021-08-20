#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>/* IPPROT_TCP */
#include<sys/socket.h>
#include<stdlib.h> /* atoi() exit()*/
#include<errno.h> /* */
#include<string.h> /* strerror() */

struct message{
    char* ssid;
    char* password;
}__attribute__((packed));;

void die_with_message(int);

int main(int argc, char** argv){
    if(argc > 5 || argc < 5){
        fprintf(stdout,"Error: Invalid arguments.\n");
        fprintf(stdout,"<IP> <PORT> <SSID> <PASSWORD>\n");
        return -1;
    }
    int client_file_handler;
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    /* Initialize */
    server_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr) == -1)
        die_with_message(1);
    server_addr.sin_port = htons(atoi(argv[2]));
    
    if((client_file_handler = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
        die_with_message(2);
    while(connect(client_file_handler, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1);
    const int msg_len = strlen(argv[3])+strlen(argv[4]);
    char* message = strcat(argv[3], argv[4]);
    fprintf(stdout, "%s\n", message);
    
    //fprintf(stdout, "%s\n", net_para.ssid);
    //fprintf(stdout, "%s\n", net_para.password);
    send(client_file_handler,message,strlen(message),0);
    fprintf(stdout, "Sent...\n");
    close(client_file_handler);
    return 0;
}
void die_with_message(int err_seq){
    fprintf(stderr, "%d==>%s\n", err_seq,strerror(errno));
    exit(EXIT_FAILURE);  
}

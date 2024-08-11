#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){

    int lfd = socket(AF_INET,SOCK_STREAM,0);
    if(lfd == -1){
        perror("socket");
        return -1;
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(10000);

    int ret = bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        return -1;
    }

    ret = listen(lfd, 128);
    if(ret == -1){
        perror("listen");
        return -1;
    }

    int maxfd = lfd;

    fd_set rdset;
    fd_set rdtemp;
    FD_ZERO(&rdset);
    FD_SET(lfd,&rdset);


    while(1){

        rdtemp = rdset;
        int num = select(maxfd+1, &rdtemp, NULL, NULL, NULL);

        if((FD_ISSET(lfd, &rdtemp))){
            struct sockaddr_in caddr;
            socklen_t len = sizeof(caddr);

            int cfd = accept(lfd, (struct sockaddr*)&caddr, &len);
            
            FD_SET(cfd, &rdset);

            maxfd = cfd > maxfd? cfd : maxfd;



            for(int i = 0;i<maxfd+1;++i){
                //判断监听描述符之后到maxfd这个范围是否存在读缓冲区
                if(i != lfd && FD_ISSET(i, &rdtemp)){

                    char buf[10] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if(len > 0){
                    printf("client says:%s\n",buf);
                    write(cfd, buf, strlen(buf)+1);
                    memset(buf, 0 ,sizeof(buf));
                    }
                    else if(len == 0){
                        printf("client disconnected\n");
                        break;
                    }
                    else if(len < 0){
                        perror("read");
                        break;
                    }

                }
            }
        }
    }


            //开始通信
        //     while(1){
        //         int len = read(cfd, buff ,sizeof(buff));
        //         if(len > 0){
        //             printf("client says:%s\n",buff);
        //             write(cfd, buff, sizeof(len));
        //             memset(buff, 0 ,sizeof(buff));
        //         }
        //         else if(len == 0){
        //             printf("client disconnected\n");
        //             break;
        //         }
        //         else if(len < 0){
        //             perror("read");
        //             break;
        //         }
        //     }
        // }

    return 0;
}
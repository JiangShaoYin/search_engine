#include <func.h>
#define N 1024
int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    struct hostent *h = gethostbyname(argv[1]);
    if(h == NULL){
        herror("gethostbyname");
        return -1;
    }

    printf("the host name = %s\n",h->h_name);
    for(int i = 0; h->h_aliases[i]!=NULL; i++){
        printf("\t aliases name = %s\n", h->h_aliases[i]);
    }
    printf("the addrtype = %d\n",h->h_addrtype);
    printf("the length = %d\n",h->h_length);
    for(int i = 0; h->h_addr_list[i]!= NULL; i++){
        char buf[N]= {0};
        inet_ntop(h->h_addrtype,h->h_addr_list[i],buf,N);
        printf("\t addrlist: %s\n",buf);
    }
    return 0;
}


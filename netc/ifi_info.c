#include "unp.h"

#define IFI_NAME 16
#define IFI_HADDR 8

struct ifi_info{
	char ifi_name[IFI_NAME];
	u_char ifi_haddr[IFI_HADDR];
	u_short ifi_hlen;
	short ifi_flags;
	short ifi_myflags;
	struct sockaddr *ifi_addr;
	struct sockaddr *ifi_brdaddr;
	struct sockaddr *ifi_dstaddr;
	struct ifi_info *ifi_next;
}

void free_ifi_info(struct ifi_info *ifihead){
	struct ifi_info *ifi,*ifinext;
	
	for(ifi= ifihead;ifi!= NULL;ifi= ifinext){
		if(ifi->ifi_addr != NULL)
			free(ifi->ifi_addr);
		if(ifi->ifi_brdaddr != NULL)
			free(ifi->ifi_brdaddr);
		if(ifi->ifi_dstaddr != NULL)
			free(ifi->ifi_dstaddr);
		ifinext = ifi->ifi_next;
		free(ifi);
	}
}



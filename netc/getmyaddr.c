#include "unp.h"
#include <sys/utsname.h>

char** my_addr(int *addrtype) {
	struct hostent *ht = NULL;
	struct utsname myname;

	if(uname(&myname) == NULL)
		return (NULL);
	if((ht = gethostbyname(myname.nodename)) == NULL)
		return (NULL);
	*addrtype = ht->addrtype;
	return ht->h_addr_list;
}

int blue_how_to_communicate(){
	 struct sockaddr_rc addr = {0};
	 int blue_socket, status;
	 bdaddr_t src;
	 bdaddr_t dst;
//	 uint8_t channel = 0;

	 str2ba("34:29:A6:C8:A6:84", &src);
	 str2ba("00:1B:35:88:0C:81", &dst);

	 if((blue_socket = socket(PF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0){
		 return -1;
	 }

	 addr.rc_family = AF_BLUETOOTH;
	 bacpy(&addr.rc_bdaddr, &src);
	 addr.rc_channel = 0;

	 printf("blue_socket: %d\n", blue_socket);

	 if((status = bind(blue_socket, (struct sockaddr *) &addr, sizeof(addr))) < 0){
		 printf("Bind not\n");
		 close(blue_socket);
		 return -1;
	 }else{
		 perror("oh yes");

		    printf("Oh dear, something went right with read()! %s\n", strerror(errno));
		    printf("bind yes, %d\n", status);
	 }



	 addr.rc_family = AF_BLUETOOTH;
	 bacpy(&addr.rc_bdaddr, &dst); // dst
	 addr.rc_channel = 0;
	 if((status = connect(blue_socket, (struct sockaddr *) &addr, sizeof(addr))) < 0){
		 printf("connect not %d\n", status);
		 perror("oh oh");
		 close(blue_socket);
		 printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
		 return -1;
	 }else{
		 printf("connect yes\n");
	 }
	return blue_socket;


}

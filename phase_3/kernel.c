void main(){
	int line = 5;
	char str[14] = "Hello World\n";
	
	char* start = (char*)(0xB8000 + line * 160);
	for(int i=0;str[i] != '\0'; ++i){
		*start++ = str[i];
		*start++ = 0x08;
	}
	return;
}

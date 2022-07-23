char get_position_in_long(char i) {
  return i * 8;
}

unsigned char compare_strings(char* string_one, char* string_two) {
  while(*string_one != '\0' && *string_two != '\0') {
    if (*string_one != *string_two) {
	return 0x00;
    }
    *string_one++;
    *string_two++;
  }
  if (*string_one == '\0' && *string_two == '\0') {
    return 0x01;
  }
  return 0x00;
}

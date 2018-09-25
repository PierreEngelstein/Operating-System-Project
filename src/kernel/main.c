void write_str(const char *string)
{
  char *video  =(char*) 0xb8000;
  string++;
  while(*string != 0)
  {
    *video = *string;
    video++;
    string++;
    *video++ = 0x0f;
    video++;
  }
}

int main()
{
  int i;
  char *video = (char*) 0xb8000;
  for(i = 0; i <= 80*25*2; i += 2)
  {
    *video = ' ';
    video++;
    *video = 0x0f;
    video++;
  }
  char *str = "hello";
  write_str(str);
  while(1){};
  return 1;
}

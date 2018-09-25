void write_str(const char *string)
{
    char *video  =(char*) 0xb8000;
    while(*string != 0)
    {
        *video = *string;
        video++;
        string++;
        *video++ = 0x0f;
    }
}

int main()
{
    int i;
    char *video = (char*) 0xb8000;
    char *str = "hellosdklfuhsdklfuhwdlkjflkugh";
    write_str(str);
    while(1){};
    return 1;
}

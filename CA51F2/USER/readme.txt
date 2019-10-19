#define KEY_MODE 0x01 //IO对应按键


void Key_Read(void)
{
    unsigned char ReadData = P0^0xff;
    Tig = ReadData & (ReadData ^ Cont);
    Cont = ReadData;
}

if(Tig & KEY_MODE )
{
    短按程序
}
if(Cont & KEY_MODE )
{
    cnt_plus++;
    if(cnt_plus > 100)
    {
        长按程序
    }

}
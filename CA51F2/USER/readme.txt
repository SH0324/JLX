#define KEY_MODE 0x01 //IO��Ӧ����


void Key_Read(void)
{
    unsigned char ReadData = P0^0xff;
    Tig = ReadData & (ReadData ^ Cont);
    Cont = ReadData;
}

if(Tig & KEY_MODE )
{
    �̰�����
}
if(Cont & KEY_MODE )
{
    cnt_plus++;
    if(cnt_plus > 100)
    {
        ��������
    }

}
inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
һ̤��������ʱ����һ�ֹ���ĸо�������� 
һ���޴�Բ�ε�ͼ������ϸһ��������һ������ͼ��Բ����
�����岼�������ǵ㣬��������Ϥ�������ʮ�������⣬��
�����������Ȼһ��������ʶ�����ɵÿ����㺹��䤱���

LONG    );

        set("exits", ([
               "up" : "d/jingyan/migong2",
                          ]));
              set("no_stab", 1); 
        setup();
        replace_program(ROOM);
}

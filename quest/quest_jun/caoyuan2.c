inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "���ԭ");
        set("long",
"��������ɹŴ��ԭ�ˣ��ɹž�Ӫ���ڲ�Զ���ˣ����ƺ����������ɹ�
���ӵ����������㲻�������˽Ų����������δ�������٣���ͼ͵͵�ӽ���
�ž��ľ�Ӫ��\n"
);    
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "west"  : __DIR__"caoyuan1",
                "east"  : __DIR__"caoyuan3",
        ]));

        setup();
} 


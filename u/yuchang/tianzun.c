#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY "����ʥ��" NOR);
        set("long", HIY "\n\n"
"������ش����ţ����˽�����һ���տ��Ĵ���ӳ���������\n"
"������ؾ��Ǵ�˵�е�����ʥ���ˡ��������ĵذ��̨�׾�\n"
"ȫΪ�׽����������еƻ�Իͣ����ȵ���Ϣ��ʹ����͸������\n"
"�������Դ��ŵ�һ���������ߵĸ�̨�Ͽ��š�����ʥ��ĸ�\n"
"���֣���̨���ķ�����ӵ����һλ��ʮ�����ҵ�����߸߶�����\n\n" NOR
);

        set("exits", ([
                "down" : "/d/city/guangchang",
                "enter" : "/u/yuchang/workroom",
                "west" : "/d/wizard/guest_room",
                "east" : "/d/city/kedian",
        ]));

        set("valid_startroom", 1);

        setup();
               "/clone/board/yuchang_b"->foo(); 
}


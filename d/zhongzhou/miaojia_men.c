#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��Ҵ���");
	set("long",
"����һ����Ϊ�޴��լԺ���������Ǹ��˵ľ�������ǰ��
������ʯʨ���������ϡ���������������ſ��ң�����д����

          " YEL "����������������������������������
          ��                              ��
          ��  " HIR "��  ��  ��  ��  ��  ��  ��" NOR YEL "  ��
          ��                              ��
          ����������������������������������" NOR "

�߸������֡����������Ѿ����Ž����ˡ�\n");

	set("exits", ([
  		//"east"  : __DIR__"miaojia_dayuan",
  		"west"  : __DIR__"wendingbei4",
	]));

	set("no_clean_up", 0);
	/*set("objects", ([
                CLASS_D("miao") + "/wen" : 1,
	]));*/

	setup();
}

//int valid_leave(object me, string dir)
//{
//        object wen;
//
//        if (dir != "east" ||
//            ! objectp(wen = present("zhong zhaowen", this_object())))
//                return ::valid_leave(me, dir);
//
//        return wen->permit_pass(me, dir);
//}
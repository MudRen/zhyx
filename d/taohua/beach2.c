// Code of ShenZhou
//Chaos, Ryu, 3/10/97
#include <ansi.h>
inherit SHEGU_ROOM;

string long_desc();

void create()
{
	set("short", "����");

        set("long", (: long_desc :));

	set("exits", ([
                "north" : __DIR__"beach",
        ]));
	 
	set("objects", ([
                __DIR__"obj/shizi" : 3,
        ]));
	
	set("cost", 2);
	set("outdoors", "taohua");

	setup();
}

void init()
{
        add_action("do_lingwu", "lingwu");
}

string long_desc()
{
        string desc;

        desc  = "����һƬ���׵�ɳ̲������ȥ���������ɳ���ĵ��죬��������˵������������Ŀ�������\n";

	if (NATURE_D->outdoor_room_event() == "event_dawn" ||
            NATURE_D->outdoor_room_event() == "event_evening")
        {
               desc += HIG "ԶԶ��ȥ�󺣺��������޲�������һ�ߴ�һ�����߹����������������죬�Ժ�\n" NOR;
               desc += HIG "������ӿ��������ɽ�����֮������̨�£����κ��˺ݺݴ���̨���ϡ����ʱ�о�\n" NOR;
	       desc += HIG "���㲻�ȣ�ҡҡ��׹���������ϱ�ɫ��Ϊ�����֮�����������\n" NOR;

        }
        else {
                desc += HIC "��Ǹ�Զ������������һ�̣������޲��������ǡ�����ƾ��Ծ�����\n" NOR;
		    desc += HIC "����ɡ������˾���������һ������ֻ���ظ�֮��������ӯ����Ʈ\n" NOR;
                desc += HIC "Ʈ���ƺ���Ҫ�˷��ȥ��\n" NOR;

        }

        return desc;
}

int do_lingwu()   
{
	object me = this_player();
        int level, check;

        if ((int)me->query_skill("bibo-shengong",1) < 30)
                return notify_fail("��ı̲��񹦻�û�����أ����������������̲�������Ҳ�á�\n");

        if ((int)me->query_skill("bibo-shengong",1) > 99)
                return notify_fail("����ź�嫵Ĵ󺣣�ͦ�������������泩��\n");

        if (me->query("jing") < 30)
                return notify_fail("��ľ���̫���ˡ�\n");

        if ( me->can_improve_skill("bibo-shengong") ) 
        {
                me->receive_damage("jing", 40);
                me->improve_skill("bibo-shengong", me->query("int")/3);
                write("���ھ��κ�����������̲������а���!\n");
        }
        else 
        {
                write("��ʵս���鲻�㣬�޷�����̲��񹦡�\n");
        }
        return 1;
} 
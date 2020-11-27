// damen.c
// Modified by Winder June.25 2000
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ʯ�Ҵ���");
        set("long", @LONG
�����Ҷ���ͻȻ֮�䣬������һ���������Բ�ԭ���Ǹ��Ż���
�Ż��ĺ�������һ��ͭ�����ɵĴ���(men)��ʮ�ֳ��ء���ʹ�Ǳ�����
�õ��ˣ�����Ҳ������Ϊ������
LONG );
	set("exits", ([
		"south" : __DIR__"yandong",
	]));
	set("item_desc", ([
		"men"  : "һ��ͭ�����ɵĴ��ţ����������ж��ء�\n�����������������(break)һ�¿�����\n",
	]));
	set("no_clean_up", 0);
	set("coor/x", -50020);
	set("coor/y", -21050);
	set("coor/z", -40);
	setup();
//	replace_program(ROOM);
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object *ob, me = this_player();
        int i;

        if (arg != "men")
		return notify_fail("���ڸ���? \n");

	if (me->query("neili") < 5000)
	{
		write("�����������������Լ����ڵ��������á�\n");
		return 1;
	}

	me->add("neili", -2000);
        if (me->query_skill("force", 1) < 300)
        {
                message_vision(CYN "$N" CYN "ѽѽ�ٺٷ��˰������������"
		   	       "ûʲô������\n", me);
		tell_object(me, "�������Լ����ڹ���򻹲�����\n");
                return 1;
        }

        message_vision(CYN "ͭ��������$N" CYN "һ��֮���������죬�����ƿ���\n" NOR,
		       me);

        set("exits/north",__DIR__"shishi2");
        me->add("neili", -500);
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close(object room)
{
        message("vision", "ͭ�����������������죬�������ϡ�\n"NOR, room);
        room->delete("exits/north");
}
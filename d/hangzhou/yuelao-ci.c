// Room: /yuelaoci.c
#define QIUQIAN __DIR__"qiuqian"

#include <ansi.h> 

#include <room.h>
inherit ROOM;
int is_chat_room() { return 1;}
void create(){
	set("short", "������");
	set("long", @LONG
�����������ƹ���Ե�����ˣ���˵���к��ߣ�������ϵ����Ů�󷽵Ľ�
�ϣ�����˻����ǧ��ջ�����Ե��������һ��СԺ���������ݡ�������
��������������������ˣ����ñ�����磬�׷�ͯ�գ�Ц�����档����ǰ����
���ǹ�������¯����̨��ǩͲ����Ȼ������Ҳ���ٲ��˵ġ�����һ�������С
������Ը���������ˣ������˾�������ǰ��ע���£�Ī�����Ե�������İ���
�����������������ǩ��qiuqian����һ����Ե���£��ſ������˽�ǩ��������
LONG );
	set("no_fight", "1");
	set("no_steal", "1");
	set("no_sleep_room","1");
    
	set("exits", ([
		"south" : __DIR__"yuanyuan-tai",
        
        ]));
    setup();
}
void init()
{
	add_action("do_qiuqian","qiuqian");
}

int do_qiuqian(string arg)
{ 
	    object me;
	     
        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if (time() - me->query("last_qiuqian_time") < 600)
                return notify_fail("��ôƵ������ǩ����Ĳ�����ǩ���飬��ʮ���������ɡ�\n");

        write(HIC "
���ϵ�����������˼��ݣ����������дʣ����������ϣ��͸��Һ���Ե�ɣ���
�����������֧ǩ��������һ�ᣬ��������۾���ǩ�ġ�\n
" NOR, me);
        write(HIC "ǩ��д�ţ�" + QIUQIAN->query_qiuqian() + "��\n" NOR, me);
        me->set("last_qiuqian_time",time());
        return 1;
}



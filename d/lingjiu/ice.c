//ROOM ice.c

#include <ansi.h>




inherit ROOM;

void init();

int do_xia(object me);

        
void create()
{
        set("short","����");
        set("long",@LONG
����һ�������ɽ֮�۵�ǧ������,��˵������������°빦����
LONG );
        
        
        set("item_desc", ([
            "ice" : "����һ�������ɽ֮�۵�ǧ������,��˵������������°빦��.\n�����������(climb)��ȥ.\n",
        ]));
        set("no_clean_up", 0);
        setup();
}


void init()
{
        add_action("do_xia", "xia");
        
        
}

int do_xia(object me)
{
        
        me=this_player();
        
        if(!me->query_temp("ice"))
        return notify_fail("����û�����������µ���ȥѽ����\n");
        
        message_vision("$N���깦��������������µ�����\n",me);
        me->set_temp("ice", 0);

        me->move("d/lingjiu/xuanbing");
        return 1;
}


